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
