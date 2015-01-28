#ifndef _VGE_TIMER_H_

#define VGETIMER_REWIND 1
#define VGETIMER_REWIND_HARD 2

struct vge_timer
{
	float expected_time;
	float period;
};

/*
	Initializes timer. vge_timer_check will return 0 until
	the time provided (in seconds).
	A timer can be initialized many times
 */
void vge_timer_init(struct vge_timer* timer, float period);
/*
	Returns 0 if the time has not passed, 1 orherwise.
	VGETIMER_REWIND rewinds the timer if the check passes by
			the period provided in vge_timer_init.
	VGETIMER_REWIND_HARD rewinds the timer to now if the check passes.
 */
int vge_timer_check(struct vge_timer* timer, int flags);

/*
	Internal function that is called each frame. do not call.
 */
void vge_timer_update();

/*
	Returns current time in seconds.
	The absolute value may not be meaningful, using time differences
	is clearly a better idea.
 */
float vge_timer_cur_time();

#endif /* _VGE_TIMER_H_ */