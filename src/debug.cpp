module;

#include <SDL2/SDL_error.h>

module sdl2;
import :debug;

using std::println;

namespace sdl2 {

void dbg(const string& msg) {
	if (g_debug) println("{}", msg);
}

runtime_error err(const string& msg) {
	return runtime_error(msg + get_error());
}

string get_error() {
	return string(SDL_GetError());
}

}
