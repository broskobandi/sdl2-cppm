/*
MIT License

Copyright (c) 2025 broskobandi

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/** @file surface.cpp
 * @brief Module implementation for the surface module partition. */
module;
#include <SDL2/SDL_surface.h>
module sdl2;
import :surface;
import :debug;

using std::filesystem::path;

namespace sdl2 {

Surface::Surface(const path& path_to_bmp) {
	sur = SDL_LoadBMP(path_to_bmp.c_str());
	if (!sur) throw err("Failed to create surface from bmp.");
	dbg("Surface creatd from bmp.");
}

Surface::Surface(Surface&& other) noexcept : sur(other.sur) {
	other.sur = nullptr;
}

Surface& Surface::operator=(Surface&& other) noexcept {
	if (this != &other) {
		if (this->sur) SDL_FreeSurface(this->sur);
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
