#include <time.h>
#include <core/game.h>
#include <renderer/renderer.h>


int vge_game_init(struct vge_game* game, char** argv, char** envp, unsigned int flags)
{
	game->state = NULL;
	game->step_frequency = 1.0f / 1.0f;
	if(flags & VGEGAME_INIT_RENDERER)
	{
		game->renderer = malloc(sizeof(struct vge_renderer));
	}
	else
	{
		game->renderer = NULL;
	}
	return 0;
}

void vge_game_start(struct vge_game* game)
{
	vge_timer_update();
	vge_timer_init(&game->step_timer, game->step_frequency);
	for(;;)
	{
		vge_timer_update();
		if(vge_timer_check(&game->step_timer, VGETIMER_REWIND))
		{
			game->onstep_cb(game);
		}
		game->onframe_cb(game);
		if(game->renderer)
		{
			vge_renderer_onframe(game->renderer);
		}
	}
}
