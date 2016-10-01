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
#include "core/math/vector3.h"

void vge_vector3_set(struct vge_vector3 *src, float x, float y, float z)
{
  src->x = x;
  src->y = y;
  src->z = z;
}

void vge_vector3_read(struct vge_vector3 *src, const char *data)
{
  sscanf(data, "%f %f %f", &src->x, &src->y, &src->z);
}
