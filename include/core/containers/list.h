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

#ifndef __VGE_LINKEDLIST_H
#define __VGE_LINKEDLIST_H
#include "engine.h"
/*
 * Circular linked list implementation, heavily influenced by linux kernel.
 * See; http://kernelnewbies.org/FAQ/LinkedLists
 * TODO: documentation
 */
struct vge_list {
  struct vge_list *next;
  struct vge_list *prev;
};
/*
 * init new node
 */
void vge_list_init(struct vge_list *src);
void vge_list_add(struct vge_list *src, struct vge_list *target);
void vge_list_remove(struct vge_list *target);
#define vge_list_first(src, type, member) vge_container_of(((src)->next), type, member)
#define vge_list_next(src, type, member) vge_container_of(((&((src)->member))->next), type, member)
#define vge_list_foreach(src, type, member, i, inode)\
  for(inode=(src)->next, i=vge_container_of(inode, type, member);\
      inode != (src);\
      inode = inode->next, i=vge_container_of(inode, type, member))
#define vge_list_empty(src) ((src)->next == (src))
u32 vge_list_count(struct vge_list *src);
#endif
