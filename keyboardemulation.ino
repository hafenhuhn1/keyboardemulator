#include <Keyboard.h>
#include <Arduino.h>

#define PINAMOUNT 19

//pinbelegung  P1Joystick(4pins) P1Knöpfe(4pins) P2Joystick(4pins),P2Knöpfe(4pins),single/multiplayer(2pins),menu(1pin) LOW active beschaltet

char keyTable[PINAMOUNT] = {'w', 's', 'a', 'd', '1', '2', '3', '4', 'i', 'k', 'j', 'l', '5', '6', '7', '8', 'v', 'b', 'n'};
volatile boolean PinData[PINAMOUNT];
void setup()
{
  for (int i = 53; i > 53 - PINAMOUNT; i--)
  {
    pinMode(i, INPUT_PULLUP);
  }
  Keyboard.begin();
}

void loop()
{
  KeyboardPressing();
}
void KeyboardPressing()
{
  for (int i = 53; i > 53 - PINAMOUNT; i--)
  {
    PinData[53 - i] = PinDigitalInput(i);
    if (!PinData[53 - i])
    {
      if (i >= 50 || (i <= 45 && i >= 42)) // joystick pins
      {
        if (!((53 - i) % 2))
        {
          Keyboard.press(keyTable[53 - i]);       //press button
          Keyboard.release(keyTable[53 - i - 1]); //release counterpart
        }
        else
        {
          Keyboard.press(keyTable[53 - i]);       //press button
          Keyboard.release(keyTable[53 - i + 1]); //release counterpart
        }
      }
      else
      {
        Keyboard.press(keyTable[53 - i]);//bei allen anderen Pins
      }
    }
    else
    {
      Keyboard.release(keyTable[53 - i]);
    }
  }
}
bool PinDigitalInput(uint8_t pin)
{
  int analogData;
  boolean digitalData;
  if ((pin >= 2 && pin <= 13) || (pin >= 22 && pin <= 53)) // für alle digitalPins
  {
    digitalData = digitalRead(pin);
  }
  else if (pin >= 54 && pin <= 65) //für alle analogpins
  {
    digitalData = analogRead(pin);
    if (digitalData < 350)
    {
      digitalData = false;
    }
    else if (analogData > 850)
    {
      digitalData = true;
    }
  }
  return digitalData;
}