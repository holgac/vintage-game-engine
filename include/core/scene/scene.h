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
#ifndef __VGE_SCENE_H
#define __VGE_SCENE_H

#include "core/containers/list.h"
#include "core/resource/resource.h"

struct vge_scene_prefab
{
  struct vge_resource resource;
  char path[0];
};

struct vge_scene
{
  struct vge_scene_prefab *prefab;
  struct vge_list entity_list;
};
struct vge_resource_loader *vge_scene_prefab_get_loader();
struct vge_scene *vge_scene_from_prefab(struct vge_game *, struct vge_resource *);
#endif
