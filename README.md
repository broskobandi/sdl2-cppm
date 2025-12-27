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
## Notes for building
Due to the fact that the project uses the new module system and some c++23 features, 
the build requirements are somewhat strict.
### Building on Linux
For building on Linux, you must use clang++ and ensure that libc++ is installed.
Installing libc++ will make std.cppm available on your system (which is essential for
the std library to be present as a c++ module) but its location may be different 
depending on the distribution you use. On voidlinux, it can be found at 
/usr/lib/llvm/<VERSION>/share/libc++/v1/std.cppm
On debian the path is:
/usr/lib/llvm-<VERSION>/share/libc++/v1/std.cppm
Locate the std.cppm on your system and passit to cmake when generating the 
build files. 
The generator also needs to support libc++ and modules. Because of this,
the generator must be set to Ninja (ensure Ninja is installed on your system).
To build the project, use the following method:
```bash
# Clone the repo
git clone https://github.com/broskobandi/sdl2-cppm.git &&

# Create build dir and cd into it
mkdir sdl2-cppm/build &&
cd sdl2-cppm/build &&

# Generate build files
cmake -DCMAKE_CXX_COMPILER=clang++ -DSTD_CPPM=/path/to/std.cppm -GNinja .. &&

# Build the project
cmake --build .
```
### Building on Windows
The project can be built on Windows using vscode.
The recommended approach is to open a terminal with alt + t, create a build dir,
cd into it and simply run
```bash
cmake ..
```
then
```bash
cmake --build .
```
No need to specify the generator.
Simply hitting F7 will result in errors. I'm sure there are configurations available
in vscode to build the project using the F7 shortcut, but I'm not very familiar 
with either vscode or windows and I did not want to dig deeper into the subject.
Installing the cmake extension in vscode and manually calling cmake .. and 
cmake --build . worked out of the box without needing to edit .json files
so I think the manual approach is objectively simpler in this instance.
If you think it is possible/necessary/you know how to make the F7 shortcut work,
I would welcome your contribution.
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
- [x] Add windows compatibility
- [ ] Make F7 compile the project in vscode on windows?
- [ ] Add install() in CMakeLists.txt
