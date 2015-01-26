#include <time.h>
#include <core/game.h>


int vge_game_init(struct vge_game* game, char** argv, char** envp)
{
	game->state = NULL;
	game->step_frequency = 1.0f / 2.0f;
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
	}
}
