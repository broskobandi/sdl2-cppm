module;

#include <SDL2/SDL_render.h>

module sdl2;
import :renderer;
import :debug;

namespace sdl2 {

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

Texture Renderer::texture(const Surface& sur) {
	if (!sur.sur) throw err("nullptr passed to Renderer::texture()");
	auto tex = SDL_CreateTextureFromSurface(ren, sur.sur);
	if (!tex) throw err("Failed to create texture from surface.");
	return Texture(tex);
}

Texture Renderer::texture(const path& path_to_bmp) {
	Surface sur(path_to_bmp);
	return texture(sur);
}

void Renderer::set_draw_color(Color color) const {
	SDL_Color col = color.to_sdl();
	if (SDL_SetRenderDrawColor(ren, col.r, col.g, col.b, col.a))
		throw err("Failed to set render draw color.");
	dbg("Render draw color set.");
}

void Renderer::clear() const {
	if (SDL_RenderClear(ren)) throw err("Failed to clear renderer.");
}

void Renderer::clear(Color color) const {
	set_draw_color(color);
	clear();
}

void Renderer::fill_rect(const Rect& rect) const {
	SDL_Rect r = rect.to_sdl();
	if (SDL_RenderFillRect(ren, &r)) throw err("Failed to fill rect.");
}

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

void Renderer::present() const {
	SDL_RenderPresent(ren);
	dbg("Rendered content presented.");
}

void Renderer::set_blend_mode(BlendMode blendmode) const {
	if (SDL_SetRenderDrawBlendMode(ren, static_cast<SDL_BlendMode>(blendmode)))
		throw err("Failed to set renderer draw blend mode.");
	dbg("Renderer draw blend mode set.");
}

void Renderer::set_blend_mode(const Texture& tex, BlendMode blendmode) const {
	if (SDL_SetTextureBlendMode(tex.tex, static_cast<SDL_BlendMode>(blendmode)))
		throw err("Failed to set texture blend mode.");
	dbg("Texture blend mode set.");
}

void Renderer::set_color_mode(const Texture& tex, Color color) const {
	if (SDL_SetTextureColorMod(tex.tex, color.r, color.g, color.b))
		throw err("Failed to set texture color mode.");
	dbg("Texture color mode set.");
}

}
