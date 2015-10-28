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
#ifndef __VGE_ENGINE_H
#define __VGE_ENGINE_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define VGETEST void
void expect(int result, char *errormsg);

typedef char s8;
typedef short s16;
typedef int s32;
typedef long s64;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long u64;
#define vge_offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#define vge_container_of(ptr, type, member) ({\
	const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
	(type *)( (char *)__mptr - vge_offsetof(type,member) );})
/*
 * Used for testing interactive parts
 */
int game_main(int argc, char **argv);
#endif
