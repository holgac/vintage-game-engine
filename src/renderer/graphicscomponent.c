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
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <renderer/graphicscomponent.h>
#include <core/scene/entity.h>
#include <core/scene/componentmanager.h>
#include <core/game.h>
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
		++i;
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
	comp->component.loader = srccomp->loader;
	return (struct vge_component*)comp;
}
static void _unload_component(struct vge_component* comp)
{
	struct vge_graphicscomponent* gcomp = (struct vge_graphicscomponent*)comp;
	free(gcomp->vertices);
	free(gcomp);
}

static void _on_frame(struct vge_component* comp, struct vge_entity* entity, 
	struct vge_game* game)
{
	struct vge_graphicscomponent* gcomp = (struct vge_graphicscomponent*)comp;
	u32 i;
	glPushMatrix();
	// glTranslatef(entity->transform.position.x, 
	// 	entity->transform.position.y,
	// 	0);
	// glRotatef(entity->transform.rotation, 0.0f, 0.0f, 1.0f);
	glBegin(GL_TRIANGLE_FAN);
	for(i=0; i<gcomp->num_vertices; ++i)
	{
		struct vge_vertex* vertex = gcomp->vertices + i;
		glVertex2f(vertex->position.x,vertex->position.y);
	}
	glEnd();
	glPopMatrix();
}

struct vge_component_loader* vge_graphicscomponent_get_loader()
{
	struct vge_component_loader* loader;
	loader = malloc(sizeof(struct vge_component_loader));
	loader->load = _load_component;
	loader->clone = _clone_component;
	loader->unload = _unload_component;
	loader->on_frame = _on_frame;
	loader->on_step = NULL;
	strcpy(loader->name, "graphics_component");
	return loader;
}
