import sdl2;
import std;

using sdl2::Sdl;
using sdl2::Window;
using sdl2::Renderer;
using sdl2::Event;
using sdl2::KeyCode;
using sdl2::Rect;
using sdl2::uint32_t;
using std::runtime_error;
using std::println;
using std::cerr;

int main(void) {

	try {

	constexpr uint32_t WIN_W = 800;
	constexpr uint32_t WIN_H = 600;
	constexpr uint32_t RECT_W = 128;
	constexpr uint32_t RECT_H = 128;

	// Initialize the SDL session.
	auto sdl = Sdl::init(Sdl::Flags::EVERYTHING);

	// Create a Window object.
	auto win = sdl->window("Awesome SDL project", {WIN_W, WIN_H}, Window::Flags::SHOWN);

	// Create a Renderer object.
	auto ren = win->renderer(Renderer::Flags::PRESENTVSYNC | Renderer::Flags::ACCELERATED);

	// Create an Event object.
	auto event = sdl->event();

	// Create a timer object.
	auto timer = sdl->timer();

	auto texture = ren.texture("../face.bmp");
	Rect rect{
		(WIN_W - RECT_W) / 2,
		(WIN_H - RECT_H) / 2,
		RECT_W,
		RECT_H
	};

	bool is_running = true;

	while (is_running) {
		while (event.poll()) {
			switch (event.type()) {
				case Event::Type::KEYDOWN:
					switch (event.keycode()) {
						case KeyCode::q:
							is_running = false;
							break;
						default: break;
					}
					break;
				default: break;
			}
		}
		ren.clear({30, 70, 70, 255});

		ren.copy(texture, rect);

		println("Time since session start: {}", timer.ticks());

		ren.set_color_mode(texture, {255, 255, 0, 255});

		if (event.mouse().has_intersection(rect))
			ren.set_color_mode(texture, {255, 0, 0, 255});

		if (event.mouse().left)
			ren.set_color_mode(texture, {0, 255, 0, 255});

		if (event.mouse().right)
			ren.set_color_mode(texture, {0, 0, 255, 255});


		ren.present();
	}

	} catch (const runtime_error& e) {
		println(cerr, "{}", e.what());
	}

	return 0;
}
