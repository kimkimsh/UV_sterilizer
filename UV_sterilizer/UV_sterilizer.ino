//library for FND display module
// you can get the library here, https://github.com/avishorp/TM1637
#include <TM1637Display.h>

#define CLK 2
#define DIO 3
#define buzzer 4

TM1637Display display(CLK, DIO);

int led1 = 6;
int led2 = 7;
int led3 = 8;
int led4 = A3;
int led5 = A4;
int led6 = A5;

// duration that the cleaner run
int duration = 15;

// data that the FND module show
uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };

// notes in the melody:
int melody[] = {
  262, 196, 196, 220, 196, 0, 248, 262
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

void setup() {
  
  display.setBrightness(15);// brightness of FND module
  display.setSegments(data);// display FND module

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
}

void loop() {
  led_control(HIGH);
  count_nb();
  led_control(LOW);
  sound();
  delay(3000);
}

// function that show count with FND dsplay module
void count_nb()
{
  int d = 0;
  for (int i = 1; i < duration+1 ; i++)
  {
    int k = i;
    if (i >= 10)
    {
      k -= 10;
      d = 1;
    }
    data[0] = display.encodeDigit(0);
    data[1] = display.encodeDigit(0);
    data[2] = display.encodeDigit(d);
    data[3] = display.encodeDigit(k);
    display.setSegments(data);
    delay(1000);
  }
}

// function that control the UVC led
void led_control(boolean stat)
{
  digitalWrite(led1, stat);
  digitalWrite(led2, stat);
  digitalWrite(led3, stat);
  digitalWrite(led4, stat);
  digitalWrite(led5, stat);
  digitalWrite(led6, stat);
}

//function that play the sound with buzzer
void sound()
{
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(buzzer, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(buzzer);
  }
}
