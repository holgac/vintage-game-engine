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
#ifndef __VGE_COMPONENT_LOADER_H
#define __VGE_COMPONENT_LOADER_H

#include "engine.h"
#include "core/containers/rbtree.h"

#define VGE_COMPONENT_LOADER_NAME_MAX 32

struct vge_component;
struct vge_entity;
struct nx_json;

struct vge_component_loader
{
	/* TODO: naming */
	struct vge_rbnode res_node;
	char name[VGE_COMPONENT_LOADER_NAME_MAX];
	struct vge_component* (*load)(struct vge_component_loader *loader,
			const struct nx_json* json);
	struct vge_component* (*clone)(struct vge_component_loader *loader,
			struct vge_component *comp);
	void (*unload)(struct vge_component_loader *loader,
			struct vge_component *comp);
	// TODO: should we pass vge_game?
	void (*on_frame)(struct vge_component *comp, struct vge_entity *ent);
	void (*on_step)(struct vge_component *comp, struct vge_entity *ent);
};


#endif
