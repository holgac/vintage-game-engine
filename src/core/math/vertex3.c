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

#include "core/math/vertex3.h"
#include "external/nxjson/nxjson.h"

void vge_vertex3_read(struct vge_vertex3 *src, const struct nx_json *json)
{
  const struct nx_json *elem;
  elem = nx_json_get(json, "position");
  if(!elem)
    vge_vector3_set(&src->position, 0, 0, 0);
  else
    vge_vector3_read(&src->position, elem->text_value);
  elem = nx_json_get(json, "texcoord");
  if(!elem)
    vge_vector2_set(&src->texcoord, 0, 0);
  else
    vge_vector2_read(&src->texcoord, elem->text_value);
}
