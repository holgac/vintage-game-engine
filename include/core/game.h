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
#ifndef __VGE_GAME_H
#define __VGE_GAME_H

#include "core/containers/list.h"
#include "core/time/timer.h"

struct vge_subsystem;
struct vge_resource_manager;

#define VGE_GAME_STATUS_QUITTING 1

struct vge_game {
	struct vge_list subsystems;
	struct vge_timer step_timer;
	struct vge_stopwatch frame_watch;
	struct vge_stopwatch step_watch;
	float frame_dt;
	float step_dt;
	u32 status;
	struct vge_resource_manager *rman;
};

int vge_game_init(struct vge_game *game);
int vge_game_add_subsystem(struct vge_game *game,
		struct vge_subsystem *subsys);
struct vge_subsystem *vge_game_get_subsystem(struct vge_game *game,
		const char *name);
/*
 * Starts main game loop.
 * All functions before that should be called from the same thread
 */
void vge_game_start(struct vge_game *game);
void vge_game_stop(struct vge_game *game);
void vge_game_destroy(struct vge_game *game);
#endif
