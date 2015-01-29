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
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <core/resource/prefab.h>
#include <core/resource/resourcemanager.h>
#include <external/nxjson/nxjson.h>

static struct vge_resource* _load_prefab(const char* path)
{
	const nx_json* json;
	const nx_json* elem;
	struct vge_prefab* prefab;
	FILE* f;
	off_t flen;
	char* buf;
	f = fopen(path, "rb");
	fseeko(f, 0, SEEK_END);
	flen = ftello(f);
	buf = alloca(flen+1);
	fseeko(f, 0, SEEK_SET);
	fread(buf, flen, 1, f);
	json = nx_json_parse(buf, 0);
	prefab = malloc(sizeof(struct vge_prefab));
	vge_transform_read(&prefab->transform, json);
	elem = nx_json_get(json, "components");
	/*
		TODO: parse components
	 */
	return (struct vge_resource*)prefab;
}

static void _unload_prefab(struct vge_resource* res)
{
	free(res);
}

static struct vge_resource* _clone_prefab(struct vge_resource* res,
	struct vge_resource_manager* rman)
{
	struct vge_prefab* orig;
	struct vge_prefab* new;
	orig = (struct vge_prefab*)res;
	new = malloc(sizeof(struct vge_prefab));
	vge_transform_clone(&new->transform, &orig->transform);
	return (struct vge_resource*)new;
}

struct vge_resource_loader* vge_prefab_get_loader()
{
	struct vge_resource_loader* loader = malloc(sizeof(struct vge_resource_loader));
	loader->load = _load_prefab;
	loader->clone = _clone_prefab;
	loader->unload = _unload_prefab;
	strcpy(loader->extension, "prefab");
	return loader;
}
