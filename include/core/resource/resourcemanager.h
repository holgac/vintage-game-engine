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
#ifndef __VGE_RESOURCEMANAGER_H
#define __VGE_RESOURCEMANAGER_H

#include "engine.h"
#include "core/containers/rbtree.h"

struct vge_resource;
struct vge_game;
struct vge_resource_loader;

struct vge_resource_manager
{
  struct vge_rbtree resources;
  struct vge_rbtree resource_loaders;
};

void vge_resource_manager_init(struct vge_resource_manager *rman);
struct vge_resource *vge_resource_manager_get_resource(
    struct vge_resource_manager *rman, const char *name);
/*
 * After registering, loader belongs to the resource manager,
 * resource manager calls free.
 * TODO: loader should have destroy function with loader argument.
 */
void vge_resource_manager_register_loader(struct vge_resource_manager *rman,
    struct vge_resource_loader *loader);
void vge_resource_manager_load_recursive(struct vge_resource_manager *rman,
    struct vge_game *game, const char *path);
struct vge_resource *vge_resource_manager_load_resource(
    struct vge_resource_manager *rman, struct vge_game *game,
    const char *path);

#endif

