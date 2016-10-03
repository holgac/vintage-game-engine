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
#include "core/scene/prefab.h"
#include "core/scene/entity.h"
#include "core/resource/resourceloader.h"
#include "core/game.h"
#include "external/nxjson/nxjson.h"
#include "core/log/logger.h"

static struct vge_resource *_load_scene_prefab(struct vge_resource_loader *loader,
    struct vge_game *game, const char *path)
{
  struct vge_scene_prefab *scene_prefab;
  const nx_json* json;
  const nx_json* elem;
  FILE* f;
  off_t flen;
  u32 pathlen;
  char* buf;
  f = fopen(path, "rb");
  fseeko(f, 0, SEEK_END);
  flen = ftello(f);
  buf = alloca(flen+1);
  fseeko(f, 0, SEEK_SET);
  fread(buf, flen, 1, f);
  fclose(f);
  json = nx_json_parse(buf, 0);
  pathlen = strlen(path);
  scene_prefab = malloc(sizeof(struct vge_scene_prefab) + pathlen + 1);
  scene_prefab->resource.loader = loader;
  elem = nx_json_get(json, "name");
  if(!elem || (elem->type != NX_JSON_STRING))
    vge_log_and_goto(free_scene_prefab, "Name invalid in scene");
  strcpy(scene_prefab->resource.name, elem->text_value);
  strcpy(scene_prefab->path, path);
  scene_prefab->path[pathlen] = 0;
  return &scene_prefab->resource;
free_scene_prefab:
  free(scene_prefab);
  return NULL;
}

static struct vge_resource *_clone_scene_prefab(struct vge_resource_loader *loader,
    struct vge_resource *old_scn)
{
  return NULL;
}

static void _unload_scene_prefab(struct vge_resource_loader *loader,
    struct vge_resource *scn)
{
}

/* TODO: move to somewhere else */
static struct vge_entity *_load_entity(struct vge_game *game, const nx_json *json)
{
  const nx_json* elem;
  struct vge_entity *entity;
  struct vge_resource *prefab;
  elem = nx_json_get(json, "prefab");
  prefab = vge_resource_manager_get_resource(&game->rman, elem->text_value);
  entity = vge_prefab_create_entity(prefab);
  elem = nx_json_get(json, "name");
  strcpy(entity->name, elem->text_value);
  elem = nx_json_get(json, "position");
  vge_vector4_read(&entity->position, elem->text_value);
  vge_matrix4_setm(&entity->rotation, &vge_matrix4_identity);
  return entity;
}

static int _compare_entities(struct vge_rbnode *lhs, struct vge_rbnode *rhs)
{
  struct vge_entity *l, *r;
  l = vge_container_of(lhs, struct vge_entity, ent_node_by_name);
  r = vge_container_of(rhs, struct vge_entity, ent_node_by_name);
  return strcmp(l->name, r->name);
}

static int _compare_entity_string(struct vge_rbnode *lhs, const void *rhs)
{
  struct vge_entity *l;
  const char *r;
  l = vge_container_of(lhs, struct vge_entity, ent_node_by_name);
  r = rhs;
  return strcmp(l->name, r);
}

struct vge_entity *vge_scene_get_entity(struct vge_scene *scene, const char *name)
{
  struct vge_rbnode *node;
  node = vge_rbtree_find_match(&scene->entity_tree_by_name, name, _compare_entity_string);
  if(!node)
    return NULL;
  return vge_container_of(node, struct vge_entity, ent_node_by_name);
}

static struct vge_scene *_load_scene(struct vge_game *game, const char *path)
{
  struct vge_scene *scene;
  struct vge_entity *entity;
  const nx_json* json;
  const nx_json* elem;
  FILE* f;
  off_t flen;
  char* buf;
  u32 i;
  int res;
  f = fopen(path, "rb");
  fseeko(f, 0, SEEK_END);
  flen = ftello(f);
  buf = alloca(flen+1);
  fseeko(f, 0, SEEK_SET);
  fread(buf, flen, 1, f);
  fclose(f);
  json = nx_json_parse(buf, 0);
  scene = malloc(sizeof(struct vge_scene));
  vge_list_init(&scene->entity_list);
  vge_rbtree_init(&scene->entity_tree_by_name, _compare_entities);
  elem = nx_json_get(json, "entities");
  if(elem) {
    for(i=0; i<elem->length; ++i) {
      entity = _load_entity(game, nx_json_item(elem, i));
      vge_list_add(&scene->entity_list, &entity->ent_node);
      res = vge_rbtree_insert(&scene->entity_tree_by_name,
          &entity->ent_node_by_name);
      if(res!=0)
        vge_log("Duplicate entity name: %s. An entity search with this name "
            "will give the first entity only", entity->name);
    }
  }
  return scene;
}

struct vge_resource_loader *vge_scene_prefab_get_loader()
{
  struct vge_resource_loader *loader;
  loader = malloc(sizeof(struct vge_resource_loader));
  loader->load = _load_scene_prefab;
  loader->clone = _clone_scene_prefab;
  loader->unload = _unload_scene_prefab;
  strcpy(loader->name, "vgescn");
  return loader;
}

struct vge_scene *vge_scene_from_prefab(struct vge_game *game, struct vge_resource *resource)
{
  struct vge_scene_prefab *prefab;
  prefab = vge_container_of(resource, struct vge_scene_prefab, resource);
  return _load_scene(game, prefab->path);
}

