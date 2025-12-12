module;

#include <SDL2/SDL_video.h>

export module sdl2:window;
import std;
import :types;
import :renderer;

using std::uint32_t;
using std::string;
using std::shared_ptr;

namespace sdl2 {

export class Sdl;

export class Window : public std::enable_shared_from_this<Window> {
	public:
		enum class Flags : uint32_t {
			FULLSCREEN = SDL_WINDOW_FULLSCREEN,
			OPENGL = SDL_WINDOW_OPENGL,
			SHOWN = SDL_WINDOW_SHOWN,
			HIDDEN = SDL_WINDOW_HIDDEN,
			BORDERLESS = SDL_WINDOW_BORDERLESS,
			RESIZABLE = SDL_WINDOW_RESIZABLE,
			MINIMIZED = SDL_WINDOW_MINIMIZED,
			MAXIMIZED = SDL_WINDOW_MAXIMIZED,
			MOUSE_GRABBED = SDL_WINDOW_MOUSE_GRABBED,
			INPUT_FOCUS = SDL_WINDOW_INPUT_FOCUS,
			MOUSE_FOCUS = SDL_WINDOW_MOUSE_FOCUS,
			FULLSCREEN_DESKTOP = SDL_WINDOW_FULLSCREEN_DESKTOP,
			FOREIGN = SDL_WINDOW_FOREIGN,
			ALLOW_HIGHDPI = SDL_WINDOW_ALLOW_HIGHDPI,
			MOUSE_CAPTURE = SDL_WINDOW_MOUSE_CAPTURE,
			ALWAYS_ON_TOP = SDL_WINDOW_ALWAYS_ON_TOP,
			SKIP_TASKBAR = SDL_WINDOW_SKIP_TASKBAR,
			UTILITY = SDL_WINDOW_UTILITY,
			TOOLTIP = SDL_WINDOW_TOOLTIP,
			POPUP_MENU = SDL_WINDOW_POPUP_MENU,
			KEYBOARD_GRABBED = SDL_WINDOW_KEYBOARD_GRABBED,
			VULKAN = SDL_WINDOW_VULKAN,
			METAL = SDL_WINDOW_METAL,
			INPUT_GRABBED = SDL_WINDOW_INPUT_GRABBED,
		};
	private:
		SDL_Window* win;
		shared_ptr<const Sdl> sdl;
		friend class Sdl;
		Window(SDL_Window* win, shared_ptr<const Sdl> sdl);
	public:
		Window(const Window&) = delete;
		Window(Window&&) = delete;
		Window& operator=(const Window&) = delete;
		Window& operator=(Window&&) = delete;
		~Window();
		Renderer renderer(Renderer::Flags flags) const;
};

}
