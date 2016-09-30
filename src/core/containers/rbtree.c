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
  Thanks to Rob Landley <rob  landley.net> for documentation,
    (C) 1999  Andrea Arcangeli <andrea  suse.de>
    (C) 2002  David Woodhouse <dwmw2  infradead.org>
    (C) 2012  Michel Lespinasse <walken  google.com>
    for implementation.
*/

#include <stdlib.h>
#include "core/containers/rbtree.h"

#define CLR_RED 0
#define CLR_BLACK 1

#define CLR(pc) ((pc) & 1)
#define CLR_IS_BLACK(pc) CLR(pc)
#define CLR_IS_RED(pc) (!CLR(pc))
#define IS_BLACK(nd) (CLR_IS_BLACK((nd)->parent_color))
#define IS_RED(nd) (CLR_IS_RED((nd)->parent_color))
#define RED_PARENT(nd) ((struct vge_rbnode *)(nd)->parent_color)
#define NODE_EMPTY(nd) ((nd)->parent_color == ((unsigned long)(nd)))
#define SET_BLACK(nd) (nd)->parent_color |= CLR_BLACK

/*
  Sets parent and color of vge_rbnode
 */
static inline void _set_parent_color(struct vge_rbnode *node,
             struct vge_rbnode *parent, int color)
{
  node->parent_color = (unsigned long)parent | color;
}

static inline void
_change_child(struct vge_rbnode *old, struct vge_rbnode *new,
      struct vge_rbnode *parent, struct vge_rbtree *tree)
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
_rotate_set_parents(struct vge_rbnode *old, struct vge_rbnode *new,
      struct vge_rbtree *tree, int color)
{
  struct vge_rbnode *parent = vge_rbtree_parent(old);
  new->parent_color = old->parent_color;
  _set_parent_color(old, new, color);
  _change_child(old, new, parent, tree);
}


/*
  The node is initially red
 */
static void _link_node(struct vge_rbnode *node, struct vge_rbnode *parent,
  struct vge_rbnode **link)
{
  node->parent_color = (unsigned long)parent;
  node->left = node->right = NULL;
  *link = node;
}

