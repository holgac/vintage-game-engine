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
#ifndef _VGE_CONTAINER_H_
#include <vge.h>

struct vge_container_chunk
{
	struct vge_container_chunk* next;
	u32 size;
	u32 capacity;
	void* first_free;
	u8* data_table;
};

/*
	Regular memory container.
	Provides chunk based allocation for fixed size objects.
	Does NOT defragment the memory!
 */
struct vge_container
{
	u32 obj_size;
	u32 size;
	u32 capacity;
	struct vge_container_chunk* chunk;
};

int vge_container_init(struct vge_container* container, int obj_size);
void vge_container_destroy(struct vge_container* container);

void* vge_container_alloc(struct vge_container* container);
void vge_container_free(struct vge_container* container, void* ptr);


#endif /* _VGE_CONTAINER_H_ */
