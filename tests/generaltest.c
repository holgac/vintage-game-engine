/*
	This file is part of Vintage Game Engine.
	Vintage Game Engine is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Vintage Game Engine is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Vintage Game Engine.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <engine.h>
#include <stdio.h>

void onframe_cb(struct vge_game* game)
{
	if(vge_input_keypressed(game->input, VGEINPUT_KEY_A))
		vge_renderer_setclearcolor(game->renderer, 1.0f, 0.0f, 0.0f);
	if(vge_input_keypressed(game->input, VGEINPUT_KEY_S))
		vge_renderer_setclearcolor(game->renderer, 0.0f, 1.0f, 0.0f);
	if(vge_input_keypressed(game->input, VGEINPUT_KEY_D))
		vge_renderer_setclearcolor(game->renderer, 0.0f, 0.0f, 1.0f);
}
void onstep_cb(struct vge_game* game)
{
}


int main(int argc, char** argv, char** envp)
{
	struct vge_game game;
	struct vge_game_state state;
	vge_game_init(&game, argv, envp, "./resources", VGEGAME_INIT_RENDERER | VGEGAME_INIT_INPUT);
	game.state = &state;
	state.onframe_cb = onframe_cb;
	state.onstep_cb = onstep_cb;
	vge_renderer_init(game.renderer, NULL);
	vge_input_init(game.input);
	vge_game_start(&game);
	return 0;
}
