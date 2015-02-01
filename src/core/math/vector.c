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
#include <math.h>
#include <stdio.h>
#include <core/math/vector.h>

void vge_vector2_set(struct vge_vector2* dst, float x, float y)
{
	dst->x = x;
	dst->y = y;
}

void vge_vector2_identity(struct vge_vector2* dst)
{
	dst->x = dst->y = 0;
}
void vge_vector2_clone(struct vge_vector2* restrict dst, 
	const struct vge_vector2* restrict src)
{
	dst->x = src->x;
	dst->y = src->y;
}
void vge_vector2_addv(struct vge_vector2* restrict dst, 
	const struct vge_vector2* restrict src)
{
	dst->x += src->x;
	dst->y += src->y;
}
void vge_vector2_adds(struct vge_vector2* dst, float scalar)
{
	dst->x += scalar;
	dst->y += scalar;
}
void vge_vector2_muls(struct vge_vector2* dst, float scalar)
{
	dst->x *= scalar;
	dst->y *= scalar;
}
float vge_vector2_cross(const struct vge_vector2* restrict v1,
	const struct vge_vector2* restrict v2)
{
	return v1->x * v2->y + v1->y * v2->x;
}
float vge_vector2_dot(const struct vge_vector2* restrict v1,
	const struct vge_vector2* restrict v2)
{
	return v1->x * v2->x + v1->y * v2->y;
}
float vge_vector2_lensqr(const struct vge_vector2* v)
{
	return v->x * v->x + v->y * v->y;
}
float vge_vector2_len(const struct vge_vector2* v)
{
	return sqrtf(vge_vector2_lensqr(v));
}
float vge_vector2_normalize(struct vge_vector2* v)
{
	float len = vge_vector2_len(v);
	float invlen = 1.0f / len;
	v->x *= invlen;
	v->y *= invlen;
	return len;
}
float vge_vector2_normalized(struct vge_vector2* restrict dst,
	const struct vge_vector2* restrict src)
{
	vge_vector2_clone(dst, src);
	return vge_vector2_normalize(dst);
}

int vge_vector2_read(struct vge_vector2* dst, const char* data)
{
	sscanf(data, "%f %f", &dst->x, &dst->y);
	/*
		TODO: error checking
	 */
	return 0;
}
