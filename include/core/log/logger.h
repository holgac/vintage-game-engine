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

#ifndef __VGE_LOGGER_H
#define __VGE_LOGGER_H
#include "engine.h"

#define VGE_LOGGER_CRIT 5
#define VGE_LOGGER_ERR 4
#define VGE_LOGGER_WARNING 3
#define VGE_LOGGER_NOTICE 2
#define VGE_LOGGER_INFO 1
#define VGE_LOGGER_DEBUG 0

#define vge_log(fmt, ...) vge_log_inner("%s:%u: " fmt, __FILE__, __LINE__, ##  __VA_ARGS__)

#define vge_log_and_return(retval, ...) { \
		vge_log(__VA_ARGS__); \
		return retval; \
	}

#define vge_log_and_vreturn(...) { \
		vge_log(__VA_ARGS__); \
		return; \
	}

#define vge_log_and_goto(label, ...) { \
		vge_log(__VA_ARGS__); \
		goto label; \
	}
void vge_log_inner(const char *fmt, ...);
#endif
