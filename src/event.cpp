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

KeyCode Event::keycode() const {
	return static_cast<KeyCode>(event.key.keysym.sym);
}

bool Event::has_scancode(ScanCode scancode) const {
	if (keystate[+scancode]) return true;
	return false;
}
	
}
