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
#include <core/scene/component.h>
#include <core/scene/componentmanager.h>
#include <core/scene/entity.h>
#include <core/scene/scene.h>

// struct vge_entity;
// struct vge_scene
// {
// 	struct vge_entity* entity;
// };

int vge_scene_init(struct vge_scene* scene)
{
	scene->entity = NULL;
	return 0;
}
void vge_scene_add_entity(struct vge_scene* scene, struct vge_entity* entity)
{
	entity->next = scene->entity;
	scene->entity = entity;
}

void vge_scene_on_frame(struct vge_scene* scene, struct vge_game* game)
{
	struct vge_entity* ent;
	ent = scene->entity;
	while(ent)
	{
		struct vge_component* comp;
		comp = ent->component;
		while(comp)
		{
			if(comp->loader->on_frame)
				comp->loader->on_frame(comp, ent, game);
			comp = comp->next;
		}
		ent = ent->next;
	}
}

void vge_scene_on_step(struct vge_scene* scene, struct vge_game* game)
{
	struct vge_entity* ent;
	ent = scene->entity;
	while(ent)
	{
		struct vge_component* comp;
		comp = ent->component;
		while(comp)
		{
			if(comp->loader->on_step)
				comp->loader->on_step(comp, ent, game);
			comp = comp->next;
		}
		ent = ent->next;
	}
}
