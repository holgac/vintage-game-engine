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
#ifndef _VGE_GAME_STATE_MANAGER_H_

struct vge_game_state;
struct vge_game_state_manager
{
	struct vge_game_state* state;
};

int vge_game_state_manager_init(struct vge_game_state_manager* gsman);
void vge_game_state_manager_destroy(struct vge_game_state_manager* gsman);
int vge_game_state_manager_registerstate(struct vge_game_state_manager* gsman,
	struct vge_game_state* state);
struct vge_game_state* vge_game_state_manager_getstate(
	struct vge_game_state_manager* gsman, const char* name);
#endif /* _VGE_GAME_STATE_H_ */
