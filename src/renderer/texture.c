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

#define ILUT_USE_OPENGL
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "renderer/texture.h"
#include "core/resource/resource.h"
#include "core/resource/resourceloader.h"

struct vge_texture
{
  struct vge_resource resource;
  ILuint handle;
};

static GLuint _load_devil_texture(const char *path)
{
  ILuint il_handle;
  GLuint gl_handle;
  ilGenImages(1, &il_handle);
  ilBindImage(il_handle);
  ilLoadImage(path);
  gl_handle = ilutGLBindTexImage();
  ilDeleteImages(1, &il_handle);
  return gl_handle;
}

static struct vge_resource *_load_texture(struct vge_resource_loader *loader,
    struct vge_game *game, const char *path)
{
  struct vge_texture *texture;
  char *name;
  texture = malloc(sizeof(struct vge_texture));
  name = strrchr(path, '/') + 1;
  strcpy(texture->resource.name, name);
  texture->resource.loader = loader;
  texture->handle = _load_devil_texture(path);
  return &texture->resource;
}

static struct vge_resource *_clone_texture(struct vge_resource_loader *loader,
    struct vge_resource *old_res)
{
  return NULL;
}

static void _unload_texture(struct vge_resource_loader *loader,
    struct vge_resource *res)
{
}

static void _init_devil()
{
  ilInit ();
  iluInit();
  ilutInit();
  ilEnable(IL_CONV_PAL);
  ilutEnable(ILUT_OPENGL_CONV);
  ilutRenderer (ILUT_OPENGL);
}

struct vge_resource_loader *vge_texture_get_loader()
{
  struct vge_resource_loader *loader;
  loader = malloc(sizeof(struct vge_resource_loader));
  loader->load = _load_texture;
  loader->clone = _clone_texture;
  loader->unload = _unload_texture;
  /* TODO: this is probably the worst place to call DevIL init functions */
  _init_devil();
  strcpy(loader->name, "png");
  return loader;
}

void *vge_texture_get_handle(struct vge_resource *res)
{
  struct vge_texture *texture;
  texture = vge_container_of(res, struct vge_texture, resource);
  return (void *)&texture->handle;
}
