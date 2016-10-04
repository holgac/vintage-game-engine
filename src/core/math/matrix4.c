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
#include "core/math/matrix4.h"

const struct vge_matrix4 vge_matrix4_identity = { .m = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f }};

void vge_matrix4_multm(struct vge_matrix4 * restrict dst,
    const struct vge_matrix4 *lhs,
    const struct vge_matrix4 *rhs)
{
  dst->m[0] = lhs->m[0]*rhs->m[0] + lhs->m[1]*rhs->m[4] + lhs->m[2]*rhs->m[8] + lhs->m[3]*rhs->m[12];
  dst->m[1] = lhs->m[0]*rhs->m[1] + lhs->m[1]*rhs->m[5] + lhs->m[2]*rhs->m[9] + lhs->m[3]*rhs->m[13];
  dst->m[2] = lhs->m[0]*rhs->m[2] + lhs->m[1]*rhs->m[6] + lhs->m[2]*rhs->m[10] + lhs->m[3]*rhs->m[14];
  dst->m[3] = lhs->m[0]*rhs->m[3] + lhs->m[1]*rhs->m[7] + lhs->m[2]*rhs->m[11] + lhs->m[3]*rhs->m[15];
  dst->m[4] = lhs->m[4]*rhs->m[0] + lhs->m[5]*rhs->m[4] + lhs->m[6]*rhs->m[8] + lhs->m[7]*rhs->m[12];
  dst->m[5] = lhs->m[4]*rhs->m[1] + lhs->m[5]*rhs->m[5] + lhs->m[6]*rhs->m[9] + lhs->m[7]*rhs->m[13];
  dst->m[6] = lhs->m[4]*rhs->m[2] + lhs->m[5]*rhs->m[6] + lhs->m[6]*rhs->m[10] + lhs->m[7]*rhs->m[14];
  dst->m[7] = lhs->m[4]*rhs->m[3] + lhs->m[5]*rhs->m[7] + lhs->m[6]*rhs->m[11] + lhs->m[7]*rhs->m[15];
  dst->m[8] = lhs->m[8]*rhs->m[0] + lhs->m[9]*rhs->m[4] + lhs->m[10]*rhs->m[8] + lhs->m[11]*rhs->m[12];
  dst->m[9] = lhs->m[8]*rhs->m[1] + lhs->m[9]*rhs->m[5] + lhs->m[10]*rhs->m[9] + lhs->m[11]*rhs->m[13];
  dst->m[10] = lhs->m[8]*rhs->m[2] + lhs->m[9]*rhs->m[6] + lhs->m[10]*rhs->m[10] + lhs->m[11]*rhs->m[14];
  dst->m[11] = lhs->m[8]*rhs->m[3] + lhs->m[9]*rhs->m[7] + lhs->m[10]*rhs->m[11] + lhs->m[11]*rhs->m[15];
  dst->m[12] = lhs->m[12]*rhs->m[0] + lhs->m[13]*rhs->m[4] + lhs->m[14]*rhs->m[8] + lhs->m[15]*rhs->m[12];
  dst->m[13] = lhs->m[12]*rhs->m[1] + lhs->m[13]*rhs->m[5] + lhs->m[14]*rhs->m[9] + lhs->m[15]*rhs->m[13];
  dst->m[14] = lhs->m[12]*rhs->m[2] + lhs->m[13]*rhs->m[6] + lhs->m[14]*rhs->m[10] + lhs->m[15]*rhs->m[14];
  dst->m[15] = lhs->m[12]*rhs->m[3] + lhs->m[13]*rhs->m[7] + lhs->m[14]*rhs->m[11] + lhs->m[15]*rhs->m[15];
}

