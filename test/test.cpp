import sdl2;
import std;

using std::println;
using std::runtime_error;
using std::cerr;
using sdl2::Sdl;
using std::uint32_t;

int main(void) {
	try {
		[[maybe_unused]] uint32_t flag_as_uint = +Sdl::Flags::EVERYTHING;
		Sdl::Flags flags = Sdl::Flags::EVERYTHING | Sdl::Flags::AUDIO;
		flags |= Sdl::Flags::TIMER;
		auto sdl = Sdl::init(flags);
		try { auto sdl = Sdl::init(Sdl::Flags::EVERYTHING); }
			catch(const runtime_error& e) { println("SDL init guard works."); };
	} catch (const runtime_error& e) {
		println(cerr, "{}", e.what());
	}

	return 0;
}
