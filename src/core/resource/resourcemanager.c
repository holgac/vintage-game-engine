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
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <core/resource/resourcemanager.h>
#include <core/resource/resource.h>

static struct vge_resource_loader* _find_loader(
	struct vge_resource_manager* rman, const char* ext)
{
	struct vge_resource_loader* loader = rman->loader;
	while(loader)
	{
		if(strcmp(ext, loader->extension) == 0)
			return loader;
		loader = loader->next;
	}
	return NULL;
}

int vge_resource_manager_init(struct vge_resource_manager* rman)
{
	rman->resource = NULL;
	rman->loader = NULL;
	return 0;
}
void vge_resource_manager_purge(struct vge_resource_manager* rman)
{

}
void vge_resource_manager_destroy(struct vge_resource_manager* rman)
{

}

struct vge_resource* vge_resource_manager_getresource(
	struct vge_resource_manager* rman, const char* name)
{
	/*
		TODO: store resources in rbtree
	 */
	struct vge_resource* res;
	res = rman->resource;
	while(res)
	{
		if(strcmp(name, res->name) == 0)
			return res;
		res = res->next;
	}
	return NULL;
}
struct vge_resource* vge_resource_manager_loadresource(
	struct vge_resource_manager* rman, const char* relativePath)
{
	char* extension;
	char* name;
	struct vge_resource_loader* loader;
	struct vge_resource* res;
	extension = strrchr(relativePath, '.');
	if(extension == NULL)
	{
		fprintf(stderr, "Cannot find extension of %s\n", relativePath);
		return NULL;
	}
	++extension;
	printf("load resource(%s): %s\n", extension, relativePath);
	loader = _find_loader(rman, extension);
	if(loader == NULL)
		return NULL;
	res = loader->load(relativePath);
	if(res == NULL)
		return NULL;
	name = strrchr(relativePath, '/') + 1;
	strcpy(res->name, name);
	printf("Loaded resource %s with name %s\n", extension, name);
	res->next = rman->resource;
	rman->resource = res;
	return res;
}
void vge_resource_manager_loadrecursive(
	struct vge_resource_manager* rman, const char* path)
{
	/*
		TODO: UNIX specific code
	 */
	char entpath[PATH_MAX];
	DIR* dir = opendir(path);
	int pathlen = strlen(path);
	struct dirent* ent;
	printf("load recursive: %s\n", path);
	strcpy(entpath, path);
	entpath[pathlen] = '/';
	while((ent = readdir(dir)))
	{
		struct stat st;
		strcpy(entpath + pathlen + 1, ent->d_name);
		stat(entpath, &st);
		if(S_ISDIR(st.st_mode) && ent->d_name[0] != '.')
		{
			vge_resource_manager_loadrecursive(rman, entpath);
		}
		else if(S_ISREG(st.st_mode) && ent->d_name[0] != '.')
		{
			vge_resource_manager_loadresource(rman, entpath);
		}
	}
	closedir(dir);
}

void vge_resource_manager_registerloader(struct vge_resource_manager* rman,
	struct vge_resource_loader* loader)
{
	/*
		TODO: sanity checks
	 */
	loader->next = rman->loader;
	rman->loader = loader;
}
