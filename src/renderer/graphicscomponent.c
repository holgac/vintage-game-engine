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
#include <string.h>
#include <renderer/graphicscomponent.h>
#include <core/scene/componentmanager.h>
#include <external/nxjson/nxjson.h>

static struct vge_component* _load_component(const struct nx_json* json)
{
	const nx_json* elem;
	const nx_json* velem;
	u32 i;
	struct vge_graphicscomponent* comp;
	elem = nx_json_get(json, "vertices");
	/* TODO: error logging */
	if(!elem)
		return NULL;
	comp = malloc(sizeof(struct vge_graphicscomponent));
	comp->num_vertices = (u32)elem->length;
	comp->vertices = malloc(comp->num_vertices * sizeof(struct vge_vertex));
	velem = elem->child;
	i = 0;
	while(velem)
	{
		vge_vertex_read(comp->vertices + i, velem);
		velem = velem->next;
	}
	return (struct vge_component*)comp;
}

static struct vge_component* _clone_component(struct vge_component* srccomp,
	struct vge_component_manager* cman)
{
	u32 i;
	struct vge_graphicscomponent* comp;
	struct vge_graphicscomponent* src = (struct vge_graphicscomponent*)srccomp;
	comp = malloc(sizeof(struct vge_graphicscomponent));
	comp->num_vertices = src->num_vertices;
	comp->vertices = malloc(comp->num_vertices * sizeof(struct vge_vertex));
	for(i=0; i<comp->num_vertices; ++i)
	{
		vge_vertex_clone(comp->vertices + i, src->vertices + i);
	}
	return (struct vge_component*)comp;
}
static void _unload_component(struct vge_component* comp)
{
	struct vge_graphicscomponent* gcomp = (struct vge_graphicscomponent*)comp;
	free(gcomp->vertices);
	free(gcomp);
}

struct vge_component_loader* vge_graphicscomponent_get_loader()
{
	struct vge_component_loader* loader;
	loader = malloc(sizeof(struct vge_component_loader));
	loader->load = _load_component;
	loader->clone = _clone_component;
	loader->unload = _unload_component;
	strcpy(loader->name, "graphics_component");
	return loader;
}
