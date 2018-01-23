#include "vge.h"
struct vge_test_game {
  struct vge_subsystem subsys;
  struct vge_subsystem *renderer;
  struct vge_subsystem *input;
  struct vge_subsystem *scene_manager;
  struct vge_camera camera;
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
  struct vge_entity *entity;
  struct vge_quaternion quat, quat2;
  entity = vge_scene_get_entity(
      vge_scene_manager_get_cur_scene(test_game->scene_manager),
      "the_only_cube");
  if(vge_input_keypressed(test_game->input, VGEINPUT_KEY_ESCAPE) ||
      vge_input_keypressed(test_game->input, VGEINPUT_KEY_Q)) {
    printf("exiting...\n");
    vge_game_stop(game);
  }
  if(vge_input_keyheld(test_game->input, VGEINPUT_KEY_A)) {
    entity->position.x += game->frame_dt * 0.5f;
  }
  if(vge_input_keyheld(test_game->input, VGEINPUT_KEY_D)) {
    entity->position.x -= game->frame_dt * 0.5f;
  }
  if(vge_input_keyheld(test_game->input, VGEINPUT_KEY_W)) {
    entity->position.y += game->frame_dt * 0.5f;
  }
  if(vge_input_keyheld(test_game->input, VGEINPUT_KEY_S)) {
    entity->position.y -= game->frame_dt * 0.5f;
  }
  if(vge_input_keyheld(test_game->input, VGEINPUT_KEY_Z)) {
    entity->position.z += game->frame_dt * 1.0f;
  }
  if(vge_input_keyheld(test_game->input, VGEINPUT_KEY_C)) {
    entity->position.z -= game->frame_dt * 1.0f;
  }
  if(vge_input_keyheld(test_game->input, VGEINPUT_KEY_R)) {
    vge_quaternion_construct(&quat, &vge_vector4_x, game->frame_dt * 0.5f);
    vge_quaternion_multq(&quat2, &quat, &entity->rotation);
    vge_quaternion_setq(&entity->rotation, &quat2);
  }
  if(vge_input_keyheld(test_game->input, VGEINPUT_KEY_T)) {
    vge_quaternion_construct(&quat, &vge_vector4_y, game->frame_dt * 0.5f);
    vge_quaternion_multq(&quat2, &quat, &entity->rotation);
    vge_quaternion_setq(&entity->rotation, &quat2);
  }
  if(vge_input_keyheld(test_game->input, VGEINPUT_KEY_Y)) {
    vge_quaternion_construct(&quat, &vge_vector4_z, game->frame_dt * 0.5f);
    vge_quaternion_multq(&quat2, &quat, &entity->rotation);
    vge_quaternion_setq(&entity->rotation, &quat2);
  }
  if(vge_input_keypressed(test_game->input, VGEINPUT_KEY_U)) {
    vge_quaternion_normalize(&entity->rotation);
  }
}

static void _on_step(struct vge_game *game, struct vge_subsystem *subsys)
{
}


int main(int argc, char **argv)
{
	printf("Running sample2\n");
  struct vge_game game;
  struct vge_test_game test_game;

  vge_game_init(&game);
  vge_vector3_set(&test_game.camera.pos, 0, 0, -10);
  vge_vector3_set(&test_game.camera.dir, 0, 0, 1);
  vge_vector3_set(&test_game.camera.up, 0, 1, 0);
  test_game.camera.fov = 50.0f;
  test_game.camera.near = 1.5f;
  test_game.camera.far = 50.0f;
  vge_renderer_init(&game, NULL, &test_game.camera, &test_game.renderer);

  vge_input_init(&game, &test_game.input);
  vge_scene_manager_init(&game, &test_game.scene_manager);
  vge_resource_manager_load_recursive(&game.rman, &game, "./resources/textures");
  vge_resource_manager_load_recursive(&game.rman, &game, "./resources/prefabs");
  vge_resource_manager_load_recursive(&game.rman, &game, "./resources/scenes");
  vge_scene_manager_load_scene(&game, test_game.scene_manager, "scene1");

  test_game.subsys.init = _init;
  test_game.subsys.destroy = _destroy;
  test_game.subsys.on_frame = _on_frame;
  test_game.subsys.on_step = _on_step;

  vge_game_add_subsystem(&game, &test_game.subsys);
  vge_game_start(&game);
  vge_game_destroy(&game);

  return 0;
}
