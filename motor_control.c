#include <xc.h>
#include "sumovore.h"
#include "motor_control.h"

void follow_simple_curves(void);
void spin_left(void);
void turn_left(void);
void straight_fwd(void);
void turn_right(void);
void spin_right(void);

void straight_forward_fast(void);
void straight_forward_medium(void);
void straight_forward_slow(void);
void straight_stop(void);
void straight_reverse_slow(void);
void straight_reverse_medium(void);
void straight_reverse_fast(void);

void default_settings(void);

void motor_control(void)
{
    
}

void follow_simple_curves(void)
{
     if ( SeeLine.b.Center ) straight_fwd();
     else if (SeeLine.b.Left) spin_left();
     else if (SeeLine.b.CntLeft) turn_left();
     else if (SeeLine.b.CntRight) turn_right();
    else if (SeeLine.b.Right) spin_right();
}

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

//******

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

void default_settings(void)
{
    OpenTimer0(TIMER_INT_OFF & T0_SOURCE_INT & T0_16BIT & T0_PS_1_256);
    
    WriteTimer0(0);
    TMR0IF = 0;
    while(!TMR0IF)
    {
        straight_forward_fast();
    }
        
    WriteTimer0(0);
    TMR0IF = 0;
    while(!TMR0IF)
    {
        straight_forward_medium();
    }
    
    WriteTimer0(0);
    TMR0IF = 0;
    while(!TMR0IF)
    {
        straight_forward_slow();
    }
    
    WriteTimer0(0);
    TMR0IF = 0;
    while(!TMR0IF)
    {
        straight_stop();
    }
    

    WriteTimer0(0);
    TMR0IF = 0;
    while(!TMR0IF)
    {
        straight_reverse_slow();
    }
   
    WriteTimer0(0);
    TMR0IF = 0;
    while(!TMR0IF)
    {
        straight_reverse_medium();
    }
    
    WriteTimer0(0);
    TMR0IF = 0;
    while(!TMR0IF)
    {
        straight_reverse_fast();
    }
    
    WriteTimer0(0);
    TMR0IF = 0;
    while(!TMR0IF)
    {
        straight_stop();
    }
    
     very simple motor control
     switch(SeeLine.B)
     {
        case 0b00100u:
        case 0b00010u:
        case 0b01000u:
        case 0b00001u:
        case 0b10000u:
                       no breaks all above readings end up here
                       follow_simple_curves();
                       break;
        case 0b00000u:
                        motors_brake_all();
                       break;
        default:       break;
      } 
}