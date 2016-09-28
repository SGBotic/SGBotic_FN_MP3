
/*************************************************** 
  This is an example sketch for our Mini MP3 Module
  http://www.sgbotic.com/index.php?dispatch=products.view&product_id=2247
 
  Written by KC for SGBotic.  
  BSD license, all text above must be included in any redistribution

=====================================================


 Wiring:
 
 MP3 module:          Arduino Uno
 Pin 1 (Vcc)  ------> 3.3V or 5V
 Pin 2 (Rx)   ------> Pin 11 (Tx)
 Pin 3 (Tx)   ------> Pin 10 (Rx)
 Pin 6 (SPK+) ------> (Speaker +ve)
 Pin 7 (GND)  ------> GND
 Pin 8 (SPK-) ------> (Speaker -ve)
 
 ****************************************************/
#include <SGBotic_FN_MP3.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

SGBotic_FN_MP3 mp3 = SGBotic_FN_MP3(&mySerial);

void setup() {

  Serial.begin(9600);
  Serial.println("SGBotic Mini MP3 Module test sketch using SoftwareSerial");
  mp3.begin(9600);
}

void loop() {
  mp3.setVolume(15);   // value: 0 to 30
  mp3.setEq(JAZZ);     // NORMAL, POP, ROCK, JAZZ, CLASSIC, BASS
  mp3.play(1);         //play track 1 in root directory
  //mp3.play(4, 1);    //play track 4 in folder "01". Folder name in two digit format: 01, 02, 03 ...
  delay(5000); delay (5000);
  mp3.play(2);         //play track 2 in root directory
  delay(5000); delay (5000);
  mp3.repeatFolder(1); //repeat all tracks in folder 01
  
  //mp3.setGain(1);    //set amplifier gain, 0 to 31
  //mp3.repeatFolder(1);  //repeat all tracks in folder 01
  //mp3.repeat(2);     // repeat track 2 in root directory
  //mp3.reset();
  //mp3.pause();
  //mp3.stop()
  //mp3.sleep();
  //mp3.next();       // next track
  //mp3.prev();       // previous track

  while (1);         //forever loop
}
