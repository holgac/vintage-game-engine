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
