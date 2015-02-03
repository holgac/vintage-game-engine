#ifndef _VGE_GAME_H_
#include "time/timer.h"
#define VGEGAME_INIT_RENDERER 1
#define VGEGAME_INIT_INPUT 2

#define VGEGAME_STATUS_QUITTING 1
struct vge_game_state;
struct vge_game_state_manager;
struct vge_renderer;
struct vge_input;
/*
	Game structure. Works like a context to avoid static variables
	and non-reentrancy.
 */
struct vge_resource_manager;

struct vge_game
{
	struct vge_game_state* state;

	struct vge_renderer* renderer;
	struct vge_input* input;
	struct vge_resource_manager* rman;
	struct vge_component_manager* cman;
	struct vge_game_state_manager* gsman;

	struct vge_timer step_timer;
	float step_frequency;

	unsigned int status;
};

/*
	Initializes vge_game. specify which modules to use via flags.
	modules must also be initialized separately via vge_[module]_init.
 */
int vge_game_init(struct vge_game* game, char** argv, char** envp, unsigned int flags);
/*
	Destroys the game and all modules. The user does NOT need to call
	vge_[module]_destroy for each module since this function destroys
	all modules.
 */
void vge_game_destroy(struct vge_game* game);
/*
	Starts game loop
 */
void vge_game_start(struct vge_game* game);
/*
	Stops game loop after handling current frame
 */
void vge_game_stop(struct vge_game* game);


#endif /* _VGE_GAME_H_ */
