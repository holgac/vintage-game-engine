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
#include <stdio.h>
#include "core/math/math.h"
#include "core/math/vector4.h"
const struct vge_vector4 vge_vector4_x = { .coords = {1.0f, 0.0f, 0.0f, 0.0f} };
const struct vge_vector4 vge_vector4_y = { .coords = {0.0f, 1.0f, 0.0f, 0.0f} };
const struct vge_vector4 vge_vector4_z = { .coords = {0.0f, 0.0f, 1.0f, 0.0f} };
const struct vge_vector4 vge_vector4_t = { .coords = {0.0f, 0.0f, 0.0f, 1.0f} };

void vge_vector4_set(struct vge_vector4 *dst, float x, float y, float z)
{
  dst->x = x;
  dst->y = y;
  dst->z = z;
  dst->t = 0.0f;
}

void vge_vector4_read(struct vge_vector4 *src, const char *data)
{
  sscanf(data, "%f %f %f", &src->x, &src->y, &src->z);
  src->t = 0.0f;
}

int vge_vector4_equals(const struct vge_vector4 *lhs,
    const struct vge_vector4 *rhs)
{
  return vge_math_equalsr(lhs->x, rhs->x)
    && vge_math_equalsr(lhs->y, rhs->y)
    && vge_math_equalsr(lhs->z, rhs->z);
}

vge_real_t vge_vector4_dot(const struct vge_vector4 *lhs,
    const struct vge_vector4 *rhs)
{
  return lhs->x * rhs->x
    + lhs->y * rhs->y
    + lhs->z * rhs->z;
}

