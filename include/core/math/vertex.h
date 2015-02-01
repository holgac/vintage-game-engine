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
#ifndef _VGE_VERTEX_H_
#define _VGE_VERTEX_H_
#include "vector.h"

struct vge_vertex
{
	struct vge_vector2 position;
	struct vge_vector2 texcoord;
	struct vge_vector2 color;
};

struct nx_json;
int vge_vertex_read(struct vge_vertex* dst, const struct nx_json* json);
void vge_vertex_clone(struct vge_vertex* restrict dst,
	const struct vge_vertex* restrict src);

#endif /* _VGE_VERTEX_H_ */
