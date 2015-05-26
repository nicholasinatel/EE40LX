//***************************************************************************************
//  EE40LX
//  Sketch 3.2
//
//  Description; Power-block a 3.3V rail at P1.1 and subsequently read inputs from
//     Wheatstone bridges, connected to P1.2 and P1.7
//
//  Tom Zajdel
//  University of California, Berkeley
//  January 26, 2014
//
//  Version 1.1 January 26, 2014 - Fixed a timing bug by using delayMicroseconds()
//  and also corrected errors in pin assignment
//
//***************************************************************************************

int PBRAIL = P1_1;   // set PBRAIL as P1.1 alias
int LPHOTO = P1_2;   // set LPHOTO as P1.2 alias
int RPHOTO = P1_7;   // set RPHOTO as P1.7 alias
int BUZZER = P1_3; // set BUZZER as P1.3 alias
int val;
int PINO = P1_4;

int REDLED = P1_0;   // set REDLED as P1_0 alias
int GRNLED = P1_6;   // set GRNLED as P1_6 alias

int MICINP = A5;   // set MICINP as P1.5 alias

int value = 0;     // variable that stores the value read in

void setup()
{ 
  
  // set power block pin and led pins as outputs
  pinMode(PBRAIL, OUTPUT);
  pinMode(REDLED, OUTPUT);
  pinMode(GRNLED, OUTPUT);
  // set BUZZER as output pin
  pinMode(BUZZER, OUTPUT);
  // random analog voltage noise at analog pin 0 will seed
  // the random number generator differently every time it runs
  // otherwise, we will hear the same pseudo-random sequence
  // every time we run the program (which is at times useful)
  randomSeed(analogRead(0));
  
  // set photocell input pins
  pinMode(LPHOTO, INPUT);
  pinMode(RPHOTO, INPUT);
  
  // start the serial monitor
  Serial.begin(9600);
  
  
  Serial.println("Setup complete!");

}

void loop()
{
  digitalWrite(PBRAIL, HIGH);        // supply 3.3V to the power rail
  delayMicroseconds(1000);           // delay briefly to allow comparator outputs to settle

  if (digitalRead(LPHOTO) == HIGH)  // if LPHOTO is on, turn REDLED on
     digitalWrite(REDLED, HIGH);     // otherwise, turn REDLED off
  else
     digitalWrite(REDLED, LOW);  
     
  if (digitalRead(RPHOTO) == HIGH)   // if RPHOTO is on, turn GRNLED on
     digitalWrite(GRNLED, HIGH);     // otherwise, turn GRNLED off
  else
     digitalWrite(GRNLED, LOW);  
  
  val = random(10,100);      // create a random number from 1 to 100 using the Energia RNG
  if (val > 50)             // if val is greater than 50, output an 800 Hz wave
    tone(BUZZER, 800, 50);  // otherwise, do nothing for the same period
  else
    delay(50);
    
  value = analogRead(MICINP);  // get the voltage from the microphone
  Serial.println(value);       // write digitized value to serial monitor  
  
  
  if (value >= 560)            // if digitized value is above 560,
    digitalWrite(PINO, HIGH);// turn on the LED...   
  
 //digitalWrite(PBRAIL, LOW);          // turn the power rail off again
 //sleep(19);                          // wait 19 ms (can do other tasks in this time,
                                      // but we are simply demonstrating that you can cut power
                                      // to the circuits for 95% of the time and not notice!

}
