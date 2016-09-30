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
#include "engine.h"
#include "core/containers/list.h"

struct test_struct
{
  struct vge_list node;
  int val;
};

static struct test_struct *create(int val)
{
  struct test_struct *new = malloc(sizeof(struct test_struct));
  new->val = val;
  return new;
}

VGETEST list_init()
{
  struct test_struct *nd1, *nd2, *tmp;
  struct vge_list list;
  struct vge_list *list_node;
  nd1 = create(0);
  nd2 = create(1);
  vge_list_init(&list);
  expect(vge_list_count(&list) == 0, "New list should be empty");
  vge_list_add(&list, &nd1->node);
  expect(vge_list_count(&list) == 1, "Size should be correct");
  vge_list_add(&list, &nd2->node);
  expect(vge_list_count(&list) == 2, "Size should be correct");

  list_node = &nd1->node;
  tmp = vge_container_of(list_node, struct test_struct, node);
  expect(tmp == nd1, "container_of macro should work");

  free(nd1);
  free(nd2);
}

VGETEST list_addremove()
{
  struct test_struct *tmp;
  struct vge_list list;
  struct vge_list *tmp_node;
  u32 i;
  const u32 elem_cnt = 100;
  u8 elements[elem_cnt];
  memset(elements, 0, elem_cnt);
  vge_list_init(&list);
  for(i=0; i<elem_cnt; ++i) {
    tmp = create(i);
    vge_list_add(&list, &tmp->node);
    expect(vge_list_count(&list) == i+1,
      "Size should increase accordingly");
  }
  vge_list_foreach(&list, struct test_struct, node, tmp, tmp_node) {
    expect(tmp->val < elem_cnt, "Added elements should be traversed");
    expect(tmp->val >= 0, "Should not back traverse");
    expect(elements[tmp->val] == 0, "Each element should be traversed once");
    elements[tmp->val] = 1;
  }
  i = 0;
  while(!vge_list_empty(&list)) {
    tmp = vge_list_first(&list, struct test_struct, node);
    expect(elements[tmp->val] == 1, "should traverse each element once");
    elements[tmp->val] = 2;
    vge_list_remove(&tmp->node);
    ++i;
    expect(vge_list_count(&list) == elem_cnt - i, "list count should decrease");
    free(tmp);
  }
  expect(i == elem_cnt, "Should not be empty until all elements are removed");
  for(i=0; i<elem_cnt; ++i) {
    expect(elements[i] == 2, "each elements should be traversed");
  }
  return;
}

