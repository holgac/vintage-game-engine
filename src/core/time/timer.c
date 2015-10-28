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

#include <time.h>
#include "core/time/timer.h"

float vge_timer_cur_time()
{
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return ts.tv_sec + ts.tv_nsec * 0.000000001f;
}

float vge_stopwatch_elapsed(struct vge_stopwatch *sw)
{
	return vge_timer_cur_time() - sw->start_time;
}

float vge_stopwatch_reset(struct vge_stopwatch *sw)
{
	float t, d;
	t = vge_timer_cur_time();
	d = t - sw->start_time;
	sw->start_time = t;
	return d;
}

void vge_timer_init(struct vge_timer *tm, float period)
{
	tm->period = period;
	tm->expected = vge_timer_cur_time() + period;
}

int vge_timer_check(struct vge_timer *tm)
{
	float t = vge_timer_cur_time();
	if(tm->expected < t) {
		tm->expected += tm->period;
		return 1;
	}
	return 0;
}

void vge_timed_counter_init(struct vge_timed_counter *tc, float period)
{
	tc->count = 0;
	vge_timer_init(&tc->timer, period);
}

u32 vge_timed_counter_increment(struct vge_timed_counter *tc)
{
	u32 c;
	tc->count++;
	if(vge_timer_check(&tc->timer)) {
		c = tc->count;
		tc->count = 0;
		return c;
	}
	return 0;
}
