#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);


//Relátka
#define REL1 10
#define REL2 11
#define REL3 11

//spínače
#define OTV_UP 10
#define OTV_DOWN 11

//koncový spínače
#define KONEC_UP 10
#define KONEC_DOWN 11

//displej
#define SCL 10
#define SDA 11

void setup() {
  lcd.begin(16, 2);
  pinMode(REL1, OUTPUT);
  pinMode(REL2, OUTPUT);
  pinMode(REL3, OUTPUT);

  pinMode(OTV_UP, INPUT);
  pinMode(OTV_DOWN, INPUT);

  pinMode(KONEC_UP, INPUT);
  pinMode(KONEC_DOWN, INPUT);
  
}

void loop() {
 
 
}
