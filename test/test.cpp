import sdl2;
import std;

using std::println;
using std::runtime_error;
using std::cerr;
using sdl2::Sdl;
using sdl2::Window;
using sdl2::Renderer;
using std::uint32_t;

int main(void) {
	try {
		[[maybe_unused]] uint32_t flag_as_uint = +Sdl::Flags::EVERYTHING;
		Sdl::Flags flags = Sdl::Flags::EVERYTHING | Sdl::Flags::AUDIO;
		flags |= Sdl::Flags::TIMER;
		auto sdl = Sdl::init(flags);
		try { auto sdl = Sdl::init(Sdl::Flags::EVERYTHING); }
			catch(const runtime_error& e) { println("SDL init guard works."); };
		auto win = sdl->window("test", {800, 600}, Window::Flags::SHOWN);
		auto ren = win->renderer(Renderer::Flags::PRESENTVSYNC);
	} catch (const runtime_error& e) {
		println(cerr, "{}", e.what());
	}

	return 0;
}
