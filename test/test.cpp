import sdl2;
import std;

int main(void) {
	try {
		using namespace sdl2;
		auto sdl = Sdl::init();
		auto win = sdl->window("test", 800, 600, window::Flags::SHOWN);
		auto ren = win->renderer(renderer::Flags::PRESENTVSYNC);
		auto ep = sdl->event();
		auto tex = ren.texture_from_bmp("../test/face.bmp");
		auto timer = sdl->timer();
		while (ep.poll()) {}
		ren.clear({30, 70, 70, 255});
		ren.copy(tex);
		if (ep.has_keycode(event::KeyCode::q)) std::println("segg");
		ren.copy(tex, Rect{0, 0, 0, 0}, Rect{0, 0, 0, 0}, 0.0f, Point{0,0}, renderer::Flip::NONE);
		std::println("{}", timer.ticks());
		ren.present();
	} catch (const std::runtime_error& e) {
		std::println(std::cerr, "{}", e.what());
	}
	return 0;
}
