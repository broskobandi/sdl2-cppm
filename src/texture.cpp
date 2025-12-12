module;

#include <SDL2/SDL_render.h>

module sdl2;
import :texture;
import :debug;

namespace sdl2 {

Texture::Texture(SDL_Texture* tex) : tex(tex) {
	dbg("Texture created.");
}

Texture::Texture(Texture&& other) noexcept :
	tex(other.tex)
{
	other.tex = nullptr;
}

Texture& Texture::operator=(Texture&& other) noexcept {
	if (this != &other) {
		if (this->tex) SDL_DestroyTexture(this->tex);
		this->tex = other.tex;
		other.tex = nullptr;
	}
	return *this;
}

Texture::~Texture() {
	if (tex) {
		SDL_DestroyTexture(tex);
		dbg("Texture destroyed.");
	}
}

}
