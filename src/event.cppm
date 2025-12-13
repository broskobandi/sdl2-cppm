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

/** @file event.cppm 
 * @brief Module partition interface file for the event module in the sdl2-cppm library.
 * @details This file contains the Event class. */

module;

#include <SDL2/SDL_events.h>

export module sdl2:event;
import std;
import :keycode;
import :scancode;
import :types;

using std::shared_ptr;
using std::uint32_t;
using std::uint8_t;

namespace sdl2 {

export class Sdl;

/** This class provides SDL_Event related functionality such as event poll
 * and input scanning. */
export class Event {
	public:
		enum class Type : uint32_t {
			FIRSTEVENT = SDL_FIRSTEVENT,
			QUIT = SDL_QUIT,
			APP_TERMINATING = SDL_APP_TERMINATING,
			APP_LOWMEMORY = SDL_APP_LOWMEMORY,
			APP_WILLENTERBACKGROUND = SDL_APP_WILLENTERBACKGROUND,
			APP_DIDENTERBACKGROUND = SDL_APP_DIDENTERBACKGROUND,
			APP_WILLENTERFOREGROUND = SDL_APP_WILLENTERFOREGROUND,
			APP_DIDENTERFOREGROUND = SDL_APP_DIDENTERFOREGROUND,
			LOCALECHANGED = SDL_LOCALECHANGED,
			DISPLAYEVENT = SDL_DISPLAYEVENT,
			WINDOWEVENT = SDL_WINDOWEVENT,
			SYSWMEVENT = SDL_SYSWMEVENT,
			KEYDOWN = SDL_KEYDOWN,
			KEYUP = SDL_KEYUP,
			TEXTEDITING = SDL_TEXTEDITING,
			TEXTINPUT = SDL_TEXTINPUT,
			KEYMAPCHANGED = SDL_KEYMAPCHANGED,
			TEXTEDITING_EXT = SDL_TEXTEDITING_EXT,
			MOUSEMOTION = SDL_MOUSEMOTION,
			MOUSEBUTTONDOWN = SDL_MOUSEBUTTONDOWN,
			MOUSEBUTTONUP = SDL_MOUSEBUTTONUP,
			MOUSEWHEEL = SDL_MOUSEWHEEL,
			JOYAXISMOTION = SDL_JOYAXISMOTION,
			JOYBALLMOTION = SDL_JOYBALLMOTION,
			JOYHATMOTION = SDL_JOYHATMOTION,
			JOYBUTTONDOWN = SDL_JOYBUTTONDOWN,
			JOYBUTTONUP = SDL_JOYBUTTONUP,
			JOYDEVICEADDED = SDL_JOYDEVICEADDED,
			JOYDEVICEREMOVED = SDL_JOYDEVICEREMOVED,
			JOYBATTERYUPDATED = SDL_JOYBATTERYUPDATED,
			CONTROLLERAXISMOTION = SDL_CONTROLLERAXISMOTION,
			CONTROLLERBUTTONDOWN = SDL_CONTROLLERBUTTONDOWN,
			CONTROLLERBUTTONUP = SDL_CONTROLLERBUTTONUP,
			CONTROLLERDEVICEADDED = SDL_CONTROLLERDEVICEADDED,
			CONTROLLERDEVICEREMOVED = SDL_CONTROLLERDEVICEREMOVED,
			CONTROLLERDEVICEREMAPPED = SDL_CONTROLLERDEVICEREMAPPED,
			CONTROLLERTOUCHPADDOWN = SDL_CONTROLLERTOUCHPADDOWN,
			CONTROLLERTOUCHPADMOTION = SDL_CONTROLLERTOUCHPADMOTION,
			CONTROLLERTOUCHPADUP = SDL_CONTROLLERTOUCHPADUP,
			CONTROLLERSENSORUPDATE = SDL_CONTROLLERSENSORUPDATE,
			CONTROLLERUPDATECOMPLETE_RESERVED_FOR_SDL3 =
				SDL_CONTROLLERUPDATECOMPLETE_RESERVED_FOR_SDL3,
			CONTROLLERSTEAMHANDLEUPDATED = SDL_CONTROLLERSTEAMHANDLEUPDATED,
			FINGERDOWN = SDL_FINGERDOWN,
			FINGERUP = SDL_FINGERUP,
			FINGERMOTION = SDL_FINGERMOTION,
			DOLLARGESTURE = SDL_DOLLARGESTURE,
			DOLLARRECORD = SDL_DOLLARRECORD,
			MULTIGESTURE = SDL_MULTIGESTURE,
			CLIPBOARDUPDATE = SDL_CLIPBOARDUPDATE,
			DROPFILE = SDL_DROPFILE,
			DROPTEXT = SDL_DROPTEXT,
			DROPBEGIN = SDL_DROPBEGIN,
			DROPCOMPLETE = SDL_DROPCOMPLETE,
			AUDIODEVICEADDED = SDL_AUDIODEVICEADDED,
			AUDIODEVICEREMOVED = SDL_AUDIODEVICEREMOVED,
			SENSORUPDATE = SDL_SENSORUPDATE,
			RENDER_TARGETS_RESET = SDL_RENDER_TARGETS_RESET,
			RENDER_DEVICE_RESET = SDL_RENDER_DEVICE_RESET,
			POLLSENTINEL = SDL_POLLSENTINEL,
			USEREVENT = SDL_USEREVENT,
			LASTEVENT = SDL_LASTEVENT,
		};
	private:
		friend class Sdl;
		SDL_Event event;
		shared_ptr<const Sdl> sdl;
		const uint8_t* keystate {nullptr};

		/** Private constructor. Sdl::event() calls this. */
		Event(shared_ptr<const Sdl> sdl);

	public:

		~Event();

		/** Calls SDL_PollEvent.
		 * @return 1 if there is a pending event, otherwise 0. */
		int32_t poll();

		/** Returns the most up-to-date event type.
		 * Requires poll() to be called first.
		 * @return Type containing the value of event.type. */
		Type type() const;

		/** Return the most up-to-date key event code.
		 * Requires poll() to be called first.
		 * @return KeyCode containing the value of event.key.keysym.sym. */
		KeyCode keycode() const;

		/** Checks whether the given key was pressed.
		 * Requires poll() to be called first.
		 * @return bool indicating whether the key was pressed. */
		bool has_scancode(ScanCode scancode) const;
};

}
