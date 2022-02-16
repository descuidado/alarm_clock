#include <LiquidCrystal.h>
#include <Wire.h>
#include <DS1307RTC.h>
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
//Buttons
#define up 6
#define down 7
#define left 8
#define right 9

bool up_stat = false;
bool down_stat = false;
bool left_stat = false;
bool right_stat = false;
//short int changeState = 9;
short int pos = 0;
short int dh = 0; //decimal hour
short int yh = 0; //yekan hour
short int dm = 0; //decimal minute
short int ym = 0; //yekan minute
short int sh = 0; //start hour
short int sm = 0; //start minute
short int oh = 0; //stop hour
short int om = 0; //stop minute

bool junk = false;
bool junk2 = false;
bool stat = false;
tmElements_t tm;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
SoftwareSerial mySoftwareSerial(10, 13);// RX, TX
DFRobotDFPlayerMini player;
void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  mySoftwareSerial.begin(9600);
  player.begin(mySoftwareSerial);
  pinMode(up, INPUT_PULLUP);
  pinMode(down, INPUT_PULLUP);
  pinMode(left, INPUT_PULLUP);
  pinMode(right, INPUT_PULLUP);
  welcome();
  player.volume(20);
}

void loop() {
  // put your main code here, to run repeatedly:

  lcdhome();
  if (pos == 0) {
    if (digitalRead(right) == HIGH) {
      delay(110);
      if (digitalRead(right) == HIGH) {
        settings();
      }
    }
    while (junk) {
      if (pos == 1) {
        lcd.setCursor(4, 0 );
        lcd.print(F("Alarm 1"));
        if (digitalRead(up) == HIGH) {
          delay(110);
          if (digitalRead(up) == HIGH) {
            lcd.clear();
            lcd.setCursor(3, 0);
            lcd.print(F("Set clock"));
            pos = 3;
          }
        } else if (digitalRead(down) == HIGH) {
          delay(110);
          if (digitalRead(down) == HIGH) {
            lcd.clear();
            lcd.setCursor(4, 0);
            lcd.print(F("Alarm 2"));
            pos = 2;
          }
        } else if (digitalRead(left) == HIGH) {
          delay(110);
          if (digitalRead(left) == HIGH) {
            pos = 0;
            lcd.clear();
            junk = false;
          }
        } else if (digitalRead(right) == HIGH) {
          delay(110);
          if (digitalRead(right) == HIGH) {
            setStartTime();
            junk = false;
          }
        }
      } else if (pos == 2) {
        if (digitalRead(up) == HIGH) {
          delay(110);
          if (digitalRead(up) == HIGH) {
            lcd.clear();
            lcd.setCursor(4, 0);
            lcd.print(F("Alram 1"));
            pos--;
          }
        } else if (digitalRead(down) == HIGH) {
          delay(110);
          if (digitalRead(down) == HIGH) {
            lcd.clear();
            lcd.setCursor(3, 0);
            lcd.print(F("Set clock"));
            pos++;
          }
        } else if (digitalRead(left) == HIGH) {
          delay(110);
          if (digitalRead(left) == HIGH) {
            pos = 0;
            lcd.clear();
            junk = false;
          }
        } else if (digitalRead(right) == HIGH) {
          delay(110);
          if (digitalRead(right) == HIGH) {
            setEndTime();
            junk = false;
          }
        }
      } else if (pos == 3) {
        if (digitalRead(up) == HIGH) {
          delay(110);
          if (digitalRead(up) == HIGH) {
            lcd.clear();
            lcd.setCursor(4, 0);
            lcd.print(F("Alarm 2"));
            pos--;
          }
        } else if (digitalRead(down) == HIGH) {
          delay(110);
          if (digitalRead(down) == HIGH) {
            lcd.clear();
            lcd.setCursor(4, 0);
            lcd.print(F("Alarm 1"));
            pos = 1;
          }
        } else if (digitalRead(left) == HIGH) {
          delay(110);
          if (digitalRead(left) == HIGH) {
            pos = 0;
            lcd.clear();
            junk = false;
          }
        } else if (digitalRead(right) == HIGH) {
          delay(110);
          if (digitalRead(right) == HIGH) {
            pos = 10;
            junk2 = true;
            setclock();
            junk = false;
          }
        }
      }
    }
  }
}
