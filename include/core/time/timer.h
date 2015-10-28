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
#ifndef __VGE_TIMER_H
#define __VGE_TIMER_H

#include "engine.h"

struct vge_stopwatch
{
	float start_time;
};

struct vge_timer
{
	float period;
	float expected;
};
struct vge_timed_counter
{
	struct vge_timer timer;
	u32 count;
};
/*
 * gets actual time, expensive!
 * TODO: optimize usage, call each frame/step once to ensure consistency
 */
float vge_timer_cur_time();
float vge_stopwatch_reset(struct vge_stopwatch *sw);
float vge_stopwatch_elapsed(struct vge_stopwatch *sw);
void vge_timer_init(struct vge_timer *tm, float period);
int vge_timer_check(struct vge_timer *tm);
void vge_timed_counter_init(struct vge_timed_counter *tc, float period);
u32 vge_timed_counter_increment(struct vge_timed_counter *tc);

#endif

