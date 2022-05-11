The code work is working in this way:

- In the file main:
    1. Read all the analogical informations: LDR, NTC and Potenciometro

    2. Send the informations to the function LedMode, that manage all the components

    3. In order to manage the while cicle, there is a HAL_DELAY(3000)

- In the file functions.h:
    The main function in the file is LedMode, that is divided in several parts:
    
    1. Read the signals from the two buttons: the left (responsable to display the LDR status or NTC status) and the right (to reset the Buzzer)

    2. Set the tick for the blinking led of the Potenciometro

    3. Manage the left button using a counter. When the button is pressed just one time, the leds will show the LDR information (with display_leds_LDR), otherwise
       it will show the NTC informations (with display_leds_NTC). In order to consider only this two cases, when the counter reach the value of 3, it stars again from the value
       1 and display LDR, an so on. 

    4. To set the alarm level, at every tick it find the right led to blink (with find_blinking_led) with the Potenciometro information

    5. To manage the alarm, considering in which situation we are, LDR or NTC, the code check is the alarm level is over a certain information.
       If its not, the buzzer is set on ON, otherwise is still in OFF

    6. To manage the buzzer, it consider the right button, that can switch off the buzzer when On

- In the file functions.c:
    Contains all the declaration of functions.c
