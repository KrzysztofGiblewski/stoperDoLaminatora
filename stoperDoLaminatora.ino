#include <LiquidCrystal_I2C.h>
#include <Wire.h>

unsigned long poczatekMilisekund = 0;
unsigned long koniecMilisekund = 0;

unsigned long poczatekOdliczania = 0;
unsigned long koniecOdliczania = 0;

int ekrany = 0;
boolean mierzCzas = false;
boolean zmierzone = false;

LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
  //  lcd.init();                      // initialize the lcd
  //  lcd.init();
  lcd.backlight();
  lcd.setCursor(3, 0);
  Serial.begin(9600);
  pinMode(A0, INPUT_PULLUP);                //przycisk dodawania sztuki A0    -   lewy
  pinMode(A1, INPUT_PULLUP);                // przycisk odejmowania A1      - środkowy
  pinMode(A2, INPUT_PULLUP);                //przycisk wyboru A2            -prawy

  // pinMode(A3, OUTPUT); //Konfiguracja A3 jako wyjście dla buzzera

  pinMode(A6, OUTPUT);       //przekaznik1 jako wyjście

}

void loop() {
  wyswietl();
  //  buzerr();
  if (digitalRead(A2) == LOW)     // jak klikniety przycisk zmiany ekranu to zmiana ekranu w metodzie switch(ekrany)
    ekrany++;
}
void wyswietl() {
  switch (ekrany)
  {
    case 0:             {
        if (digitalRead(A0) == LOW)   {
          mierzCzas = true;
          zmierzone = false;
          poczatekMilisekund = millis();
          pierwszaLinia(millis());
          drugaLinia("Start ", 0, "  STOP  ", 0);
        }
        if (digitalRead(A1) == LOW)   {
          mierzCzas = false;
          zmierzone = true;
          koniecMilisekund = millis() - poczatekMilisekund;
          pierwszaLinia(millis());
          drugaLinia("Stop                                     ",  koniecMilisekund / 1000, ",", koniecMilisekund % 1000);
          drugaLinia("S ",  koniecMilisekund / 1000, ",", koniecMilisekund % 1000);
        }
        break;
      }
    case 1:              {
        pierwszaLinia("odliczanie 15,5 sekundy");

        if (digitalRead(A0) == LOW)   {
          poczatekOdliczania = millis();
          koniecOdliczania = poczatekOdliczania + 15500; //15,5sekundy to 15500 milisekund


        }
        if (digitalRead(A1) == LOW)   {
          drugaLinia("Stop",koniecOdliczania," wyznaczony",0);
        }
        drugaLinia("Start Odliczania" , poczatekOdliczania, " GO", koniecOdliczania);
        if (poczatekOdliczania <= koniecOdliczania) {
          drugaLinia("Koniec odliczania", koniecOdliczania,"czas minoł",0);
        }
        break;
      }


  }
  if (mierzCzas == true) {
    koniecMilisekund = millis() - poczatekMilisekund;
    drugaLinia("S ",  koniecMilisekund / 1000, ",", koniecMilisekund % 1000);
  }
  if (zmierzone == true && mierzCzas == false)
    drugaLinia("S ",  koniecMilisekund / 1000, ",", koniecMilisekund % 1000);
  if (zmierzone == false && mierzCzas == false)
    drugaLinia("START ",  0, " STOP ", 0);
}
void zmienEkrany() {
  ekrany++;
  delay(100);
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
void buzerr() {
  //      digitalWrite(A3, HIGH);
  //      digitalWrite(A3, LOW);


}
