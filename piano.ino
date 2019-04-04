// Import the CapacitiveSensor Library.
#include <CapacitiveSensor.h>

 
#define speaker 11
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

int melody[] = {
  NOTE_D4, NOTE_D4, NOTE_D5, 0, NOTE_A4, 0, 0, NOTE_GS4, 0,
  NOTE_G4, 0, NOTE_F4, 0, NOTE_D4, NOTE_F4,
  NOTE_G4,
  NOTE_C4, NOTE_C4, NOTE_D4, 0, NOTE_A4, 0, 0, NOTE_GS4, 0, NOTE_G4,
  0, NOTE_F4, 0, NOTE_D4, NOTE_F4, NOTE_G4,
  NOTE_B4, NOTE_B4, NOTE_D4, 0, NOTE_A4, 0, 0, NOTE_GS4, 0, NOTE_G4, 0, NOTE_F4, 0, NOTE_D4, NOTE_F4, NOTE_G4,
  NOTE_AS4, NOTE_AS4, NOTE_D4, 0, NOTE_A4, 0, 0, NOTE_GS4, 0, NOTE_G4, 0, NOTE_F4, 0, NOTE_D4, NOTE_F4, NOTE_G4,
};

int tempo[] = {
  16, 16, 16, 16, 16, 16, 16, 16, 16,
  16, 16, 16, 16, 16, 16, 
  16, 16,
  16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
  16, 16, 16, 16, 16, 16,
  16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
  16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
};

// Set the Send Pin & Receive Pin.
CapacitiveSensor   cs_2_3 = CapacitiveSensor(2,3);        
CapacitiveSensor   cs_2_4 = CapacitiveSensor(2,4);         
CapacitiveSensor   cs_2_5 = CapacitiveSensor(2,5);     
CapacitiveSensor   cs_2_6 = CapacitiveSensor(2,6);     
CapacitiveSensor   cs_2_7 = CapacitiveSensor(2,7);      
CapacitiveSensor   cs_2_8 = CapacitiveSensor(2,8);         
CapacitiveSensor   cs_2_9 = CapacitiveSensor(2,9);  
CapacitiveSensor   cs_2_10 = CapacitiveSensor(2,10);
CapacitiveSensor   cs_2_A0 = CapacitiveSensor(2,A0);
CapacitiveSensor   cs_2_A1 = CapacitiveSensor(2,A1);  
CapacitiveSensor   cs_2_A2 = CapacitiveSensor(2,A2);  
CapacitiveSensor   cs_2_A3 = CapacitiveSensor(2,A3);       
int led = A4;

void setup()
{
  cs_2_6.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
  pinMode(led, OUTPUT);
  pinMode(11, OUTPUT);
  // Arduino start communicate with computer.
  Serial.begin(9600);
}


int song = 0;

void sing(int s) {
  song = s;
  if (song == 1) {
    Serial.println(" 'Megalovania' ");
    int size = sizeof(melody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {
      int noteDuration = 1000 / tempo[thisNote];

      buzz(speaker, melody[thisNote], noteDuration);

      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);

      buzz(speaker, 0, noteDuration);

    }
  }
}

void buzz(int targetPin, long frequency, long length) {
  long delayValue = 1000000 / frequency / 2; // calculate the delay value between transitions
  //// 1 second's worth of microseconds, divided by the frequency, then split in half since
  //// there are two phases to each cycle
  long numCycles = frequency * length / 1000; // calculate the number of cycles for proper timing
  //// multiply frequency, which is really cycles per second, by the number of seconds to
  //// get the total number of cycles to produce
  for (long i = 0; i < numCycles; i++) { // for the calculated length of time...
    digitalWrite(targetPin, HIGH); // write the buzzer pin high to push out the diaphram
    delayMicroseconds(delayValue); // wait for the calculated delay value
    digitalWrite(targetPin, LOW); // write the buzzer pin low to pull back the diaphram
    delayMicroseconds(delayValue); // wait again or the calculated delay value
  }
}



