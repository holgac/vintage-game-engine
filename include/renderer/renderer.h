/*
	This file is part of Vintage Game Engine.
	Vintage Game Engine is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Vintage Game Engine is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Vintage Game Engine.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef _VGE_RENDERER_H_
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

struct vge_window_properties
{
	char* window_title;
	int pos_x;
	int pos_y;
	int width;
	int height;
	int depth_buffer_size;
};

struct vge_renderer
{
	struct SDL_Window* sdl_window;
	SDL_GLContext sdl_glcontext;
	SDL_Renderer* sdl_renderer;
};
struct vge_game;
int vge_renderer_init(struct vge_game* game, struct vge_window_properties* window_properties);
void vge_renderer_destroy(struct vge_renderer* renderer);

void vge_renderer_onframe(struct vge_renderer* renderer);
void vge_renderer_setclearcolor(struct vge_renderer* renderer, float r, float g, float b);

#endif /* _VGE_RENDERER_H_ */
