#include <Keyboard.h>
#include <Arduino.h>

#define PINAMOUNT 19
#define STARTPIN 33

//pinbelegung  P1Joystick(4pins) P1Knöpfe(4pins) P2Joystick(4pins),P2Knöpfe(4pins),single/multiplayer(2pins),menu(1pin) LOW active beschaltet

char keyTable[PINAMOUNT] = {'w', 's', 'a', 'd', '1', '2', '3', '4', 'i', 'k', 'j', 'l', '5', '6', '7', '8', 'v', 'b', 'n'};
boolean PinData[PINAMOUNT];
int PinDataFromRegister[79];
boolean pressed[PINAMOUNT];
void setup()
{
  for (int i = STARTPIN; i < STARTPIN + PINAMOUNT; i++)
  {
    pinMode(i, INPUT_PULLUP);
    pressed[i]=false;
  }
  Keyboard.begin();
  Serial.begin(115200);
}
uint32_t dataA;
uint32_t dataB;
uint32_t dataC;
uint32_t dataD;
void registerRead()
{
  //https://www.arduino.cc/en/Hacking/PinMappingSAM3X

  dataA = PIOA->PIO_PDSR;
  dataB = PIOB->PIO_PDSR;
  dataC = PIOC->PIO_PDSR;
  dataD = PIOD->PIO_PDSR;
  /* PinDataFromRegister[0] = (dataA & (1 << 8));
  PinDataFromRegister[1] = (dataA & (1 << 9));
  PinDataFromRegister[2] = (dataB & (1 << 25));
  PinDataFromRegister[3] = (dataC & (1 << 28));
  PinDataFromRegister[4] = (dataC & (1 << 26));
  PinDataFromRegister[5] = (dataC & (1 << 25));
  PinDataFromRegister[6] = (dataC & (1 << 24));
  PinDataFromRegister[7] = (dataC & (1 << 23));
  PinDataFromRegister[8] = (dataC & (1 << 22));
  PinDataFromRegister[9] = (dataC & (1 << 21));
  PinDataFromRegister[10] = (dataC & (1 << 29));
  PinDataFromRegister[11] = (dataD & (1 << 7));
  PinDataFromRegister[12] = (dataD & (1 << 8));
  PinDataFromRegister[13] = (dataB & (1 << 27));
  PinDataFromRegister[14] = (dataD & (1 << 4));
  PinDataFromRegister[15] = (dataD & (1 << 5));
  PinDataFromRegister[16] = (dataA & (1 << 13));
  PinDataFromRegister[17] = (dataA & (1 << 12));
  PinDataFromRegister[18] = (dataA & (1 << 11));
  PinDataFromRegister[19] = (dataA & (1 << 10));
  PinDataFromRegister[20] = (dataB & (1 << 12));
  PinDataFromRegister[21] = (dataB & (1 << 13));
  PinDataFromRegister[22] = (dataB & (1 << 26));
  PinDataFromRegister[23] = (dataA & (1 << 14));
  PinDataFromRegister[24] = (dataA & (1 << 15));
  PinDataFromRegister[25] = (dataD & (1 << 0));
  PinDataFromRegister[26] = (dataD & (1 << 1));
  PinDataFromRegister[27] = (dataD & (1 << 2));
  PinDataFromRegister[28] = (dataD & (1 << 3));
  PinDataFromRegister[29] = (dataD & (1 << 6));
  PinDataFromRegister[30] = (dataD & (1 << 9));
  PinDataFromRegister[31] = (dataA & (1 << 7));
  PinDataFromRegister[32] = (dataD & (1 << 10));*/
  PinDataFromRegister[33] = (dataC & (1 << 1));
  PinDataFromRegister[34] = (dataC & (1 << 2));
  PinDataFromRegister[35] = (dataC & (1 << 3));
  PinDataFromRegister[36] = (dataC & (1 << 4));
  PinDataFromRegister[37] = (dataC & (1 << 5));
  PinDataFromRegister[38] = (dataC & (1 << 6));
  PinDataFromRegister[39] = (dataC & (1 << 7));
  PinDataFromRegister[40] = (dataC & (1 << 8));
  PinDataFromRegister[41] = (dataC & (1 << 9));
  PinDataFromRegister[42] = (dataA & (1 << 19));
  PinDataFromRegister[43] = (dataA & (1 << 20));
  PinDataFromRegister[44] = (dataC & (1 << 19));
  PinDataFromRegister[45] = (dataC & (1 << 18));
  PinDataFromRegister[46] = (dataC & (1 << 17));
  PinDataFromRegister[47] = (dataC & (1 << 16));
  PinDataFromRegister[48] = (dataC & (1 << 15));
  PinDataFromRegister[49] = (dataC & (1 << 14));
  PinDataFromRegister[50] = (dataC & (1 << 13));
  PinDataFromRegister[51] = (dataC & (1 << 12));
  PinDataFromRegister[52] = (dataB & (1 << 21));
  PinDataFromRegister[53] = (dataB & (1 << 14));
  /*PinDataFromRegister[54] = (dataA & (1 << 16));
  PinDataFromRegister[55] = (dataA & (1 << 24));
  PinDataFromRegister[56] = (dataA & (1 << 23));
  PinDataFromRegister[57] = (dataA & (1 << 22));
  PinDataFromRegister[58] = (dataA & (1 << 6));
  PinDataFromRegister[59] = (dataA & (1 << 4));
  PinDataFromRegister[60] = (dataA & (1 << 3));
  PinDataFromRegister[61] = (dataA & (1 << 2));
  PinDataFromRegister[62] = (dataB & (1 << 17));
  PinDataFromRegister[63] = (dataB & (1 << 18));
  PinDataFromRegister[64] = (dataB & (1 << 19));
  PinDataFromRegister[65] = (dataB & (1 << 20));
  PinDataFromRegister[66] = (dataB & (1 << 15));
  PinDataFromRegister[67] = (dataB & (1 << 16));
  PinDataFromRegister[68] = (dataA & (1 << 1));
  PinDataFromRegister[69] = (dataA & (1 << 0));
  PinDataFromRegister[70] = (dataA & (1 << 17));
  PinDataFromRegister[71] = (dataA & (1 << 18));
  PinDataFromRegister[72] = (dataC & (1 << 30));
  PinDataFromRegister[73] = (dataA & (1 << 21));
  PinDataFromRegister[74] = (dataA & (1 << 25));
  PinDataFromRegister[75] = (dataA & (1 << 26));
  PinDataFromRegister[76] = (dataA & (1 << 27));
  PinDataFromRegister[77] = (dataA & (1 << 28));
  PinDataFromRegister[78] = (dataB & (1 << 23));*/
}
void loop()
{
  registerRead();
  dataToUSB();
}
void dataToUSB()
{
  for (int i = STARTPIN; i < STARTPIN + PINAMOUNT; i++)
  {
   
    if (!PinDataFromRegister[i])
    {
      if (pressed[i]==false)
      {
         Serial.println("pressed");
        Keyboard.press(keyTable[i - STARTPIN]);
        pressed[i] = true;
      }
    }

    else
    {
      if (pressed[i]==true )
      {
         Serial.println("released");
        pressed[i] = false;
        Keyboard.release(keyTable[i - STARTPIN]);
      }
    }
  }
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
        Keyboard.press(keyTable[53 - i]); //bei allen anderen Pins
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