static void _insert_node(struct vge_rbtree *tree, struct vge_rbnode *node)
{
  struct vge_rbnode *parent = RED_PARENT(node);
  struct vge_rbnode *gparent;
  struct vge_rbnode *tmp;
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
        parent = vge_rbtree_parent(node);
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
        parent = vge_rbtree_parent(node);
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

int vge_rbtree_init(struct vge_rbtree *tree,
  int (*compare)(struct vge_rbnode *lhs, struct vge_rbnode *rhs))
{
  tree->root = NULL;
  tree->compare = compare;
  return 0;
}

int vge_rbtree_insert(struct vge_rbtree *tree, struct vge_rbnode *node)
{
  struct vge_rbnode **new, *parent = NULL;
  new = &tree->root;
  while(*new)
  {
    int result = tree->compare(node, *new);
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

struct vge_rbnode *vge_rbtree_first(struct vge_rbtree *tree)
{
  struct vge_rbnode *n;
  n = tree->root;
  if(!n)
    return NULL;
  while(n->left)
    n = n->left;
  return n;
}

struct vge_rbnode *vge_rbtree_next(struct vge_rbnode *node)
{
  struct vge_rbnode *p;
  if(NODE_EMPTY(node))
    return NULL;
  if(node->right) {
    node = node->right;
    while(node->left)
      node = node->left;
    return node;
  }
  while((p = vge_rbtree_parent(node)) && (node == p->right))
    node = p;
  return p;
}

static struct vge_rbnode *_erase_node(struct vge_rbtree *tree, struct vge_rbnode *node)
{
  struct vge_rbnode *child, *tmp, *parent, *rebalance;
  unsigned long pc;
  child = node->right;
  tmp = node->left;
  if(!tmp) {
    pc = node->parent_color;
    parent = vge_rbtree_parent(node);
    _change_child(node, child, parent, tree);
    if(child) {
      child->parent_color = pc;
      rebalance = NULL;
    } else
      rebalance = CLR_IS_BLACK(pc) ? parent : NULL;
    tmp = parent;
  } else if(!child) {
    tmp->parent_color = pc = node->parent_color;
    parent = vge_rbtree_parent(node);
    _change_child(node, tmp, parent, tree);
    rebalance = NULL;
    tmp = parent;
  } else {
    struct vge_rbnode *successor, *child2;
    successor = child;
    tmp = child->left;
    if(!tmp) {
      parent = successor;
      child2 = successor->right;
    } else {
      do {
        parent = successor;
        successor = tmp;
        tmp = tmp->left;
      } while(tmp);
      parent->left = child2 = successor->right;
      successor->right = child;
      _set_parent_color(child, successor, CLR(child->parent_color));
    }
    successor->left = tmp = node->left;
    _set_parent_color(tmp, successor, CLR(tmp->parent_color));
    pc = node->parent_color;
    tmp = vge_rbtree_parent(node);
    _change_child(node, successor, tmp, tree);
    if(child2) {
      successor->parent_color = pc;
      _set_parent_color(child2, parent, CLR_BLACK);
      rebalance = NULL;
    } else {
      unsigned long pc2 = successor->parent_color;
      successor->parent_color = pc;
      rebalance = CLR_IS_BLACK(pc2) ? parent : NULL;
    }
    tmp = successor;
  }
  return rebalance;
}

void _erase_color(struct vge_rbtree *tree, struct vge_rbnode *parent)
{
  struct vge_rbnode *node, *sibling, *tmp1, *tmp2;
  node = NULL;
  for(;;) {
    sibling = parent->right;
    if(node != sibling) {
      if(IS_RED(sibling)) {
        parent->right = tmp1 = sibling->left;
        sibling->left = parent;
        _set_parent_color(tmp1, parent, CLR_BLACK);
        _rotate_set_parents(parent, sibling, tree, CLR_RED);
        sibling = tmp1;
      }
      tmp1 = sibling->right;
      if(!tmp1 || IS_BLACK(tmp1)) {
        tmp2 = sibling->left;
        if(!tmp2 || IS_BLACK(tmp2)) {
          _set_parent_color(sibling, parent, CLR_RED);
          if(IS_RED(parent))
            SET_BLACK(parent);
          else {
            node = parent;
            parent = vge_rbtree_parent(node);
            if(parent)
              continue;
          }
          break;
        }
        sibling->left = tmp1 = tmp2->right;
        tmp2->right = sibling;
        parent->right = tmp2;
        if(tmp1)
          _set_parent_color(tmp1, sibling, CLR_BLACK);
        tmp1 = sibling;
        sibling = tmp2;
      }
      parent->right = tmp2 = sibling->left;
      sibling->left = parent;
      _set_parent_color(tmp1, sibling, CLR_BLACK);
      if(tmp2)
        _set_parent_color(tmp2, parent, CLR(tmp2->parent_color));
      _rotate_set_parents(parent, sibling, tree, CLR_BLACK);
      break;
    } else {
      sibling = parent->left;
      if(IS_RED(sibling)) {
        parent->left = tmp1 = sibling->right;
        sibling->right = parent;
        _set_parent_color(tmp1, parent, CLR_BLACK);
        _rotate_set_parents(parent, sibling, tree, CLR_RED);
        sibling = tmp1;
      }
      tmp1 = sibling->left;
      if(!tmp1 || IS_BLACK(tmp1)) {
        tmp2 = sibling->right;
        if(!tmp2 || IS_BLACK(tmp2)) {
          _set_parent_color(sibling, parent, CLR_RED);
          if(IS_RED(parent))
            SET_BLACK(parent);
          else {
            node = parent;
            parent = vge_rbtree_parent(node);
            if(parent)
              continue;
          }
          break;
        }
        sibling->right = tmp1 = tmp2->left;
        tmp2->left = sibling;
        parent->left = tmp2;
        if(tmp1)
          _set_parent_color(tmp1, sibling, CLR_BLACK);
        tmp1 = sibling;
        sibling = tmp2;
      }
      parent->left = tmp2 = sibling->right;
      sibling->right = parent;
      _set_parent_color(tmp1, sibling, CLR_BLACK);
      if(tmp2)
        _set_parent_color(tmp2, parent, CLR(tmp2->parent_color));
      _rotate_set_parents(parent, sibling, tree, CLR_BLACK);
      break;
    }
  }
}

void vge_rbtree_remove(struct vge_rbtree *tree, struct vge_rbnode *node)
{
  struct vge_rbnode *rebalance;
  rebalance = _erase_node(tree, node);
  if(rebalance)
    _erase_color(tree, rebalance);
}

/*
 * TODO: inline
 */
struct vge_rbnode* vge_rbtree_find(struct vge_rbtree *tree, struct vge_rbnode *node)
{
  return vge_rbtree_find_match(tree, node,
      (int(*)(struct vge_rbnode *, const void *))tree->compare);
}

struct vge_rbnode* vge_rbtree_find_match(struct vge_rbtree *tree,
    const void *obj,
    int (*compare)(struct vge_rbnode *lhs, const void *rhs))
{
  struct vge_rbnode *tmp = tree->root;
  int r;
  while(tmp) {
    r = compare(tmp, obj);
    if(r < 0)
      tmp = tmp->right;
    else if (r > 0)
      tmp = tmp->left;
    else
      return tmp;
  }
  return NULL;
}




