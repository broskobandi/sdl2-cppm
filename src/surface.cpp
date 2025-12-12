module;
#include <SDL2/SDL_surface.h>
module sdl2;
import :surface;
import :debug;

namespace sdl2 {

Surface::Surface(const path& path_to_bmp) {
	sur = SDL_LoadBMP(path_to_bmp.c_str());
	if (!sur) throw err("Failed to create surface from bmp.");
	dbg("Surface creatd from bmp.");
}

const SDL_Surface* Surface::get() const {
	return sur;
}


Surface::Surface(Surface&& other) noexcept : sur(other.sur) {
	other.sur = nullptr;
}

Surface& Surface::operator=(Surface&& other) noexcept {
	if (this != &other) {
		this->sur = other.sur;
		other.sur = nullptr;
	}
	return *this;
}

Surface::~Surface() {
	if (sur) {
		SDL_FreeSurface(sur);
		dbg("Surface freed.");
	}
}

}
