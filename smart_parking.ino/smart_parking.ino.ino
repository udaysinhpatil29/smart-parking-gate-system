#include <LiquidCrystal.h>
#include <Servo.h>
LiquidCrystal lcd(21, 22, 25, 26, 27, 28);

Servo gateServo;

int irEntry = PD2;
int irExit  = PD3;

int totalSlots = 5;
int availableSlots = 5;

void setup() {

  pinMode(irEntry, INPUT);
  pinMode(irExit, INPUT);

  gateServo.attach(PD5);

  gateServo.write(0);

  lcd.begin(16, 2);

  lcd.setCursor(0, 0);
  lcd.print("Smart Parking");

  lcd.setCursor(0, 1);
  lcd.print("System Ready");

  delay(2000);

  lcd.clear();
}

void loop() {

  lcd.setCursor(0, 0);
  lcd.print("Slots Left:");

  lcd.setCursor(0, 1);
  lcd.print(availableSlots);
  lcd.print("   ");

  if (digitalRead(irEntry) == LOW) {

    if (availableSlots > 0) {

      gateServo.write(90);

      delay(5000);

      availableSlots--;

      gateServo.write(0);

      delay(1000);
    }

    else {

      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print("Parking Full");

      delay(2000);

      lcd.clear();
    }
  }

  if (digitalRead(irExit) == LOW) {

    if (availableSlots < totalSlots) {

      gateServo.write(90);

      delay(5000);

      availableSlots++;

      gateServo.write(0);

      delay(1000);
    }
  }

  delay(300);
}