int vge_matrix4_equals(const struct vge_matrix4 *lhs,
    const struct vge_matrix4 *rhs)
{
  return vge_math_equalsr(lhs->m[0], rhs->m[0])
      && vge_math_equalsr(lhs->m[1], rhs->m[1])
      && vge_math_equalsr(lhs->m[2], rhs->m[2])
      && vge_math_equalsr(lhs->m[3], rhs->m[3])
      && vge_math_equalsr(lhs->m[4], rhs->m[4])
      && vge_math_equalsr(lhs->m[5], rhs->m[5])
      && vge_math_equalsr(lhs->m[6], rhs->m[6])
      && vge_math_equalsr(lhs->m[7], rhs->m[7])
      && vge_math_equalsr(lhs->m[8], rhs->m[8])
      && vge_math_equalsr(lhs->m[9], rhs->m[9])
      && vge_math_equalsr(lhs->m[10], rhs->m[10])
      && vge_math_equalsr(lhs->m[11], rhs->m[11])
      && vge_math_equalsr(lhs->m[12], rhs->m[12])
      && vge_math_equalsr(lhs->m[13], rhs->m[13])
      && vge_math_equalsr(lhs->m[14], rhs->m[14])
      && vge_math_equalsr(lhs->m[15], rhs->m[15]);
}

void vge_matrix4_rotation(struct vge_matrix4 *dst,
    const struct vge_vector4 *axis,
    vge_real_t angle)
{
  vge_real_t cosa, sina, onem;
  cosa = cos(angle);
  sina = sin(angle);
  /* TODO: floats all around makes vge_real_t less useful */
  onem = 1.0f - cosa;
  dst->m[0] = cosa + axis->x * axis->x * onem;
  dst->m[1] = axis->x * axis->y * onem - axis->z * sina;
  dst->m[2] = axis->x * axis->z * onem + axis->y * sina;
  dst->m[3] = 0.0f;
  dst->m[4] = axis->y * axis->x * onem + axis->z * sina;
  dst->m[5] = cosa + axis->y * axis->y * onem;
  dst->m[6] = axis->y * axis->z * onem - axis->x * sina;
  dst->m[7] = 0.0f;
  dst->m[8] = axis->z * axis->x * onem - axis->y * sina;
  dst->m[9] = axis->z * axis->y * onem + axis->x * sina;
  dst->m[10] = cosa + axis->z * axis->z * onem;
  dst->m[11] = 0.0f;
  dst->m[12] = 0.0f;
  dst->m[13] = 0.0f;
  dst->m[14] = 0.0f;
  dst->m[15] = 0.0f;
}

void vge_matrix4_position(struct vge_matrix4 *dst,
    const struct vge_vector4 *pos)
{
  dst->m[0] = 0.0f;
  dst->m[1] = 0.0f;
  dst->m[2] = 0.0f;
  dst->m[3] = 0.0f;
  dst->m[4] = 0.0f;
  dst->m[5] = 0.0f;
  dst->m[6] = 0.0f;
  dst->m[7] = 0.0f;
  dst->m[8] = 0.0f;
  dst->m[9] = 0.0f;
  dst->m[10] = 0.0f;
  dst->m[11] = 0.0f;
  dst->m[12] = pos->x;
  dst->m[13] = pos->y;
  dst->m[14] = pos->z;
  dst->m[15] = 0.0f;
}
/*
w2+x2-y2-z2 2xy-2wz 2xz+2wy 0
2xy+2wz w2-x2+y2-z2 2yz+2wx 0
2xz-2wy 2yz-2wx w2-x2-y2+z2 0
0 0 0 1
*/
void vge_matrix4_construct(struct vge_matrix4 *dst,
    const struct vge_quaternion *quat,
    const struct vge_vector4 *pos)
{
  dst->m[0] = 1.0f - 2*quat->y*quat->y - 2*quat->z*quat->z;
  dst->m[1] = 2*quat->x*quat->y + 2*quat->w*quat->z;
  dst->m[2] = 2*quat->x*quat->z - 2*quat->w*quat->y;
  dst->m[3] = 0.0f;
  dst->m[4] = 2*quat->x*quat->y - 2*quat->w*quat->z;
  dst->m[5] = 1.0f - 2*quat->x*quat->x - 2*quat->z*quat->z;
  dst->m[6] = 2*quat->y*quat->z + 2*quat->w*quat->x;
  dst->m[7] = 0.0f;
  dst->m[8] = 2*quat->x*quat->z + 2*quat->w*quat->y;
  dst->m[9] = 2*quat->y*quat->z - 2*quat->w*quat->x;
  dst->m[10] = 1.0f - 2*quat->x*quat->x - 2*quat->y*quat->y;
  dst->m[11] = 0.0f;
  dst->m[12] = pos->x;
  dst->m[13] = pos->y;
  dst->m[14] = pos->z;
  dst->m[15] = 1.0f;
}
