/*
  Simple example for receiving
  
  https://github.com/sui77/rc-switch/
*/
#include <M5Stack.h>
#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();


void setup() {
M5.Power.begin();
M5.begin();
  mySwitch.enableReceive(2);  // Receiver on interrupt 0 => that is pin #2

}

void loop() {
  if (mySwitch.available()) {
    if (mySwitch.getReceivedValue()==14257176) {
      M5.Lcd.fillScreen(BLACK);
      delay(500);
      M5.Lcd.fillScreen(WHITE);
      delay(500);
      M5.Lcd.fillScreen(BLACK);
      delay(500);
      M5.Lcd.fillScreen(WHITE);
      delay(500);
      M5.Lcd.fillScreen(BLACK);
      
      }


    mySwitch.resetAvailable();
  }
}
