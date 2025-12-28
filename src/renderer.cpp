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

/** @file renderer.cpp
 * @brief Module implementation for the renderer module partition. */
module;

#include <SDL2/SDL_render.h>

module sdl2;
import :renderer;
import :debug;

using std::shared_ptr;
using std::uint32_t;
using std::optional;
using std::nullopt;
using std::filesystem::path;

namespace sdl2 {

/** Private constructor, Window::renderer() calls this. */
Renderer::Renderer(SDL_Renderer* ren, shared_ptr<const Window> win) :
	ren(ren), win(win)
{
	dbg("Renderer created.");
}

Renderer::~Renderer() {
	if (ren) {
		SDL_DestroyRenderer(ren);
		dbg("Renderer destroyed.");
	}
}

Renderer::Renderer(Renderer&& other) noexcept :
	ren(other.ren), win(other.win)
{
	other.ren = nullptr;
}

Renderer& Renderer::operator=(Renderer&& other) noexcept {
	if (this != &other) {
		if (this->ren) SDL_DestroyRenderer(this->ren);
		this->ren = other.ren;
		this->win = other.win;
		other.ren = nullptr;
	}
	return *this;
}

/** Creates a new Texture from a Surface object.
 * @param sur The surface to be used.
 * @throw runtime_error.
 * @return A stack allocted instance of a Texture object. */
Texture Renderer::texture(const Surface& sur) {
	if (!sur.sur) throw err("nullptr passed to Renderer::texture()");
	auto tex = SDL_CreateTextureFromSurface(ren, sur.sur);
	if (!tex) throw err("Failed to create texture from surface.");
	return Texture(tex);
}

/** Creates a new Texture from a bmp file.
 * @param path_to_bmp Path to the bmp file.
 * @throw runtime_error.
 * @return A stack allocted instance of a Texture object. */
Texture Renderer::texture(const path& path_to_bmp) {
	Surface sur(path_to_bmp);
	return texture(sur);
}

/** Sets the renderer's draw color.
 * @param color The color to be used.
 * @throw runtime_error. */
void Renderer::set_draw_color(Color color) const {
	SDL_Color col = color.to_sdl();
	if (SDL_SetRenderDrawColor(ren, col.r, col.g, col.b, col.a))
		throw err("Failed to set render draw color.");
	dbg("Render draw color set.");
}

/** Clears the renderer.
 * @throw runtime_error. */
void Renderer::clear() const {
	if (SDL_RenderClear(ren)) throw err("Failed to clear renderer.");
}

/** Clears the renderer with the specified color.
 * @param color The color to be used.
 * @throw runtime_error. */
void Renderer::clear(Color color) const {
	set_draw_color(color);
	clear();
}

/** Fills the rect with the currently set renderer color.
 * @param rect The rect to be filled. Pass nullopt to use 
 * the entire render target.
 * @throw runtime_error. */
void Renderer::fill_rect(optional<Rect> rect) const {
	SDL_Rect r = rect.has_value() ? rect.value().to_sdl() : SDL_Rect{0, 0, 0, 0};
	SDL_Rect* rptr = rect.has_value() ? &r : nullptr;
	if (SDL_RenderFillRect(ren, rptr)) throw err("Failed to fill rect.");
	dbg("Rect filled.");
}

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
void Renderer::copy(
	const Texture& tex,
	optional<Rect> dstrect,
	optional<Rect> srcrect,
	float angle,
	optional<Point> center,
	Flip flip
) const {
	SDL_Rect dst = dstrect.has_value() ? dstrect.value().to_sdl() : SDL_Rect{0, 0, 0, 0};
	SDL_Rect src = srcrect.has_value() ? srcrect.value().to_sdl() : SDL_Rect{0, 0, 0, 0};
	SDL_Rect* dstptr = dstrect.has_value() ? &dst : nullptr;
	SDL_Rect* srcptr = srcrect.has_value() ? &src : nullptr;
	SDL_Point cen = center.has_value() ? center.value().to_sdl() : SDL_Point{0, 0};
	SDL_Point* cenptr = center.has_value() ? &cen : nullptr;

	if (SDL_RenderCopyEx(ren, tex.tex, srcptr, dstptr, angle, cenptr,
		static_cast<SDL_RendererFlip>(flip))
	) throw err("Failed to copy texture.");
	dbg("Texture copied.");
}

/** Presents the rendered data. */
void Renderer::present() const {
	SDL_RenderPresent(ren);
	dbg("Rendered content presented.");
}

/** Sets the renderer's blend mode.
 * @param blendmode Renderer::Blendmode enum representing the blend mode.
 * @throw runtime_error. */
void Renderer::set_blend_mode(BlendMode blendmode) const {
	if (SDL_SetRenderDrawBlendMode(ren, static_cast<SDL_BlendMode>(blendmode)))
		throw err("Failed to set renderer draw blend mode.");
	dbg("Renderer draw blend mode set.");
}

/** Sets a texture's blend mode. 
 * @param tex The texture to be used. 
 * @param blendmode Renderer::Blendmode enum representing the blend mode.
 * @throw runtime_error. */
void Renderer::set_blend_mode(const Texture& tex, BlendMode blendmode) const {
	if (SDL_SetTextureBlendMode(tex.tex, static_cast<SDL_BlendMode>(blendmode)))
		throw err("Failed to set texture blend mode.");
	dbg("Texture blend mode set.");
}

/** Sets a texture's color mode. 
 * @param tex The texture to be used. 
 * @param color The color to be used.
 * @throw runtime_error. */
void Renderer::set_color_mode(const Texture& tex, Color color) const {
	if (SDL_SetTextureColorMod(tex.tex, color.r, color.g, color.b))
		throw err("Failed to set texture color mode.");
	dbg("Texture color mode set.");
}

}
