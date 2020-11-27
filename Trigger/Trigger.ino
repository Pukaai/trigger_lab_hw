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

const int buttonPin = 7;     // the number of the pushbutton pin
const int outputPin = 12;    // the number of the LED pin
const int ledPin = 13;    // the number of the LED pin
int incomingByte = 0; // for incoming serial data
int buttonState = 0; // 
int freq = 1; // freq input
int continuousMode = 0; // test mode on means continious sending, notest mode means sending just once
int lastStateHigh = 1; // last state of the button is initialize to 1 because start of the controller

// the setup function runs once when you press reset or power the board
void setup() 
{
  // initialize digital pins
  pinMode(ledPin, OUTPUT);
  pinMode(outputPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, LOW);

  // initialize serial port
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() 
{
  checkButtonState();
  checkFreqUpdate();
}

void checkButtonState()
{
  buttonState = digitalRead(buttonPin);

  if (continuousMode)
  {
    if (buttonState) {
      digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(outputPin, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay((1000/freq)-10); // shorten for 10 to not repeate the sequence 
      digitalWrite(ledPin, LOW);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(outputPin, LOW);   // turn the LED on (HIGH is the voltage level)
      delay(1000/freq); 
    
      Serial.print("Output was send with frequency: ");
      Serial.println(freq, DEC);
      Serial.println(freq);
    } else {
      digitalWrite(ledPin, LOW);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(outputPin, LOW);   // turn the LED on (HIGH is the voltage level)
    }
  }
  else
  {
    if (!lastStateHigh)
    {
      if (buttonState) {
        digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
        digitalWrite(outputPin, HIGH);   // turn the LED on (HIGH is the voltage level)
        delay((1000/freq)-10); // shorten for 10 to not repeate the sequence 
        digitalWrite(ledPin, LOW);   // turn the LED on (HIGH is the voltage level)
        digitalWrite(outputPin, LOW);   // turn the LED on (HIGH is the voltage level)
        delay(1000/freq); 
    
        Serial.println("Output was send with frequency: ");
        Serial.println(freq, DEC);

        lastStateHigh = 1;
      } else {
        digitalWrite(ledPin, LOW);   // turn the LED on (HIGH is the voltage level)
        digitalWrite(outputPin, LOW);   // turn the LED on (HIGH is the voltage level)
      }
    }
    else
    {
      // Reset the last state when button is released
      if (!buttonState)
      {
        lastStateHigh = 0;
        Serial.println("Reseting the state!");
      }
    }
  }
}

void checkFreqUpdate()
{
  if (Serial.available() > 0) {
    // read the incoming msg:
    incomingByte = Serial.parseInt();

    if(incomingByte == 2236)
    {
      Serial.println("Command activated: continuous Mode ON");
      continuousMode = 1;
    }
    else if(incomingByte == 2235)
    {
      Serial.println("Command activated: continuous Mode OFF");
      continuousMode = 0;
    }
    else if(incomingByte != 0)
    {
      Serial.print("Command activated: ");
      Serial.println(incomingByte, DEC);

      freq = incomingByte;
    }
  }
}
