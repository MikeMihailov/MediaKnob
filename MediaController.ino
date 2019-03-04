//************************************************
//*******************INCLUDE**********************
//************************************************
#include <HID-Project.h>
#include <HID-Settings.h>
//************************************************
//*******************DEFINE***********************
//************************************************
#define MutePin       A3
#define Apin          A1
#define Bpin          A2
#define stepPerTrig   1   // Steps of encoder for change the volume
#define changeDir         // Comment to change direction of rotations
//#define debug             // Uncomment to enable debug messages via serial
//************************************************
//********************VAR*************************
//************************************************
uint8_t muteData    = 0;  // Mute data
uint8_t muteDone    = 0;  // Mute state
uint8_t aData       = 0;
uint8_t aLast       = 0;
uint8_t SoundChange = 0;
int     counter     = 0;
//************************************************
//********************INIT************************
//************************************************
void setup() {
  #ifdef debug
    Serial.begin(9600);
  #endif
  pinMode(MutePin, INPUT);
  pinMode(Apin, INPUT);
  pinMode(Bpin, INPUT);
  digitalWrite(MutePin, HIGH);
  digitalWrite(Apin, HIGH);
  digitalWrite(Bpin, HIGH);
  aLast = digitalRead(Apin);
}
//************************************************
//*******************MAIN*************************
//************************************************
void loop() 
{
  //**********************************************
  muteData = digitalRead(MutePin);
  if ((muteData == 0) && (!muteDone))
  {
    #ifdef debug
      Serial.print("Button: Clicked\n");
    #endif
    volumeChange(MEDIA_VOL_MUTE);
    muteDone  = 1;
  }
  if ((muteData != 0) && (muteDone))
  {
    muteDone = 0;
  }
  //**********************************************
  aData = digitalRead(Apin);
  if (aLast != aData)
  {
    if (digitalRead(Bpin) != aData)
    {
      counter++;
    }
    else
    {
      counter--;
    }
  }
  aLast = aData;
  //**********************************************
  if (counter > stepPerTrig)
  {
    #ifdef changeDir
      volumeChange(MEDIA_VOL_DOWN);
    #else
      volumeChange(MEDIA_VOL_UP);
    #endif
    #ifdef debug
      Serial.print("Encoder: Up\n");
    #endif
    counter = 0;
  }
  if (counter < (0-stepPerTrig))
  {
    #ifdef changeDir
      volumeChange(MEDIA_VOL_UP);
    #else
      volumeChange(MEDIA_VOL_DOWN);
    #endif
    #ifdef debug
      Serial.print("Encoder: Down\n");
    #endif
    counter = 0;
  }
}

void volumeChange(uint16_t key) 
{
  Consumer.write(key);
}
