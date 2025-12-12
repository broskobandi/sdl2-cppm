module;

#include <SDL2/SDL_rect.h>

module sdl2;
import :types;

namespace sdl2 {

auto Point::get_sdl() const {
	return SDL_Point {
		static_cast<int>(x),
		static_cast<int>(y),
	};
}

auto Rect::get_sdl() const {
	return SDL_Rect {
		static_cast<int>(x),
		static_cast<int>(y),
		static_cast<int>(w),
		static_cast<int>(h),
	};
}

}
