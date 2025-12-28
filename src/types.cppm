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

/** @file timer.cppm 
 * @brief Module partition interface file for the types module in the sdl2-cppm library.
 * @details This file contains POD structs and template operator overloads for enum classes. */
module;

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_pixels.h>

export module sdl2:types;
import std;

namespace sdl2 {

export using std::int32_t;
export using std::uint32_t;
export using std::uint8_t;
using std::underlying_type_t;

export struct Dimensions {
	uint32_t w, h;
};

export struct Rect {
	int32_t x, y;
	uint32_t w, h;
	friend class Point;
	private:
		friend class Renderer;
		SDL_Rect to_sdl() const;
	public:
		bool has_intersection(const Rect& rect) const;
};

export struct Point {
	int32_t x, y;
	private:
		friend class Renderer;
		SDL_Point to_sdl() const;
	public:
		bool has_intersection(const Rect& rect) const;
};


export struct Color {
	uint8_t r, g, b, a;
	private:
		friend class Renderer;
		SDL_Color to_sdl() const;
};

export template<typename T>
concept EnumClass = std::is_scoped_enum_v<T>;

export template<EnumClass E>
constexpr underlying_type_t<E> operator+(const E& e) noexcept {
	return underlying_type_t<E>(e);
}

export template<EnumClass E>
constexpr E operator|(const E& e1, const E& e2) noexcept {
	return static_cast<E>(+e1 | +e2);
}

export template<EnumClass E>
constexpr E operator|=(E& e1, const E& e2) noexcept {
	return e1 = e1 | e2;
}

}
