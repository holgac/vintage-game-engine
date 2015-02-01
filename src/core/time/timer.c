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
#include <sys/types.h>
#include <core/time/timer.h>
#include <mach/clock.h>
#include <mach/mach.h>
/*
	Storing current time is beneficial both in terms of speed
		and consistency.
 */
float _vge_cur_time;

float vge_timer_cur_time()
{
#ifdef __MACH__ // OS X does not have clock_gettime, use clock_get_time
	clock_serv_t cclock;
	mach_timespec_t tm;
	host_get_clock_service(mach_host_self(), SYSTEM_CLOCK, &cclock);
	clock_get_time(cclock, &tm);
	mach_port_deallocate(mach_task_self(), cclock);
	return (tm.tv_sec + (tm.tv_nsec * 0.000000001f));
#else
	struct timespec tm;
	clock_gettime(CLOCK_MONOTONIC, &tm);
	return (tm.tv_sec + (tm.tv_nsec * 0.000000001f));
#endif
}

void vge_timer_init(struct vge_timer* timer, float period)
{
	timer->expected_time = _vge_cur_time + period;
	timer->period = period;
}
int vge_timer_check(struct vge_timer* timer, int flags)
{
	if(_vge_cur_time < timer->expected_time)
		return 0;
	if(flags & VGETIMER_REWIND)
		timer->expected_time += timer->period;
	else if(flags & VGETIMER_REWIND_HARD)
		timer->expected_time = _vge_cur_time + timer->period;
	return 1;
}

void vge_timer_update()
{
	_vge_cur_time = vge_timer_cur_time();
}

void vge_stopwatch_init(struct vge_stopwatch* stopwatch)
{
	stopwatch->start_time = _vge_cur_time;
	stopwatch->is_running = 1;
}
float vge_stopwatch_elapsed(struct vge_stopwatch* stopwatch)
{
	if(stopwatch->is_running)
		return _vge_cur_time - stopwatch->start_time;
	return stopwatch->start_time;

}
/*
	Pauses stopwatch
 */
void vge_stopwatch_pause(struct vge_stopwatch* stopwatch)
{
	/*
		TODO: assert(is_running)
	 */
	stopwatch->start_time = vge_stopwatch_elapsed(stopwatch);
	stopwatch->is_running = 0;
}
/*
	Resumes stopwatch
 */
void vge_stopwatch_resume(struct vge_stopwatch* stopwatch)
{
	/*
		TODO: assert(!is_running)
	 */
	stopwatch->start_time = _vge_cur_time - stopwatch->start_time;
}
