#!/bin/bash

if [ $# -ne 2 ]; then
    echo "Usage: $0 <library> <process id>"
    exit 1
fi

LIBRARY_FILE="$1"
PROCESS_ID="$2"

# Check that the library file exists
if [ ! -f "$LIBRARY_FILE" ]; then
    echo "File $LIBRARY_FILE does not exist"
    exit 1
fi

# Check that the supplied PID is valid
kill -0 $PROCESS_ID > /dev/null 2>&1
if [ $? -ne 0 ]; then
    echo "Invalid PID"
    exit 1
fi

LIBRARY_FILE="$(realpath "$LIBRARY_FILE")"

# Check that the library file is loaded
if [ -z "$(cat /proc/$PROCESS_ID/maps | grep "$LIBRARY_FILE")" ]; then
    echo "Library could not be found in /proc/$PROCESS_ID/maps"
    exit 1
fi

echo -e "\033[1mShared library: $LIBRARY_FILE\033[0m"
echo -e "\033[1mProcess: $PROCESS_ID - $(realpath /proc/$PROCESS_ID/exe)\033[0m"

echo -e "\033[1mRunning GDB\033[0m"

# void* handle = dlopen(LIBRARY_FILE, RTLD_LAZY | RTLD_NOLOAD)
# dlerror()
# dlclose(handle)
# dlclose(handle)
gdb -batch                                                                              \
    -ex "attach $PROCESS_ID"                                                            \
    -ex "echo \033[1mCalling dlopen\033[0m\n"                                           \
    -ex "set \$handle = ((void*(*)(const char*, int))dlopen)(\"$LIBRARY_FILE\", 5)"     \
    -ex "echo \033[1mCalling dlerror\033[0m\n"                                          \
    -ex "call ((char*(*)(void))dlerror)()"                                              \
    -ex "echo \033[1mCalling dlclose (x2)\033[0m\n"                                     \
    -ex "call ((void(*)(void*))dlclose)(\$handle)"                                      \
    -ex "call ((void(*)(void*))dlclose)(\$handle)"                                      \
    -ex "detach"                                                                        \
    -ex "quit"
