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
#include "engine.h"
#include "core/math/math.h"
#include "core/math/vector4.h"
#include "core/math/matrix4.h"

VGETEST matrix_identity()
{
  struct vge_matrix4 m1, m2, res;
  vge_matrix4_setm(&m1, &vge_matrix4_identity);
  vge_matrix4_setm(&m2, &vge_matrix4_identity);
  expect(vge_matrix4_equals(&m1, &m2), "Both should be identity");
  vge_matrix4_multm(&res, &m1, &m2);
  expect(vge_matrix4_equals(&res, &m2), "matrix identity^2 is still identity");
}

