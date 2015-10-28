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
#include "core/containers/list.h"


void vge_list_init(struct vge_list *src)
{
	src->next = src->prev = src;
}
void vge_list_add(struct vge_list *src, struct vge_list *target)
{
	target->prev = src;
	target->next = src->next;
	src->next->prev = target;
	src->next = target;
}
void vge_list_remove(struct vge_list *target)
{
	target->prev->next = target->next;
	target->next->prev = target->prev;
}
u32 vge_list_count(struct vge_list *src)
{
	struct vge_list *nd = src;
	u32 cnt = 0;
	while((nd = nd->next) != src) ++cnt;
	return cnt;
}
