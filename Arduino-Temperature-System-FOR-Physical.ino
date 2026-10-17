#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define DHTPIN 6
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

int buzzer = 2;
int ledRed = 3;
int ledYellow = 4;
int ledGreen = 5;

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledGreen, OUTPUT);

  dht.begin();

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Bonjour");
  delay(2000);
  lcd.clear();
}

void loop() {
  float tempC = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(tempC) || isnan(humidity)) {
    lcd.setCursor(0, 0);
    lcd.print("Erreur capteur  ");
    lcd.setCursor(0, 1);
    lcd.print("Verifier DHT11  ");

    digitalWrite(buzzer, LOW);
    digitalWrite(ledRed, LOW);
    digitalWrite(ledYellow, LOW);
    digitalWrite(ledGreen, LOW);

    delay(2000);
    return;
  }

  lcd.setCursor(0, 0);
  lcd.print("TEMP:   ");
  lcd.print(tempC, 2);
  lcd.write((byte)223);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("HUM:   ");
  lcd.print(humidity, 2);
  lcd.print("%");

  if (tempC <= 16) {
    digitalWrite(buzzer, HIGH);
    digitalWrite(ledRed, LOW);
    digitalWrite(ledYellow, LOW);
    digitalWrite(ledGreen, HIGH);
  }
  else if (tempC >= 17 && tempC <= 36) {
    digitalWrite(buzzer, LOW);
    digitalWrite(ledRed, LOW);
    digitalWrite(ledYellow, HIGH);
    digitalWrite(ledGreen, LOW);
  }
  else {
    digitalWrite(buzzer, HIGH);
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledYellow, LOW);
    digitalWrite(ledGreen, LOW);
  }

  delay(2000);
}
