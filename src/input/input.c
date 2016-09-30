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
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "input/input.h"
#include "core/game.h"
#include "core/containers/list.h"
#include "core/subsystem.h"

struct vge_input_sdl
{
  struct vge_subsystem subsys;
  u8 cur_keys[VGE_INPUT_KEY_COUNT];
  u8 persistent_keys[VGE_INPUT_KEY_COUNT];
};

static void _vge_input_sdl_init(struct vge_game *game,
    struct vge_subsystem *subsys)
{
}

static void _vge_input_sdl_destroy(struct vge_game *game,
    struct vge_subsystem *subsys)
{
  struct vge_input_sdl *input;
  input = vge_container_of(subsys, struct vge_input_sdl, subsys);
  free(input);
}

static void _vge_input_sdl_on_step(struct vge_game *game,
    struct vge_subsystem *subsys)
{
}

static void _vge_input_handle_keyevent(struct vge_input_sdl *input, vge_key key,
    int press)
{
  if(input->persistent_keys[key] == press)
    return;
  input->cur_keys[key] = input->persistent_keys[key] = press;
}

static void _vge_input_sdl_on_frame(struct vge_game *game,
    struct vge_subsystem *subsys)
{
/* 
    SDL_KEYDOWN        = 0x300,
    SDL_KEYUP,
    SDL_TEXTEDITING,
    SDL_TEXTINPUT,
    SDL_MOUSEMOTION    = 0x400,
    SDL_MOUSEBUTTONDOWN,
    SDL_MOUSEBUTTONUP,
    SDL_MOUSEWHEEL,
 */
  SDL_Event event;
  struct vge_input_sdl *input;
  int keysym;
  input = vge_container_of(subsys, struct vge_input_sdl, subsys);
  memset(input->cur_keys, 0, sizeof(u8) * VGE_INPUT_KEY_COUNT);
  while(SDL_PeepEvents(&event, 1, SDL_GETEVENT, SDL_KEYDOWN, SDL_KEYUP)) {
    keysym = event.key.keysym.sym;
    keysym = VGE_REGULAR_KEY_END * ((keysym & SDLK_SCANCODE_MASK) >> 30)
        + (keysym & ~SDLK_SCANCODE_MASK);
    switch(event.type) {
    case SDL_KEYDOWN:
      if(!event.key.repeat)
        _vge_input_handle_keyevent(input, keysym, 1);
      break;
    case SDL_KEYUP:
      _vge_input_handle_keyevent(input, keysym, 0);
      break;
    }
  }
}

int vge_input_init(struct vge_game *game, struct vge_subsystem **subsys)
{
  struct vge_input_sdl *input;
  input = malloc(sizeof(struct vge_input_sdl));
  memset(input->cur_keys, 0, sizeof(u8) * VGE_INPUT_KEY_COUNT);
  memset(input->persistent_keys, 0, sizeof(u8) * VGE_INPUT_KEY_COUNT);
  strcpy(input->subsys.name, "input");
  input->subsys.init = _vge_input_sdl_init;
  input->subsys.destroy = _vge_input_sdl_destroy;
  input->subsys.on_frame = _vge_input_sdl_on_frame;
  input->subsys.on_step = _vge_input_sdl_on_step;

  vge_game_add_subsystem(game, &input->subsys);
  *subsys = &input->subsys;
  return 0;
}

char vge_input_keypressed(struct vge_subsystem *subsys, int key)
{
  struct vge_input_sdl *input;
  input = vge_container_of(subsys, struct vge_input_sdl, subsys);
  return input->cur_keys[key];
}

char vge_input_keyheld(struct vge_subsystem *subsys, int key)
{
  struct vge_input_sdl *input;
  input = vge_container_of(subsys, struct vge_input_sdl, subsys);
  return input->persistent_keys[key];
}
