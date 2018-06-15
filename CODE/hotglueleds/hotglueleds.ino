/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/
 int leds[] = {3,5,6,9};
 int previous_choice = 0;
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);

  Serial.begin(115200);
}

// the loop function runs over and over again forever
void loop() {
  for(int i = 0 ; i < 5 ; i++)
  {
    scan();
  }
  fade();
  fade_all();
  while(1) 
  {
    fade_random();
    if(random(0,4) == 0)
    {
      delay(250);
      sweep(random(0,2));
    }
    delay(random(0,200));
  }
}


void scan(void)
{
  led(3);
  led(5);
  led(6);
  led(9);  
}
void led(int led_pin)
{
  digitalWrite(led_pin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);                       // wait for a second
  digitalWrite(led_pin, LOW);    // turn the LED off by making the voltage LOW
}

void fade(void)
{
  fade_led(3, 10);
  fade_led(5, 10);
  fade_led(6, 10);
  fade_led(9, 10);
}
void fade_led(int ledPin, int spd) 
{
  // fade in from min to max in increments of 5 points:
  for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
    // sets the value (range from 0 to 255):
    analogWrite(ledPin, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(spd);
  }

  // fade out from max to min in increments of 5 points:
  for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
    // sets the value (range from 0 to 255):
    analogWrite(ledPin, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(spd);
  }
}

void fade_all(void)
{
    // fade in from min to max in increments of 5 points:
  for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
    // sets the value (range from 0 to 255):
    analogWrite(3, fadeValue);
    analogWrite(5, fadeValue);
    analogWrite(6, fadeValue);
    analogWrite(9, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(10);
  }

  // fade out from max to min in increments of 5 points:
  for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
    // sets the value (range from 0 to 255):
    analogWrite(3, fadeValue);
    analogWrite(5, fadeValue);
    analogWrite(6, fadeValue);
    analogWrite(9, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(10);
  }
}

void fade_random(void)
{
  int choice = random(0,4);
  while(choice == previous_choice) choice = random(0,4); // prevent repeats
  int choice_spd = random(10,20);
  fade_led(leds[choice], choice_spd);
  previous_choice = choice;
}

void sweep_random(void)
{
  boolean direction = random(0,2);
  if(direction)
  {

  }
  else
  {
    
  }
}

void sweep(boolean direction)
{
  boolean effect_active = true;
  int fade_value[] = {0,0,0,0};
  boolean fade_direction[] = {1,1,1,1}; // all fade "up" to start
  int start_time[] = {0,10,20,30};
  
  // order of start times effect the left/right direction that the sweep happens
  if(direction == false) // flip direction
  {
    start_time[0] = 30;
    start_time[1] = 20;
    start_time[2] = 10;
    start_time[3] = 0;
  }
  
  int counter = 0;
  
  while(effect_active)
  {
    for(int i = 0 ; i < 4 ; i++) 
    {
      if(counter >= start_time[i]) // only effect the LEDs that are beyond their start times.
      {
        if(fade_direction[i])
        {
           if(fade_value[i] < 255) fade_value[i] += 5;
           if(fade_value[i] == 255) fade_direction[i] = false; // switch directions when we get to the top (255)
        }
        else
        {
          if(fade_value[i] > 0) fade_value[i] -= 5; // decent down to zero
        }
      }
    }

    // write current values to leds
    for(int i = 0 ; i < 4 ; i++) 
    {
      analogWrite(leds[i], fade_value[i]);
    }

    delay(10);

    // check that we're done (all LEDs off), then get us out of this while loop
    if( (fade_value[0] == 0) && (fade_value[1] == 0) && (fade_value[2] == 0) && (fade_value[3] == 0) )
    {
      effect_active = false;
    }
    counter++;
    Serial.print("counter:");
    Serial.print(counter);
    Serial.print("\t");
    Serial.print(fade_value[0]);  
    Serial.print("\t");
    Serial.print(fade_value[1]);
    Serial.print("\t");
    Serial.print(fade_value[2]);
    Serial.print("\t");
    Serial.println(fade_value[3]);  
  }
}

