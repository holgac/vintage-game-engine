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
#ifndef __VGE_MATH_H
#define __VGE_MATH_H
#include "engine.h"

extern const vge_real_t vge_math_epsilon;
extern const vge_real_t vge_math_halfpi;
extern const vge_real_t vge_math_pi;
extern const vge_real_t vge_math_threehalfpi;
extern const vge_real_t vge_math_doublepi;
static inline vge_real_t vge_math_absr(vge_real_t r)
{
  return r>0?r:-r;
}
static inline int vge_math_equalsr(vge_real_t r1, vge_real_t r2)
{
  return vge_math_absr(r1-r2) < vge_math_epsilon;
}
/* TODO: trigonometry with tables */
#endif
