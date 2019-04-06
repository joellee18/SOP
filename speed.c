#include <xc.h>
#include "sumovore.h"
#include "speed.h"

void spin_left(void)
{
  set_motor_speed(left, rev_fast, 0); 
  set_motor_speed(right, fast, 0); 
}

void turn_left(void)
{
  set_motor_speed(left, stop, 0); 
  set_motor_speed(right, fast, 0); 
}
void straight_fwd(void)
{
  set_motor_speed(left, fast, 0); 
  set_motor_speed(right, fast, 0); 
}
void spin_right(void)
{
  set_motor_speed(left, fast, 0); 
  set_motor_speed(right, rev_fast, 0); 
}
void turn_right(void)
{
  set_motor_speed(left, fast, 0); 
  set_motor_speed(right, stop, 0); 
}

void straight_forward_fast(void)
{
    set_motor_speed(left, fast, -100); 
    set_motor_speed(right, fast, 0);
}

void straight_forward_medium(void)
{
    set_motor_speed(left, medium, -100); 
    set_motor_speed(right, medium, -120);
}

void straight_forward_slow(void)
{
    set_motor_speed(left, slow, -100); 
    set_motor_speed(right, slow, -117);
}

void straight_stop(void)
{
    set_motor_speed(left, stop, 0); 
    set_motor_speed(right, stop, 0);
}

void straight_reverse_slow(void)
{
    set_motor_speed(left, rev_slow, 100); 
    set_motor_speed(right, rev_slow, 130);
}

void straight_reverse_medium(void)
{
    set_motor_speed(left, rev_medium, 100); 
    set_motor_speed(right, rev_medium, 127);
}

void straight_reverse_fast(void)
{
    set_motor_speed(left, rev_fast, 0); 
    set_motor_speed(right, rev_fast, 0);
}

