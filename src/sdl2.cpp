module;

#include <SDL2/SDL.h>

module sdl2;
import :debug;

namespace sdl2 {

Sdl::Sdl(Flags flags) {
	if (SDL_WasInit(0)) throw err("SDL cannot be initialized twice.");
	if (SDL_Init(static_cast<Uint32>(flags)))
		throw err("Failed to initialize SDL.");
	dbg("SDL initialized.");
}

shared_ptr<Sdl> Sdl::init(Flags flags) {
	return shared_ptr<Sdl>(new Sdl(flags));
}

Sdl::~Sdl() {
	SDL_Quit();
	dbg("SDL terminated.");
}

shared_ptr<Window> Sdl::window(
	const string& title,
	Dimensions dimensions,
	Window::Flags flags
) const {
	auto win = SDL_CreateWindow(title.c_str(), 0, 0,
		static_cast<int>(dimensions.w),
		static_cast<int>(dimensions.w),
		static_cast<Uint32>(flags));
	if (!win) throw err("Failed to create window.");
	return shared_ptr<Window>(new Window(win, shared_from_this()));
}

}
