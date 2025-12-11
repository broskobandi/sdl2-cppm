module;

#include <SDL2/SDL.h>

export module sdl2;
import std;

using std::hash;
using std::uint32_t;
using std::int32_t;
using std::uint8_t;
using std::size_t;
using std::shared_ptr;
using std::runtime_error;
using std::string;
using std::is_scoped_enum_v;
using std::filesystem::path;
using std::println;
using std::optional;
using std::nullopt;
using std::enable_shared_from_this;
using std::string_view;

#include "enums.inc"

#define ERR(msg)\
	runtime_error(string(msg) + string(SDL_GetError()))

namespace sdl2 {

export template<typename T>
concept EnumClass = is_scoped_enum_v<T>;

export template<EnumClass E>
constexpr auto operator+(const E& e) {
	return std::underlying_type_t<E>(e);
}

export template<EnumClass E>
constexpr E operator|(const E& e1, const E& e2) {
	return static_cast<E>(+e1 | +e2);
}

export template<EnumClass E>
constexpr E& operator|=(E& e1, const E& e2) {
	return e1 = e1 | e2;
}

export template<EnumClass E>
constexpr bool operator&(const E& e1, const E& e2) {
	return (+e1 & +e2) == +e1;
}

string get_error() {
	return SDL_GetError();
}

export class Sdl;
export class Texture;
export class Surface;

namespace event {
export class Event;
}

namespace window {
export class Window;
}

namespace renderer {
export class Renderer;
}

export struct Point {
	int32_t x, y;
private:
	friend class renderer::Renderer;
	auto to_sdl_point() const {
		return SDL_Point{static_cast<int>(x), static_cast<int>(y)};
	}
};

export struct PointHash {
	size_t operator()(const Point& p) const {
		return hash<int32_t>{}(p.x) ^ (hash<int32_t>{}(p.y) << 1);
	}
};

export constexpr bool operator==(const Point& p1, const Point& p2) noexcept {
	return p1.x == p2.x && p1.y == p2.y;
}

export constexpr bool operator>(const Point& p1, const Point& p2) noexcept {
	if (p1.x == p2.x) {
		return p1.y > p2.y;
	} else {
		return p1.x > p2.x;
	}
}

export constexpr bool operator<(const Point& p1, const Point& p2) noexcept {
	if (p1.x == p2.x) {
		return p1.y < p2.y;
	} else {
		return p1.x < p2.x;
	}
}

export struct Dimensions {
	uint32_t w, h;
};

export struct Rect {
	int32_t x, y;
	uint32_t w, h;
	Rect(int32_t x, int32_t y, uint32_t w, uint32_t h) :
		x(x), y(y), w(w), h(h) {}
	Rect(Point position, Dimensions dimensions) :
		x(position.x), y(position.y), w(dimensions.w), h(dimensions.h) {}
private:
	friend class renderer::Renderer;
	auto to_sdl_rect() const {
		return SDL_Rect{x, y, static_cast<int>(w), static_cast<int>(h)};
	}
};

export struct Color {
	uint8_t r, g, b, a;
private:
	friend class renderer::Renderer;
	auto to_sdl_color() const {
		return SDL_Color{r, g, b, a};
	}
};

export class Timer {
private:
	friend class Sdl;
	const shared_ptr<const Sdl> sdl;
	Timer(const shared_ptr<const Sdl> sdl) : sdl(sdl) {}
public:
	uint32_t ticks() const {
		return SDL_GetTicks();
	}
};

namespace event {

// this should be a pod
export class MouseState {
private:
	Point position;
	bool left_button;
	bool right_button;
	bool middle_button;
	friend class Event;
	MouseState(
		Point pos,
		bool left,
		bool right,
		bool middle
	) :
		position(pos), left_button(left), right_button(right), middle_button(middle)
	{}
public:
	bool left() const {
		return left_button;
	}
	bool right() const {
		return right_button;
	}
	bool middle() const {
		return middle_button;
	}
	Point pos() const {
		return Point{position.x, position.y};
	}
};

export class Event {
private:
	friend class sdl2::Sdl;
	SDL_Event event;
	const shared_ptr<const Sdl> sdl;
	Event(const shared_ptr<const Sdl> sdl) : sdl(sdl) {}
public:
	int poll() {
		return SDL_PollEvent(&event);
	}
	bool has_type(Type type) const {
		SDL_EventType t = static_cast<SDL_EventType>(type);
		return event.type == t;
	}
	bool has_keycode(KeyCode keycode) const {
		SDL_KeyCode k = static_cast<SDL_KeyCode>(keycode);
		return event.key.keysym.sym == k;
	}
	bool has_scancode(ScanCode scancode) const {
		SDL_Scancode s = static_cast<SDL_Scancode>(scancode);
		return SDL_GetKeyboardState(nullptr)[s];
	}
	auto type() const {
		return static_cast<Type>(event.type);
	}
	auto keycode() const {
		return static_cast<KeyCode>(event.key.keysym.sym);
	}
	auto mouse_state() const {
		int x {0};
		int y {0};
		bool left {false};
		bool right {false};
		bool middle {false};
		auto ms = SDL_GetMouseState(&x, &y);
		if (ms & SDL_BUTTON(SDL_BUTTON_LEFT)) left = true;
		if (ms & SDL_BUTTON(SDL_BUTTON_MIDDLE)) middle = true;
		if (ms & SDL_BUTTON(SDL_BUTTON_RIGHT)) right = true;
		return MouseState(
			{static_cast<int32_t>(x), y},
			left, right, middle
		);
	}
};

}

export class Surface {
private:
	friend class renderer::Renderer;
	SDL_Surface* sur;
	const auto& get() const {
		return sur;
	}
	Surface(SDL_Surface* sur) : sur(sur) {}
public:
	Surface(const Surface&) = delete;
	Surface(Surface&&) = delete;
	Surface& operator=(const Surface&) = delete;
	Surface& operator=(Surface&&) = delete;
	static auto load_bmp(path path) {
		auto sur = SDL_LoadBMP(path.c_str());
		if (!sur) throw ERR("Failed to load bmp.");
		return Surface(sur);
	}
	~Surface() {
		if (sur) SDL_FreeSurface(sur);
	}
};

export class Texture {
private:
	friend class renderer::Renderer;
	SDL_Texture* tex;
	const auto& get() const {
		return tex;
	}
	Texture(SDL_Texture* tex) : tex(tex) {}
public:
	Texture(const Texture&) = delete;
	Texture& operator=(const Texture&) = delete;
	Texture(Texture&& other) : tex(other.tex) {
		other.tex = nullptr;
	}
	Texture& operator=(Texture&&) = delete;
	~Texture() {
		if (tex) {
			SDL_DestroyTexture(tex);
			println("texture destroyed.");
		}
	}
};

namespace renderer {

export class Renderer {
private:
	friend class window::Window;
	const shared_ptr<const window::Window> win;
	SDL_Renderer* ren;
	Renderer(const shared_ptr<const window::Window> win, SDL_Renderer* ren) :
		win(win), ren(ren) {}
public:
	Renderer(const Renderer&) = delete;
	Renderer(Renderer&&) = delete;
	Renderer& operator=(const Renderer&) = delete;
	Renderer& operator=(Renderer&&) = delete;
	auto texture(const Surface& sur) const {
		auto tex = SDL_CreateTextureFromSurface(ren, sur.get());
		if (!tex) throw ERR("Failed to create texture from surface.");
		return Texture(tex);
	}
	auto texture(path path_to_bmp) const {
		return texture(Surface::load_bmp(path_to_bmp));
	}
	void set_draw_color(Color color) const {
		auto c = color.to_sdl_color();
		if (SDL_SetRenderDrawColor(ren, c.r, c.g, c.b, c.a))
			throw ERR("Failed to set render draw color.");
	}
	void clear() const {
		if (SDL_RenderClear(ren))
			throw ERR("Failed to clear renderer.");
	}
	void clear(Color color) const {
		set_draw_color(color);
		clear();
	}
	void present() const {
		SDL_RenderPresent(ren);
	}
	void set_render_draw_blend_mode(BlendMode blendmode) {
		auto bm = static_cast<SDL_BlendMode>(blendmode);
		if (SDL_SetRenderDrawBlendMode(ren, bm))
			throw ERR("Failed to set render draw blend mode.");
	}
	void set_texture_blend_mode(const Texture& tex, BlendMode blendmode) const {
		auto bm = static_cast<SDL_BlendMode>(blendmode);
		if (SDL_SetTextureBlendMode(tex.get(), bm))
			throw ERR("Failed to set texture blend mode.");
	}
	void set_texture_alpha_mod(const Texture& tex, uint8_t alpha) const {
		if (SDL_SetTextureAlphaMod(tex.get(), alpha))
			throw ERR("Failed to set texture alpha mode.");
	}
	void set_texture_color_mod(const Texture& tex, Color color) const {
		if (SDL_SetTextureColorMod(tex.get(), color.r, color.g, color.b))
			throw ERR("Failed to set texture color mode.");
	}
	void fill_rect(optional<Rect> rect) const {
		SDL_Rect r = rect.value_or(Rect{0, 0, 0, 0}).to_sdl_rect();
		SDL_Rect *rptr = rect.has_value() ? &r : nullptr;
		if (SDL_RenderFillRect(ren, rptr))
			throw ERR("Failed to fill rect.");
	}
	void copy(
		const Texture& tex,
		optional<Rect> dstrect = nullopt,
		optional<Rect> srcrect = nullopt,
		float angle = 0.0f,
		optional<Point> center = nullopt,
		Flip flip = Flip::NONE
	) const {
		SDL_Rect src = srcrect.value_or(Rect{0, 0, 0, 0}).to_sdl_rect();
		SDL_Rect dst = dstrect.value_or(Rect{0, 0, 0, 0}).to_sdl_rect();
		SDL_Rect* srcptr = srcrect.has_value() ? &src : nullptr;
		SDL_Rect* dstptr = dstrect.has_value() ? &dst : nullptr;
		SDL_RendererFlip f = static_cast<SDL_RendererFlip>(flip);
		SDL_Point c = center.value_or(Point{0, 0}).to_sdl_point();
		SDL_Point* cptr = center.has_value() ? &c : nullptr;
		if (SDL_RenderCopyEx(ren, tex.get(), srcptr, dstptr, angle, cptr, f))
			throw ERR("Failed to render texture.");
	}
	~Renderer() {
		if (ren) SDL_DestroyRenderer(ren);
	}
};

}

namespace window {

export class Window : public enable_shared_from_this<Window> {
private:
	friend class sdl2::Sdl;
	const shared_ptr<const Sdl> sdl;
	SDL_Window* win;
	Window(const shared_ptr<const Sdl> sdl, SDL_Window* win) :
		sdl(sdl), win(win) {}
public:
	Window(const Window&) = delete;
	Window(Window&&) = delete;
	Window& operator=(const Window&) = delete;
	Window& operator=(Window&&) = delete;
	auto renderer(renderer::Flags flags) const {
		SDL_RendererFlags f = static_cast<SDL_RendererFlags>(flags);
		auto ren = SDL_CreateRenderer(win, -1, f);
		return renderer::Renderer(shared_from_this(), ren);
	}
	~Window() {
		if (win) SDL_DestroyWindow(win);
	}
};

}
	
export class Sdl : public enable_shared_from_this<Sdl> {
private:
	Sdl() {
		if (SDL_Init(SDL_INIT_EVERYTHING))
			throw ERR("Failed to initialize SDL.");
	}
public:
	Sdl(const Sdl&) = delete;
	Sdl(Sdl&&) = delete;
	Sdl& operator=(const Sdl&) = delete;
	Sdl& operator=(Sdl&&) = delete;
	static auto init() {
		return shared_ptr<Sdl>(new Sdl);
	}
	auto window(string_view title, int w, int h, window::Flags flag) const {
		auto f = static_cast<SDL_WindowFlags>(flag);
		auto win = SDL_CreateWindow(title.data(), 0, 0, w, h, f);
		if (!win) throw ERR("Failed to create window.");
		return shared_ptr<window::Window>(new window::Window(shared_from_this(), win));
	}
	auto event() const {
		return event::Event(shared_from_this());
	}
	auto timer() const {
		return Timer(shared_from_this());
	}
	~Sdl() {
		SDL_Quit();
	}
};

}
