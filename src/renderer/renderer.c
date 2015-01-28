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
#include <unistd.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <renderer/renderer.h>
#include <core/game.h>


int vge_renderer_init(struct vge_renderer* renderer, struct vge_window_properties* window_properties)
{
	GLenum gl_error;

	renderer->sdl_window = SDL_CreateWindow(
		window_properties?window_properties->window_title:"vge test",
		window_properties?window_properties->pos_x:SDL_WINDOWPOS_CENTERED,
		window_properties?window_properties->pos_y:SDL_WINDOWPOS_CENTERED,
		window_properties?window_properties->width:640,
		window_properties?window_properties->height:640,
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if(!renderer->sdl_window)
	{
		fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
		SDL_Quit();
		return -1;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 
		window_properties?window_properties->depth_buffer_size:24);

	renderer->sdl_glcontext = SDL_GL_CreateContext(renderer->sdl_window);
	SDL_GL_SetSwapInterval(1);

	renderer->sdl_renderer = SDL_CreateRenderer(renderer->sdl_window, -1, SDL_RENDERER_ACCELERATED);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	gl_error = glGetError();
	if( gl_error != GL_NO_ERROR )
	{
		printf("ERROR ERROR");
		return -1;
	}

	//Initialize Modelview Matrix
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	return 0;
}

void vge_renderer_onframe(struct vge_renderer* renderer)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBegin( GL_QUADS );
	glVertex2f( -0.5f, -0.5f );
	glVertex2f( 0.5f, -0.5f );
	glVertex2f( 0.5f, 0.5f );
	glVertex2f( -0.5f, 0.5f );
	glEnd();
	SDL_GL_SwapWindow(renderer->sdl_window);
}

void vge_renderer_destroy(struct vge_renderer* renderer)
{
	SDL_GL_DeleteContext(renderer->sdl_glcontext);
	SDL_DestroyRenderer(renderer->sdl_renderer);
	SDL_DestroyWindow(renderer->sdl_window);
}

void vge_renderer_setclearcolor(struct vge_renderer* renderer, float r, float g, float b)
{
	glClearColor(r,g,b,1.0f);
}
