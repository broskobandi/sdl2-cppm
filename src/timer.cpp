module;

#include <SDL2/SDL_timer.h>

module sdl2;
import :timer;
import :debug;

namespace sdl2 {

Timer::Timer(shared_ptr<const Sdl> sdl) : sdl(sdl) {
	dbg("Timer created.");
}

uint32_t Timer::ticks() const {
	return SDL_GetTicks();
}

Timer::~Timer() {
	dbg("Timer destroyed.");
}

}
