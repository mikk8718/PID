#include <DFPlayerMini_Fast.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(11, 10);
///
#include <LiquidCrystal.h>
// This comment is here for no reason
int potPin = 1;
int potPin2 = 2;
LiquidCrystal lcd(12, 9, 5, 4, 3, 2);

int button = 8;
int button2 = 7;
int selectedTrack;
DFPlayerMini_Fast myMP3;

void setup() {
    Serial.begin(115200); //this is the rate for the serial monitor, can be changed, doesn't matter much.
    lcd.begin(16, 2); //This is the LCD (Collums, Rows) so max 16 letters per row.

    pinMode(button, INPUT);
    pinMode(button2, INPUT);
    //digitalWrite(button, HIGH);
    //digitalWrite(button2, LOW);
    mySerial.begin (9600);
    myMP3.begin(mySerial);
    delay(1000);
    myMP3.volume(30);
    delay(20);
    

}
void loop() {
  int valPotLCD = 0;
  valPotLCD = analogRead(potPin); //Value goes from 0 to 1023 with potentiometers
  //From here we treshhold values from the slider to display text on the LCD.
  //However due to a 1k resistor being attached to the slider, the first threshold is larger
  //Than the other... IDK if this is why, but my best guess. (It shoudl change around 1/3 of the way for each.

if (!myMP3.isPlaying()){ 
  
    
    if (valPotLCD > 0 && valPotLCD < 169){
      selectedTrack = 2;
      lcd.setCursor(0, 1);
      lcd.print("Adventure track ");
  }
    if (valPotLCD > 169 && valPotLCD < 1023){
      selectedTrack = 1;
      lcd.setCursor(0, 1);
      lcd.print("Journey track   ");
  }
}

  Serial.print(selectedTrack);

  if (digitalRead(button) == HIGH){
    myMP3.play(selectedTrack);
    Serial.print("play");
  }

  if (digitalRead(button2) == HIGH){
    myMP3.reset();
    Serial.print("reset");
     }
lcd.setCursor(0, 0);
lcd.print(valPotLCD);
}
