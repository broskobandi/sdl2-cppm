import sdl2;

int main(void) {
	auto sdl = sdl2::Sdl::init();
	auto win = sdl->window("test", 800, 600);
	auto ren = win->renderer(true);
	auto event = sdl->event();
	auto timer = sdl->timer();
	return 0;
}
