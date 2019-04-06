#include <xc.h>
#include "challenge_actions.h"
#include "sumovore.h"

unsigned char left_counter3(unsigned char left_value3)
{
    if (SeeLine.B == 0b11100u)
        left_value3++;
    
    return left_value3;
}

unsigned char right_counter3(unsigned char right_value3)
{
    if (SeeLine.B == 0b00111u)
        right_value3++;

   return right_value3; 
}

void follow_simple_curves(void)
{
        if (SeeLine.b.Center)
            straight_forward_fast();       //sensors bit 2, 0b00100u
        else if (SeeLine.b.Left)
            spin_left();          //sensors bit 4, 0b10000u
        else if (SeeLine.b.CntLeft)
            turn_left();          //sensors bit 3, 0b01000u
        else if (SeeLine.b.CntRight) 
            turn_right();        //sensors bit 1, 0b00010u
        else if (SeeLine.b.Right)
            spin_right();        //sensors bit 0, 0b00001u
}

void follow_right_angle_crossover(void)
{
    unsigned char detect_left_value3, detect_right_value3;
    detect_right_value3 = right_counter3(right_value3);
    detect_left_value3 = left_counter3(left_value3);
    
    if (detect_right_value3 > detect_left_value3)
    {
        spin_right;
        right_counter3(0);
        left_counter3(0);
    }
    else if (detect_right_value3 < detect_left_value3)
    {
        spin_left;
        right_counter3(0);
        left_counter3(0);
    }
    else if (detect_right_value3 == detect_left_value3)
    {
        straight_fwd;  
        right_counter3(0);
        left_counter3(0);
    }
}

void follow_acute_angle_turn(void)
{
    if ((SeeLine.B == 0b10100u)||(SeeLine.B == 0b11110u))
    {
       straight_forward_slow();
       _delay(100000ul);
       
       left_acute = 1;
    } 
    
    if ((SeeLine.B == 0b00101u)||(SeeLine.B == 0b01111u))
    {
       straight_forward_slow();
       _delay(100000ul);
       
       right_acute = 1;
    }
    
    if ( SeeLine.B == 0b00000u && left_acute == 1 && right_acute != 1 )
    {
         set_motor_speed(left, rev_fast, 0); 
         set_motor_speed(right, fast, 0);
         for (int j = 0; j < 25; j++)      // 0.5 s
             _delay(100000ul);
         
         OpenTimer0(TIMER_INT_OFF & T0_SOURCE_INT & T0_16BIT & T0_PS_1_128);     //1 second

         WriteTimer0(0);
         TMR0IF = 0;

         while(!TMR0IF)
         {
            follow_simple_curves();
         }
         
         left_acute = 0;
    }
    
    if ( SeeLine.B == 0b00000u && right_acute == 1 && left_acute != 1 )
    {
         set_motor_speed(left, fast, 0); 
         set_motor_speed(right, rev_fast, 0);
         for (int j = 0; j < 25; j++)      // 0.5 s
             _delay(100000ul);

         OpenTimer0(TIMER_INT_OFF & T0_SOURCE_INT & T0_16BIT & T0_PS_1_128);     //1 second

         WriteTimer0(0);
         TMR0IF = 0;

         while(!TMR0IF)
         {
            follow_simple_curves();
         }
         
         right_acute = 0;
    }
}

void follow_gaps_deadends(void)
{
    
    if (SeeLine.B == 0b00000u && none_value == 0 && left_acute == 0 && right_acute == 0)     
    {

        OpenTimer0(TIMER_INT_OFF & T0_SOURCE_INT & T0_16BIT & T0_PS_1_128);
        WriteTimer0(0);
        TMR0IF = 0;
        while(!TMR0IF)
        {
            straight_forward_fast(); 
        }
        none_value++;
    }    
    
    else if (none_value == 1 && SeeLine.B == 0b00000u)
    {
        straight_reverse_slow();
        for( int i = 0 ; i < 45; i++)
            _delay(100000ul);
        none_value++;
    }
    
    else if (none_value == 2 && SeeLine.B == 0b00000u)
    {
        spin_right();
        for( int i = 0 ; i < 55; i++)
            _delay(100000ul);
        none_value = 0;
    }
    
    else
    {
        follow_simple_curves();
                
        none_value = 0;
    }
}

void follow_landing_pad(void)
{
    if ( SeeLine.B == 0b11111u && all_value > 5 )
    {
        motors_brake_all();
        
        while(1)
            _delay(100000ul);
    }
    
    if (SeeLine.B == 0b11111u)
    {
        all_value++;

        OpenTimer0(TIMER_INT_OFF & T0_SOURCE_INT & T0_16BIT & T0_PS_1_8);
    
        WriteTimer0(0);
        TMR0IF = 0;
        while(!TMR0IF)
        {
            straight_forward_fast(); 
        }
    } 
    
    if (SeeLine.B != 0b11111u && all_value > 0)
    {
        all_value = 0;
    }    
}
