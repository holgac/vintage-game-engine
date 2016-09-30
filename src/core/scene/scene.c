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

#include "core/scene/scenemanager.h"
#include "core/scene/scene.h"
#include "core/resource/resourceloader.h"
#include "external/nxjson/nxjson.h"
#include "core/log/logger.h"

static struct vge_resource *_load_scene(struct vge_resource_loader *loader,
    struct vge_game *game, const char *path)
{
  struct vge_scene_prefab *scene_prefab;
  const nx_json* json;
  const nx_json* elem;
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
  scene_prefab = malloc(sizeof(struct vge_scene_prefab));
  scene_prefab->resource.loader = loader;
	elem = nx_json_get(json, "name");
	if(!elem || (elem->type != NX_JSON_STRING))
		vge_log_and_return(NULL, "Name invalid in scene");
	strcpy(scene_prefab->resource.name, elem->text_value);
  return &scene_prefab->resource;
}

static struct vge_resource *_clone_scene(struct vge_resource_loader *loader,
    struct vge_resource *old_scn)
{
  return NULL;
}

static void _unload_scene(struct vge_resource_loader *loader,
    struct vge_resource *scn)
{
}

struct vge_resource_loader *vge_scene_prefab_get_loader()
{
	struct vge_resource_loader *loader;
	loader = malloc(sizeof(struct vge_resource_loader));
	loader->load = _load_scene;
	loader->clone = _clone_scene;
	loader->unload = _unload_scene;
	strcpy(loader->name, "vgescn");
	return loader;
}

struct vge_scene *vge_scene_from_prefab(struct vge_scene_prefab *)
{
  return NULL;
}

