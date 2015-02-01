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
#ifndef _VGE_GRAPHICSCOMPONENT_H_
#include "../core/scene/component.h"
#include "../core/math/vertex.h"
#include "../vge.h"

struct vge_graphicscomponent
{
	struct vge_component component;
	u32 num_vertices;
	struct vge_vertex* vertices;
};

struct vge_component_loader;

struct vge_component_loader* vge_graphicscomponent_get_loader();

#endif /* _VGE_GRAPHICSCOMPONENT_H_ */
