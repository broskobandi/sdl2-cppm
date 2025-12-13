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

/** @file surface.cppm 
 * @brief Module partition interface file for the surface module in the sdl2-cppm library.
 * @details This file contains the Surface class. */
module;

#include <SDL2/SDL_surface.h>

export module sdl2:surface;
import std;

using std::filesystem::path;

namespace sdl2 {

/** The surface class can be used, for example, to store pixel data loaded from a 
 * bmp file that can be used to create Texture-s. Does not need an active SDL session.
 * This class is move only. */
export class Surface {
	private:
		SDL_Surface* sur;
		friend class Renderer;
	public:
		Surface(const path& path_to_bmp);
		Surface(Surface&&) noexcept;
		Surface& operator=(Surface&&) noexcept;
		Surface(const Surface&) = delete;
		Surface& operator=(const Surface&) = delete;
		~Surface();

};

}
