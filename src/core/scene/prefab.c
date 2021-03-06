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

#include "core/containers/list.h"
#include "core/scene/prefab.h"
#include "core/scene/entity.h"
#include "core/scene/component.h"
#include "core/scene/componentloader.h"
#include "core/game.h"
#include "core/scene/componentmanager.h"
#include "core/resource/resourceloader.h"
#include "external/nxjson/nxjson.h"
#include "core/log/logger.h"

/* TODO: maybe lazy conversion to entity? */
struct vge_prefab
{
  struct vge_resource resource;
  struct vge_list component_list;
};

static struct vge_prefab *_load_single(struct vge_resource_loader *loader,
    struct vge_game *game, const struct nx_json *json)
{
  struct vge_prefab *prefab;
  const struct nx_json *elem;
  struct vge_component *comp;
  u32 i;
  prefab = malloc(sizeof(struct vge_prefab));
  vge_list_init(&prefab->component_list);

  prefab->resource.loader = loader;
  elem = nx_json_get(json, "name");
  /* TODO: free */
  if(!elem || (elem->type != NX_JSON_STRING))
    vge_log_and_return(NULL, "Name invalid in prefab");
  strcpy(prefab->resource.name, elem->text_value);
  elem = nx_json_get(json, "components");
  if(elem) {
    for(i=0; i<elem->length; ++i) {
      comp = vge_component_manager_load_component(&game->cman, game,
          nx_json_item(elem, i));
      vge_list_add(&prefab->component_list, &comp->comp_node);
    }
  }
  return prefab;
}

static struct vge_resource *_load_prefab(struct vge_resource_loader *loader,
    struct vge_game *game, const char *path)
{
  const struct nx_json *json;
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
  if(json->type != NX_JSON_OBJECT)
    vge_log_and_return(NULL, "Prefab file is invalid: %s", path);
  return &_load_single(loader, game, json)->resource;
}

static struct vge_resource *_clone_prefab(struct vge_resource_loader *loader,
    struct vge_resource *old_res)
{
  return NULL;
}

static void _unload_prefab(struct vge_resource_loader *loader,
    struct vge_resource *scn)
{
}

struct vge_resource_loader *vge_prefab_get_loader()
{
  struct vge_resource_loader *loader;
  loader = malloc(sizeof(struct vge_resource_loader));
  loader->load = _load_prefab;
  loader->clone = _clone_prefab;
  loader->unload = _unload_prefab;
  strcpy(loader->name, "prefab");
  return loader;
}

struct vge_entity *vge_prefab_create_entity(struct vge_resource *res)
{
  struct vge_prefab *prefab;
  struct vge_entity *entity;
  struct vge_list *tmp_node;
  struct vge_component *compi;
  struct vge_component *new_comp;
  prefab = vge_container_of(res, struct vge_prefab, resource);
  entity = malloc(sizeof(struct vge_entity));
  vge_list_init(&entity->ent_node);
  vge_list_init(&entity->component_list);
  vge_list_foreach(&prefab->component_list, struct vge_component, comp_node, compi, tmp_node) {
    new_comp = compi->loader->clone(compi->loader, compi);
    vge_list_add(&entity->component_list, &new_comp->comp_node);
  }
  entity->prefab = prefab;
  return entity;
}
