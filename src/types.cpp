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

/** @file timer.cpp
 * @brief Module implementation for the types module partition. */
module;

#include <SDL2/SDL_rect.h>

module sdl2;
import :types;

namespace sdl2 {

SDL_Point Point::to_sdl() const {
	return SDL_Point {
		static_cast<int>(x),
		static_cast<int>(y),
	};
}

SDL_Rect Rect::to_sdl() const {
	return SDL_Rect {
		static_cast<int>(x),
		static_cast<int>(y),
		static_cast<int>(w),
		static_cast<int>(h),
	};
}

SDL_Color Color::to_sdl() const {
	return SDL_Color {
		static_cast<Uint8>(r),
		static_cast<Uint8>(g),
		static_cast<Uint8>(b),
		static_cast<Uint8>(a),
	};
}

}
