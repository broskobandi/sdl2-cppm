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

/** @file window.cpp
 * @brief Module implementation for the window module partition. */
module;

#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>

module sdl2;
import :window;
import :debug;

using std::uint32_t;
using std::string;
using std::shared_ptr;

namespace sdl2 {

/** Private constructor. Window::renderer() calls this. */
Window::Window(
	SDL_Window* win,
	shared_ptr<const Sdl> sdl
) :
	win(win), sdl(sdl)
{
	dbg("Window created.");
}

Window::~Window() {
	if (win) {
		SDL_DestroyWindow(win);
		dbg("Window destroyed.");
	}
}

/** Constructs a instance of a Renderer class.
 * @param flags Renderer::Flags representing the Renderer 
 * init flags.
 * @throw runtime_error. 
 * @return A stack allocated instance of the Renderer class. */
Renderer Window::renderer(Renderer::Flags flags) const {
	auto ren = SDL_CreateRenderer(win, -1, static_cast<Uint32>(flags));
	if (!ren) throw err("Failed to create renderer.");
	return Renderer(ren, shared_from_this());
}


}
