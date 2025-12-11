import sdl2;
import std;

using sdl2::Sdl;
using sdl2::Rect;
using sdl2::Point;
using std::println;
using std::cerr;

int main(void) {
	try {
		auto sdl = Sdl::init();
		auto win = sdl->window("test", 800, 600, sdl2::window::Flags::SHOWN);
		auto ren = win->renderer(sdl2::renderer::Flags::PRESENTVSYNC);
		auto ep = sdl->event();
		auto tex = ren.texture("../test/face.bmp");
		auto timer = sdl->timer();
		while (ep.poll()) {}
		ren.clear({30, 70, 70, 255});
		ren.copy(tex);
		if (ep.has_keycode(sdl2::event::KeyCode::q)) std::println("segg");
		ren.copy(
			tex,
			Rect{0, 0, 0, 0},
			Rect{0, 0, 0, 0},
			0.0f,
			Point{0,0},
			sdl2::renderer::Flip::NONE
		);
		println("{}", timer.ticks());
		ren.present();
	} catch (const std::runtime_error& e) {
		println(cerr, "{}", e.what());
	}
	return 0;
}
