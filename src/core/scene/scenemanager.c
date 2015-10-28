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

#include "core/scene/scenemanager.h"
#include "core/scene/scene.h"
#include "core/scene/entity.h"
#include "core/scene/component.h"
#include "core/scene/componentloader.h"
#include "core/resource/resourcemanager.h"
#include "core/resource/resourceloader.h"
#include "core/game.h"
#include "external/nxjson/nxjson.h"

struct vge_scene_manager
{
	struct vge_subsystem subsys;
	struct vge_list entity_list;
	struct vge_scene *cur_scene;
	struct vge_resource_loader loader;
};

static void _destroy_scene(struct vge_scene *scene)
{
}

static void _init(struct vge_game *game,
		struct vge_subsystem *subsys)
{
}

static void _destroy(struct vge_game *game,
		struct vge_subsystem *subsys)
{
	struct vge_scene_manager *sman;
	sman = vge_container_of(subsys, struct vge_scene_manager, subsys);
	if(sman->cur_scene)
		_destroy_scene(sman->cur_scene);
	free(sman);
}

static void _on_step(struct vge_game *game,
		struct vge_subsystem *subsys)
{
	struct vge_scene_manager *sman;
	struct vge_scene *scene;
	struct vge_entity *entity;
	struct vge_list *tmp_node;
	struct vge_list *tmp2_node;
	struct vge_component *component;
	sman = vge_container_of(subsys, struct vge_scene_manager, subsys);
	scene = sman->cur_scene;
	if(scene) {
		vge_list_foreach(&scene->entity_list, struct vge_entity, ent_node,
				entity, tmp_node) {
			vge_list_foreach(&entity->component_list, struct vge_component, comp_node,
					component, tmp2_node) {
				component->loader->on_step(component, entity);
			}
		}
	}
}

static void _on_frame(struct vge_game *game,
		struct vge_subsystem *subsys)
{
	struct vge_scene_manager *sman;
	struct vge_scene *scene;
	struct vge_entity *entity;
	struct vge_list *tmp_node;
	struct vge_list *tmp2_node;
	struct vge_component *component;
	sman = vge_container_of(subsys, struct vge_scene_manager, subsys);
	scene = sman->cur_scene;
	if(scene) {
		vge_list_foreach(&scene->entity_list, struct vge_entity, ent_node,
				entity, tmp_node) {
			vge_list_foreach(&entity->component_list, struct vge_component, comp_node,
					component, tmp2_node) {
				component->loader->on_frame(component, entity);
			}
		}
	}
}

static struct vge_resource *_load_scene(struct vge_resource_loader *loader,
		const char *path)
{
	struct vge_scene_manager *sman;
	struct vge_scene *scene;
    const nx_json* json;
    const nx_json* elem;
    FILE* f;
    off_t flen;
    char* buf;
    f = fopen(path, "rb");
    fseeko(f, 0, SEEK_END);
    flen = ftello(f);
    buf = alloca(flen+1);
    fseeko(f, 0, SEEK_SET);
    fread(buf, flen, 1, f);
    json = nx_json_parse(buf, 0);
	sman = vge_container_of(loader, struct vge_scene_manager, loader);
	scene = malloc(sizeof(struct vge_scene));
	scene->resource.loader = loader;
	vge_list_init(&scene->entity_list);
	return &scene->resource;
}

static struct vge_resource *_clone_scene(struct vge_resource_loader *loader,
		struct vge_resource *old_scn)
{
	return NULL;
}

void _unload_scene(struct vge_resource_loader *loader,
		struct vge_resource *scn)
{
}

int vge_scene_manager_load_scene(struct vge_game *game,
		struct vge_subsystem *subsys, const char *name)
{
	struct vge_scene_manager *sman;
	struct vge_scene *scene;
	struct vge_resource *scene_res;
	sman = vge_container_of(subsys, struct vge_scene_manager, subsys);
	if(sman->cur_scene)
		_destroy_scene(sman->cur_scene);
	scene_res = vge_resource_manager_getresource(game->rman, name);
	if(!scene_res)
		return -1;
	sman->cur_scene = vge_container_of(scene_res, struct vge_scene, resource);
	return 0;
}

int vge_scene_manager_init(struct vge_game *game,
		struct vge_subsystem **subsys)
{
	struct vge_scene_manager *sman;
	sman = malloc(sizeof(struct vge_scene_manager));
	vge_list_init(&sman->entity_list);
	sman->cur_scene = NULL;
	strcpy(sman->subsys.name, "scene_manager");
	sman->subsys.init = _init;
	sman->subsys.destroy = _destroy;
	sman->subsys.on_step = _on_step;
	sman->subsys.on_frame = _on_frame;

	vge_game_add_subsystem(game, &sman->subsys);
	strcpy(sman->loader.name, "vgescn");
	sman->loader.load = _load_scene;
	sman->loader.clone = _clone_scene;
	sman->loader.unload = _unload_scene;
	*subsys = &sman->subsys;
	return 0;
}

