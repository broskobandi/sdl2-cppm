import sdl2;
import std;

using std::println;
using std::runtime_error;
using std::cerr;
using sdl2::Sdl;
using sdl2::Window;
using sdl2::Renderer;
using sdl2::Surface;
using sdl2::KeyCode;
using sdl2::ScanCode;
using sdl2::Event;
using sdl2::Rect;
using std::uint32_t;
using std::int32_t;

int main(void) {
	try {
		[[maybe_unused]] uint32_t flag_as_uint = +Sdl::Flags::EVERYTHING;
		Sdl::Flags flags = Sdl::Flags::EVERYTHING | Sdl::Flags::AUDIO;
		flags |= Sdl::Flags::TIMER;
		auto sdl = Sdl::init(flags);
		try { auto sdl = Sdl::init(Sdl::Flags::EVERYTHING); }
			catch(const runtime_error& e) { };
		auto win = sdl->window("test", {800, 600}, Window::Flags::SHOWN);
		auto ren = win->renderer(Renderer::Flags::PRESENTVSYNC);
		auto timer = sdl->timer();
		Surface sur("../face.bmp");
		auto tex = ren.texture(sur);
		auto tex2 = ren.texture("../face.bmp");
		auto event = sdl->event();
		while (event.poll()) {
			[[maybe_unused]] KeyCode key = event.keycode();
		}
		[[maybe_unused]] bool a =  event.has_scancode(ScanCode::A);
		[[maybe_unused]] Event::Type type = event.type();
		ren.set_blend_mode(Renderer::BlendMode::BLEND);
		ren.set_blend_mode(tex, Renderer::BlendMode::ADD);
		ren.set_color_mode(tex, {255, 0, 0, 0});
		ren.set_draw_color({30, 70, 70, 255});
		ren.clear();
		ren.set_draw_color({70, 30, 30, 255});
		ren.fill_rect(Rect{0, 0, 100, 100});
		ren.copy(tex);
		ren.present();
		[[maybe_unused]] auto time = timer.ticks();
	} catch (const runtime_error& e) {
		println(cerr, "{}", e.what());
	}

	println("All tests passed.");

	return 0;
}
