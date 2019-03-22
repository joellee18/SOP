#include <xc.h>
#include "sumovore.h"
#include "motor_control.h"

void follow_simple_curves(void);
void follow_right_angle_turn(void);
void follow_acute_angle_turn(void);

unsigned char left_counter(unsigned char left_value);
unsigned char right_counter(unsigned char right_value);

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
//unsigned char last_sense = 0b00000u;
unsigned char last_sense_left = 0b00000000u;
unsigned char last_sense_right = 0b00000000u;
unsigned char right_value, left_value;

void motor_control(void)
{
    follow_simple_curves();
    left_counter(left_value);
    right_counter(right_value);
    follow_right_angle_turn();
    follow_acute_angle_turn();
     //very simple motor control
//     switch(SeeLine.B)      //defined sumovore.h > struct sensors
//                            //                   > union sensors_union
//                            //                   > extern union union_sensor SeeLine
//     {
//        case 0b00100u:      //Center
//        case 0b00010u:      //CntRight
//        case 0b01000u:      //CntLeft
//        case 0b00001u:      //Right
//        case 0b10000u:      //Left
//                       //no breaks all above readings end up here
//                       left_counter(0);
//                       right_counter(0);
//                       follow_simple_curves();
//                       break;
//                       
//  
//        case 0b11100u: 
//        case 0b00111u:    
//   
//                         left_counter(left_value);
//                         right_counter(right_value);
//                         follow_right_angle_turn();
////                       follow_acute_angle_turn();
//                       break;
//
//        case 0b00000u:      //no sensors on
//                        motors_brake_all();
//                       break;
//        default:       break;
//      } 
}


unsigned char right_counter(unsigned char right_value)
{
    if (SeeLine.B == 0b00111u)
    {
        //straight_fwd();
        right_value++;
    }
    return right_value;
}

unsigned char left_counter(unsigned char left_value)
{
    if (SeeLine.B == 0b11100u)
    {
        //straight_fwd();
        left_value++;
    }
    return left_value;
}

void follow_simple_curves(void)
{
     if ( SeeLine.b.Center ) straight_fwd();        //sensors bit 2, 0b00100u
     else if (SeeLine.b.Left) spin_left();          //sensors bit 4, 0b10000u
     else if (SeeLine.b.CntLeft) turn_left();       //sensors bit 3, 0b01000u
     else if (SeeLine.b.CntRight) turn_right();     //sensors bit 1, 0b00010u
     else if (SeeLine.b.Right) spin_right();        //sensors bit 0, 0b00001u
}

void follow_right_angle_turn(void)
{
    unsigned char detect_right_value = 0, detect_left_value = 0;
    
    detect_right_value = right_counter(right_value);
    detect_left_value = left_counter(left_value);
    
    if (detect_right_value > detect_left_value)
    {
        spin_right;
        right_counter(0);
        left_counter(0);
    }
    else if (detect_right_value < detect_left_value)
    {
        spin_left;
        right_counter(0);
        left_counter(0);
    }
    else if (detect_right_value == detect_left_value)
    {
        straight_fwd;  
        right_counter(0);
        left_counter(0);
    }
    
}

void follow_acute_angle_turn(void)
{
//    if (SeeLine.B == 0b00101u) SeeLine.B = last_sense;
//    {
//        straight_fwd();
//        for (int i=0; i<25; i++)  //
//            _delay(100000ul); //  1/80 s
//        spin_right();
//        for (int i=0; i<40; i++)  //
//            _delay(100000ul); //  1/80 s
//    }
//    
//    if (SeeLine.B == 0b10100u) SeeLine.B = last_sense;
//    {
//        straight_fwd();
//        for (int i=0; i<60; i++)  //
//            _delay(100000ul); //  1/80 s
//        spin_left();
//        for (int i=0; i<40; i++)  //
//            _delay(100000ul); //  1/80 s
//    }
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


//void spin_left(void)
//{
//  set_motor_speed(left, rev_fast, 0); //
//  set_motor_speed(right, fast, 0); //
//}
//
//void turn_left(void)
//{
//  set_motor_speed(left, stop, 0); //
//  set_motor_speed(right, fast, 0); //
//}
//void straight_fwd(void)
//{
//  set_motor_speed(left, fast, -100); //
//  set_motor_speed(right, fast, 0); //
//}
//void spin_right(void)
//{
//  set_motor_speed(left, fast, -100); //
//  set_motor_speed(right, rev_fast, 0); //
//}
//void turn_right(void)
//{
//  set_motor_speed(left, fast, -100); //
//  set_motor_speed(right, stop, 0); //
//}
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
 
}
