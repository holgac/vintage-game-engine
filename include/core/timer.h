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