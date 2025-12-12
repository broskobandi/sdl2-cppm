module;

#include <SDL2/SDL_render.h>

export module sdl2:renderer;
import std;
import :types;

using std::shared_ptr;
using std::uint32_t;

namespace sdl2 {

export class Window;

export class Renderer {
	public:
		enum class Flags : uint32_t {
			SOFTWARE = SDL_RENDERER_SOFTWARE,
			ACCELERATED = SDL_RENDERER_ACCELERATED,
			PRESENTVSYNC = SDL_RENDERER_PRESENTVSYNC,
			TARGETTEXTURE = SDL_RENDERER_TARGETTEXTURE,
		};
	private:
		SDL_Renderer* ren;
		shared_ptr<const Window> win;
		friend class Window;
		Renderer(SDL_Renderer* ren, shared_ptr<const Window> win);
	public:
		Renderer(const Renderer&) = delete;
		Renderer& operator=(const Renderer&) = delete;
		Renderer(Renderer&&) noexcept;
		Renderer& operator=(Renderer&&) noexcept;
		~Renderer();
};

}
