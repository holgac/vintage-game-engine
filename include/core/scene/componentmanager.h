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
#ifndef __VGE_COMPONENT_MANAGER_H
#define __VGE_COMPONENT_MANAGER_H

#include "core/containers/list.h"
#include "core/resource/resource.h"

struct nx_json;
struct vge_component_loader;
struct vge_game;

struct vge_component_manager
{
  struct vge_rbtree loaders;
};
void vge_component_manager_init(struct vge_component_manager *cman);
void vge_component_manager_register_loader(
    struct vge_component_manager *cman, struct vge_component_loader *loader);
struct vge_component *vge_component_manager_load_component(
    struct vge_component_manager *cman, struct vge_game *game,
    const struct nx_json *json);
#endif



