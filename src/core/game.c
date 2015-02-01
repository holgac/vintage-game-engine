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
#include <time.h>
#include <SDL2/SDL.h>
#include <core/game.h>
#include <core/gamestate/gamestate.h>
#include <core/resource/resourcemanager.h>
#include <core/resource/prefab.h>
#include <renderer/renderer.h>
#include <input/input.h>


int vge_game_init(struct vge_game* game, char** argv, char** envp, char* resourcedir, unsigned int flags)
{
	unsigned int sdl_init_flags = SDL_INIT_NOPARACHUTE;
	game->status = 0;
	game->state = NULL;
	game->step_frequency = 1.0f / 60.0f;
	if(flags & VGEGAME_INIT_INPUT)
	{
		if(!(flags & VGEGAME_INIT_RENDERER))
		{
			fprintf(stderr, "Cannot initialize input without renderer!\n");
			return -1;
		}
		game->input = malloc(sizeof(struct vge_input));
	}
	else
	{
		game->input = NULL;
	}
	if(flags & VGEGAME_INIT_RENDERER)
	{
		sdl_init_flags |= SDL_INIT_VIDEO;
		game->renderer = malloc(sizeof(struct vge_renderer));
	}
	else
	{
		game->renderer = NULL;
	}
	if (SDL_Init(sdl_init_flags) != 0)
	{
		fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
		if(game->renderer)
		{
			free(game->renderer);
			game->renderer = NULL;
		}
		if(game->input)
		{
			free(game->input);
			game->input = NULL;
		}
		return -1;
	}
	game->rman = malloc(sizeof(struct vge_resource_manager));
	vge_resource_manager_init(game->rman);
	vge_resource_manager_registerloader(game->rman, vge_prefab_get_loader());
	vge_resource_manager_loadrecursive(game->rman, resourcedir);
	return 0;
}

void vge_game_start(struct vge_game* game)
{
	vge_timer_update();
	vge_timer_init(&game->step_timer, game->step_frequency);
	while(!(game->status & VGEGAME_STATUS_QUITTING))
	{
		SDL_Event sdl_event;
		vge_timer_update();
		if(vge_timer_check(&game->step_timer, VGETIMER_REWIND))
		{
			game->state->onstep_cb(game);
		}
		game->state->onframe_cb(game);
		if(game->renderer)
		{
			vge_renderer_onframe(game->renderer);
		}
		if(game->input)
		{
			vge_input_onframe(game->input);
		}
		SDL_PumpEvents();
		while(SDL_PollEvent(&sdl_event))
		{
			switch(sdl_event.type)
			{
			case SDL_KEYDOWN:
				if(sdl_event.key.repeat == 0)
					vge_input_keyevent(game->input, sdl_event.key.keysym.sym, 1);
				break;
			case SDL_KEYUP:
				vge_input_keyevent(game->input, sdl_event.key.keysym.sym, 0);
				break;
			case SDL_QUIT:
				vge_game_stop(game);
				break;
			}
		}
	}
}

void vge_game_destroy(struct vge_game* game)
{
	if(game->renderer)
	{
		vge_renderer_destroy(game->renderer);
		game->renderer = NULL;
	}
	if(game->input)
	{
		vge_input_destroy(game->input);
		game->input = NULL;
	}
	SDL_Quit();
}
void vge_game_stop(struct vge_game* game)
{
	game->status |= VGEGAME_STATUS_QUITTING;
}
