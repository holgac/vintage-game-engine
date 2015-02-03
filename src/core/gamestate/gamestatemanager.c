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
#include <string.h>
#include <stdlib.h>
#include <core/gamestate/gamestate.h>
#include <core/gamestate/gamestatemanager.h>

int vge_game_state_manager_init(struct vge_game_state_manager* gsman)
{
	gsman->state = NULL;
	return 0;
}

void vge_game_state_manager_destroy(struct vge_game_state_manager* gsman)
{

}

int vge_game_state_manager_registerstate(struct vge_game_state_manager* gsman,
	struct vge_game_state* state)
{
	/*
		TODO: check for name conflicts
	 */
	state->next = gsman->state;
	gsman->state = state;
	return 0;
}

struct vge_game_state* vge_game_state_manager_getstate(
	struct vge_game_state_manager* gsman, const char* name)
{
	struct vge_game_state* state;
	state = gsman->state;
	while(state)
	{
		if(strcmp(name, state->name) == 0)
			return state;
		state = state->next;
	}
	return NULL;
}
