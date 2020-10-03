#pragma once

namespace mem {

	/* Hook a function by replacing its entry in the */
	/* SDL jump table.                               */
	template <typename Fn>
	class SDLHook {
	public:
		SDLHook(Fn* table_entry)
			: hooked(false), table_entry(table_entry),
			  func_original(*table_entry) {}

		~SDLHook() {
			if (hooked) {
				remove();
			}
		}

		inline void apply(Fn func_user) {
			*table_entry = func_user;
			hooked = true;
		}

		inline Fn get_original() {
			return func_original;
		}

		inline void remove() {
			*table_entry = func_original;
			hooked = false;
		}
	private:
		bool hooked;
		Fn* table_entry;
		Fn  func_original;
	};

}

