#include <RCSwitch.h>
#include <M5StickC.h>
RCSwitch mySwitch = RCSwitch();

void setup() {


  // Transmitter is connected to Arduino Pin #10
  mySwitch.enableTransmit(26);
  M5.begin();

  // Optional set pulse length.


  // set protocol (default is 1, will work for most outlets)
  // mySwitch.setProtocol(2);

  // Optional set number of transmission repetitions.
  //  mySwitch.setRepeatTransmit(10);




}

void loop() {
  M5.update();

  if (M5.BtnA.wasReleased()) {

    mySwitch.setPulseLength(500);
    mySwitch.send(14367376, 24);

  }




}
