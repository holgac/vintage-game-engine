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
#include <input/input.h>
#include <input/keycodes.h>

#include <SDL2/SDL.h>


int vge_input_init(struct vge_input* input)
{
	memset(input->cur_keys, 0, sizeof(char) * VGEINPUT_KEY_COUNT);
	memset(input->persistent_keys, 0, sizeof(char) * VGEINPUT_KEY_COUNT);
	return 0;
}

void vge_input_destroy(struct vge_input* renderer)
{
}

void vge_input_onframe(struct vge_input* input)
{
	memset(input->cur_keys, 0, sizeof(char) * VGEINPUT_KEY_COUNT);
}

void vge_input_keyevent(struct vge_input* input, int key, int press)
{
	if(key & SDLK_SCANCODE_MASK)
	{
		key ^= SDLK_SCANCODE_MASK;
		key += VGEINPUT_REGULAR_KEY_END;
	}
	if(input->persistent_keys[key] == press)
		return;
	printf("key %d %d!\n", key, press);
	input->cur_keys[key] = press;
	input->persistent_keys[key] = press;
}


char vge_input_keypressed(struct vge_input* input, int key)
{
	if(key & SDLK_SCANCODE_MASK)
	{
		key ^= SDLK_SCANCODE_MASK;
		key += VGEINPUT_REGULAR_KEY_END;
	}
	return input->cur_keys[key];
}
char vge_input_keyheld(struct vge_input* input, int key)
{
	if(key & SDLK_SCANCODE_MASK)
	{
		key ^= SDLK_SCANCODE_MASK;
		key += VGEINPUT_REGULAR_KEY_END;
	}
	return input->persistent_keys[key];
}
