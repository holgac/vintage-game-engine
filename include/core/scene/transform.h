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
#ifndef _VGE_TRANSFORM_H_
#define _VGE_TRANSFORM_H_

#include "../math/vector.h"

struct vge_transform
{
	struct vge_vector2 position;
	float rotation;
};
struct nx_json;
int vge_transform_read(struct vge_transform* dst, const struct nx_json* json);
void vge_transform_clone(struct vge_transform* restrict dst,
	const struct vge_transform* restrict src);
#endif /* _VGE_TRANSFORM_H_ */
