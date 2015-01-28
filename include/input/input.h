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
#ifndef _VGE_INPUT_H_
#include <SDL2/SDL.h>

#define VGEINPUT_KEY_COUNT 512
#define VGEINPUT_REGULAR_KEY_END 256

struct vge_input
{
	char cur_keys[VGEINPUT_KEY_COUNT];
	char persistent_keys[VGEINPUT_KEY_COUNT];
};


int vge_input_init(struct vge_input* input);
void vge_input_destroy(struct vge_input* input);

void vge_input_onframe(struct vge_input* input);

void vge_input_keyevent(struct vge_input* input, int key, int press);

char vge_input_keypressed(struct vge_input* input, int key);
char vge_input_keyheld(struct vge_input* input, int key);

#endif /* _VGE_RENDERER_H_ */
