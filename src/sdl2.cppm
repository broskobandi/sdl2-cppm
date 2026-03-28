module;

#include <SDL.h>

export module sdl2;

import std;

namespace sdl2 {

export struct Rect {
	std::int32_t x,y;
	std::uint32_t w, h;
	operator SDL_Rect() const {
		return {
			static_cast<int>(x),
			static_cast<int>(y),
			static_cast<int>(w),
			static_cast<int>(h),
		};
	}
};

export struct FRect {
	float x, y, w, h;
	operator SDL_FRect() const {
		return {x, y, w, h};
	}
};

export struct Point {
	std::int32_t x,y;
	operator SDL_Point() const {
		return {
			static_cast<int>(x),
			static_cast<int>(y)
		};
	}
};

export struct FPoint {
	float x, y;
	operator SDL_FPoint() const {
		return {x, y};
	}
};

export struct Color {
	std::uint8_t r, g, b, a;
	operator SDL_Color() const {
		return {r, g, b, a};
	}
};

export class Sdl;
export class Window;
export class Renderer;

export class Surface {
private:
	friend class Renderer;
	SDL_Surface* sur;
public:
	Surface(const std::filesystem::path& path) {
		auto sur = SDL_LoadBMP(path.string().c_str());
		if (!sur) throw std::runtime_error("Failed to create surface from bmp.");
	}
	Surface(const Surface&) = delete;
	Surface(Surface&&) = delete;
	Surface& operator=(const Surface&) = delete;
	Surface& operator=(Surface&&) = delete;
	~Surface() {
		if (sur) SDL_FreeSurface(sur);
	}
};

export class Texture {
private:
	friend class Renderer;
	SDL_Texture* tex;
	Texture(SDL_Texture* tex) : tex(tex) {}
public:
	Texture(const Texture&) = delete;
	Texture& operator=(const Texture&) = delete;
	Texture(Texture&& other) noexcept : tex(other.tex) {
		other.tex = nullptr;
	}
	Texture& operator=(Texture&& other) noexcept {
		if (&other != this) {
			if (this->tex) SDL_DestroyTexture(tex);
			this->tex = other.tex;
			other.tex = nullptr;
		}
		return *this;
	}
	~Texture() {
		if (tex) SDL_DestroyTexture(tex);
	}
};

export class Timer {
private:
	friend class Sdl;
	const std::shared_ptr<const Sdl> sdl;
	Timer(const std::shared_ptr<const Sdl>& sdl) : sdl(sdl) {}
public:
};

export class Event {
private:
	friend class Sdl;
	// SDL_Event event;
	const std::shared_ptr<const Sdl> sdl;
	Event(const std::shared_ptr<const Sdl>& sdl) : sdl(sdl) {}
public:
};

export class Renderer {
private:
	friend class Window;
	SDL_Renderer* ren;
	const std::shared_ptr<const Window> win;
	Renderer(SDL_Renderer* ren, const std::shared_ptr<const Window>& win) :
		ren(ren), win(win)
	{}
public:
	Renderer(const Renderer&) = delete;
	Renderer(Renderer&&) = delete;
	Renderer& operator=(const Renderer&) = delete;
	Renderer& operator=(Renderer&&) = delete;
	~Renderer() {
		if (ren) SDL_DestroyRenderer(ren);
	}
};

export class Window : public std::enable_shared_from_this<Window> {
private:
	friend class Sdl;
	SDL_Window* win;
	const std::shared_ptr<const Sdl> sdl;
	Window(SDL_Window* win, const std::shared_ptr<const Sdl>& sdl) :
		win(win), sdl(sdl)
	{}
public:
	Window(const Window&) = delete;
	Window(Window&&) = delete;
	Window& operator=(const Window&) = delete;
	Window& operator=(Window&&) = delete;
	auto renderer(bool vsync) const {
		auto ren = SDL_CreateRenderer(win, -1, vsync ? SDL_RENDERER_PRESENTVSYNC : 0);
		if (!ren) throw std::runtime_error("Failed to create renderer.");
		return Renderer(ren, shared_from_this());
	}
	~Window() {
		if (win) SDL_DestroyWindow(win);
	}
};

export class Sdl : public std::enable_shared_from_this<Sdl> {
private:
	Sdl() {
		static bool is_init{false};
		if (is_init)
			throw std::runtime_error("SDL cannot be init twice.");
		if (SDL_Init(SDL_INIT_EVERYTHING))
			throw std::runtime_error("Failed to init SDL.");
		is_init = true;
	}
public:
	static auto init() {
		return std::shared_ptr<Sdl>(new Sdl);
	}
	Sdl(const Sdl&) = delete;
	Sdl(Sdl&&) = delete;
	Sdl& operator=(const Sdl&) = delete;
	Sdl& operator=(Sdl&&) = delete;
	auto window(const std::string& title, std::uint32_t w, std::uint32_t h) const {
		auto win = SDL_CreateWindow(
			title.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			static_cast<int>(w),
			static_cast<int>(h),
			SDL_WINDOW_SHOWN
		);
		if (!win)
			throw std::runtime_error("Failed to create window");
		return std::shared_ptr<Window>(new Window(win, shared_from_this()));
	}
	auto event() const {
		return Event(shared_from_this());
	}
	auto timer() const {
		return Timer(shared_from_this());
	}
	~Sdl() {
		SDL_QuitSubSystem(SDL_INIT_EVERYTHING);
		SDL_Quit();
	}
};

template<typename T>
T operator|(const T& a, const T& b) {
	return static_cast<T>(
		static_cast<std::underlying_type_t<T>>(a) |
		static_cast<std::underlying_type_t<T>>(b)
	);
}

template<typename T>
T& operator|=(T& a, const T& b) {
	return a | b;
}

}
