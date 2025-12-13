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

/** @file window.cppm 
 * @brief Module partition interface file for the window` module in the sdl2-cppm library.
 * @details This file contains the Window class. */
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

/** The window class is created by Sdl::window(). It is not movable/copyable.
 * This is responsible for constructing the Renderer class. */
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

		/** Private constructor. Window::renderer() calls this. */
		Window(SDL_Window* win, shared_ptr<const Sdl> sdl);
	public:
		Window(const Window&) = delete;
		Window(Window&&) = delete;
		Window& operator=(const Window&) = delete;
		Window& operator=(Window&&) = delete;
		~Window();

		/** Constructs a instance of a Renderer class.
		 * @param flags Renderer::Flags representing the Renderer 
		 * init flags.
		 * @throw runtime_error. 
		 * @return A stack allocated instance of the Renderer class. */
		Renderer renderer(Renderer::Flags flags) const;
};

}
