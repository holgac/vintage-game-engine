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

#include "external/nxjson/nxjson.h"
#include "renderer/graphicscomponent.h"
#include "renderer/texture.h"
#include "core/math/vertex3.h"
#include "core/math/math.h"
#include "core/math/vector3.h"
#include "core/math/matrix4.h"
#include "core/scene/component.h"
#include "core/scene/componentloader.h"
#include "core/scene/entity.h"
#include "core/log/logger.h"
#include "core/game.h"

#define VGE_GRAPHICS_COMPONENT_CLONE 1

struct vge_graphics_component
{
  struct vge_component component;
  u32 num_vertices;
  struct vge_vertex3 *vertices;
  u32 num_indices;
  u32 *indices;
  u32 flags;
  struct vge_resource *texture;
};

struct vge_component *_load_component(struct vge_component_loader *loader,
    struct vge_game *game, const struct nx_json *json)
{
  const struct nx_json *elem;
  struct vge_graphics_component *comp;
  u32 i;
  comp = malloc(sizeof(struct vge_graphics_component));
  elem = nx_json_get(json, "vertices");
  if(!elem)
    vge_log_and_goto(freecomp, "Graphics Component should have vertices!");
  comp->vertices = malloc(elem->length * sizeof(struct vge_vertex3));
  for(i=0; i<elem->length; ++i)
    vge_vertex3_read(&comp->vertices[i], nx_json_item(elem, i));
  comp->num_vertices = elem->length;

  elem = nx_json_get(json, "indices");
  if(!elem)
    vge_log_and_goto(freevert, "Graphics Component should have indices!");
  comp->indices = malloc(elem->length * 3 * sizeof(u32));
  for(i=0; i<elem->length; ++i)
    sscanf(nx_json_item(elem, i)->text_value, "%u %u %u",
        &comp->indices[i*3], &comp->indices[i*3 + 1],
        &comp->indices[i*3 + 2]);
  comp->num_indices = elem->length;
  elem = nx_json_get(json, "texture");
  if(!elem)
    comp->texture = NULL;
  else {
    comp->texture = vge_resource_manager_get_resource(&game->rman, elem->text_value);
  }
  comp->component.loader = loader;
  comp->flags = 0;

  return &comp->component;
freevert:
  free(comp->vertices);

freecomp:
  free(comp);
  return NULL;
}

struct vge_component *_clone_component(struct vge_component_loader *loader,
    struct vge_component *comp)
{
  struct vge_graphics_component *orig, *clone;
  orig = vge_container_of(comp, struct vge_graphics_component, component);
  clone = malloc(sizeof(struct vge_graphics_component));
  clone->component.loader = orig->component.loader;
  vge_list_init(&clone->component.comp_node);
  clone->num_vertices = orig->num_vertices;
  clone->vertices = orig->vertices;
  clone->num_indices = orig->num_indices;
  clone->indices = orig->indices;
  clone->texture = orig->texture;
  clone->flags = orig->flags | VGE_GRAPHICS_COMPONENT_CLONE;
  return &clone->component;
}

void _unload_component(struct vge_component_loader *loader,
    struct vge_component *comp)
{
  struct vge_graphics_component *grcomp;
  grcomp = vge_container_of(comp, struct vge_graphics_component, component);
  if (!(grcomp->flags & VGE_GRAPHICS_COMPONENT_CLONE)) {
    free(grcomp->indices);
    free(grcomp->vertices);
  }
  free(grcomp);
}

void _on_step(struct vge_component *comp, struct vge_entity *ent)
{
}

void _on_frame(struct vge_component *comp, struct vge_entity *ent)
{
  struct vge_graphics_component *grcomp;
  u32 i;
  struct vge_vertex3 *vert;
  GLuint *handle;
  struct vge_matrix4 mat;
  grcomp = vge_container_of(comp, struct vge_graphics_component, component);
  glPushMatrix();
  vge_matrix4_construct(&mat, &ent->rotation, &ent->position);
  glMultMatrixf(mat.m);
  if (grcomp->texture) {
    glEnable(GL_TEXTURE_2D);
    handle = vge_texture_get_handle(grcomp->texture);
    glBindTexture(GL_TEXTURE_2D, *handle);
  } else {
    glDisable(GL_TEXTURE_2D);
  }
  
  /* TODO: vertex/index buffer rendering */
  glBegin(GL_TRIANGLES);
  for(i=0; i<grcomp->num_indices; ++i) {
    vert = grcomp->vertices + grcomp->indices[i*3];
    glTexCoord2fv(&vert->texcoord.x);
    glVertex3fv(&vert->position.x);
    vert = grcomp->vertices + grcomp->indices[i*3 + 1];
    glTexCoord2fv(&vert->texcoord.x);
    glVertex3fv(&vert->position.x);
    vert = grcomp->vertices + grcomp->indices[i*3 + 2];
    glTexCoord2fv(&vert->texcoord.x);
    glVertex3fv(&vert->position.x);
  }
  glEnd();
  glPopMatrix();
}

struct vge_component_loader *vge_graphics_component_get_loader()
{
  struct vge_component_loader *loader;
  loader = malloc(sizeof(struct vge_component_loader));
  strcpy(loader->name, "graphics_component_raw");
  loader->load = _load_component;
  loader->clone = _clone_component;
  loader->unload = _unload_component;
  loader->on_step = _on_step;
  loader->on_frame = _on_frame;
  return loader;
}
