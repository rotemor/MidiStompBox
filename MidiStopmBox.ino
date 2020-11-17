#include <pitchToFrequency.h>
#include <pitchToNote.h>
#include <frequencyToNote.h>
#include <MIDIUSB_Defs.h>
#include <MIDIUSB.h>


#define Serial SerialUSB;

// this constant won't change:
const int  buttonPin = 7;    // the pin that the pushbutton is attached to

const int ledPin = 13;       // the pin that the LED is attached to

// Variables will change:
int buttonPushCounter = 0;   // counter for the number of button presses


const int  powerLed = 1;
const int  button_1 = 2;    // the pin that the pushbutton is attached to
const int  button_2 = 3;    // the pin that the pushbutton is attached to
const int  button_3 = 4;    // the pin that the pushbutton is attached to
const int  button_4 = 5;    // the pin that the pushbutton is attached to
const int  button_5 = 6;    // the pin that the pushbutton is attached to


int lastState_Button_1 = 0;     // previous state of the button
int lastState_Button_2 = 0;     // previous state of the button
int lastState_Button_3 = 0;     // previous state of the button
int lastState_Button_4 = 0;     // previous state of the button
int lastState_Button_5 = 0;     // previous state of the button


// send a 3-byte midi message
void midiCommand(byte cmd, byte data1, byte  data2) {
  // First parameter is the event type (top 4 bits of the command byte).
  // Second parameter is command byte combined with the channel.
  // Third parameter is the first data byte
  // Fourth parameter second data byte

  midiEventPacket_t midiMsg = {cmd >> 4, cmd, data1, data2};
  MidiUSB.sendMIDI(midiMsg);
}


void setup() {
  // initialize the button pin as a input:
  pinMode(powerLed, OUTPUT);
  pinMode(button_1, INPUT_PULLUP);
  pinMode(button_2, INPUT_PULLUP);
  pinMode(button_3, INPUT_PULLUP);
  pinMode(button_4, INPUT_PULLUP);
  pinMode(button_5, INPUT_PULLUP);
  

  // initialize serial communication:
    digitalWrite(powerLed, HIGH);   // turn the LED on (HIGH is the voltage level)

  SerialUSB.begin(9600);
}


void CheckButton(int buttonPin, int &lastButtonState )
{
  // read the pushbutton input pin:
  int buttonState = digitalRead(buttonPin);

  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
   
      buttonPushCounter++;
      
      SerialUSB.print(" pin - ");
      SerialUSB.print(buttonPin);
      SerialUSB.println(" was pressed");
      midiCommand(0x90, 0x05 + buttonPin , 0x7F);
      midiCommand(0x90, 0x05 + buttonPin, 0);
      lastButtonState = buttonState;

    delay(70);
    
  }
  }

void loop() {


  CheckButton(button_1, lastState_Button_1);
  CheckButton(button_2, lastState_Button_2);
  CheckButton(button_3, lastState_Button_3);
  CheckButton(button_4, lastState_Button_4);
  CheckButton(button_5, lastState_Button_5);
  


}
