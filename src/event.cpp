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

/** @file event.cpp
 * @brief Module implementation for the event module partition. */

module;

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_mouse.h>

module sdl2;
import :event;
import :debug;

using std::shared_ptr;
using std::int32_t;

namespace sdl2 {

Event::Event(shared_ptr<const Sdl> sdl) :
	sdl(sdl)
{
	keystate = SDL_GetKeyboardState(nullptr);
	dbg("Event created.");
}

Event::~Event() {
	dbg("Event destroyed.");
}

/** Calls SDL_PollEvent.
 * @return 1 if there is a pending event, otherwise 0. */
int32_t Event::poll() {
	return SDL_PollEvent(&event);
}

/** Returns the most up-to-date event type.
 * Requires poll() to be called first.
 * @return Type containing the value of event.type. */
Event::Type Event::type() const {
	return static_cast<Type>(event.type);
}

/** Return the most up-to-date key event code.
 * Requires poll() to be called first.
 * @return KeyCode containing the value of event.key.keysym.sym. */
KeyCode Event::keycode() const {
	return static_cast<KeyCode>(event.key.keysym.sym);
}

/** Checks whether the given key was pressed.
 * Requires poll() to be called first.
 * @return bool indicating whether the key was pressed. */
bool Event::has_scancode(ScanCode scancode) const {
	if (keystate[+scancode]) return true;
	return false;
}

/** Returns an instance of struct Mouse as POD containing information 
 * about the current mouse state. */
Event::Mouse Event::mouse() const {
	Mouse mouse;
	auto mouse_state = SDL_GetMouseState(&mouse.x, &mouse.y);
	if (mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT))
		mouse.left = true;
	if (mouse_state & SDL_BUTTON(SDL_BUTTON_MIDDLE))
		mouse.middle = true;
	if (mouse_state & SDL_BUTTON(SDL_BUTTON_RIGHT))
		mouse.right = true;
	return mouse;
}
	
}
