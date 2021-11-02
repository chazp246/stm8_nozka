#include "DigiKeyboard.h"
void setup() {
}

void loop() {
  DigiKeyboard.delay(500);
  DigiKeyboard.sendKeyStroke(KEY_L, MOD_GUI_LEFT);
 
  
  }
