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
#include <string.h>
#include <external/nxjson/nxjson.h>
#include <core/scene/componentmanager.h>

static struct vge_component_loader* _find_loader(
	struct vge_component_manager* cman, const char* name)
{
	struct vge_component_loader* loader = cman->loader;
	while(loader)
	{
		if(strcmp(name, loader->name) == 0)
			return loader;
		loader = loader->next;
	}
	return NULL;
}

int vge_component_manager_init(struct vge_component_manager* cman)
{
	cman->loader = NULL;
	return 0;
}
void vge_component_manager_destroy(struct vge_component_manager* cman)
{

}

struct vge_component* vge_component_manager_loadcomponent(
	struct vge_component_manager* cman, const struct nx_json* json)
{
	const struct nx_json* elem;
	struct vge_component_loader* loader;
	elem = nx_json_get(json, "type");
	loader = _find_loader(cman, elem->text_value);
	if(!loader)
		return NULL;
	return loader->load(json);
}
void vge_component_manager_registerloader(struct vge_component_manager* cman,
										struct vge_component_loader* loader)
{
	/*
		TODO: sanity checks
	 */
	loader->next = cman->loader;
	cman->loader = loader;
	return;
}
