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
}
