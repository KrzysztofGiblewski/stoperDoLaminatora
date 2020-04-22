#include <LiquidCrystal_I2C.h>
//#include <Wire.h>

unsigned long poczatekMilisekund = 0;
unsigned long koniecMilisekund = 0;

unsigned long poczatekOdliczania = 0;
unsigned long koniecOdliczania = 0;

int ekrany = 0;
boolean mierzCzas = false;
boolean zmierzone = false;

LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
  lcd.init();                      // initialize the lcd
  lcd.backlight();
  lcd.setCursor(3, 0);
  Serial.begin(9600);
  pinMode(A0, INPUT_PULLUP);                //przycisk dodawania sztuki A0    -   lewy
  pinMode(A1, INPUT_PULLUP);                // przycisk odejmowania A1      - środkowy
  pinMode(A2, INPUT_PULLUP);                //przycisk wyboru ekranu A2            -prawy

  // pinMode(A3, OUTPUT); //Konfiguracja A3 jako wyjście dla buzzera

  pinMode(A6, OUTPUT);       //przekaznik1 jako wyjście

}

void loop() {

  //  buzerr();
  if (digitalRead(A2) == LOW)     // jak klikniety przycisk zmiany ekranu to zmiana ekranu w metodzie switch(ekrany)
    zmienEkrany();
  wyswietl();
}
void wyswietl() {
  switch (ekrany)
  {
    case 0:             {
        if (digitalRead(A0) == LOW)   {
          poczatekMilisekund = millis();
          pierwszaLinia(millis());
          drugaLinia("Start ", 0, "  STOP  ", 0);
          Serial.println(millis());

        }
        if (digitalRead(A1) == LOW)   {
          koniecMilisekund = millis() - poczatekMilisekund;
          pierwszaLinia(millis());
          drugaLinia("S ",  koniecMilisekund / 1000UL, ",", koniecMilisekund % 1000UL);
        }
        break;
      }
    case 1:
      {
        if (digitalRead(A0) == LOW)   {
          poczatekOdliczania = millis();
          koniecOdliczania = poczatekOdliczania + 5500UL; //5,5sekundy to 5500 milisekund
          drugaLinia("Start Odliczania" , poczatekOdliczania);
        }
        if (digitalRead(A1) == LOW)   {
          drugaLinia("Stop odliczania ", koniecOdliczania);
          poczatekOdliczania = koniecOdliczania;
        }
         if (koniecOdliczania <= poczatekOdliczania) {
          drugaLinia("Zakończone odliczanie ", koniecMilisekund);
        }
        break;
      }
  }
}

void zmienEkrany() {
  ekrany++;
  delay(500);
  if (ekrany > 1)
    ekrany = 0;
}
void pierwszaLinia(unsigned long milisekundy) {
  lcd.setCursor(0, 0);
  lcd.print(milisekundy);
}
void drugaLinia(String raz, unsigned long dwa, String trzy, unsigned long cztery) {
  lcd.setCursor(0, 1);
  lcd.print(raz);
  lcd.print(dwa);
  lcd.print(trzy);
  lcd.print(cztery);

}
void drugaLinia(String raz, unsigned long dwa) {
  lcd.setCursor(0, 1);
  lcd.print(raz);
  lcd.print(dwa);


}
void buzerr() {
  //      digitalWrite(A3, HIGH);
  //      digitalWrite(A3, LOW);


}
