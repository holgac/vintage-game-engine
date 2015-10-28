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

	This implementation was inspired by/based on the rbtree implementation in
	Linux Kernel.
	Thanks to Rob Landley <rob@landley.net> for documentation,
		(C) 1999  Andrea Arcangeli <andrea@suse.de>
		(C) 2002  David Woodhouse <dwmw2@infradead.org>
		(C) 2012  Michel Lespinasse <walken@google.com>
		for implementation.
*/

#ifndef __VGE_RBTREE_H
#define __VGE_RBTREE_H
#include "engine.h"

struct vge_rbnode
{
	/*
		stores color in least significant bit, parent in other bits.
	 */
	unsigned long parent_color;
	struct vge_rbnode *left;
	struct vge_rbnode *right;
} __attribute__((aligned(sizeof(long))));

struct vge_rbtree
{
	struct vge_rbnode *root;
	int (*compare)(struct vge_rbnode *lhs, struct vge_rbnode *rhs);
};

int vge_rbtree_init(struct vge_rbtree *tree,
	int (*compare)(struct vge_rbnode *lhs, struct vge_rbnode *rhs));
int vge_rbtree_insert(struct vge_rbtree *tree, struct vge_rbnode *node);
struct vge_rbnode* vge_rbtree_find(struct vge_rbtree *tree,
		struct vge_rbnode *node);
struct vge_rbnode* vge_rbtree_find_match(struct vge_rbtree *tree,
		const void *obj,
		int (*compare)(struct vge_rbnode *lhs, const void *rhs));
void vge_rbtree_remove(struct vge_rbtree *tree, struct vge_rbnode *node);
struct vge_rbnode *vge_rbtree_first(struct vge_rbtree *tree);
struct vge_rbnode *vge_rbtree_next(struct vge_rbnode *node);
#define vge_rbtree_parent(nd) ((struct vge_rbnode *)((nd)->parent_color & ~3))

#endif
