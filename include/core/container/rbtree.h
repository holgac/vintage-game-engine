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

	This implementation was inspired by the implementation in Linux Kernel 3.18.1
	Thanks to Rob Landley <rob@landley.net> for documentation,
		(C) 1999  Andrea Arcangeli <andrea@suse.de>
		(C) 2002  David Woodhouse <dwmw2@infradead.org>
		(C) 2012  Michel Lespinasse <walken@google.com>
		for implementation.
*/

#ifndef _VGE_RBTREE_H_
#include <vge.h>

struct vge_rbnode
{
	/*
		stores color in least significant bit, parent in other bits.
	 */
	unsigned long parent_color;
	struct vge_rbnode* left;
	struct vge_rbnode* right;
} __attribute__((aligned(sizeof(long))));

struct vge_rbtree
{
	struct vge_rbnode* root;
	int (*compare)(void* lhs, void* rhs);
};

int vge_rbtree_init(struct vge_rbtree* tree,
	int (*compare)(void* lhs, void* rhs));
int vge_rbtree_insert(struct vge_rbtree* tree, struct vge_rbnode* node);

#endif /* _VGE_RBTREE_H_ */
