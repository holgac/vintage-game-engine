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

#include <math.h>
#include "core/math/math.h"
#include "core/math/vector4.h"
#include "core/math/quaternion.h"

const struct vge_quaternion vge_quaternion_identity = { .coords = { 1.0f, 0.0f, 0.0f, 0.0f}};

vge_real_t vge_quaternion_lengthsqr(const struct vge_quaternion *quat)
{
  return (quat->x*quat->x + quat->y*quat->y + quat->z*quat->z + quat->w*quat->w);
}
vge_real_t vge_quaternion_length(const struct vge_quaternion *quat)
{
  return sqrt(vge_quaternion_lengthsqr(quat));
}

void vge_quaternion_multq(struct vge_quaternion * restrict dst,
    const struct vge_quaternion *lhs,
    const struct vge_quaternion *rhs)
{
  dst->w = lhs->w*rhs->w - lhs->x*rhs->x - lhs->y*rhs->y - lhs->z*rhs->z;
  dst->x = lhs->w*rhs->x + lhs->x*rhs->w + lhs->y*rhs->z - lhs->z*rhs->y;
  dst->y = lhs->w*rhs->y - lhs->x*rhs->z + lhs->y*rhs->w + lhs->z*rhs->x;
  dst->z = lhs->w*rhs->z + lhs->x*rhs->y - lhs->y*rhs->x + lhs->z*rhs->w;
}

void vge_quaternion_construct(struct vge_quaternion *dst,
    const struct vge_vector4 *axis,
    vge_real_t angle)
{
  vge_real_t cosa, sina;
  cosa = cos(angle/2);
  sina = sin(angle/2);
  dst->w = cosa;
  dst->x = axis->x * sina;
  dst->y = axis->y * sina;
  dst->z = axis->z * sina;
}

void vge_quaternion_normalize(struct vge_quaternion *quat)
{
  vge_real_t invlen;
  invlen = vge_quaternion_length(quat);
  quat->w *= invlen;
  quat->x *= invlen;
  quat->y *= invlen;
  quat->z *= invlen;
}

void vge_quaternion_getangleaxis(const struct vge_quaternion *quat,
    struct vge_vector4 *axis, vge_real_t *angle)
{
  vge_real_t sqlen = quat->x * quat->x + quat->y * quat->y + quat->z * quat->z;
  vge_real_t inv;
  if(sqlen < vge_math_epsilon) {
    vge_vector4_set(axis, 1.0f, 0.0f, 0.0f);
    *angle = 0.0f;
  } else {
    *angle = 2 * acos(quat->w);
    inv = 1.0f / sqrt(sqlen);
    vge_vector4_set(axis, quat->x*inv, quat->y*inv, quat->z*inv);
  }
}
