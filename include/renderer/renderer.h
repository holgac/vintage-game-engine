#ifndef _VGE_RENDERER_H_
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

struct vge_window_properties
{
	char* window_title;
	int pos_x;
	int pos_y;
	int width;
	int height;
	int depth_buffer_size;
};

struct vge_renderer
{
	int dummy;
	struct SDL_Window* sdl_window;
	SDL_GLContext sdl_glcontext;
	SDL_Renderer* sdl_renderer;
};


struct vge_game;

int vge_renderer_init(struct vge_renderer* renderer, struct vge_window_properties* window_properties);
void vge_renderer_destroy(struct vge_renderer* renderer);

void vge_renderer_onframe(struct vge_renderer* renderer);
void vge_renderer_setclearcolor(struct vge_renderer* renderer, float r, float g, float b);

#endif /* _VGE_RENDERER_H_ */
