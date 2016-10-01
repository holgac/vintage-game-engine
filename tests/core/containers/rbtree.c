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
#include <assert.h>
#include <time.h>
#include "engine.h"
#include "core/containers/rbtree.h"

struct test_struct
{
  struct vge_rbnode node;
  int val;
};

static struct test_struct *create(int val)
{
  struct test_struct *new = malloc(sizeof(struct test_struct));
  new->val = val;
  return new;
}

static void push_elems(struct vge_rbtree *tree, u32 elem_cnt, u32 elem_range, u8 *elements, u8 oldval)
{
  u32 i, j;
  struct test_struct *tmp;
  for(i=0; i<elem_cnt; ++i) {
    j = 0;
    while(elements[j] != oldval)
      j = rand() % elem_range;
    tmp = create(j);
    vge_rbtree_insert(tree, &tmp->node);
    elements[j]++;
  }
}

static int compare(struct vge_rbnode *lhs, struct vge_rbnode *rhs)
{
  struct test_struct *l, *r;
  l = vge_container_of(lhs, struct test_struct, node);
  r = vge_container_of(rhs, struct test_struct, node);
  if(l->val < r->val)
    return -1;
  return l->val > r->val;
}

static int compare_obj(struct vge_rbnode *lhs, const void *rhs)
{
  struct test_struct *l;
  const int *r;
  l = vge_container_of(lhs, struct test_struct, node);
  r = rhs;
  if(l->val < *r)
    return -1;
  return l->val > *r;
}

VGETEST rbtree_init()
{
  struct vge_rbtree tree;
  vge_rbtree_init(&tree, compare);
  expect(vge_rbtree_first(&tree) == NULL, "empty tree should not have elements");
}

VGETEST rbtree_insert()
{
  struct vge_rbtree tree;
  struct test_struct *tmp;
  struct vge_rbnode *tmp_node, *tmp2_node;
  const u32 elem_cnt = 100;
  const u32 elem_range = 1000;
  u32 i, j;
  u8 elements[elem_range];
  vge_rbtree_init(&tree, compare);
  srand(time(NULL));
  memset(elements, 0, elem_range);
  push_elems(&tree, elem_cnt, elem_range, elements, 0);
  i = j = 0;
  tmp_node = vge_rbtree_first(&tree);
  do {
    tmp = vge_container_of(tmp_node, struct test_struct, node);
    expect(elements[tmp->val] != 0, "Unknown elements should not be traversed");
    expect(elements[tmp->val] != 2, "Each element should be traversed once");
    expect(elements[tmp->val] == 1, "Element traversal shuld be correct");
    elements[tmp->val] = 2;
    for(i=0; i<tmp->val; ++i)
      expect(elements[i] != 1, "Elements should be traversed in order");
    for(i=tmp->val+1; i<elem_range; ++i)
      expect(elements[i] != 2, "Elements should be traversed in order");
    j++;
  } while((tmp_node = vge_rbtree_next(tmp_node)));
  expect(j == elem_cnt, "All elements should be traversed");
  j = 0;
  tmp_node = vge_rbtree_first(&tree);
  while((tmp2_node = vge_rbtree_next(tmp_node))) {
    tmp = vge_container_of(tmp_node, struct test_struct, node);
    expect(elements[tmp->val] == 2, "Should traverse once");
    vge_rbtree_remove(&tree, tmp_node);
    elements[tmp->val] = 3;
    free(tmp);
    tmp_node = tmp2_node;
    j++;
  }
  tmp = vge_container_of(tmp_node, struct test_struct, node);
  expect(elements[tmp->val] == 2, "Should traverse once");
  vge_rbtree_remove(&tree, tmp_node);
  elements[tmp->val] = 3;
  free(tmp);
  j++;
  expect(j == elem_cnt, "All elements should be deleted");
  j = 0;
  for(i=0; i<elem_range; ++i) {
    expect(elements[i] == 0 || elements[i] == 3,
        "elements should be deleted");
    j += (elements[i] == 3);
  }
  expect(j == elem_cnt, "All elements should be traversed");
  expect(vge_rbtree_first(&tree) == NULL, "Tree should be emptied");
}

void ensure_consistency(struct vge_rbtree *tree)
{
  int last;
  struct test_struct *tmp;
  struct vge_rbnode *tmp_node;
  tmp_node = vge_rbtree_first(tree);
  if(!tmp_node)
    return;
  last = -1;
  do {
    tmp = vge_container_of(tmp_node, struct test_struct, node);
    expect(last <= tmp->val, "Should traverse in order");
    last = tmp->val;
  } while((tmp_node = vge_rbtree_next(tmp_node)));
}

VGETEST rbtree_delete()
{
  struct vge_rbtree tree;
  struct test_struct *tmp, *tmp2;
  struct test_struct tmp3;
  struct vge_rbnode *tmp_node, *tmp2_node;
  const u32 elem_cnt = 1000;
  const u32 elem_range = 10000;
  u32 i, j;
  u8 elements[elem_range];
  vge_rbtree_init(&tree, compare);
  srand(time(NULL));
  memset(elements, 0, elem_range);
  push_elems(&tree, elem_cnt, elem_range, elements, 0);
  i = j = 0;
  ensure_consistency(&tree);
  tmp_node = vge_rbtree_first(&tree);
  while(i < elem_cnt) {
    j = rand() % elem_range;
    while(j < elem_range && elements[j] != 1)
      ++j;
    if(j == elem_range)
      continue;
    tmp3.val = j;
    tmp_node = vge_rbtree_find(&tree, &tmp3.node);
    expect(tmp_node != NULL, "Should be able to find");
    tmp = vge_container_of(tmp_node, struct test_struct, node);
    expect(tmp->val == tmp3.val, "that doesnt even make sense");
    tmp2_node = vge_rbtree_find_match(&tree, &j, compare_obj);
    tmp2 = vge_container_of(tmp2_node, struct test_struct, node);
    expect(tmp == tmp2, "find_obj should return the same object");
    vge_rbtree_remove(&tree, tmp_node);
    free(tmp);
    ++i;
    elements[j] = 2;
    ensure_consistency(&tree);
  }
  j = 0;
  for(i=0; i<elem_range; ++i) {
    expect(elements[i] == 0 || elements[i] == 2,
        "elements should be deleted");
    j += (elements[i] == 2);
  }
  expect(j == elem_cnt, "All elements should be traversed");
  expect(vge_rbtree_first(&tree) == NULL, "Tree should be emptied");
}

VGETEST rbtree_duplicate()
{
  struct vge_rbtree tree;
  struct vge_rbnode *tmp_node;
  struct test_struct *tmp;
  const u32 elem_cnt = 1;
  const u32 elem_range = 10000;
  u32 i;
  u8 elements[elem_range];
  srand(time(NULL));
  vge_rbtree_init(&tree, compare);
  memset(elements, 0, elem_range);
  /* push 1000 elems */
  push_elems(&tree, elem_cnt, elem_range, elements, 0);
  /* push same 1000 elems */
  push_elems(&tree, elem_cnt, elem_range, elements, 1);
  tmp_node = vge_rbtree_first(&tree);
  i = 0;
  do {
    tmp = vge_container_of(tmp_node, struct test_struct, node);
    expect(elements[tmp->val] == 2,
        "All elements should be added twice, traversed once");
    ++elements[tmp->val];
    ++i;
  } while((tmp_node = vge_rbtree_next(tmp_node)));
  expect(i==elem_cnt, "Should not be able to store duplicate elements");
}

