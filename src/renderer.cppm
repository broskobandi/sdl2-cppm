module;

#include <SDL2/SDL_render.h>

export module sdl2:renderer;
import std;
import :types;
import :surface;
import :texture;

using std::shared_ptr;
using std::uint32_t;
using std::optional;
using std::nullopt;
using std::filesystem::path;

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
		enum class Flip : uint32_t {
			NONE = SDL_FLIP_NONE,
			HORIZONTAL = SDL_FLIP_HORIZONTAL,
			VERTICAL = SDL_FLIP_VERTICAL,
		};
		enum class BlendMode : uint32_t {
			NONE = SDL_BLENDMODE_NONE,
			BLEND = SDL_BLENDMODE_BLEND,
			ADD = SDL_BLENDMODE_ADD,
			MOD = SDL_BLENDMODE_MOD,
			MUL = SDL_BLENDMODE_MUL,
			INVALID = SDL_BLENDMODE_INVALID,
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
		Texture texture(const Surface& sur);
		Texture texture(const path& path_to_bmp);
		void set_draw_color(Color color) const;
		void clear() const;
		void clear(Color color) const;
		void copy(
			const Texture& tex,
			optional<Rect> dstrect = nullopt,
			optional<Rect> srcrect = nullopt,
			float angle = 0.0f,
			optional<Point> center = nullopt,
			Flip flip = Flip::NONE
		) const;
		void fill_rect(const Rect& rect) const;
		void set_blend_mode(BlendMode blendmode) const;
		void set_blend_mode(const Texture& tex, BlendMode blendmode) const;
		void set_color_mode(const Texture& tex, Color color) const;
		void present() const;
};

}
