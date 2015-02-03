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
#ifndef _VGE_SCENE_H_

struct vge_entity;
struct vge_game;
struct vge_scene
{
	struct vge_entity* entity;
};

int vge_scene_init(struct vge_scene* scene);

void vge_scene_on_frame(struct vge_scene* scene, struct vge_game* game);

void vge_scene_on_step(struct vge_scene* scene, struct vge_game* game);

void vge_scene_add_entity(struct vge_scene* scene, struct vge_entity* entity);
#endif /* _VGE_SCENE_H_ */
