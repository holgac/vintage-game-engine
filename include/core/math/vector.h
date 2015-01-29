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
#ifndef _VGE_VECTOR_H_

struct vge_vector2
{
	float x, y;
};
/*
	TODO: Documentation
	TODO: inline
 */
void vge_vector2_identity(struct vge_vector2* dst);
void vge_vector2_clone(struct vge_vector2* restrict dst, 
	struct vge_vector2* restrict src);
void vge_vector2_addv(struct vge_vector2* restrict dst, 
	struct vge_vector2* restrict src);
void vge_vector2_adds(struct vge_vector2* dst, float scalar);
void vge_vector2_muls(struct vge_vector2* dst, float scalar);
float vge_vector2_cross(struct vge_vector2* restrict v1,
	struct vge_vector2* restrict v2);
float vge_vector2_dot(struct vge_vector2* restrict v1,
	struct vge_vector2* restrict v2);
float vge_vector2_lensqr(struct vge_vector2* v);
float vge_vector2_len(struct vge_vector2* v);
float vge_vector2_normalize(struct vge_vector2* v);
float vge_vector2_normalized(struct vge_vector2* restrict dst,
	struct vge_vector2* restrict v);

#endif /* _VGE_VECTOR_H_ */
