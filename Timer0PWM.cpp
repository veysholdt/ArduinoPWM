
#include <Arduino.h>
#include "ArduinoPWM.h"

void pwm::init_timer0()
{
    TCCR0A = 0;
    TCCR0B = 0;
    TCNT0 = 0; 
    // Mode 3 Fast PWM, TOP=0xFF (255)
    TCCR0A |= (1 << WGM00) | (1 << WGM01); 
}

void pwm::init_pin_D6()
{   
    if (!called0) 
    {
        init_timer0();
        called0 = true;
    }

    DDRD |= (1 << DDD6); // PD6 (OC0A) --> OUTPUT
    // connect OC0A, Clear OC0A on compare match, set OC0A at BOTTOM (non-inverting mode) -> digital pin 6
    TCCR0A |= (1 << COM0A1); 
}

void pwm::init_pin_D5()
{   
    if (!called0) 
    {
        init_timer0();
        called0 = true;
    }

    DDRD |= (1 << DDD5); // PD5 (OC0B) --> OUTPUT
    // connect OC0B, Clear OC0B on compare match, set OC0B at BOTTOM (non-inverting mode) -> digital pin 5
    TCCR0A |= (1 << COM0B1); 
}

void pwm::set_frequency_D5_D6(unsigned int freq)
{   
    TCCR0B &= ~(1 << CS02) & ~(1 << CS01) & ~(1 << CS00);

    switch (freq)
    {
        case    61: TCCR0B |= (1 << CS02) | (1 << CS00);    //prescaler 1024
                    prescaler0 = 1024; 
                    break;   
        case   244: TCCR0B |= (1 << CS02);                  //prescaler 256
                    prescaler0 = 256; 
                    break;
        case   976: TCCR0B |= (1 << CS01) | (1 << CS00);    //prescaler 64
                    prescaler0 = 64; 
                    break;
        case  7812: TCCR0B |= (1 << CS01);                  //prescaler 8
                    prescaler0 = 8; 
                    break;
        case 62500: TCCR0B |= (1 << CS00);                  //prescaler 1
                    prescaler0 = 1; 
                    break;
        default: return;
    }
}

void pwm::set_duty_cycle_D6(float dcycle)
{   
    if (dcycle > 100 || dcycle < 0)
        return;
    
    if (dcycle == 100)
    {
        TCCR0A &= ~(1 << COM0A1); //disconnect OC0A
        PORTD |= (1 << PORTD6);
    }
    else if (dcycle == 0) 
    {
        TCCR0A &= ~(1 << COM0A1); //disconnect OC0A
        PORTD &= ~(1 << PORTD6);
    }
    else
    {   
        TCCR0A |= (1 << COM0A1); //connect OC0A
        float pVal = dcycle / 100;
        int dutyCycle = pVal * 255;
        OCR0A = dutyCycle;
    }
}

void pwm::set_duty_cycle_D5(float dcycle)
{   
    if (dcycle > 100 || dcycle < 0)
        return;
    
    if (dcycle == 100) 
    { 
        TCCR0A &= ~(1 << COM0B1); //disconnect OC0B
        PORTD |= (1 << PORTD5);
    }
    else if (dcycle == 0) 
    { 
        TCCR0A &= ~(1 << COM0B1); //disconnect OC0B
        PORTD &= ~(1 << PORTD5);
    }
    else
    {   
        TCCR0A |= (1 << COM0B1); //connect OC0B
        float pVal = dcycle / 100;
        int dutyCycle = pVal * 255;
        OCR0B = dutyCycle;
    }
}

long int pwm::get_frequency_D5_D6()
{
    long int freq = CLK_SPEED/(prescaler0*256UL);
    return freq;
}

int pwm::get_resolution_D5_D6()
{
    return 255;
}
