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
#include <stdlib.h>
#include <core/gamestate/gamestate.h>
#include <core/scene/scene.h>

int vge_game_state_init(struct vge_game_state* state)
{
	state->scene = malloc(sizeof(struct vge_scene));
	vge_scene_init(state->scene);
	state->onframe_cb = NULL;
	state->onstep_cb = NULL;
	state->init_cb = NULL;
	state->destroy_cb = NULL;
	return 0;
}
