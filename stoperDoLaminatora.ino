#include <LiquidCrystal_I2C.h>
//#include <Wire.h>

unsigned long poczatekMilisekund = 0;
unsigned long koniecMilisekund = 0;

unsigned long poczatekOdliczania = 0;
unsigned long koniecOdliczania = 0;

int ekrany = 1;
boolean mierzCzas = false;
boolean odliczajCzas = false;
String tekst, tekst2="Czekam                    ";

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
 
  sprawdz();
  if (digitalRead(A0) == LOW)
    startuj();
  if (digitalRead(A1) == LOW) 
  zatrzymaj(); 
   wyswietl(); 
}

void wyswietl() {
  pierwszaLinia(tekst);
     drugaLinia(tekst2, koniecOdliczania - millis());
 }
void sprawdz() {

  if (odliczajCzas == true) {
    tekst2="Odliczam    ";
    drugaLinia(tekst2, koniecOdliczania - millis());
    if ( koniecOdliczania <= millis()) {
      odliczajCzas = false;
      zatrzymaj();
    } if (odliczajCzas != true) {
      pierwszaLinia("Nie odliczam");
      drugaLinia("wciśnij przycisk ", 0);
    }
  }
}
void startuj() {

  delay(50);
  tekst="ODLICZANIE TRWA           ";
  tekst2="Czas mija";
  odliczajCzas = true;
  poczatekOdliczania = millis();
  koniecOdliczania = poczatekOdliczania + 5500UL; //5,5sekundy to 5500 milisekund

}
void zatrzymaj(){
  tekst="Zatrzymane               ";
  tekst2="Odliczanie STOP ";
odliczajCzas = false;
 poczatekOdliczania = koniecOdliczania;
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
