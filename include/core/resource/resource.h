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
#ifndef _VGE_RESOURCE_H_

#define VGERESOURCE_NAME_MAX 32
enum vge_resource_type
{
	vge_resource_type_prefab
};
struct vge_resource_loader;

/*
	All of those fields are filled by the resource manager.
	New resources should have vge_resource as their first field.
 */
struct vge_resource
{
	char name[VGERESOURCE_NAME_MAX];
	struct vge_resource* next;
	struct vge_resource_loader* loader;
};

#endif /* _VGE_RESOURCE_H_ */