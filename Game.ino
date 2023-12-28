/*
Buzzer -> 11 pin
Joystic -> VR_X - A0, VR_Y - A1
LCD -> I2C
*/

#include <LiquidCrystal_I2C.h>
#define X analogRead(A1)
#define Y analogRead(A0)
#define sfx 11

LiquidCrystal_I2C lcd(0x27, 20, 4);

int x = 9;
const int y = 3;
int score = 0;
int time = 600;
bool end = false;

int pr_x[5];
int pr_y[5];

void setup() {
  pinMode(sfx, OUTPUT);
  pinMode(A1, INPUT);
  pinMode(A0, INPUT);

  lcd.init();
  lcd.backlight();
  lcd.clear();

  for (int i = 0; i < 5; i++) {
    pr_y[i] = 0;
    pr_x[i] = random(0, 19);
  }
}

void loop() {
  noTone(sfx);
  lcd.clear();
  lcd.setCursor(x, y);
  lcd.print("@");

  time--;

  if (X <= 2 && x <= 19 && !end) {
    x++;
  } else if (X >= 1020 && x >= 0 && !end) {
    x--;
  }

  for (int i = 0; i < 5; i++) {
    pr_y[i]++;
    if (pr_y[i] == 4 && !end) {
      pr_x[i] = random(0, 19);
      pr_y[i] = 0;
    }
    if (pr_y[i] == y && pr_x[i] == x && !end) {
      score++;
      pr_y[i] = 0;
      pr_x[i] = random(0, 19);
      tone(sfx, 300);
    }
    lcd.setCursor(pr_x[i], pr_y[i]);
    lcd.print("#");

    if (time <= 0) {
      end = true;
    }
  }
  lcd.setCursor(0, 0);
  lcd.print("SCORE:");
  lcd.setCursor(6, 0);
  lcd.print(score);
  lcd.setCursor(12, 0);
  lcd.print("TIME:");
  lcd.setCursor(17, 0);
  lcd.print(time);
  if (end) {
    lcd.clear();
    lcd.setCursor(5, 1);
    lcd.print("GAME OVER!");
    lcd.setCursor(5, 2);
    lcd.print("SCORE:");
    lcd.setCursor(11, 2);
    lcd.print(score);
  }
  delay(250);
}
