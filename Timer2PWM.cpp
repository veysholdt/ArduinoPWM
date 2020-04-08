
#include <Arduino.h>
#include "ArduinoPWM.h"

void pwm::init_timer2()
{
    TCCR2A = 0;
    TCCR2B = 0;
    TCNT2 = 0; 
    // Mode 3 Fast PWM, TOP=0xFF (255)
    TCCR2A |= (1 << WGM20) | (1 << WGM21); 
}

void pwm::init_pin_D11()
{   
    if (!called2) 
    {
        init_timer2();
        called2 = true;
    }

    DDRB |= (1 << DDB3); // PB3 (OC2A) --> OUTPUT
    // connect OC2A, Clear OC2A on compare match, set OC2A at BOTTOM (non-inverting mode) -> digital pin 11
    TCCR2A |= (1 << COM2A1); 
}

void pwm::init_pin_D3()
{   
    if (!called2) 
    {
        init_timer2();
        called2 = true;
    }

    DDRD |= (1 << DDD3); // PD3 (OC2B) --> OUTPUT
    // connect OC2B, Clear OC2B on compare match, set OC2B at BOTTOM (non-inverting mode) -> digital pin 3
    TCCR2A |= (1 << COM2B1); 
}

void pwm::set_frequency_D3_D11(unsigned int freq)
{   
    TCCR2B &= ~(1 << CS22) & ~(1 << CS21) & ~(1 << CS20);

    switch (freq)
    {
        case    61: TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);  //prescaler 1024
                    prescaler2 = 1024; 
                    break;   
        case   244: TCCR2B |= (1 << CS22) | (1 << CS21);                //prescaler 256
                    prescaler2 = 256; 
                    break;
        case   488: TCCR2B |= (1 << CS22) | (1 << CS20);                //prescaler 128
                    prescaler2 = 128; 
                    break;
        case   976: TCCR2B |= (1 << CS22);                               //prescaler 64
                    prescaler2 = 64; 
                    break;
        case  1953: TCCR2B |= (1 << CS21) | (1 << CS20);                //prescaler 32
                    prescaler2 = 32; 
                    break;
        case  7812: TCCR2B |= (1 << CS21);                              //prescaler 8
                    prescaler2 = 8; 
                    break;
        case 62500: TCCR2B |= (1 << CS20);                              //prescaler 1
                    prescaler2 = 1; 
                    break;
        default: return;
    }
}

void pwm::set_duty_cycle_D11(float dcycle)
{   
    if (dcycle > 100 || dcycle < 0)
        return;
    
    if (dcycle == 100)
    {
        TCCR2A &= ~(1 << COM2A1); //disconnect OC2A
        PORTB |= (1 << PORTB3);
    }
    else if (dcycle == 0) 
    {
        TCCR2A &= ~(1 << COM2A1); //disconnect OC2A
        PORTB &= ~(1 << PORTB3);
    }
    else
    {   
        TCCR2A |= (1 << COM2A1); //connect OC2A
        float pVal = dcycle / 100;
        int dutyCycle = pVal * 255;
        OCR2A = dutyCycle;
    }
}

void pwm::set_duty_cycle_D3(float dcycle)
{   
    if (dcycle > 100 || dcycle < 0)
        return;
    
    if (dcycle == 100) 
    { 
        TCCR2A &= ~(1 << COM2B1); //disconnect OC2B
        PORTD |= (1 << PORTD3);
    }
    else if (dcycle == 0)
    { 
        TCCR2A &= ~(1 << COM2B1); //disconnect OC2B
        PORTD &= ~(1 << PORTD3);
    }
    else
    {   
        TCCR2A |= (1 << COM2B1); //connect OC2B
        float pVal = dcycle / 100;
        int dutyCycle = pVal * 255;
        OCR2B = dutyCycle;
    }
}

long int pwm::get_frequency_D3_D11()
{
    long int freq = CLK_SPEED/(prescaler2*256UL);
    return freq;
}

int pwm::get_resolution_D3_D11()
{
    return 255;
}
