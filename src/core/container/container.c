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
#include <stdlib.h>
#include <core/container/container.h>

#define INITIAL_CAPACITY 8

static struct vge_container_chunk* _create_chunk(u32 size, u32 obj_size)
{
	u32 i;
	struct vge_container_chunk* ptr = malloc(sizeof(struct vge_container_chunk) + size*obj_size);
	ptr->size = 0;
	ptr->capacity = size;
	ptr->data_table = (u8*)ptr + sizeof(struct vge_container_chunk);
	ptr->first_free = ptr->data_table;
	for(i=0; i<size-1; ++i)
	{
		u64* p = (u64*)(ptr->data_table + i*obj_size);
		u64* n = (u64*)(ptr->data_table + (i+1)*obj_size);
		*p = (u64)n;
		n = NULL;
	}
	*(u64*)(ptr->data_table + i*obj_size) = (u64)NULL;
	ptr->next = NULL;
	return ptr;
}

static void* _alloc_from_chunk(struct vge_container_chunk* chunk, u32 obj_size)
{
	void* ptr = chunk->first_free;
	chunk->first_free = *(void**)(chunk->first_free);
	chunk->size += 1;
	return ptr;
}

struct vge_container_chunk* _get_free_chunk(struct vge_container* container)
{
	if(container->size == container->capacity)
	{
		struct vge_container_chunk* free_chunk = _create_chunk(container->capacity, container->obj_size);
		free_chunk->next = container->chunk;
		container->chunk = free_chunk;
		container->capacity *= 2;
		return free_chunk;
	}
	else
	{
		struct vge_container_chunk* free_chunk = container->chunk;
		while(free_chunk)
		{
			if(free_chunk->first_free != NULL)
				return free_chunk;
			free_chunk = free_chunk->next;
		}
	}
	/*
		Impossible condition here
	 */
	fprintf(stderr, "vge_container chunk corrupt\n");
	return NULL;
}

int vge_container_init(struct vge_container* container, int obj_size)
{
	if(obj_size < 4)
		obj_size = 4;
	container->obj_size = obj_size;
	container->size = 0;
	container->capacity = INITIAL_CAPACITY;
	container->chunk = _create_chunk(INITIAL_CAPACITY, obj_size);
	return container->chunk?0:-1;
}

void vge_container_destroy(struct vge_container* container)
{
	struct vge_container_chunk* chnk,* prev;
	chnk = container->chunk;
	while(chnk)
	{
		prev = chnk;
		chnk = chnk->next;
		free(prev);
	}
}
void* vge_container_alloc(struct vge_container* container)
{
	void* ptr;
	struct vge_container_chunk* free_chunk;
	free_chunk = _get_free_chunk(container);
	if(!free_chunk)
		return NULL;
	container->size += 1;
	ptr = _alloc_from_chunk(free_chunk, container->obj_size);
	return ptr;
}

void vge_container_free(struct vge_container* container, void* ptr)
{
	/*
		TODO: put chunk data just before ptr to avoid iterating all chunks
	 */
	struct vge_container_chunk* owner = container->chunk;
	struct vge_container_chunk* prev = NULL;
	while(owner)
	{
		u32 size = sizeof(struct vge_container_chunk) + owner->size * container->obj_size;
		if(ptr > (void*)owner && ptr < (void*)(owner + size))
		{
			*(void**)ptr = owner->first_free;
			owner->first_free = ptr;
			container->size -= 1;
			owner->size -= 1;
			if(owner->size == 0)
			{
				if(prev)
					prev->next = owner->next;
				else if(owner->next)
					container->chunk = owner->next;
				else
					return;
				container->capacity -= owner->capacity;
				free(owner);
			}
			return;
		}
		prev = owner;
		owner = owner->next;
	}
	fprintf(stderr, "vge_container_free on unknown memory\n");
}


