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
#ifndef _VGE_PREFAB_H_
#include "resource.h"
#include "../scene/transform.h"
struct vge_component;

struct vge_prefab
{
	struct vge_resource resource;
	struct vge_transform transform;
	/*
		TODO: rbtree
	 */
	struct vge_component* component;
};

struct vge_resource_loader;
struct vge_entity;
struct vge_game;

struct vge_resource_loader* vge_prefab_get_loader();
struct vge_entity* vge_prefab_create_entity(struct vge_prefab* prefab, struct vge_game* game);

#endif /* _VGE_PREFAB_H_ */
