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
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <limits.h>

#include "core/resource/resource.h"
#include "core/resource/resourceloader.h"
#include "core/resource/resourcemanager.h"
#include "core/log/logger.h"

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
  l = vge_container_of(lhs, struct vge_resource_loader, loader_node);
  r = vge_container_of(rhs, struct vge_resource_loader, loader_node);
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
  l = vge_container_of(lhs, struct vge_resource_loader, loader_node);
  return strcmp(l->name, rhs);
}

void vge_resource_manager_init(struct vge_resource_manager *rman)
{
  vge_rbtree_init(&rman->resources, _resource_compare);
  vge_rbtree_init(&rman->resource_loaders, _resource_loader_compare);
}

struct vge_resource *vge_resource_manager_get_resource(
    struct vge_resource_manager *rman, const char *name)
{
  struct vge_rbnode *n;
  n = vge_rbtree_find_match(&rman->resources, name, _resource_match);
  if(!n)
    return NULL;
  return vge_container_of(n, struct vge_resource, res_node);
}

void vge_resource_manager_register_loader(struct vge_resource_manager *rman,
    struct vge_resource_loader *loader)
{
  vge_rbtree_insert(&rman->resource_loaders, &loader->loader_node);
}

void vge_resource_manager_load_recursive(struct vge_resource_manager *rman,
    struct vge_game *game, const char *path)
{
    /*
        TODO: UNIX specific code
     */
    char entpath[PATH_MAX];
    DIR* dir = opendir(path);
    int pathlen = strlen(path);
    struct dirent* ent;
    vge_log("load recursive: %s", path);
    strcpy(entpath, path);
    entpath[pathlen] = '/';
    while((ent = readdir(dir)))
    {
        struct stat st;
        strcpy(entpath + pathlen + 1, ent->d_name);
        stat(entpath, &st);
    if(ent->d_name[0] == '.')
      continue;
        if(S_ISDIR(st.st_mode))
            vge_resource_manager_load_recursive(rman, game, entpath);
        else if(S_ISREG(st.st_mode))
            vge_resource_manager_load_resource(rman, game, entpath);
    }
    closedir(dir);
}

struct vge_resource *vge_resource_manager_load_resource(
    struct vge_resource_manager *rman, struct vge_game *game,
    const char *path)
{
  char *extension;
  struct vge_rbnode *rbnode;
  struct vge_resource_loader *loader;
  struct vge_resource *res;
  extension = strrchr(path, '.');
  if(extension == NULL)
    vge_log_and_return(NULL, "No extension found in file %s", path);
  if(strchr(extension, '/'))
    vge_log_and_return(NULL, "Error in extension of %s", path);
  /* TODO: multiple extension support for resource loaders */
  rbnode = vge_rbtree_find_match(&rman->resource_loaders, extension + 1, _resource_loader_match);
  if(!rbnode)
    vge_log_and_return(NULL, "No loader registered to load %s", path);
  loader = vge_container_of(rbnode, struct vge_resource_loader, loader_node);
  /* TODO: passing around vge_resource defeats the type safety except that
   * loader->name can be checked. Find a more elegant method for this? */
  res = loader->load(loader, game, path);
  if(!res)
    vge_log_and_return(NULL, "Failed to load %s", path);
  /* TODO: name collision checks */
  vge_rbtree_insert(&rman->resources, &res->res_node);
  vge_log("Loaded resource %s", res->name);
  return res;
}












