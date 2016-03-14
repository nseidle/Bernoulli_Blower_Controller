/*
 Blower Controller reads a button and turns on/off a blower.
 By: Nathan Seidle
 SparkFun Electronics
 Date: March 12th, 2016
 License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

 The WOW Kid's museum in Lafayette, CO has a large curved blower facing tagential
 to the ground. Pressing the button causes the blower to turn on and allows kids
 to send beach balls into the air. Because of differential air pressures around
 the ball it is held, hovering and spinning in mid air above the outlet of the 
 blower.

 The big arcade button is a leaf switch with an LED that we pulse/breath on/off
 to try to get kids to press it. The SAMD21 Mini then turns on an AC outlet. You
 can build your own DC conrolled AC outlet with a solid-state relay (SSR) or
 you can buy an off the shelf product like power switch tail or IoT Relay.

 SSR is controlled through an NPN transistor to 5V with a 330 base resistor. 
 SAMD21 is only 3.3V and is not quite enough to forward bias the SSR. 
 I used a 2N2222 but any NPN (2N3904) should work.

*/

//#include <avr/wdt.h> //We need watch dog for this program
//SAMD21 does not yet have WDT support under Arduino
#include <SimpleTimer.h> //https://github.com/jfturcot/SimpleTimer

//Hardware definitions
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#define SSR_CONTROL 12

#define BUTTON_LED 6 //Needs to be PWM
#define BUTTON_LED_GND 5
#define BUTTON_SWITCH 4
#define BUTTON_SWITCH_GND 3

#define STATUS_LED 13
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

SimpleTimer timer;
long secondTimerID; //Keeps track of the blinking 'I'm alive' status LED

unsigned long blowerStarted; //millis time when the blower was started
#define MAX_RUN_TIME (45L * 1000L) //In ms, 45 seconds
//#define MAX_RUN_TIME (3L * 1000L) //Testing

unsigned long timeSinceLastFade; //Keeps track of off time between fades
#define MIN_TIME_BETWEEN_FADES 2000L //Amount of time to be off between fades

char systemState;
#define WAITING 'W'
#define BLOWING 'B'
#define FADING 'F'

int brightness = 0; //Keeps track of our fading LED
int fadeAmount = 5; //How many points to fade the LED by

void setup()
{
  //wdt_reset(); //Pet the dog
  //wdt_disable(); //We don't want the watchdog during init

  SerialUSB.begin(9600);

  pinMode(SSR_CONTROL, OUTPUT);
  digitalWrite(SSR_CONTROL, LOW); //Turn off blower

  pinMode(BUTTON_LED, OUTPUT);
  pinMode(BUTTON_LED_GND, OUTPUT);
  pinMode(BUTTON_SWITCH, INPUT_PULLUP);
  pinMode(BUTTON_SWITCH_GND, OUTPUT);
  pinMode(STATUS_LED, OUTPUT);

  digitalWrite(BUTTON_LED, LOW);
  digitalWrite(BUTTON_LED_GND, LOW);
  digitalWrite(BUTTON_SWITCH_GND, LOW);
  digitalWrite(STATUS_LED, LOW);

  secondTimerID = timer.setInterval(1000L, statusBlink); //Call statusBlink every 1000ms

  systemState = WAITING;
  timeSinceLastFade = millis();

  SerialUSB.println("Blower controller online!");

  //wdt_reset(); //Pet the dog
  //wdt_enable(WDTO_500MS); //Unleash the beast
}

void loop()
{
  //wdt_reset(); //Pet the dog
  timer.run(); //Update any timers we are running

  if (systemState == WAITING || systemState == FADING)
  {
    //Has anyone hit the button?
    if (digitalRead(BUTTON_SWITCH) == LOW)
    {
      SerialUSB.println("Starting blower!");

      digitalWrite(BUTTON_LED, HIGH); //Turn on button LED

      brightness = 0; //Reset brightness when the next fade happens

      systemState = BLOWING;

      //Turn on blower
      digitalWrite(SSR_CONTROL, HIGH);

      //Mark this time
      blowerStarted = millis();
    }

    //If we're are fading, update the LED
    if(systemState == FADING)
    {
      //Pulse LED up/down
      
      analogWrite(BUTTON_LED, brightness);
      delay(30); //Give the fade a chance to be seen

      //Change the brightness for next time through the loop
      brightness += fadeAmount;

      //Reverse the direction of the fading at the end of the fade
      if (brightness >= 255) fadeAmount = -fadeAmount;

      if(brightness < 0)
      {
        //We're done fading!
        systemState = WAITING;

        digitalWrite(BUTTON_LED, LOW); //Turn off LED

        brightness = 0;
        
        fadeAmount = -fadeAmount; //Make the fadeAmount positive again for next loop
        
        timeSinceLastFade = millis(); //Remember this moment
      }
      
    } //Done fading LED
  
  } //Done with Waiting/Fading
  else if (systemState == BLOWING)
  {
    //Has the timer expired?
    if (millis() - blowerStarted > MAX_RUN_TIME)
    {
      SerialUSB.println("Shut down!");

      //Turn off blower
      digitalWrite(SSR_CONTROL, LOW);

      //Turn off LED
      digitalWrite(BUTTON_LED, LOW);

      systemState = WAITING;
      timeSinceLastFade = millis(); //Reset the fade timer so it doesn't immediately start again
    }
  }

  //Has enough time passed since the last fade?
  if(millis() - timeSinceLastFade > MIN_TIME_BETWEEN_FADES)
  {
    if(systemState == WAITING) systemState = FADING;
  }
}

//When called, toggles the status LED
void statusBlink()
{
  SerialUSB.println("Blink");
  digitalWrite(STATUS_LED, !digitalRead(STATUS_LED));
}

