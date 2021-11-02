#include <M5Stack.h>
#include <SPI.h>
#include <Wire.h>
#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

// Libraries for SD card
#include "FS.h"
#include "SD.h"

// Define CS pin for the SD card module
const int chipSelect = 4;

// Variables to save date and time
String Data;
long Received;
int Pulse;
int Protocol;
int Bits;

void setup() {
  M5.begin();
  M5.Power.begin();
  M5.Lcd.begin();

  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(10, 10);
  M5.Lcd.setTextColor(GREEN);

  mySwitch.enableReceive(2);

  SD.begin(chipSelect);

  File file = SD.open("/data.txt");
  if (!file) {
    writeFile(SD, "/data.txt", "Received, Pulse, Protocol, Bits \r\n");
  }

  file.close();
  pinMode(37, INPUT);
  pinMode(38, INPUT);
  pinMode(39, INPUT);
}


void loop() {

  M5.update();

  //mySwitch.available();
  if (mySwitch.available() && readFile(SD, "/data.txt" == mySwitch.getReceivedValue()) {

    //    M5.Lcd.printf("New Sample");
    M5.Lcd.fillScreen(GREEN);
    Received = mySwitch.getReceivedValue();
    Pulse = mySwitch.getReceivedDelay();
    Protocol = mySwitch.getReceivedProtocol();
    Bits = mySwitch.getReceivedBitlength();

    Data = String(Received) + "," + String(Pulse) + "," +
           String(Protocol) + "," + String(Bits) + "\r\n";
    appendFile(SD, "/data.txt", Data.c_str());

    mySwitch.resetAvailable();
  }
  else if (M5.BtnC.wasReleasefor(1000)) {
    M5.Lcd.fillScreen(BLACK);
  }

}


// Write to the SD card (DON'T MODIFY THIS FUNCTION)
void writeFile(fs::FS &fs, const char * path, const char * message) {

  File file = fs.open(path, FILE_WRITE);
  if (!file) {
    return;
  }
  if (file.print(message)) {
  } else {
  }
  file.close();
}

// Append data to the SD card (DON'T MODIFY THIS FUNCTION)
void appendFile(fs::FS &fs, const char * path, const char * message) {

  File file = fs.open(path, FILE_APPEND);
  if (!file) {
    return;
  }
  if (file.print(message)) {
  }
  else {
  }
  file.close();
}

//čtení souboru
void readFile(fs::FS &fs, const char * path) {
  File file = fs.open(path);
  if (!file) {
    return;
  }
  while (file.available()) {
    file.read();
  }
  file.close();
}
