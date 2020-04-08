
/* 
    PWM Library for ATmega328 (Arduino Uno, Nano, Pro Mini)

* Since two digital PWM-pins are tied to one timer, the PWM-frequency of those is the same.
    - pin 3 and 11 -> timer 2 (8-bit)
    - pin 9 and 10 -> timer 1 (16-bit)
    - pin 5 and 6 -> timer 0 (8-bit)

* PWM-pins D5 and D6:
    - The PWM frequency is fixed to 62500/7812/976/244/61 Hz.
    - The PWM resolution is a fixed to 8-bit.

 PWM-pins D3 and D11:
    - The PWM frequency is fixed to 62500/7812/1953/976/488/244/61 Hz.
    - The PWM resolution is a fixed to 8-bit.

* PWM-pins D9 and D10:
    - The PWM frequency can be set to any value from 4 - 62500 Hz.
    - The PWM-resolution depends on the PWM-frequency
    - The minimal resolution is 8-bit (62500 Hz)

* NOTE:
    - Any changes to timer 0 (pin D5 and D6) may effect the time-functions of the Arduino-Library,
      which may cause problems calling millis(), micros() and delay().

* The measured PWM-frequency may slightly differ from the actual set one.
* Remember, after changing the frequency, the duty cycle must be set as well.

*/

#define CLK_SPEED 16000000

class pwm
{
    public:
        void init_pin_D3();
        void init_pin_D5();
        void init_pin_D6();
        void init_pin_D9();
        void init_pin_D10();
        void init_pin_D11();

        void set_frequency_D3_D11(unsigned int freq);
        void set_frequency_D5_D6(unsigned int freq);
        void set_frequency_D9_D10(unsigned int freq);

        void set_duty_cycle_D3(float dcycle);
        void set_duty_cycle_D5(float dcycle);
        void set_duty_cycle_D6(float dcycle);
        void set_duty_cycle_D9(float dcycle);
        void set_duty_cycle_D10(float dcycle);
        void set_duty_cycle_D11(float dcycle);

        long int get_frequency_D3_D11();
        int get_resolution_D3_D11(); 

        long int get_frequency_D5_D6();
        int get_resolution_D5_D6(); 

        long int get_frequency_D9_D10();
        int get_resolution_D9_D10(); 
    
    private:
        void init_timer0();
        void init_timer1();
        void init_timer2();
        bool called0 = false;
        bool called1 = false;
        bool called2 = false;
        int prescaler0;
        int prescaler1;
        int prescaler2;
};