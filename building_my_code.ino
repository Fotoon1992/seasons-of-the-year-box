//pn532
#include <Wire.h>
#include <Adafruit_PN532.h>

#define PN532_SCK  (2)
#define PN532_MOSI (3)
#define PN532_SS   (4)
#define PN532_MISO (5)

#define PN532_IRQ   (2)
#define PN532_RESET (5)

Adafruit_PN532 nfc(PN532_IRQ, PN532_RESET);

#if defined(ARDUINO_ARCH_SAMD)

#define Serial SerialUSB
#endif

uint32_t lastcard = 0;

//music shield
#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>

// These are the pins used for the music maker shield
#define SHIELD_RESET  -1      // VS1053 reset pin (unused!)
#define SHIELD_CS     7      // VS1053 chip select pin (output)
#define SHIELD_DCS    6      // VS1053 Data/command select pin (output)

// These are common pins between breakout and shield
#define CARDCS 4     // Card chip select pin
// DREQ should be an Int pin, see http://arduino.cc/en/Reference/attachInterrupt
#define DREQ 3       // VS1053 Data request, ideally an Interrupt pin

Adafruit_VS1053_FilePlayer musicPlayer = 
  // create shield-example object!
  Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);


void setup() {
  // put your setup code here, to run once:

 Serial.begin(115200);
 Serial.println(F("Hello!"));
 
 //music shield

 Serial.println(F("Adafruit VS1053 Simple Test"));

  if (! musicPlayer.begin()) { // initialise the music player
     Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
     while (1);
  }
  Serial.println(F("VS1053 found"));
  
   if (!SD.begin(CARDCS)) {
    Serial.println(F("SD failed, or not present"));
    while (1);  // don't do anything more
   }

 printDirectory(SD.open("/"), 0);
    musicPlayer.setVolume(2,2);
    musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);

  
 //PN532
 nfc.begin();

 uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
    Serial.print("Didn't find PN53x board");
    while (1); // halt
}

  Serial.print("Found chip PN5"); Serial.println((versiondata>>24) & 0xFF, HEX); 
  Serial.print("Firmware ver. "); Serial.print((versiondata>>16) & 0xFF, DEC); 
  Serial.print('.'); Serial.println((versiondata>>8) & 0xFF, DEC);

nfc.setPassiveActivationRetries(0xFF);
nfc.SAMConfig();

Serial.println(F("Waiting for an ISO14443A card"));

Serial.println(F("Playing welcome"));
    musicPlayer.playFullFile("welcome.mp3");
}


unsigned digit = 0;

