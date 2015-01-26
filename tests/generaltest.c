#include <engine.h>
#include <stdio.h>

void onframe_cb(struct vge_game* game)
{
	// printf("on frame!\n");
}
void onstep_cb(struct vge_game* game)
{
	printf("on step!\n");
}

int main(int argc, char** argv, char** envp)
{
	struct vge_game game;
	vge_game_init(&game, argv, envp);
	game.onframe_cb = onframe_cb;
	game.onstep_cb = onstep_cb;
	vge_game_start(&game);
	return 0;
}