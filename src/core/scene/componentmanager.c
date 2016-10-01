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
#include "core/scene/componentmanager.h"
#include "core/scene/componentloader.h"
#include "external/nxjson/nxjson.h"
#include "core/log/logger.h"

static int _component_loader_compare(struct vge_rbnode *lhs, struct vge_rbnode *rhs)
{
  struct vge_component_loader *l, *r;
  l = vge_container_of(lhs, struct vge_component_loader, res_node);
  r = vge_container_of(rhs, struct vge_component_loader, res_node);
  return strcmp(l->name, r->name);
}

static int _component_loader_match(struct vge_rbnode *lhs, const void *rhs)
{
  struct vge_component_loader *l;
  l = vge_container_of(lhs, struct vge_component_loader, res_node);
  return strcmp(l->name, rhs);
}


void vge_component_manager_init(struct vge_component_manager *cman)
{
  vge_rbtree_init(&cman->loaders, _component_loader_compare);
}

struct vge_component *vge_component_manager_load_component(
    struct vge_component_manager *cman, struct vge_game *game,
    const struct nx_json *json)
{
  struct vge_rbnode *node;
  struct vge_component_loader *loader;
  const struct nx_json *elem;
  elem = nx_json_get(json, "type");
  if(!elem)
    vge_log_and_return(NULL, "Components in json should specify type");
  node = vge_rbtree_find_match(&cman->loaders, elem->text_value, 
      _component_loader_match);
  if(!node)
    vge_log_and_return(NULL, "Cannot load component %s", elem->text_value);
  loader = vge_container_of(node, struct vge_component_loader, res_node);
  return loader->load(loader, game, json);
}

void vge_component_manager_register_loader(
    struct vge_component_manager *cman, struct vge_component_loader *loader)
{
  vge_rbtree_insert(&cman->loaders, &loader->res_node);
}


