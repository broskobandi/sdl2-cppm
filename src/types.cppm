module;

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_pixels.h>

export module sdl2:types;
import std;

namespace sdl2 {

export using std::int32_t;
export using std::uint32_t;
using std::underlying_type_t;

export struct Point {
	int32_t x, y;
	private:
		friend class Renderer;
		auto get_sdl() const;
};

export struct Dimensions {
	uint32_t w, h;
};

export struct Rect {
	int32_t x, y;
	uint32_t w, h;
	private:
		friend class Renderer;
		auto get_sdl() const;
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
