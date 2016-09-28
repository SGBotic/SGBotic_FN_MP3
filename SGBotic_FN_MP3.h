/*************************************************** 
  This is a library for our Mini MP3 Module (DEV-02247)
  http://www.sgbotic.com/index.php?dispatch=products.view&product_id=2247
  
  Written by KC for SGBotic.com
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include "Arduino.h"
#ifdef __AVR__
  #include <SoftwareSerial.h>
#endif

//#define FN_MP3_DEBUG 

//control commands
#define FN_MP3_NEXT 0x01
#define FN_MP3_PREV 0x02
#define FN_MP3_PLAYTRACK 0x03
#define FN_MP3_INCVOLUME 0x04
#define FN_MP3_DECVOLUME 0x05
#define FN_MP3_SETVOLUME 0x06
#define FN_MP3_SETEQ 0x07
#define FN_MP3_REPEATTRACK 0x08
#define FN_MP3_SETDEVICE 0x09
#define FN_MP3_SLEEP 0x0A
#define FN_MP3_RESET 0x0C
#define FN_MP3_PLAY 0x0D
#define FN_MP3_PAUSE 0x0E
#define FN_MP3_PLAYTRACKFOLDER 0x0F
#define FN_MP3_SETGAIN 0x10
#define FN_MP3_SETALLREPEATPLAYBACK 0x11
#define FN_MP3_SETPLAYBACKMP3 0x12
#define FN_MP3_INTERCUTADVERTISEMENT OX13
#define FN_MP3_PLAYFOLDER3K 0x14
#define FN_MP3_STOPADV 0x15
#define FN_MP3_STOP 0x16
#define FN_MP3_REPEATFOLDER 0x17
#define FN_MP3_RANDOMP 0x18
#define FN_MP3_REPEATCURRENT 0x19
#define FN_MP3_SETDAC 0x1A
//Query commands
#define FN_MP3_GETDEVICE 0x3F
#define FN_MP3_ACKERROR 0x40
#define FN_MP3_ACKFEEDBACK 0x41
#define FN_MP3_GETSTATUS 0x42
#define FN_MP3_GETVOLUME 0x43
#define FN_MP3_GETEQ 0x44
#define FN_MP3_GETTOTALTRACKUSBROOT 0x47
#define FN_MP3_GETTOTALTRACKSDROOT 0x48
#define FN_MP3_GETTRACKUSB 0x4B
#define FN_MP3_GETTRACKSD 0x4C
#define FN_MP3_GETTOTALTRACKFOLDER 0x4E
#define FN_MP3_GETTOTALFOLDER 0x4F

#define FN_MP3_STARTCODE 0x7E
#define FN_MP3_ENDCODE 0xEF
#define FN_MP3_VERSION 0xFF
#define FN_MP3_PACKETSIZE 0x06

#define NORMAL 0x00
#define POP 0x01
#define ROCK 0xO2
#define JAZZ 0x03
#define CLASSIC 0x04
#define BASS 0x05

class SGBotic_FN_MP3 {
 public:
 
#ifdef __AVR__
  SGBotic_FN_MP3(SoftwareSerial *);
#endif
  SGBotic_FN_MP3(HardwareSerial *);

    void begin(uint16_t baud);
    void writePacket(uint8_t cmd, uint8_t feedback, uint16_t packet);
    void setVolume(uint16_t volume);
    void play();
    void play(uint16_t track);
    void play(uint8_t track, uint8_t folder);
    void repeat(uint16_t track);
    void repeatFolder(uint16_t track);
    void reset();
    void pause();
    void next();
    void prev();
    void stop();
    void sleep();
    void setEq(uint16_t eq);
    void setGain(uint16_t gain);

 private: 
    
  Stream *mySerial;
   
#ifdef __AVR__
  SoftwareSerial *swSerial;
#endif
  HardwareSerial *hwSerial;
  
};
