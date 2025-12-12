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
