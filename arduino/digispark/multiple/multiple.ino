#include "DigiKeyboard.h"
#include <RCSwitch.h>
int H1;
int H2;
int done = 0;
int hodnota;

RCSwitch mySwitch = RCSwitch();

void setup() {
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  mySwitch.enableReceive(5);
}

void loop() {
  H1 = digitalRead(1);
  H2 = digitalRead(0);
  if (mySwitch.available()) {
    hodnota = mySwitch.getReceivedValue();
  }


  if ((H1 == 1 && H2 == 0) or hodnota == 14367376)
  {
    DigiKeyboard.delay(500);
    DigiKeyboard.sendKeyStroke(KEY_L, MOD_GUI_LEFT);
  }

  else if ((H1 == 1 && H2 == 1) or hodnota == 14367453)
  {
    DigiKeyboard.sendKeyStroke(15, MOD_ALT_LEFT | MOD_CONTROL_LEFT);

  }

  else if (H1 == 0 && H2 == 1 && done != 1)
  {
    done = 1;
    DigiKeyboard.sendKeyStroke(KEY_F2, MOD_ALT_LEFT);
    DigiKeyboard.delay(500);
    DigiKeyboard.print("terminal");
    DigiKeyboard.sendKeyStroke(KEY_ENTER);
    DigiKeyboard.delay(500);
    DigiKeyboard.print("startqemu L main");
    DigiKeyboard.sendKeyStroke(KEY_ENTER);
    DigiKeyboard.delay(5000);
    DigiKeyboard.print("root");
    DigiKeyboard.sendKeyStroke(KEY_ENTER);
    DigiKeyboard.delay(500);
    DigiKeyboard.print("heslo");
    DigiKeyboard.sendKeyStroke(KEY_ENTER);
    DigiKeyboard.delay(500);
    DigiKeyboard.print("passwd");
    DigiKeyboard.sendKeyStroke(KEY_ENTER);
    DigiKeyboard.delay(500);
    DigiKeyboard.print("weeb");
    DigiKeyboard.sendKeyStroke(KEY_ENTER);
    DigiKeyboard.delay(500);
    DigiKeyboard.print("weeb");
    DigiKeyboard.sendKeyStroke(KEY_ENTER);
    DigiKeyboard.delay(500);
    DigiKeyboard.print("ip link eth0 up");
    DigiKeyboard.sendKeyStroke(KEY_ENTER);
    DigiKeyboard.delay(500);
    DigiKeyboard.print("ip addr add 172.30.0.7/24 dev eth0");
    DigiKeyboard.sendKeyStroke(KEY_ENTER);
    DigiKeyboard.delay(500);
    DigiKeyboard.print("ip route add default via 172.30.0.222");
    DigiKeyboard.sendKeyStroke(KEY_ENTER);

  }
}
