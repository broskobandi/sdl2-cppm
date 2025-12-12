module;

export module sdl2:timer;
import std;

using std::shared_ptr;
using std::uint32_t;

namespace sdl2 {

export class Sdl;

export class Timer {
	private:
		shared_ptr<const Sdl> sdl;
		friend class Sdl;
		Timer(shared_ptr<const Sdl> sdl);
	public:
		uint32_t ticks() const;
		~Timer();
};

}
