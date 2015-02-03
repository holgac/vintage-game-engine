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
#ifndef _VGE_COMPONENT_MANAGER_H_

#define VGECOMPONENT_NAME_MAX 32

struct vge_component;
struct vge_component_manager;
struct nx_json;
struct vge_game;
struct vge_entity;

struct vge_component_loader
{
	char name[VGECOMPONENT_NAME_MAX];
	/*
		TODO: implement as rbtree
	 */
	struct vge_component_loader* next;
	struct vge_component* (*load)(const struct nx_json* json);
	struct vge_component* (*clone)(struct vge_component* comp,
		struct vge_component_manager* cman);
	void (*unload)(struct vge_component* comp);
	void (*on_frame)(struct vge_component* comp, struct vge_entity* entity,
		struct vge_game* game);
	void (*on_step)(struct vge_component* comp, struct vge_entity* entity,
		struct vge_game* game);
};

struct vge_component_manager
{
	struct vge_component_loader* loader;
};

int vge_component_manager_init(struct vge_component_manager* cman);
void vge_component_manager_destroy(struct vge_component_manager* cman);


struct vge_component* vge_component_manager_loadcomponent(
	struct vge_component_manager* cman, const struct nx_json* json);
void vge_component_manager_registerloader(struct vge_component_manager* cman,
										struct vge_component_loader* loader);

#endif /* _VGE_COMPONENT_MANAGER_H_ */
