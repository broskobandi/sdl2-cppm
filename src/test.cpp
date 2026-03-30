#include "face.h"

import sdl2;
import std;

using sdl2::Sdl;
using sdl2::Renderer;

int main(void) {
	auto sdl = Sdl::init();
	auto win = sdl->window("test", 800, 600);
	auto ren = win->renderer(Renderer::Flag::ACCELERATED | Renderer::Flag::PRESENTVSYNC);
	auto event = sdl->event();
	auto timer = sdl->timer();
	while (event.poll()) {}
	auto tex = ren.texture("../src/face.bmp");
	auto tex2 = ren.texture(std::vector<std::uint8_t>(face_bmp, face_bmp + face_bmp_len));
	return 0;
}
