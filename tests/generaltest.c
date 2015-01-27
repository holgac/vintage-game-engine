#include <engine.h>
#include <stdio.h>

void onframe_cb(struct vge_game* game)
{
	// printf("on frame!\n");
}
void onstep_cb(struct vge_game* game)
{
	printf("on step!\n");
	vge_renderer_setclearcolor(game->renderer,
		rand() * 1.0f / RAND_MAX,
		rand() * 1.0f / RAND_MAX,
		rand() * 1.0f / RAND_MAX);
}

int main(int argc, char** argv, char** envp)
{
	struct vge_game game;
	vge_game_init(&game, argv, envp, VGEGAME_INIT_RENDERER);
	vge_renderer_init(game.renderer, NULL);
	game.onframe_cb = onframe_cb;
	game.onstep_cb = onstep_cb;
	vge_game_start(&game);
	return 0;
}