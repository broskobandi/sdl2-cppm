# sdl2-cppm
Abstractions for objects and functionalities of SDL2 written using C++23 modules.
## The goal
The goal of the project is to learn about the new c++ modules as well as to provide
a higher level library for SDL2 that integrates better with modular C++ projects.
## Why SDL2?
I chose SDL2 because I have been using it for many years in small games that I wrote in C,
so I am much more familiar with it than SDL3. I'm sure SDL3 is also stable enough 
for such a project to make sense but I'm going to leave that for another developer 
for now.
## Why C++23?
std::println...
## Example usage
```c
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

		ren.present();
	}

	} catch (const runtime_error& e) {
		println(cerr, "{}", e.what());
	}

	return 0;
}
```
## Todo
- [x] Add more comments
- [x] Add example usage in readme
- [ ] Add install() in CMakeLists.txt
