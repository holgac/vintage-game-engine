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
#ifndef __VGE_MATRIX4_H
#define __VGE_MATRIX4_H
#include "engine.h"

struct vge_vector4;
struct vge_quaternion;

struct vge_matrix4
{
  vge_real_t m[16];
};

extern const struct vge_matrix4 vge_matrix4_identity;

#define vge_matrix4_setm(dst, src) memcpy(dst, src, sizeof(struct vge_matrix4))
void vge_matrix4_multm(struct vge_matrix4 * restrict dst,
    const struct vge_matrix4 *lhs,
    const struct vge_matrix4 *rhs);
int vge_matrix4_equals(const struct vge_matrix4 *lhs,
    const struct vge_matrix4 *rhs);
/* axis should be unit */
void vge_matrix4_rotation(struct vge_matrix4 *dst,
    const struct vge_vector4 *axis,
    vge_real_t angle);
void vge_matrix4_position(struct vge_matrix4 *dst,
    const struct vge_vector4 *pos);
void vge_matrix4_construct(struct vge_matrix4 *dst,
    const struct vge_quaternion *quat,
    const struct vge_vector4 *pos);
#endif


