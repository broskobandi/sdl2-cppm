import sdl2;

using sdl2::Sdl;
using sdl2::Renderer;

int main(void) {
	auto sdl = Sdl::init();
	auto win = sdl->window("test", 800, 600);
	auto ren = win->renderer(Renderer::Flag::ACCELERATED | Renderer::Flag::PRESENTVSYNC);
	auto event = sdl->event();
	auto timer = sdl->timer();
	return 0;
}
