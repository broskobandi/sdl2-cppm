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

/** @file sdl2.cppm 
 * @brief Public module interface file for the sdl2-cppm library.
 * @defaults This file contains the main Sdl class that other objects in the library 
 * depend on. */

module;

#include <SDL2/SDL.h>

export module sdl2;
import std;
export import :types;
export import :window;
export import :renderer;
export import :surface;
export import :texture;
export import :event;
export import :scancode;
export import :keycode;

using std::enable_shared_from_this;
using std::shared_ptr;

namespace sdl2 {
	
/** Main Sdl class. It is responsible for initializing the 
 * underlying SDL2 session and create child objects such as 
 * Window, Renderer, Event, and Timer.
 * It can only be constructed via the init() associated 
 * function and is not movable/copyable. 
 * All the constructed child classes store a shared pointer 
 * to this object ensuring that it lives at least as long as 
 * the child classes. */
export class Sdl : public enable_shared_from_this<Sdl> {
	public:
		enum class Flags {
			TIMER = SDL_INIT_TIMER,
			AUDIO = SDL_INIT_AUDIO,
			VIDEO = SDL_INIT_VIDEO,
			JOYSTICK = SDL_INIT_JOYSTICK,
			HAPTIC = SDL_INIT_HAPTIC,
			GAMECONTROLLER = SDL_INIT_GAMECONTROLLER,
			EVENTS = SDL_INIT_EVENTS,
			SENSOR = SDL_INIT_SENSOR,
			NOPARACHUTE = SDL_INIT_NOPARACHUTE,
			EVERYTHING = SDL_INIT_EVERYTHING,
		};
	private:

		/** Private constructor. init() calls this. */
		Sdl(Flags flags);

	public:

		/** Creates a shared pointer of Sdl.
		 * @throw runtime_error if the initialization fails or 
		 * if an SDL session has already been initialized. */
		static shared_ptr<Sdl> init(Flags flags);

		Sdl(const Sdl&) = delete;
		Sdl(Sdl&&) = delete;
		Sdl& operator=(const Sdl&) = delete;
		Sdl& operator=(Sdl&&) = delete;
		~Sdl();

		/** Constructs a Window object.
		 * @param title The title of the window.
		 * @param dimensions The size of the window.
		 * @param flags Window initialization flags.
		 * @throw runtime_error.
		 * @return A shared_ptr of a heap allocated Window object. */
		shared_ptr<Window> window(
			const string& title,
			Dimensions dimensions,
			Window::Flags flags
		) const;

		/** Constructs an Event object.
		 * @return A stack allocated instance of an Event object. */
		Event event() const;
};

}
