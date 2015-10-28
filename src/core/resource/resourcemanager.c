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

#include "core/resource/resource.h"
#include "core/resource/resourceloader.h"
#include "core/resource/resourcemanager.h"

static int _resource_compare(struct vge_rbnode *lhs, struct vge_rbnode *rhs)
{
	struct vge_resource *l, *r;
	l = vge_container_of(lhs, struct vge_resource, res_node);
	r = vge_container_of(rhs, struct vge_resource, res_node);
	return strcmp(l->name, r->name);
}

static int _resource_loader_compare(struct vge_rbnode *lhs, struct vge_rbnode *rhs)
{
	struct vge_resource_loader *l, *r;
	l = vge_container_of(lhs, struct vge_resource_loader, res_node);
	r = vge_container_of(rhs, struct vge_resource_loader, res_node);
	return strcmp(l->name, r->name);
}

static int _resource_match(struct vge_rbnode *lhs, const void *rhs)
{
	struct vge_resource *l;
	l = vge_container_of(lhs, struct vge_resource, res_node);
	return strcmp(l->name, rhs);
}

static int _resource_loader_match(struct vge_rbnode *lhs, const void *rhs)
{
	struct vge_resource_loader *l;
	l = vge_container_of(lhs, struct vge_resource_loader, res_node);
	return strcmp(l->name, rhs);
}

void vge_resource_manager_init(struct vge_resource_manager *rman)
{
	vge_rbtree_init(&rman->resources, _resource_compare);
	vge_rbtree_init(&rman->resource_loaders, _resource_loader_compare);
}

struct vge_resource *vge_resource_manager_getresource(
		struct vge_resource_manager *rman, const char *name)
{
	struct vge_rbnode *n;
	n = vge_rbtree_find_match(&rman->resources, name, _resource_match);
	if(!n)
		return NULL;
	return vge_container_of(n, struct vge_resource, res_node);
}


