
/*
PWM Library for ATmega328 (Arduino Uno, Nano, Pro Mini)

* Easy changing Arduino PWM-frequencies

* Since two digital PWM-pins are tied to one timer, the PWM-frequency of those is the same.
    - pin 3 and 11 -> timer 2 (8-bit)
    - pin 9 and 10 -> timer 1 (16-bit)
    - pin 5 and 6 -> timer 0 (8-bit)

* PWM-pins D5 and D6:
    - The PWM frequency is fixed to 62500/7812/976/244/61 Hz.
    - The PWM resolution is a fixed to 8-bit.

* PWM-pins D3 and D11:
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

#include <ArduinoPWM.h>

pwm pwm;

void setup()
{  
    Serial.begin(9600);

    pwm.init_pin_D9(); // activate PWM on pin 9
    pwm.init_pin_D10(); // activate PWM on pin 10
    pwm.set_frequency_D9_D10(2000); // set PWM-frequency (Hz) for pin 9 and 10

    pwm.init_pin_D3(); // activate PWM on pin 3
    pwm.init_pin_D11(); // activate PWM on pin 11
    pwm.set_frequency_D3_D11(488); // set PWM-frequency (Hz) for pin 3 and 11

    Serial.print("Frequency pin 9 and 10: ");
    Serial.print(pwm.get_frequency_D9_D10()); // get the current PWM-frequency of pin 9 and 10
    Serial.println(" Hz");

    Serial.print("Frequency pin 3 and 11: ");
    Serial.print(pwm.get_frequency_D3_D11()); // get the current PWM-frequency of pin 3 and 11
    Serial.println(" Hz");

    Serial.print("Resolution pin 9 and 10: ");
    Serial.print(pwm.get_resolution_D9_D10()); // get the current PWM-resolution of pin 9 and 10
    Serial.println(" Hz");

    Serial.print("Resolution pin 3 and 11: ");
    Serial.print(pwm.get_resolution_D3_D11()); // get the current PWM-resolution of pin 3 and 11
    Serial.println(" Hz");

    // Not recommended: using this Library for PWM on pins 5 and 6, see above for explanation

    pwm.init_pin_D5(); // activate PWM on pin 5
    pwm.init_pin_D6(); // activate PWM on pin 6
    pwm.set_frequency_D5_D6(976); // set PWM-frequency (Hz) for pin 5 and 6

    Serial.print("Frequency pin 5 and 6: ");
    Serial.print(pwm.get_frequency_D5_D6()); // get the current PWM-frequency of pin 5 and 6
    Serial.println(" Hz");

    Serial.print("Resolution pin 5 and 6: ");
    Serial.print(pwm.get_resolution_D5_D6()); // get the current PWM-resolution of pin 5 and 6
    Serial.println(" Hz");


    pwm.set_duty_cycle_D10(43.35); // setting PWM duty cycle to 43.35 % (pin 10)
    pwm.set_duty_cycle_D9(60.5); // 60.5 % (pin 9)

    pwm.set_duty_cycle_D3(70.6); // 70.6 % (pin 3)
    pwm.set_duty_cycle_D11(30); // 30 %  (pin 11)

    pwm.set_duty_cycle_D5(10); // 10 % (pin 5)
    pwm.set_duty_cycle_D6(80); // 80 % (pin 6)
} 

void loop()
{

}
