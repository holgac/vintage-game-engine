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
#ifndef __VGE_SCENE_MANAGER_H
#define __VGE_SCENE_MANAGER_H

#include "core/containers/list.h"
#include "core/resource/resource.h"
#include "core/subsystem.h"

int vge_scene_manager_init(struct vge_game *game,
    struct vge_subsystem **subsys);
int vge_scene_manager_load_scene(struct vge_game *game,
    struct vge_subsystem *subsys, const char *scene_name);
struct vge_scene *vge_scene_manager_get_cur_scene(struct vge_subsystem *);
#endif
