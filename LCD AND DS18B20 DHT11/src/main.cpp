#include <Arduino.h>
#include <LiquidCrystal.h>
#include <DHT.h>
#include <OneWire.h>

#define DHTPIN 13
#define DHTTYPE DHT11
#define POL_BTTN 11
#define ENG_BTTN 10
#define GER_BTTN 9

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
DHT dht(DHTPIN, DHTTYPE);

enum Language {POLISH, ENGLISH, GERMAN};
Language currentLanguage = POLISH;

bool languageSelected = false;

void setup() 
{
  Serial.begin(9600);

  pinMode(POL_BTTN, INPUT_PULLUP);
  pinMode(ENG_BTTN, INPUT_PULLUP);
  pinMode(GER_BTTN, INPUT_PULLUP);

  lcd.begin(16, 2);
  lcd.clear();

  dht.begin();
  Serial.print(F("DHT11 test!"));
}

void loop() 
{
  delay(1000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("check the temp");
  lcd.setCursor(0, 1);
  lcd.print("and humidity");

  delay(5000);

  if(!languageSelected)
    {
    unsigned long start = millis();
    int langIndex = 0;

    while (!languageSelected && millis() - start < 15000)
    {   
    lcd.clear();
    lcd.setCursor(0, 0);

    switch (langIndex)
    {
      case 0:
      lcd.print("Polish");
      lcd.setCursor(0, 1);
      lcd.print("button 1");
      break;

      case 1:
      lcd.print("English");
      lcd.setCursor(0, 1);
      lcd.print("button 2");
      break;

      case 2:
      lcd.print("German");
      lcd.setCursor(0, 1);
      lcd.print("button 3");
      break;    
    }
    unsigned long waitStart = millis();
    while(millis() - waitStart < 5000)
    {
      if(digitalRead(POL_BTTN) == LOW)
      {
        currentLanguage = POLISH;
        languageSelected = true;
        break;
      }
       if(digitalRead(ENG_BTTN) == LOW)
      {
        currentLanguage = ENGLISH;
        languageSelected = true;
        break;
      }
       if(digitalRead(GER_BTTN) == LOW)
      {
        currentLanguage = GERMAN;
        languageSelected = true;
        break;
      }
    }
    langIndex = (langIndex + 1) % 3;
  }
  lcd.clear();
}
//bttn read 
bool PolBttnState = digitalRead(POL_BTTN);
bool EngBttnState = digitalRead(ENG_BTTN);
bool GerBttnState = digitalRead(GER_BTTN);

// DHT11 settings
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  if (isnan(h) || isnan(t) || isnan(f))
  {
    Serial.println(F("FAILED to read DHT sensor!!"));
    return;
  }
  //For Fahrenheit
  float hif = dht.computeHeatIndex(f, h);
  //For CELCIUS
  float hic = dht.computeHeatIndex(t, h, false);
// LCD settings and display
  switch(currentLanguage){
    case POLISH:
  //POLISH VERSION
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("DHT11 Odczytuje..."); 

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Wilgotnosc: "));
  lcd.setCursor(0, 1);
  lcd.print(h);

  delay(4000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Temperatura: "));
  lcd.setCursor(0, 1);
  lcd.print(t);

  delay(4000);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Wskaznik ciepla: "));
  lcd.setCursor(0, 1);
  lcd.print(hic);
  
  delay(4000);
  break;

    case ENGLISH:
  //ENGLISH VERSION
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("DHT11 Working..."); 

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Humidity: "));
  lcd.setCursor(0, 1);
  lcd.print(h);

  delay(4000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Temperature: "));
  lcd.setCursor(0, 1);
  lcd.print(t);

  delay(4000);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Heat index: "));
  lcd.setCursor(0, 1);
  lcd.print(hic);

  delay(4000);
  break;
    case GERMAN:
  //GERMAN VERSION
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("DHT11 Liest..."); 

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Luftfeuchtigkeit: "));
  lcd.setCursor(0, 1);
  lcd.print(h);

  delay(4000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Temperatur: "));
  lcd.setCursor(0, 1);
  lcd.print(t);

  delay(4000);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Hitzeindex: "));
  lcd.setCursor(0, 1);
  lcd.print(hic);

  delay(4000);
  break;
  }
}