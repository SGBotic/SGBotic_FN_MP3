/*************************************************** 
  This is a library f Mini MP3 Module (DEV-02247)
  http://www.sgbotic.com/index.php?dispatch=products.view&product_id=2247
  
  Written by KC for SGBotic.com  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include "SGBotic_FN_MP3.h"
#ifdef __AVR__
    #include <util/delay.h> 
    #include <SoftwareSerial.h>
#endif

#ifdef __AVR__
SGBotic_FN_MP3::SGBotic_FN_MP3(SoftwareSerial *ss) {

  hwSerial = NULL;
  swSerial = ss;
  mySerial = swSerial;
}
#endif

SGBotic_FN_MP3::SGBotic_FN_MP3(HardwareSerial *ss) {
 
#ifdef __AVR__
  swSerial = NULL;
#endif
  hwSerial = ss;
  mySerial = hwSerial;
}

void SGBotic_FN_MP3::begin(uint16_t baudrate) {
  delay(100);  // 1ms delay to let the MP3 module initialize.

  if (hwSerial) hwSerial->begin(baudrate);
#ifdef __AVR__
  if (swSerial) swSerial->begin(baudrate);
#endif
}

void SGBotic_FN_MP3::writePacket(uint8_t cmd, uint8_t feedback, uint16_t packet) {
#ifdef FN_MP3_DEBUG 
  Serial.print("---> 0x");
  Serial.print((uint8_t)FN_MP3_STARTCODE, HEX);
  Serial.print(" 0x");
  Serial.print((uint8_t)FN_MP3_VERSION, HEX);
  Serial.print(" 0x");
  Serial.print((uint8_t)FN_MP3_PACKETSIZE, HEX);
  Serial.print(" 0x");
  Serial.print((uint8_t)cmd, HEX);
  Serial.print(" 0x");
  Serial.print((uint8_t)feedback, HEX);
  Serial.print(" 0x");
  Serial.print((uint8_t)(packet >> 8), HEX);
  Serial.print(" 0x");
  Serial.print((uint8_t)(packet), HEX);
#endif
 
#if ARDUINO >= 100
  mySerial->write((uint8_t)FN_MP3_STARTCODE);
  mySerial->write((uint8_t)FN_MP3_VERSION);
  mySerial->write((uint8_t)FN_MP3_PACKETSIZE);
  mySerial->write((uint8_t)cmd);
  mySerial->write((uint8_t)feedback);
  mySerial->write((uint8_t)(packet >> 8));
  mySerial->write((uint8_t)(packet));
#else
  mySerial->print((uint8_t)FN_MP3_STARTCODE, BYTE);
  mySerial->print((uint8_t)FN_MP3_VERSION, BYTE);
  mySerial->print((uint8_t)FN_MP3_PACKETSIZE, BYTE);
  mySerial->print((uint8_t)cmd, BYTE);
  mySerial->print((uint8_t)feedback, BYTE);
  mySerial->print((uint8_t)(packet >> 8), BYTE);
  mySerial->print((uint8_t)(packet), BYTE);
#endif
  
    uint16_t sum = 0x00 -(FN_MP3_VERSION + FN_MP3_PACKETSIZE + cmd + feedback +
                    (uint8_t)(packet>>8) + (uint8_t)(packet));
    
 #ifdef FN_MP3_DEBUG 
  Serial.print(" 0x"); Serial.print((uint8_t)(sum>>8), HEX);
  Serial.print(" 0x"); Serial.print((uint8_t)(sum), HEX);
  Serial.print(" 0x"); Serial.println((uint8_t)(FN_MP3_ENDCODE), HEX); 
#endif
#if ARDUINO >= 100
  mySerial->write((uint8_t)(sum>>8));
  mySerial->write((uint8_t)sum);
  mySerial->write((uint8_t)FN_MP3_ENDCODE);
#else
  mySerial->print((uint8_t)(sum>>8), BYTE);
  mySerial->print((uint8_t)sum, BYTE);
  mySerial->print((uint8_t)FN_MP3_ENDCODE, BYTE);
#endif    
 
}

// play 
void SGBotic_FN_MP3::play(){
    writePacket(FN_MP3_PLAY, 0, 0);
}

// play track
void SGBotic_FN_MP3::play(uint16_t track){
    writePacket(FN_MP3_PLAYTRACK, 0, track);
}

//play track in folder, folder name in sdcard must be in two digit format, e.g. 01, 02, 03
void SGBotic_FN_MP3::play(uint8_t track, uint8_t folder){
    if (folder > 99)
        folder = 99;
    uint16_t data = ((uint16_t)folder << 8) | (uint16_t)track;
    writePacket(FN_MP3_PLAYTRACKFOLDER, 0, data);
}

//repeat single track
void SGBotic_FN_MP3::repeat(uint16_t track){
    writePacket(FN_MP3_REPEATTRACK, 0, track);
}

//repeat single track in a folder
void SGBotic_FN_MP3::repeatFolder(uint16_t folder){
    writePacket(FN_MP3_REPEATFOLDER, 0, folder);
}

void SGBotic_FN_MP3::reset(){
    writePacket(FN_MP3_RESET, 0, 0);
}

void SGBotic_FN_MP3::pause(){
    writePacket(FN_MP3_PAUSE, 0, 0);
}

void SGBotic_FN_MP3::next(){
    writePacket(FN_MP3_NEXT, 0, 0);
}

void SGBotic_FN_MP3::prev(){
    writePacket(FN_MP3_PREV, 0, 0);
}

void SGBotic_FN_MP3::stop(){
    writePacket(FN_MP3_STOP, 0, 0);
}

void SGBotic_FN_MP3::sleep(){
    writePacket(FN_MP3_SLEEP, 0, 0);
}

void SGBotic_FN_MP3::setEq(uint16_t eq){
    if(eq < 0)
        eq = 0;
    if(eq > 5)
        eq = 5;
    writePacket(FN_MP3_SETEQ, 0, eq);
}

void SGBotic_FN_MP3::setGain(uint16_t gain){
    if(gain < 0)
        gain = 0;
    if(gain > 31)
        gain = 31;
    
    gain = gain | 0x0100;
    writePacket(FN_MP3_SETGAIN, 0, gain);
}

void SGBotic_FN_MP3::setVolume(uint16_t volume) {
    if (volume <0)
        volume = 0;
    if (volume > 30)
        volume = 30;
    writePacket(FN_MP3_SETVOLUME, 0, volume);
}