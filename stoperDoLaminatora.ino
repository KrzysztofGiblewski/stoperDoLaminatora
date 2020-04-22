#include <LiquidCrystal_I2C.h>
//#include <Wire.h>

unsigned long poczatekMilisekund = 0;
unsigned long koniecMilisekund = 0;

unsigned long poczatekOdliczania = 0;
unsigned long koniecOdliczania = 0;

int ekrany = 1;
boolean mierzCzas = false;
boolean odliczajCzas = false;

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
  wyswietl();

  if (odliczajCzas == true) {
    drugaLinia("CZAS MIJA   ", koniecOdliczania - millis());
    if ( koniecOdliczania <= millis()) {
      odliczajCzas = false;
      pierwszaLinia("koniec odliczania");
      drugaLinia("KONIEC  odliczania   ", koniecOdliczania - millis());
    } if (odliczajCzas != true) {
      pierwszaLinia("Nie odliczam");
      drugaLinia("wciśnij przycisk ", 0);
    }
  }
}

void wyswietl() {

  if (digitalRead(A0) == LOW)   {
    delay(50);
    odliczajCzas = true;
    poczatekOdliczania = millis();
    koniecOdliczania = poczatekOdliczania + 5500UL; //5,5sekundy to 5500 milisekund
    pierwszaLinia("start odliczania   ");
    drugaLinia("Start Odl " , koniecOdliczania - millis());
  }
  if (digitalRead(A1) == LOW)   {
    odliczajCzas = false;
    pierwszaLinia("Czas minoł          ");
    drugaLinia("Stop odliczania ", koniecOdliczania - millis());
    poczatekOdliczania = koniecOdliczania;
  }
}

void pierwszaLinia(unsigned long milisekundy) {
  lcd.setCursor(0, 0);
  lcd.print(milisekundy);
}
void pierwszaLinia(String tekst) {
  lcd.setCursor(0, 0);
  lcd.print(tekst);
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
