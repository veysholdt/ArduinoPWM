# PWM Library for ATmega328 (Arduino Uno, Nano, Pro Mini)
See example code for implementation example.

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

* The measured PWM-frequency may slightly differ from the actual set one.
* Remember, after changing the frequency, the duty cycle must be set as well.

### NOTE:
    * Any changes to timer 0 (pin D5 and D6) may effect the time-functions of the Arduino-Library,
      which may cause problems calling millis(), micros() and delay().
