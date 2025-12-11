# sdl2-cppm
Abstractions for objects and functionalities of SDL2 written using C++23 modules.
## Usage
```cpp
import sdl2;
import std;

int main(void) {
	try {

		using namespace sdl2;

		auto sdl = Sdl::init();
		auto win = sdl->window("test", 800, 600, window::Flags::SHOWN);
		auto ren = win->renderer(renderer::Flags::PRESENTVSYNC);
		auto event = sdl->event();
		auto tex = ren.texture_from_bmp("../test/face.bmp");

        bool is_running = true;

        while (is_running) {
            while (event.poll()) {
                if (event.has_keycode(event::KeyCode::q) is_running = false;

                ren.clear({30, 70, 70, 255});

                ren.copy(tex);

                ren.present();
            }
        }

	} catch (const std::runtime_error& e) {
		std::println(std::cerr, "{}", e.what());
	}

	return 0;
}
```
## Todo
- [ ] Add more tests
