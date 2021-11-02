long randNumber;
long randtrvani;

void setup() {
  
  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(5));
  pinMode(13, OUTPUT);
}

void loop() {
  // print a random number from 0 to 299
  randNumber = random(6000, 12000);
delay(randNumber);
digitalWrite(13, HIGH);


randtrvani = random(200, 600);
delay(randtrvani);
digitalWrite(13, LOW);

  // print a random number from 10 to 19

}
