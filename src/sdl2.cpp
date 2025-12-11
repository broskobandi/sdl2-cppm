module;

#include <SDL2/SDL.h>

module sdl2;


import std;

#define ERR(msg)\
	std::runtime_error(std::string(msg) + std::string(SDL_GetError()))

std::string get_error() {
	return SDL_GetError();
}

using namespace sdl2;

auto Timer::ticks() const {
	return SDL_GetTicks();
}
