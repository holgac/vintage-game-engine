#ifndef _VGE_GAME_H_
#include "timer.h"
struct vge_game_state;

struct vge_game
{
	struct vge_game_state* state;

	struct vge_timer step_timer;
	float step_frequency;
	void (*onframe_cb)(struct vge_game*);
	void (*onstep_cb)(struct vge_game*);
};


int vge_game_init(struct vge_game* game, char** argv, char** envp);
void vge_game_start(struct vge_game* game);

#endif /* _VGE_GAME_H_ */
