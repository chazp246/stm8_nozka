#include <RCSwitch.h>
#include <M5StickC.h>
RCSwitch mySwitch = RCSwitch();
long sequence = 14257100;

void setup() {
  Serial.begin(115200);

  // Transmitter is connected to Arduino Pin #10
  mySwitch.enableTransmit(26);
  M5.begin();
  // Optional set pulse length.


  // set protocol (default is 1, will work for most outlets)
  // mySwitch.setProtocol(2);

  // Optional set number of transmission repetitions.
    mySwitch.setRepeatTransmit(1);

  mySwitch.setPulseLength(500);


}

void loop() {
  sequence = sequence + 1;
  Serial.println(sequence);
  mySwitch.send(sequence, 24);


}
