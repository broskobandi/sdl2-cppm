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

/** @file sdl2.cpp
 * @brief Module implementation for the Sdl class. */

module;

#include <SDL2/SDL.h>

module sdl2;
import :debug;

using std::enable_shared_from_this;
using std::shared_ptr;
using std::string;

namespace sdl2 {

/** Private constructor. init() calls this. */
Sdl::Sdl(Flags flags) {
	if (SDL_WasInit(0)) throw err("SDL cannot be initialized twice.");
	if (SDL_Init(static_cast<Uint32>(flags)))
		throw err("Failed to initialize SDL.");
	dbg("SDL initialized.");
}

/** Creates a shared pointer of Sdl.
 * @throw runtime_error if the initialization fails or 
 * if an SDL session has already been initialized. */
shared_ptr<Sdl> Sdl::init(Flags flags) {
	return shared_ptr<Sdl>(new Sdl(flags));
}

Sdl::~Sdl() {
	SDL_Quit();
	dbg("SDL terminated.");
}

/** Constructs a Window object.
 * @param title The title of the window.
 * @param dimensions The size of the window.
 * @param flags Window initialization flags.
 * @throw runtime_error.
 * @return A shared_ptr of a heap allocated Window object. */
shared_ptr<Window> Sdl::window(
	const string& title,
	Dimensions dimensions,
	Window::Flags flags
) const {
	auto win = SDL_CreateWindow(title.c_str(), 0, 0,
		static_cast<int>(dimensions.w),
		static_cast<int>(dimensions.h),
		static_cast<Uint32>(flags));
	if (!win) throw err("Failed to create window.");
	return shared_ptr<Window>(new Window(win, shared_from_this()));
}

/** Constructs an Event object.
 * @return A stack allocated instance of an Event object. */
Event Sdl::event() const {
	return Event(shared_from_this());
}

/** Construct a Timer object.
 * @return A stack allocated instance of a Timer object.*/
Timer Sdl::timer() const {
	return Timer(shared_from_this());
}

}
