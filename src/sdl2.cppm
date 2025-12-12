module;

#include <SDL2/SDL.h>

export module sdl2;
import std;
export import :types;

using std::enable_shared_from_this;
using std::shared_ptr;

namespace sdl2 {
	
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
		Sdl(Flags flags);
	public:
		static shared_ptr<Sdl> init(Flags flags);
		Sdl(const Sdl&) = delete;
		Sdl(Sdl&&) = delete;
		Sdl& operator=(const Sdl&) = delete;
		Sdl& operator=(Sdl&&) = delete;
		~Sdl();
};

}
