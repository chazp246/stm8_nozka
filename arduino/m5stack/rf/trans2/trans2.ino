#include <RCSwitch.h>
#include <M5Stack.h>
RCSwitch mySwitch = RCSwitch();
int pulse = 500;
int bits = 1;
void setup() {


  // Transmitter is connected to Arduino Pin #10
  mySwitch.enableTransmit(5);
  M5.Power.begin();
  // Optional set pulse length.


  // set protocol (default is 1, will work for most outlets)
  // mySwitch.setProtocol(2);

  // Optional set number of transmission repetitions.
  //  mySwitch.setRepeatTransmit(10);




}

void loop() {
  M5.update();
  if (M5.BtnA.wasReleased() || M5.BtnA.pressedFor(1000, 200)) {
    mySwitch.setPulseLength(500);
    mySwitch.send(14257176, 24);
  }




}
