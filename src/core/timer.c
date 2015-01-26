#include <sys/types.h>
#include <core/timer.h>
#include <mach/clock.h>
#include <mach/mach.h>
/*
	Storing current time is beneficial both in terms of speed
		and consistency.
 */
float _vge_cur_time;

static float _vge_get_cur_time()
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
	_vge_cur_time = _vge_get_cur_time();
}
