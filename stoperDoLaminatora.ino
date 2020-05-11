#include <LiquidCrystal_I2C.h>
//#include <Wire.h>

unsigned long poczatekMilisekund = 0;
unsigned long koniecMilisekund = 0;

unsigned long poczatekOdliczania = 0;
unsigned long koniecOdliczania = 0;

unsigned long ileCzasuOdliczam = 5500;

int ekrany = 0;

boolean odliczajCzas = false; //kontrolka czy liczy czy stoi
boolean stanPrzycisku=false; //stan czyli fals to stoi a true bedzie w trybie odliczania 

String tekst, tekst2 = "------------------";

LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
  lcd.init();                      // initialize the lcd
  lcd.backlight();
  lcd.setCursor(3, 0);
  Serial.begin(9600);
  pinMode(A0, INPUT_PULLUP);                //przycisk dodawania sztuki A0    -   lewy
  pinMode(A1, INPUT_PULLUP);                // przycisk odejmowania A1      - środkowy
  pinMode(A2, INPUT_PULLUP);                //przycisk START STOP A2            -prawy

  // pinMode(A3, OUTPUT); //Konfiguracja A3 jako wyjście dla buzzera

  pinMode(7, OUTPUT);       //przekaznik1 jako wyjście D7
  digitalWrite(7, HIGH); //wyłączony przekaźnik
}

void loop() {

  if (odliczajCzas == false && stanPrzycisku==false);
  if (digitalRead(A2) == LOW) { //prawy skrajny będzie startował
    delay(300);
    startuj();
    stanPrzycisku=true;
  }
  if (odliczajCzas == true && stanPrzycisku==true); {
    sprawdz();
    if (digitalRead(A2) == LOW) { //prawy skrajny będzie STOP
      delay(300);
      zatrzymaj();
      stanPrzycisku=false;
    }
  }

  if (digitalRead(A0) == LOW) {
    delay(200);
    ileCzasuOdliczam = ileCzasuOdliczam + 100;
    tekst = ileCzasuOdliczam;

  }

  if (digitalRead(A1) == LOW) {
    delay(200);
    ileCzasuOdliczam = ileCzasuOdliczam - 100;
    tekst = ileCzasuOdliczam;

  }
  wyswietl();
}


// obsługa przekaźnika WŁĄCZANIE
void zalacz() {
  digitalWrite(7, LOW);  // włączanie przekaźnika
}
//obsługa przekaźnika WYŁĄCZANIE
void wylacz() {
  digitalWrite(7, HIGH); // wyłączam przekażnik
}

void sprawdz() {
  if ( koniecOdliczania <= millis()) {
    odliczajCzas = false;
    zatrzymaj(); // przekaźnik
  }
  if (odliczajCzas != true) {
    //pierwszaLinia("Nie odliczam");
  //  drugaLinia("wciśnij przycisk ", 0);

  }
}

void startuj() {
  odliczajCzas = true;
  tekst = "ODLICZANIE TRWA           ";
  tekst2 = "Czas mija";
  poczatekOdliczania = millis();
  koniecOdliczania = poczatekOdliczania + ileCzasuOdliczam;
  zalacz();  //przekaźnik
}

void zatrzymaj() {
  odliczajCzas = false;
  tekst = ileCzasuOdliczam;
  tekst2 = "Odliczanie STOP ";
  poczatekOdliczania = koniecOdliczania;
  wylacz();
}

void wyswietl() {
  pierwszaLinia(tekst);
  drugaLinia(tekst2, koniecOdliczania - millis());
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
