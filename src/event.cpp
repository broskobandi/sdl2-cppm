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

module sdl2;
import :event;
import :debug;

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

int32_t Event::poll() {
	return SDL_PollEvent(&event);
}

Event::Type Event::type() const {
	return static_cast<Type>(event.type);
}

KeyCode Event::keycode() const {
	return static_cast<KeyCode>(event.key.keysym.sym);
}

bool Event::has_scancode(ScanCode scancode) const {
	if (keystate[+scancode]) return true;
	return false;
}
	
}
