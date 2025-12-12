module;

#include <SDL2/SDL_render.h>

export module sdl2:texture;
import std;

namespace sdl2 {

export class Texture {
	private:
		friend class Renderer;
		SDL_Texture* tex;
		Texture(SDL_Texture* tex);
	public:
		Texture(Texture&&) noexcept;
		Texture& operator=(Texture&&) noexcept;
		Texture(const Texture&) = delete;
		Texture& operator=(const Texture&) = delete;
		~Texture();
};

}
