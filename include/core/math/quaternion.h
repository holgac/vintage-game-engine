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
#ifndef __VGE_QUATERNION_H
#define __VGE_QUATERNION_H
#include "engine.h"

struct vge_vector4;

struct vge_quaternion
{
  union {
    struct {
    vge_real_t w, x, y, z;
    };
    vge_real_t coords[4];
  };
};

extern const struct vge_quaternion vge_quaternion_identity;

vge_real_t vge_quaternion_lengthsqr(const struct vge_quaternion *quat);
vge_real_t vge_quaternion_length(const struct vge_quaternion *quat);
void vge_quaternion_multq(struct vge_quaternion * restrict dst,
    const struct vge_quaternion *lhs,
    const struct vge_quaternion *rhs);
void vge_quaternion_construct(struct vge_quaternion *dst,
    const struct vge_vector4 *axis, vge_real_t angle);
void vge_quaternion_getangleaxis(const struct vge_quaternion *quat,
    struct vge_vector4 *axis, vge_real_t *angle);
void vge_quaternion_normalize(struct vge_quaternion *quat);
#define vge_quaternion_setq(dst, src) memcpy((dst), (src), sizeof(struct vge_quaternion))
#endif


