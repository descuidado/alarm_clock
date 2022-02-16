void welcome() {
  lcd.setCursor(3, 0);
  lcd.print(F("I Love You"));
  lcd.setCursor(4, 1);
  lcd.print(F("Niloofar"));
  delay(1000);
  lcd.clear();
}

void lcdhome() {
  lcd.home();
  lcd.print(F("Time:"));
  lcd.setCursor(11, 0);
  RTC.read(tm);
  lcd.print(tm.Hour);
  lcd.print(F(":"));
  lcd.print(tm.Minute);
  lcd.setCursor(0, 1);
  lcd.print(F("Date:"));
  lcd.setCursor(7, 1);
  lcd.print(tmYearToCalendar(tm.Year));
  lcd.print(F("/"));
  lcd.print(tm.Month);
  lcd.print(F("/"));
  lcd.print(tm.Day);

  if (sh == tm.Hour && sm == tm.Minute) {
    allon();
  }
  if (oh == tm.Hour && om == tm.Minute) {
    allon();
  }
  pos = 0;
}

void allon() {
  if (!stat) {
    lcd.clear();
    lcd.home();
    lcd.print("Alarm");
    player.play(1);
    stat = true;
    delay(20000);
    lcd.clear();
  }
}

void settings() {
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print(F("Settings"));
  delay(1000);
  junk = true;
  pos = 1;
  lcd.clear();
}

void setclock() {
  lcd.blink();
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print(F("Set time"));
  settime();
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.noBlink();
  lcd.print(F("Time saved"));
  lcd.setCursor(2, 1);
  lcd.print(F("successfully"));
  //change ds1307 time here
  tm.Hour = ((dh * 10) + yh);
  tm.Minute = ((dm * 10) + ym);
  tm.Second = (0);
  RTC.write(tm);
  dh = 0;
  yh = 0;
  dm = 0;
  ym = 0;
  delay(1500);
  lcd.clear();
}

void setStartTime() {
  lcd.blink();
  lcd.setCursor(4, 0);
  lcd.print(F("Alarm 1"));
  settime();
  lcd.clear();
  lcd.home();
  lcd.noBlink();
  sh = (dh * 10) + yh;
  sm = (dm * 10) + ym;
  dh = 0;
  yh = 0;
  dm = 0;
  ym = 0;
  //delay(1500);
  //lcd.clear();
}

void setEndTime() {
  lcd.blink();
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print(F("Alarm 2"));
  settime();
  lcd.clear();
  lcd.home();
  lcd.noBlink();
  oh = (dh * 10) + yh;
  om = (dm * 10) + ym;
  dh = 0;
  yh = 0;
  dm = 0;
  ym = 0;
  //delay(500);
  //lcd.clear();
}

void settime() {
  lcd.setCursor(5, 1);
  lcd.print("00:00");
  lcd.setCursor(5, 1);
  junk2 = true;
  pos = 10;
  while (junk2) {
    if (pos == 10) {
      lcd.setCursor(5, 1);
      if (digitalRead(up) == HIGH) {
        delay(110);
        if (digitalRead(up) == HIGH) {
          dh++;
          if (dh > 2) {
            dh = 0;
          }
          lcd.print(dh);
          lcd.setCursor(5, 1);
        }
      } else if (digitalRead(down) == HIGH) {
        delay(110);
        if (digitalRead(down) == HIGH) {
          dh--;
          if (dh < 0) {
            dh = 2;
          }
          lcd.print(dh);
          lcd.setCursor(5, 1);
        }
      } else if (digitalRead(right) == HIGH) {
        delay(110);
        if (digitalRead(right) == HIGH) {
          pos++; //11
        }
      } else if (digitalRead(left) == HIGH) {
        delay(110);
        if (digitalRead(left) == HIGH) {
          junk2 = false;
        }
      }
    } else if (pos == 11) {
      lcd.setCursor(6, 1);
      if (digitalRead(up) == HIGH) {
        delay(110);
        if (digitalRead(up) == HIGH) {
          yh++;
          if (dh < 2 && yh > 9) {
            yh = 0;
          } else if (dh == 2 && yh >= 4) {
            yh = 0;
          }
          lcd.print(yh);
          lcd.setCursor(6, 1);
        }
      } else if (digitalRead(down) == HIGH) {
        delay(110);
        if (digitalRead(down) == HIGH) {
          yh--;
          if (dh < 2 && yh <= 0) {
            yh = 9;
          } else if (yh < 0) {
            yh = 3;
          }
          lcd.print(yh);
          lcd.setCursor(6, 1);
        }
      } else if (digitalRead(right) == HIGH) {
        delay(110);
        if (digitalRead(right) == HIGH) {
          pos++; //12
        }
      } else if (digitalRead(left) == HIGH) {
        delay(110);
        if (digitalRead(left) == HIGH) {
          pos--; //10
        }
      }
    } else if (pos == 12) {
      lcd.setCursor(8, 1);
      if (digitalRead(up) == HIGH) {
        delay(110);
        if (digitalRead(up) == HIGH) {
          dm++;
          if (dm >= 6) {
            dm = 0;
          }
          lcd.print(dm);
          lcd.setCursor(8, 1);
        }
      } else if (digitalRead(down) == HIGH) {
        delay(110);
        if (digitalRead(down) == HIGH) {
          dm--;
          if (dm < 0) {
            dm = 6;
          }
          lcd.print(dm);
          lcd.setCursor(8, 1);
        }
      } else if (digitalRead(right) == HIGH) {
        delay(110);
        if (digitalRead(right) == HIGH) {
          lcd.setCursor(9, 1);
          pos++;
        }
      } else if (digitalRead(left) == HIGH) {
        delay(110);
        if (digitalRead(left) == HIGH) {
          pos--;
        }
      }
    } else if (pos == 13) {
      lcd.setCursor(9, 1);
      if (digitalRead(up) == HIGH) {
        delay(110);
        if (digitalRead(up) == HIGH) {
          ym++;
          if (ym >= 10) {
            ym = 0;
          }
          lcd.print(ym);
          lcd.setCursor(9, 1);
        }
      } else if (digitalRead(down) == HIGH) {
        delay(110);
        if (digitalRead(down) == HIGH) {
          ym--;
          if (ym <= 0) {
            ym = 9;
          }
          lcd.print(ym);
          lcd.setCursor(9, 1);
        }
      } else if (digitalRead(right) == HIGH) {
        delay(110);
        if (digitalRead(right) == HIGH) {
          junk2 = false;
          lcd.clear();
          lcd.setCursor(6, 1);
          lcd.print(F("Saved"));
          delay(1000);
        }
      } else if (digitalRead(left) == HIGH) {
        delay(110);
        if (digitalRead(left) == HIGH) {
          pos--;
        }
      }
    }
  }
}