void loop()
{

sing(0);
  
  // Set a timer.
  long start = millis();
  
  // Set the sensitivity of the sensors.
  long total1 =  cs_2_3.capacitiveSensor(30);
  long total2 =  cs_2_4.capacitiveSensor(30);
  long total3 =  cs_2_5.capacitiveSensor(30);
  long total4 =  cs_2_6.capacitiveSensor(30);
  long total5 =  cs_2_7.capacitiveSensor(30);
  long total6 =  cs_2_8.capacitiveSensor(30);
  long total7 =  cs_2_9.capacitiveSensor(30);
  long total8 =  cs_2_10.capacitiveSensor(30);
  long total9 =  cs_2_A0.capacitiveSensor(30);
  long tota20 =  cs_2_A1.capacitiveSensor(30);
  long tota21 =  cs_2_A2.capacitiveSensor(30);
  long tota22 =  cs_2_A3.capacitiveSensor(30);

  Serial.print(millis() - start);        // check on performance in milliseconds
  Serial.print("\t");                    // tab character for debug windown spacing

  Serial.print(total1);                  // print sensor output 1
  Serial.print("\t");                    // Leave some space before print the next output
  Serial.print(total2);                  // print sensor output 2
  Serial.print("\t");                    // Leave some space before print the next output
  Serial.print(total3);                  // print sensor output 3
  Serial.print("\t");                    // Leave some space before print the next output
  Serial.print(total4);                  // print sensor output 4
  Serial.print("\t");                    // Leave some space before print the next output
  Serial.print(total5);                  // print sensor output 5
  Serial.print("\t");                    // Leave some space before print the next output
  Serial.print(total6);                  // print sensor output 6
  Serial.print("\t");                    // Leave some space before print the next output
  Serial.print(total7);                   // print sensor output 7
  Serial.print("\t");
  Serial.print(total8);                 // print sensor output 8
  Serial.print("\t");                     // "println" - "ln" represent as "line", system will jump to next line after print the output.
  Serial.print(total9);
  Serial.print("\t");
  Serial.print(tota20);
  Serial.print("\t");
  Serial.print(tota21);
  Serial.print("\t");
  
  Serial.println(tota22);
  Serial.print("\t");
  
  // When hand is touched the sensor, the speaker will produce a tone.
  // I set a threshold for it, so that the sensor won't be too sensitive.
  // you can see https://www.arduino.cc/en/Tutorial/toneMelody if you want to change frequency

  //if (total1 > 500 & total2 > 500)
  //{
  //  sing(1);
  //}
  
  if (total1 > 500)
  {
    tone(speaker,NOTE_C4);
    digitalWrite(led, HIGH);
  }
  if (total2 > 500)
  {
    tone(speaker,NOTE_CS4);
    digitalWrite(led, HIGH);
  }
  if (total3 > 500)
  {
    tone(speaker,NOTE_D4);
    digitalWrite(led, HIGH);
  }
  if (total4 > 500)
  {
    tone(speaker,NOTE_DS4);
    digitalWrite(led, HIGH);
  }
  if (total5 > 500)
  {
    tone(speaker,NOTE_E4);
    digitalWrite(led, HIGH);
  }
  if (total6 > 500)
  {
    tone(speaker,NOTE_F4);
    digitalWrite(led, HIGH);
  }
  if (total7 > 500)
  {
    tone(speaker,NOTE_FS4);
    digitalWrite(led, HIGH);
  }
  if (total8 > 500)
  {
    tone(speaker,NOTE_G4);
    digitalWrite(led, HIGH);
  }
  if (total9 > 500)
  {
    tone(speaker,NOTE_GS4);
    digitalWrite(led, HIGH);
  }
  if (tota20 > 500)
  {
    tone(speaker,NOTE_A4);
    digitalWrite(led, HIGH);
  }
  if (tota21 > 500)
  {
    tone(speaker,NOTE_AS4);
    digitalWrite(led, HIGH);
  }
  if (tota22 > 500)
  {
    tone(speaker,NOTE_B4);
    digitalWrite(led, HIGH);  
  }
  
  // When hand didn't touch on it, no tone is produced.
  if (total1<=500  &  total2<=500  &  total3<=500 & total4<=500  &  total5<=500  &  total6<=500 &  total7<=500 & total8<=500 & total9<=500 & tota20<=500 &  tota21<=500 & tota22<=500)
    {
      digitalWrite(led, LOW);
      noTone(speaker);
    }
    
  delay(10);                             // arbitrary delay to limit data to serial port 
}
