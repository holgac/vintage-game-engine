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
	Linux Kernel 3.18.1.
	Thanks to Rob Landley <rob@landley.net> for documentation,
		(C) 1999  Andrea Arcangeli <andrea@suse.de>
		(C) 2002  David Woodhouse <dwmw2@infradead.org>
		(C) 2012  Michel Lespinasse <walken@google.com>
		for implementation.
*/

#include <stdlib.h>
#include <core/container/rbtree.h>

#define CLR_RED 0
#define CLR_BLACK 1

#define CLR(pc) ((pc) & 1)
#define CLR_IS_BLACK(pc) CLR(pc)
#define CLR_IS_RED(pc) (!CLR(pc))
#define IS_BLACK(nd) (CLR_IS_BLACK((nd)->parent_color))
#define IS_RED(nd) (CLR_IS_RED((nd)->parent_color))
#define PARENT(nd) ((struct vge_rbnode*)((nd)->parent_color & ~3))
#define RED_PARENT(nd) ((struct vge_rbnode*)(nd)->parent_color)

/*
	Sets parent and color of vge_rbnode
 */
static inline void _set_parent_color(struct vge_rbnode* node,
					   struct vge_rbnode* parent, int color)
{
	node->parent_color = (unsigned long)parent | color;
}

static inline void
_change_child(struct vge_rbnode* old, struct vge_rbnode* new,
		  struct vge_rbnode* parent, struct vge_rbtree* tree)
{
	if (parent) {
		if (parent->left == old)
			parent->left = new;
		else
			parent->right = new;
	} else
		tree->root = new;
}

/*
 * Helper function for rotations:
 * - old's parent and color get assigned to new
 * - old gets assigned new as a parent and 'color' as a color.
 */
static inline void
_rotate_set_parents(struct vge_rbnode* old, struct vge_rbnode* new,
			struct vge_rbtree* tree, int color)
{
	struct vge_rbnode* parent = PARENT(old);
	new->parent_color = old->parent_color;
	_set_parent_color(old, new, color);
	_change_child(old, new, parent, tree);
}


/*
	The node is initially red
 */
static void _link_node(struct vge_rbnode* node, struct vge_rbnode* parent,
	struct vge_rbnode** link)
{
	node->parent_color = (unsigned long)parent;
	node->left = node->right = NULL;
	*link = node;
}

static void _insert_node(struct vge_rbtree* tree, struct vge_rbnode* node)
{
	struct vge_rbnode* parent = RED_PARENT(node);
	struct vge_rbnode* gparent;
	struct vge_rbnode* tmp;
	while(1)
	{
		if(parent == NULL)
		{
			_set_parent_color(node, NULL, CLR_BLACK);
			break;
		}
		if(IS_BLACK(parent))
			break;
		gparent = RED_PARENT(parent);
		tmp = gparent->right;
		if(tmp != parent) /* parent = gparent->left */
		{
			if(tmp && IS_RED(tmp))
			{
				_set_parent_color(tmp, gparent, CLR_BLACK);
				_set_parent_color(parent, gparent, CLR_BLACK);
				node = gparent;
				parent = PARENT(node);
				_set_parent_color(node, parent, CLR_RED);
				continue;
			}
			tmp = parent->right;
			if(node == tmp)
			{
				parent->right = tmp = node->left;
				node->left = parent;
				if(tmp)
					_set_parent_color(tmp, parent, CLR_BLACK);
				_set_parent_color(parent, node, CLR_RED);
				parent = node;
				tmp = node->right;
			}
			gparent->left = tmp;
			parent->right = gparent;
			if(tmp)
				_set_parent_color(tmp, gparent, CLR_BLACK);
			_rotate_set_parents(gparent, parent, tree, CLR_RED);
			break;
		}
		else /* parent = gparent->right */
		{
			tmp = gparent->left;
			if(tmp && IS_RED(tmp))
			{
				_set_parent_color(tmp, gparent, CLR_BLACK);
				_set_parent_color(parent, gparent, CLR_BLACK);
				node = gparent;
				parent = PARENT(node);
				_set_parent_color(node, parent, CLR_RED);
				continue;
			}
			tmp = parent->left;
			if(node == tmp)
			{
				parent->left = tmp = node->right;
				node->right = parent;
				if(tmp)
					_set_parent_color(tmp, parent, CLR_BLACK);
				_set_parent_color(parent, node, CLR_RED);
				parent = node;
				tmp = node->left;
			}
			gparent->right = tmp;
			parent->left = gparent;
			if(tmp)
				_set_parent_color(tmp, gparent, CLR_BLACK);
			_rotate_set_parents(gparent, parent, tree, CLR_RED);
			break;
		}
	}
}

int vge_rbtree_init(struct vge_rbtree* tree,
	int (*compare)(void* lhs, void* rhs))
{
	tree->root = NULL;
	tree->compare = compare;
	return 0;
}

int vge_rbtree_insert(struct vge_rbtree* tree, struct vge_rbnode* node)
{
	struct vge_rbnode** new,* parent = NULL;
	new = &tree->root;
	while(*new)
	{
		int result = tree->compare(*new, node);
		parent = *new;
		if(result < 0)
			new = &(*new)->left;
		else if(result > 0)
			new = &(*new)->right;
		else
			return -1;
	}
	_link_node(node, parent, new);
	_insert_node(tree, node);
	return 0;
}
