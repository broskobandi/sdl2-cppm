/*
MIT License

Copyright (c) 2025 broskobandi

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/** @file renderer.cppm 
 * @brief Module partition interface file for the renderer module in the sdl2-cppm library.
 * @details This file contains the Renderer class. */
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

/** This class is responsible for creating, managing, and rendering textures,
 * and all other rendering tasks. It's constructed with Window::renderer(). */
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

		/** Private constructor, Window::renderer() calls this. */
		Renderer(SDL_Renderer* ren, shared_ptr<const Window> win);
	public:
		Renderer(const Renderer&) = delete;
		Renderer& operator=(const Renderer&) = delete;
		Renderer(Renderer&&) noexcept;
		Renderer& operator=(Renderer&&) noexcept;
		~Renderer();

		/** Creates a new Texture from a Surface object.
		 * @param sur The surface to be used.
		 * @throw runtime_error.
		 * @return A stack allocted instance of a Texture object. */
		Texture texture(const Surface& sur);

		/** Creates a new Texture from a bmp file.
		 * @param path_to_bmp Path to the bmp file.
		 * @throw runtime_error.
		 * @return A stack allocted instance of a Texture object. */
		Texture texture(const path& path_to_bmp);

		/** Sets the renderer's draw color.
		 * @param color The color to be used.
		 * @throw runtime_error. */
		void set_draw_color(Color color) const;

		/** Clears the renderer.
		 * @throw runtime_error. */
		void clear() const;

		/** Clears the renderer with the specified color.
		 * @param color The color to be used.
		 * @throw runtime_error. */
		void clear(Color color) const;

		/** Renders a texture to the render target.
		 * @param tex The texture to be rendered. 
		 * @param dstrect The rect to render to.
		 * pass nullopt to use the entire render target. 
		 * @param srcrect The portion of the texture to be 
		 * used. Pass nullopt to use the entire texture.
		 * @param angle A float that represents the extent 
		 * of the rotation. 
		 * @param center The center of the rotation. 
		 * Pass nullopt to use the center of the render target. 
		 * @param flip Renderer::Flip enum that represents 
		 * vertical/horizontal flip.
		 * @throw runtime_error. */
		void copy(
			const Texture& tex,
			optional<Rect> dstrect = nullopt,
			optional<Rect> srcrect = nullopt,
			float angle = 0.0f,
			optional<Point> center = nullopt,
			Flip flip = Flip::NONE
		) const;

		/** Fills the rect with the currently set renderer color.
		 * @param rect The rect to be filled. Pass nullopt to use 
		 * the entire render target.
		 * @throw runtime_error. */
		void fill_rect(optional<Rect> rect) const;

		/** Sets the renderer's blend mode.
		 * @param blendmode Renderer::Blendmode enum representing the blend mode.
		 * @throw runtime_error. */
		void set_blend_mode(BlendMode blendmode) const;

		/** Sets a texture's blend mode. 
		 * @param tex The texture to be used. 
		 * @param blendmode Renderer::Blendmode enum representing the blend mode.
		 * @throw runtime_error. */
		void set_blend_mode(const Texture& tex, BlendMode blendmode) const;

		/** Sets a texture's color mode. 
		 * @param tex The texture to be used. 
		 * @param color The color to be used.
		 * @throw runtime_error. */
		void set_color_mode(const Texture& tex, Color color) const;

		/** Presents the rendered data. */
		void present() const;
};

}
