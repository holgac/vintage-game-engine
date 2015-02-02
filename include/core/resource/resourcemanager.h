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
#ifndef _VGE_RESOURCE_MANAGER_H_
#define VGERESOURCE_EXTENSION_MAX 8

struct vge_resource;
struct vge_resource_manager;

struct vge_resource_loader
{
	char extension[VGERESOURCE_EXTENSION_MAX];
	struct vge_resource_loader* next;
	struct vge_resource* (*load)(const char* path, struct vge_game* game);
	struct vge_resource* (*clone)(struct vge_resource* res,
		struct vge_game* game);
	void (*unload)(struct vge_resource* res, struct vge_game* game);
};
struct vge_resource_manager
{
	struct vge_resource* resource;
	struct vge_resource_loader* loader;
};
struct vge_game;

int vge_resource_manager_init(struct vge_resource_manager* rman);
void vge_resource_manager_purge(struct vge_resource_manager* rman);
void vge_resource_manager_destroy(struct vge_resource_manager* rman);

struct vge_resource* vge_resource_manager_getresource(
	struct vge_resource_manager* rman, const char* name);
struct vge_resource* vge_resource_manager_loadresource(
	struct vge_resource_manager* rman, const char* relativePath,
	struct vge_game* game);
void vge_resource_manager_loadrecursive(struct vge_resource_manager* rman,
									const char* path, struct vge_game* game);
void vge_resource_manager_registerloader(struct vge_resource_manager* rman,
										struct vge_resource_loader* loader);

#endif /* _VGE_RESOURCE_MANAGER_H_ */
