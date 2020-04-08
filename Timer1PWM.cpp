
#include <Arduino.h>
#include "ArduinoPWM.h"

void pwm::init_timer1()
{
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = 0; 
    ICR1 = 0; 
    // Mode 14 Fast PWM, TOP=ICR1
    TCCR1A |= (1 << WGM11); 
    TCCR1B |= (1 << WGM12) | (1 << WGM13);
    ICR1 = 0;
}

void pwm::init_pin_D9()
{   
    if (!called1) 
    {
        init_timer1();
        called1 = true;
    }

    DDRB |= (1 << DDB1); // PB1 (OC1A) --> OUTPUT
    // connect OC1A, Clear OC1A on compare match, set OC1A at BOTTOM (non-inverting mode) -> digital pin 9
    TCCR1A |= (1 << COM1A1); 
}

void pwm::init_pin_D10()
{   
    if (!called1) 
    {
        init_timer1();
        called1 = true;
    }

    DDRB |= (1 << DDB2); // PB2 (OC1B) --> OUTPUT
    // connect OC1B, Clear OC1B on compare match, set OC1B at BOTTOM (non-inverting mode) -> digital pin 10
    TCCR1A |= (1 << COM1B1); 
}

void pwm::set_frequency_D9_D10(unsigned int freq)
{   
    if (freq > 62500 || freq < 4)
        return;

    TCCR1B &= ~(1 << CS11) & ~(1 << CS10);

    if (freq <= 31) // prescaler 64
    {
        TCCR1B |= (1 << CS11) | (1 << CS10);
        prescaler1 = 64;
    }
    else if (freq > 31 && freq <= 244) // prescaler 8
    {
        TCCR1B |= (1 << CS11);
        prescaler1 = 8;
    }
    else if (freq > 244) // prescaler 1
    {
        TCCR1B |= (1 << CS10);
        prescaler1 = 1;
    }

    ICR1 = ((CLK_SPEED/(prescaler1*freq)) -1);
    TCNT1 = 0; 
}

void pwm::set_duty_cycle_D9(float dcycle)
{   
    if (dcycle > 100 || dcycle < 0)
        return;
    
    float pVal = dcycle / 100;
    int dutyCycle = pVal * ICR1;
    OCR1A = dutyCycle;
}

void pwm::set_duty_cycle_D10(float dcycle)
{   
     if (dcycle > 100 || dcycle < 0)
        return;

    float pVal = dcycle / 100;
    int dutyCycle = pVal * ICR1;
    OCR1B = dutyCycle;
}

long int pwm::get_frequency_D9_D10()
{
    long int freq = CLK_SPEED/(prescaler1*(1UL+ICR1));
    return freq;
}

int pwm::get_resolution_D9_D10()
{
    return ICR1;
}