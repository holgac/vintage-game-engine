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
#include <core/scene/transform.h>
#include <external/nxjson/nxjson.h>

int vge_transform_read(struct vge_transform* dst, const struct nx_json* json)
{
	const nx_json* elem;
	elem = nx_json_get(json, "position");
	if(elem)
		vge_vector2_read(&dst->position, elem->text_value);
	else
		vge_vector2_identity(&dst->position);
	elem = nx_json_get(json, "rotation");
	if(elem)
		dst->rotation = (float)elem->dbl_value;
	else
		dst->rotation = 0.0f;
	/*
		TODO: return -1 if position or rotation types are not appropriate
	 */
	return 0;
}

void vge_transform_clone(struct vge_transform* restrict dst,
	const struct vge_transform* restrict src)
{
	vge_vector2_clone(&dst->position, &src->position);
	dst->rotation = src->rotation;
}
