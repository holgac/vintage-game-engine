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
#ifndef __VGE_VECTOR4_H
#define __VGE_VECTOR4_H
#include "engine.h"

struct vge_vector4
{
  union {
    struct {
    vge_real_t x, y, z, t;
    };
    vge_real_t coords[4];
  };
};

void vge_vector4_set(struct vge_vector4 *src, float x, float y, float z);
void vge_vector4_read(struct vge_vector4 *src, const char *data);
int vge_vector4_equals(struct vge_vector4 *lhs, struct vge_vector4 *rhs);
extern const struct vge_vector4 vge_vector4_x;
extern const struct vge_vector4 vge_vector4_y;
extern const struct vge_vector4 vge_vector4_z;
extern const struct vge_vector4 vge_vector4_t;
#endif

