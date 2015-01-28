#include <engine.h>
#include <stdio.h>

void onframe_cb(struct vge_game* game)
{
	if(vge_input_keypressed(game->input, VGEINPUT_KEY_A))
	{
		printf("A\n");
		vge_renderer_setclearcolor(game->renderer, 1.0f, 0.0f, 0.0f);
	}
	if(vge_input_keypressed(game->input, VGEINPUT_KEY_S))
	{
		printf("S\n");
		vge_renderer_setclearcolor(game->renderer, 0.0f, 1.0f, 0.0f);
	}
	if(vge_input_keypressed(game->input, VGEINPUT_KEY_D))
	{
		printf("D\n");
		vge_renderer_setclearcolor(game->renderer, 0.0f, 0.0f, 1.0f);
	}
}
void onstep_cb(struct vge_game* game)
{
}

int main(int argc, char** argv, char** envp)
{
	struct vge_game game;
	vge_game_init(&game, argv, envp, VGEGAME_INIT_RENDERER | VGEGAME_INIT_INPUT);
	vge_renderer_init(game.renderer, NULL);
	vge_input_init(game.input);
	game.onframe_cb = onframe_cb;
	game.onstep_cb = onstep_cb;
	vge_game_start(&game);
	return 0;
}