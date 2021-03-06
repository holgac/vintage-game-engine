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
#ifndef __VGE_RESOURCE_H
#define __VGE_RESOURCE_H

#include "engine.h"
#include "core/containers/rbtree.h"

#define VGE_RESOURCE_NAME_MAX 64

struct vge_resouce_loader;
struct vge_resource
{
  struct vge_rbnode res_node;
  char name[VGE_RESOURCE_NAME_MAX];
  struct vge_resource_loader *loader;
};

#endif
