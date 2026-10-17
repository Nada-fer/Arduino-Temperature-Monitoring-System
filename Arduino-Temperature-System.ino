#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x26, 16, 2); 

int tempPin = A3;
int buzzer = 2;
int ledRed = 3;
int ledYellow = 4;
int ledGreen = 5;

void setup() {
  pinMode(tempPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.begin(16, 2);
  
  lcd.print("Bonjour");
  delay(2000); 
  lcd.clear(); 
}

void loop() {
  int sensorValue = analogRead(tempPin);
  double tempC = sensorValue * (4.88/10) - 50;
  
  lcd.setCursor(0, 0); 
  lcd.print("Temp ");
  lcd.setCursor(8, 0);
  lcd.print(tempC);
  lcd.setCursor(14, 0);
  lcd.print("C");
  
  if (tempC <= 16){
    digitalWrite(buzzer, HIGH);
    digitalWrite(ledRed, LOW);
    digitalWrite(ledYellow, LOW);
    digitalWrite(ledGreen, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("Temp froide");
  } 
  else if (tempC <= 36 && tempC >= 17){
    digitalWrite(buzzer, LOW);
    digitalWrite(ledRed, LOW);
    digitalWrite(ledYellow, HIGH);
    digitalWrite(ledGreen, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Temp normale"); 
  }
  else if (tempC >= 37){
    digitalWrite(buzzer, HIGH);
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledYellow, LOW);
    digitalWrite(ledGreen, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Alerte           ");
  }
}
