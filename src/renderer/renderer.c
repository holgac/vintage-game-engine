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
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "renderer/renderer.h"
#include "core/game.h"
#include "core/containers/list.h"
#include "core/subsystem.h"

struct vge_renderer_gl
{
	struct vge_subsystem subsys;
	struct SDL_Window *sdl_window;
	SDL_GLContext sdl_glcontext;
	SDL_Renderer* sdl_renderer;
};

static void _vge_renderer_gl_init(struct vge_game *game,
		struct vge_subsystem *subsys)
{
}

static void _vge_renderer_gl_destroy(struct vge_game *game,
		struct vge_subsystem *subsys)
{
	struct vge_renderer_gl *renderer;
	renderer = vge_container_of(subsys, struct vge_renderer_gl, subsys);
	SDL_GL_DeleteContext(renderer->sdl_glcontext);
	SDL_DestroyRenderer(renderer->sdl_renderer);
	SDL_DestroyWindow(renderer->sdl_window);
	free(renderer);
}

static void _vge_renderer_gl_on_step(struct vge_game *game,
		struct vge_subsystem *subsys)
{
}

static void _vge_renderer_gl_on_frame(struct vge_game *game,
		struct vge_subsystem *subsys)
{
	struct vge_renderer_gl *renderer;
	renderer = vge_container_of(subsys, struct vge_renderer_gl, subsys);
	SDL_GL_SwapWindow(renderer->sdl_window);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


int vge_renderer_init(struct vge_game *game,
		struct vge_window_properties *props, struct vge_subsystem **subsys)
{
	struct vge_renderer_gl *renderer;
	GLenum gl_error;

	renderer = malloc(sizeof(struct vge_renderer_gl));

	renderer->sdl_window = SDL_CreateWindow(
		props?props->window_title:"VGE TEST",
		props?props->pos_x:SDL_WINDOWPOS_CENTERED,
		props?props->pos_y:SDL_WINDOWPOS_CENTERED,
		props?props->width:640,
		props?props->height:640,
		SDL_WINDOW_OPENGL);
	if(!renderer->sdl_window)
	{
		fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
		SDL_Quit();
		return -1;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,
		props?props->depth_buffer_size:24);
	renderer->sdl_glcontext = SDL_GL_CreateContext(renderer->sdl_window);
	SDL_GL_SetSwapInterval(1);
	renderer->sdl_renderer = SDL_CreateRenderer(renderer->sdl_window, -1,
			SDL_RENDERER_ACCELERATED);

	glClearColor(1.0f, 0.0f, 1.0f, 1.0f );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	gl_error = glGetError();
	if( gl_error != GL_NO_ERROR )
	{
		fprintf(stderr, "OpenGL Error\n");
		return -1;
	}
	//Initialize Modelview Matrix
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	strcpy(renderer->subsys.name, "renderer");
	renderer->subsys.init = _vge_renderer_gl_init;
	renderer->subsys.destroy = _vge_renderer_gl_destroy;
	renderer->subsys.on_frame = _vge_renderer_gl_on_frame;
	renderer->subsys.on_step = _vge_renderer_gl_on_step;

	vge_game_add_subsystem(game, &renderer->subsys);
	*subsys = &renderer->subsys;
	return 0;
}

