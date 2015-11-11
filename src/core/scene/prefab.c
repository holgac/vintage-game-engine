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

#include "core/scene/prefab.h"
#include "core/resource/resourceloader.h"
#include "external/nxjson/nxjson.h"
#include "core/log/logger.h"

static struct vge_prefab *_load_single(struct vge_resource_loader *loader,
		const struct nx_json *json)
{
	struct vge_prefab *prefab;
	const struct nx_json *elem;
	prefab = malloc(sizeof(struct vge_prefab));
	vge_list_init(&prefab->component_list);

	prefab->resource.loader = loader;
	elem = nx_json_get(json, "name");
	if(!elem || (elem->type != NX_JSON_STRING))
		vge_log_and_return(NULL, "Name invalid in prefab");
	strcpy(prefab->resource.name, elem->text_value);
	return prefab;
}

static struct vge_resource *_load_prefab(struct vge_resource_loader *loader,
		const char *path)
{
    const struct nx_json *json;
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
	if(json->type != NX_JSON_OBJECT)
		vge_log_and_return(NULL, "Prefab file is invalid: %s", path);
	return &_load_single(loader, json)->resource;
}

static struct vge_resource *_clone_prefab(struct vge_resource_loader *loader,
		struct vge_resource *old_res)
{
	return NULL;
}

void _unload_prefab(struct vge_resource_loader *loader,
		struct vge_resource *scn)
{
}

struct vge_resource_loader *vge_prefab_get_loader()
{
	struct vge_resource_loader *loader;
	loader = malloc(sizeof(struct vge_resource_loader));
	loader->load = _load_prefab;
	loader->clone = _clone_prefab;
	loader->unload = _unload_prefab;
	strcpy(loader->name, "prefab");
	return loader;
}

