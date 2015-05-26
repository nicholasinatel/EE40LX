//***************************************************************************************
//  EE40LX
//  Sketch 3.4
//
//  Description; P1.3 outputs 800 Hz square wave in random burst patterns
//
//  Tom Zajdel
//  University of California, Berkeley
//  January 24, 2014
//
//***************************************************************************************

int BUZZER = P1_3; // set BUZZER as P1.3 alias
int val;

void setup()
{
  // set BUZZER as output pin
  pinMode(BUZZER, OUTPUT);
  
  // random analog voltage noise at analog pin 0 will seed
  // the random number generator differently every time it runs
  // otherwise, we will hear the same pseudo-random sequence
  // every time we run the program (which is at times useful)
  randomSeed(analogRead(0));
}

void loop()
{
  val = random(80,100);      // create a random number from 1 to 100 using the Energia RNG
  if (val > 50)             // if val is greater than 50, output an 800 Hz wave
    tone(BUZZER, 800, 50);  // otherwise, do nothing for the same period
  else
    delay(50);
}
