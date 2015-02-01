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
#include <core/math/vertex.h>
#include <external/nxjson/nxjson.h>

int vge_vertex_read(struct vge_vertex* dst, const struct nx_json* json)
{
	const nx_json* elem;
	elem = nx_json_get(json, "position");
	if(elem)
		vge_vector2_read(&dst->position, elem->text_value);
	else
		vge_vector2_identity(&dst->position);
	elem = nx_json_get(json, "texcoord");
	if(elem)
		vge_vector2_read(&dst->texcoord, elem->text_value);
	else
		vge_vector2_identity(&dst->texcoord);
	elem = nx_json_get(json, "color");
	if(elem)
		vge_vector2_read(&dst->color, elem->text_value);
	else
		vge_vector2_set(&dst->color, 1.0f, 1.0f);
	return 0;

}
void vge_vertex_clone(struct vge_vertex* restrict dst,
	const struct vge_vertex* restrict src)
{
	vge_vector2_clone(&dst->position, &src->position);
	vge_vector2_clone(&dst->texcoord, &src->texcoord);
	vge_vector2_clone(&dst->color, &src->color);
}
