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
#ifndef __VGE_SUBSYSTEM_H
#define __VGE_SUBSYSTEM_H

struct vge_game;

/*
 * All subsystems, like physics, renderer, input etc.
 * Each subsystem will run in a different thread
 * on_frame called each frame. Called as much as we can.
 * on_step called periodically
 * A typical init function is in this format:
 *   int vge_scene_manager_init(struct vge_game *, struct vge_subsystem **)
 * and it registers the subsystem to game with vge_game_add_subsystem.
 */
struct vge_subsystem {
  struct vge_list subsys_list;
  void (*init)(struct vge_game *, struct vge_subsystem *);
  void (*destroy)(struct vge_game *, struct vge_subsystem *);
  void (*on_frame)(struct vge_game *, struct vge_subsystem *);
  void (*on_step)(struct vge_game *, struct vge_subsystem *);
  char name[32];
};

#endif

