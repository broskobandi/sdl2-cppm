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

/** @file texture.cpp
 * @brief Module implementation for the texture module partition. */
module;

#include <SDL2/SDL_render.h>

module sdl2;
import :texture;
import :debug;

namespace sdl2 {

/** Private constructor. Renderer::texture() calls this. */
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
