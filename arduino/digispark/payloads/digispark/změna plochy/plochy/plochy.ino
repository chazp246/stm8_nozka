//This DigiKeyboard Script downloads and sets a wallpaper through the Windows PowerShell. It has been tested successfully
//on Windows 10 and should probably work with Windows 7/8/8.1 etc.

#include "DigiKeyboard.h"
void setup() {
  //empty
}
void loop() {
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
  for(;;){ /*empty*/ }
}
