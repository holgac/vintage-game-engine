#include "vge.h"
struct vge_test_game {
	struct vge_subsystem subsys;
	struct vge_subsystem *renderer;
	struct vge_subsystem *input;
};

static void _init(struct vge_game *game, struct vge_subsystem *subsys)
{
}

static void _destroy(struct vge_game *game, struct vge_subsystem *subsys)
{
}

static void _on_frame(struct vge_game *game, struct vge_subsystem *subsys)
{
	struct vge_test_game *test_game = vge_container_of(subsys, struct vge_test_game, subsys);
	if(vge_input_keypressed(test_game->input, VGEINPUT_KEY_ESCAPE)) {
		printf("exiting...\n");
		vge_game_stop(game);
	}
}

static void _on_step(struct vge_game *game, struct vge_subsystem *subsys)
{
}


int game_main(int argc, char **argv)
{
	struct vge_game game;
	struct vge_test_game test_game;

	vge_game_init(&game);
	vge_renderer_init(&game, NULL, &test_game.renderer);
	vge_input_init(&game, &test_game.input);

	test_game.subsys.init = _init;
	test_game.subsys.destroy = _destroy;
	test_game.subsys.on_frame = _on_frame;
	test_game.subsys.on_step = _on_step;

	vge_game_add_subsystem(&game, &test_game.subsys);
	vge_game_start(&game);
	vge_game_destroy(&game);

	return 0;
}