void loop() {
  // put your main code here, to run repeatedly:

  boolean success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  uint8_t uidLength;
  
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength);

  uint32_t cardidentifier = 0;

  if (success) {
    
    Serial.print("Card detected #");
    // turn the four byte UID of a mifare classic into a single variable #
    cardidentifier = uid[3];
    cardidentifier <<= 8; cardidentifier |= uid[2];
    cardidentifier <<= 8; cardidentifier |= uid[1];
    cardidentifier <<= 8; cardidentifier |= uid[0];
    Serial.println(cardidentifier);

    //A Fall
  if (cardidentifier == 815239292  && cardidentifier != lastcard) {
    Serial.println(F("Playing Fall"));
    musicPlayer.playFullFile("Fall.mp3");
    lastcard = cardidentifier;
  }
  //B Spring
  if (cardidentifier == 814796204 && cardidentifier != lastcard) {
    Serial.println(F("Playing Spring"));
    musicPlayer.playFullFile("Spring.mp3");
    lastcard = cardidentifier;
  }
  //C Winter
   if (cardidentifier == 815248828 && cardidentifier != lastcard) {
    Serial.println(F("Playing Winter"));
    musicPlayer.playFullFile("Winter.mp3");
    lastcard = cardidentifier;
  }
  //D Summer
   if (cardidentifier == 814833868 && cardidentifier != lastcard) {
    Serial.println(F("Playing Summer"));
    musicPlayer.playFullFile("Summer.mp3");
    lastcard = cardidentifier;
   }

   // summer stuff: ice cream, snow cone, swimmimg, sun
   if (cardidentifier == 814896156 && cardidentifier != lastcard) {
    Serial.println(F("Playing ice cream"));
    musicPlayer.playFullFile("Icecream.mp3");
    lastcard = cardidentifier;
   }
   if (cardidentifier == 814443612 && cardidentifier != lastcard) {
    Serial.println(F("Playing snow cone"));
    musicPlayer.playFullFile("snowcone.mp3");
    lastcard = cardidentifier;
   }
   if (cardidentifier == 815016284 && cardidentifier != lastcard) {
    Serial.println(F("Playing swimming"));
    musicPlayer.playFullFile("swimming.mp3");
    lastcard = cardidentifier;
   }
   if (cardidentifier == 815083196 && cardidentifier != lastcard) {
    Serial.println(F("Playing sun"));
    musicPlayer.playFullFile("sun.mp3");
    lastcard = cardidentifier;
   }
   // fall stuff: wind, orange leaves, yellow leavs
    if (cardidentifier == 814581836 && cardidentifier != lastcard) {
    Serial.println(F("Playing wind"));
    musicPlayer.playFullFile("wind.mp3");
    lastcard = cardidentifier;
   }
    if (cardidentifier == 815082604 && cardidentifier != lastcard) {
    Serial.println(F("Playing orange leaves"));
    musicPlayer.playFullFile("orange.mp3");
    lastcard = cardidentifier;
   }
    if (cardidentifier == 814779820 && cardidentifier != lastcard) {
    Serial.println(F("Playing yellow leaves"));
    musicPlayer.playFullFile("yellow.mp3");
    lastcard = cardidentifier;
   }
   // spring stuff: flowers, bird, insects
    if (cardidentifier == 814955772 && cardidentifier != lastcard) {
    Serial.println(F("Playing flowers"));
    musicPlayer.playFullFile("flowers.mp3");
    lastcard = cardidentifier;
   }
    if (cardidentifier == 814976348 && cardidentifier != lastcard) {
    Serial.println(F("Playing bird"));
    musicPlayer.playFullFile("bird.mp3");
    musicPlayer.playFullFile("birds.mp3");
    lastcard = cardidentifier;
    
   }
    if (cardidentifier == 814855244 && cardidentifier != lastcard) {
    Serial.println(F("Playing insects"));
    musicPlayer.playFullFile("insects.mp3");
    lastcard = cardidentifier;
   }
   // winter stuff: gloves, cap, coat, snow flake, hot chocolate
    if (cardidentifier == 814753036 && cardidentifier != lastcard) {
    Serial.println(F("Playing mittens"));
    musicPlayer.playFullFile("mittens.mp3");
    lastcard = cardidentifier;
   }
    if (cardidentifier == 814937836 && cardidentifier != lastcard) {
    Serial.println(F("Playing hat"));
    musicPlayer.playFullFile("hat.mp3");
    lastcard = cardidentifier;
   }
    if (cardidentifier == 815016636 && cardidentifier != lastcard) {
    Serial.println(F("Playing coat"));
    musicPlayer.playFullFile("coat.mp3");
    lastcard = cardidentifier;
   }
    if (cardidentifier == 814937692 && cardidentifier != lastcard) {
    Serial.println(F("Playing snow flake"));
    musicPlayer.playFullFile("flake.mp3");
    lastcard = cardidentifier;
   }
    if (cardidentifier == 815032140 && cardidentifier != lastcard) {
    Serial.println(F("Playing hot chocolate"));
    musicPlayer.playFullFile("choco.mp3");
    lastcard = cardidentifier;
   }
    
  }
}

  /// File listing helper
void printDirectory(File dir, int numTabs) {
   while(true) {
     
     File entry =  dir.openNextFile();
     if (! entry) {
       // no more files
       //Serial.println("**nomorefiles**");
       break;
     }
     for (uint8_t i=0; i<numTabs; i++) {
       Serial.print('\t');
     }
     Serial.print(entry.name());
     if (entry.isDirectory()) {
       Serial.println("/");
       printDirectory(entry, numTabs+1);
     } else {
       // files have sizes, directories do not
       Serial.print("\t\t");
       Serial.println(entry.size(), DEC);
     }
     entry.close();
   }
}
