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
#include <assert.h>
#include <time.h>
#include "engine.h"
#include "core/math/math.h"
#include "core/math/vector4.h"

VGETEST vector4_set_and_equals()
{
  struct vge_vector4 v1, v2;
  srand(time(NULL));
  v2.x = 1.23f;
  v2.y = 4.56f;
  v2.z = 7.89f;
  v2.t = rand() * 0.00001f;
  vge_vector4_set(&v1, 1.23f, 4.56f, 7.89f);
  expect(vge_vector4_equals(&v1, &v2), "vector4 set should work");
  vge_vector4_read(&v1, "1.23 4.56 7.89");
  expect(vge_vector4_equals(&v1, &v2), "vector4 read should work");
  vge_vector4_read(&v1, "0.23 4.56 7.89");
  expect(!vge_vector4_equals(&v1, &v2), "vector4 read should work");
  vge_vector4_setv(&v1, &v2);
  expect(vge_vector4_equals(&v1, &v2), "vector4 set should work");
}

VGETEST vector4_consts()
{
  struct vge_vector4 v;
  vge_vector4_set(&v, 1.0f, 0.0f, 0.0f);
  expect(vge_vector4_equals(&v, &vge_vector4_x),
        "vge_vector4_x is not unit x vector");
  vge_vector4_set(&v, 0.0f, 1.0f, 0.0f);
  expect(vge_vector4_equals(&v, &vge_vector4_y),
      "vge_vector4_y is not unit y vector");
  vge_vector4_set(&v, 0.0f, 0.0f, 1.0f);
  expect(vge_vector4_equals(&v, &vge_vector4_z),
      "vge_vector4_z is not unit t vector");
  vge_vector4_set(&v, 0.0f, 0.0f, 0.0f);
  v.t = 1234.5678f;
  expect(vge_vector4_equals(&v, &vge_vector4_t),
      "vge_vector4_t is not unit t vector or vector equals also checks t");
}

VGETEST vector4_dot()
{
  struct vge_vector4 v1, v2;
  expect(vge_math_equalsr(vge_vector4_dot(&vge_vector4_x, &vge_vector4_y), 0.0f),
      "x and y should be orthogonal");
  expect(vge_math_equalsr(vge_vector4_dot(&vge_vector4_x, &vge_vector4_z), 0.0f),
      "x and z should be orthogonal");
  expect(vge_math_equalsr(vge_vector4_dot(&vge_vector4_y, &vge_vector4_z), 0.0f),
      "y and z should be orthogonal");
  vge_vector4_set(&v1, 1.0f, 3.0f, -5.0f);
  vge_vector4_set(&v2, 4.0f, -2.0f, -1.0f);
  expect(vge_math_equalsr(vge_vector4_dot(&v1, &v2), 3.0f),
      "dot should work");

}
