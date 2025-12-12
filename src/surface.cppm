module;

#include <SDL2/SDL_surface.h>

export module sdl2:surface;
import std;

using std::filesystem::path;

namespace sdl2 {

export class Surface {
	private:
		SDL_Surface* sur;
		friend class Renderer;
	public:
		Surface(const path& path_to_bmp);
		Surface(Surface&&) noexcept;
		Surface& operator=(Surface&&) noexcept;
		Surface(const Surface&) = delete;
		Surface& operator=(const Surface&) = delete;
		~Surface();

};

}
