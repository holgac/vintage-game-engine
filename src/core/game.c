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
#include "core/game.h"
#include "core/subsystem.h"
#include "core/scene/prefab.h"

int vge_game_init(struct vge_game *game)
{
	vge_list_init(&game->subsystems);
	SDL_Init(SDL_INIT_EVERYTHING);
	game->status = 0;
	vge_resource_manager_init(&game->rman);
	vge_resource_manager_register_loader(&game->rman, vge_prefab_get_loader());
	vge_component_manager_init(&game->cman);
	return 0;
}

int vge_game_add_subsystem(struct vge_game *game,
		struct vge_subsystem *subsys)
{
	vge_list_add(&game->subsystems, &subsys->subsys_list);
	subsys->init(game, subsys);
	return 0;
}

struct vge_subsystem *vge_game_get_subsystem(struct vge_game *game,
		const char *name)
{
	struct vge_list *inode;
	struct vge_subsystem *subsys;
	vge_list_foreach(&game->subsystems, struct vge_subsystem, subsys_list, subsys, inode) {
		if(strcmp(subsys->name, name) == 0)
			return subsys;
	}
	return NULL;
}

static void _vge_game_frame(struct vge_game *game)
{
	struct vge_list *inode;
	struct vge_subsystem *subsys;
	vge_list_foreach(&game->subsystems, struct vge_subsystem, subsys_list, subsys, inode) {
		subsys->on_frame(game, subsys);
	}
}
static void _vge_game_step(struct vge_game *game)
{
	struct vge_list *inode;
	struct vge_subsystem *subsys;
	vge_list_foreach(&game->subsystems, struct vge_subsystem, subsys_list, subsys, inode) {
		subsys->on_step(game, subsys);
	}
}

void vge_game_start(struct vge_game *game)
{
	struct vge_timed_counter fps_counter;
	vge_timer_init(&game->step_timer, 1.0f/60);
	vge_stopwatch_reset(&game->frame_watch);
	vge_stopwatch_reset(&game->step_watch);
	vge_timed_counter_init(&fps_counter, 3.0f);
	u32 tmp;
	
	while(!(game->status & VGE_GAME_STATUS_QUITTING)) {
		if(vge_timer_check(&game->step_timer)) {
			game->step_dt = vge_stopwatch_reset(&game->step_watch);
			_vge_game_step(game);
		}
		/*
		 * TODO: call it somewhere else
		 */
		SDL_PumpEvents();
		game->frame_dt = vge_stopwatch_reset(&game->frame_watch);
		_vge_game_frame(game);
		if((tmp = vge_timed_counter_increment(&fps_counter)))
			printf("FPS: %d\n", tmp/3);
	}
}

void vge_game_stop(struct vge_game *game)
{
	game->status |= VGE_GAME_STATUS_QUITTING;
}

void vge_game_destroy(struct vge_game *game)
{
	struct vge_subsystem *subsys;
	while(!(vge_list_empty(&game->subsystems))) {
		subsys = vge_list_first(&game->subsystems, struct vge_subsystem, subsys_list);
		vge_list_remove(&subsys->subsys_list);
		subsys->destroy(game, subsys);
	}
	SDL_Quit();
}
