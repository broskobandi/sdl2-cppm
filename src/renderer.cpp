module;

#include <SDL2/SDL_render.h>

module sdl2;
import :renderer;
import :debug;

namespace sdl2 {

Renderer::Renderer(SDL_Renderer* ren, shared_ptr<const Window> win) :
	ren(ren), win(win)
{
	dbg("Renderer created.");
}

Renderer::~Renderer() {
	if (ren) {
		SDL_DestroyRenderer(ren);
		dbg("Renderer destroyed.");
	}
}

Renderer::Renderer(Renderer&& other) noexcept :
	ren(other.ren), win(other.win)
{
	other.ren = nullptr;
}

Renderer& Renderer::operator=(Renderer&& other) noexcept {
	if (this != &other) {
		if (this->ren) SDL_DestroyRenderer(this->ren);
		this->ren = other.ren;
		this->win = other.win;
		other.ren = nullptr;
	}
	return *this;
}

}
