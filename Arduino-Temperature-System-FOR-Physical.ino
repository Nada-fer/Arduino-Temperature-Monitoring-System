
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define DHTPIN 6
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const int buzzer = 2;
const int ledRed = 3;
const int ledYellow = 4;
const int ledGreen = 5;

const float COLD_THRESHOLD = 16.0;
const float HOT_THRESHOLD = 37.0;

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledGreen, OUTPUT);

  Serial.begin(9600);

  dht.begin();

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Temperature &");
  lcd.setCursor(0, 1);
  lcd.print("Humidity System");

  delay(2000);
  lcd.clear();
}

void loop() {
  float tempC = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(tempC) || isnan(humidity)) {
    lcd.setCursor(0, 0);
    lcd.print("Sensor error    ");
    lcd.setCursor(0, 1);
    lcd.print("Check DHT11     ");

    digitalWrite(buzzer, LOW);
    digitalWrite(ledRed, LOW);
    digitalWrite(ledYellow, LOW);
    digitalWrite(ledGreen, LOW);

    delay(2000);
    return;
  }
  
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(tempC, 1);
  lcd.print((char)223);
  lcd.print("C H:");
  lcd.print(humidity, 0);
  lcd.print("%   ");

  Serial.print("Temperature: ");
  Serial.print(tempC);
  Serial.print(" C | Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  if (tempC <= COLD_THRESHOLD) {
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledYellow, LOW);
    digitalWrite(ledRed, LOW);
    digitalWrite(buzzer, HIGH);

    lcd.setCursor(0, 1);
    lcd.print("Temp froide     ");
  }
  else if (tempC < HOT_THRESHOLD) {
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledYellow, HIGH);
    digitalWrite(ledRed, LOW);
    digitalWrite(buzzer, LOW);

    lcd.setCursor(0, 1);
    lcd.print("Temp normale    ");
  }
  else {
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledYellow, LOW);
    digitalWrite(ledRed, HIGH);
    digitalWrite(buzzer, HIGH);

    lcd.setCursor(0, 1);
    lcd.print("Alerte chaleur  ");
  }

  delay(2000);
}
