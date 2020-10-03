#include <stdio.h>

#include <Windows.h>
#include <TlHelp32.h>

#define INJ_INVALID_PID -1

/* Find the process ID from a name, returns INJ_INVALID_PID on failure */
static DWORD get_target_pid(const char* process_name) {
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (snapshot == INVALID_HANDLE_VALUE) {
		perror("Failed to create process snapshot");
		return INJ_INVALID_PID;
	}

	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(PROCESSENTRY32);

	DWORD pid = INJ_INVALID_PID;

	if (!Process32First(snapshot, &pe)) {
		perror("Failed to get info from process snapshot");
		return INJ_INVALID_PID;
	}

	do {
		if (strcmp(pe.szExeFile, process_name) == 0) {
			pid = pe.th32ProcessID;
			break;
		}
	} while (Process32Next(snapshot, &pe));

	CloseHandle(snapshot);
	return pid;
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		fprintf(stderr, "Usage: %s <dll path> <process name>\n", argv[0]);
		return EXIT_FAILURE;
	}

	/* Get game PID */
	DWORD game_pid = get_target_pid(argv[2]);
	if (game_pid == INJ_INVALID_PID) {
		perror("Failed to find game PID");
		return EXIT_FAILURE;
	}

	/* Get full dll path */
	char dll_path[MAX_PATH];
	if (GetFullPathName(argv[1], MAX_PATH, dll_path, NULL) == 0) {
		fprintf(stderr, "Failed to get full DLL path (%i)\n", GetLastError());
			return EXIT_FAILURE;
	}

	printf("Injecting %s into %s (pid = %ul)\n", dll_path, argv[2], game_pid);

	HANDLE proc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, game_pid);
	if (proc == NULL) {
		fprintf(stderr, "Failed to open game process (%i)\n", GetLastError());
		return EXIT_FAILURE;
	}

	HMODULE kern_handle = GetModuleHandle("kernel32.dll");
	if (kern_handle == NULL) {
		fprintf(stderr, "Failed to get handle to kernel32.dll (%i)\n", GetLastError());
		return EXIT_FAILURE;
	}

	LPVOID load_address = (LPVOID)GetProcAddress(kern_handle, "LoadLibraryA");
	if (load_address == NULL) {
		fprintf(stderr, "Failed to get address of LoadLibraryA (%i)\n", GetLastError());
		return EXIT_FAILURE;
	}

	/* Allocate space for DLL path */
	size_t dll_len = strlen(dll_path);
	LPVOID dll_path_address = VirtualAllocEx(proc, NULL, dll_len, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	if (dll_path_address == NULL) {
		fprintf(stderr, "Failed to allocate memory for dll path (%i)\n", GetLastError());
		return EXIT_FAILURE;
	}

	if (WriteProcessMemory(proc, dll_path_address, dll_path, dll_len, NULL) == 0) {
		fprintf(stderr, "Failed to write dll path (%i)\n", GetLastError());
		return EXIT_FAILURE;
	}

	printf("Wrote %zu bytes of DLL path to target memory\n", dll_len);

	/* Create thread at LoadLibrary with the DLL path as an arg */
	CreateRemoteThread(proc, NULL, 0, (LPTHREAD_START_ROUTINE)load_address, dll_path_address, 0, NULL);

	printf("Thread created. The DLL will now be loaded.\n");

	CloseHandle(proc);

	return EXIT_SUCCESS;
}