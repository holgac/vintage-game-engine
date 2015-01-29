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
#ifndef _VGE_GAME_STATE_H_

struct vge_scene;
struct vge_game;

struct vge_game_state
{
	struct vge_scene* scene;
	void (*onframe_cb)(struct vge_game*);
	void (*onstep_cb)(struct vge_game*);
};

#endif /* _VGE_GAME_STATE_H_ */
