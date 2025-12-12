module;

#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>

module sdl2;
import :window;
import :debug;

namespace sdl2 {

Window::Window(
	SDL_Window* win,
	shared_ptr<const Sdl> sdl
) :
	win(win), sdl(sdl)
{
	dbg("Window created.");
}

Window::~Window() {
	if (win) {
		SDL_DestroyWindow(win);
		dbg("Window destroyed.");
	}
}

Renderer Window::renderer(Renderer::Flags flags) const {
	auto ren = SDL_CreateRenderer(win, -1, static_cast<Uint32>(flags));
	if (!ren) throw err("Failed to create renderer.");
	return Renderer(ren, shared_from_this());
}


}
