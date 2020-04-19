#include <LiquidCrystal_I2C.h>
#include <Wire.h>
long ilePacz = 0;   //ile sztuk w bierzacej paczce
long ileKart = 0;   //ile pelnych kartonow
long ileWszy = 0;   //ile wszystkich produktow
long ustawPacz = 100; // zadaje ilosc w paczce np 100szt
long ustawKart = 0; //zadaje ilosc w kartonie np 1000sz
long ileWOsta = 0; //ile w ostatnim nie pelnym kartonie
int ekrany = 0;
int poIle = 1; //po ile dodawać kolejne sztuki jeśli robi dwa na raz to niech dodaje po 2 sztuki
int coIle = 1;
int takty = 0;
int sztuka = 1;
int wartoscImpulsu = 0;
int wartoscZblizImp = 0;
int popWartoscImpu  = 0;
char impuls = 1; //wartosc 0 lub 1 zeby po podaniu ciaglego napiecia nie naliczal kolejnych sztuk
double napImpulsu = 4.0; //minimalna wartość impulsu w voltach dla impulsu
double zeroNapiecia = 0.1; // wartosc napiecia ponirzej ktorego uznajemy za zanik impulsu
int opuznij = 10; //przerwa miedzy cyklami
int sygnal = 1; // wyprzedzenie przed iloma workami ma piszcec
int dlugoscSygnal = 0; //zabezpieczenie przed zatrzymaniem na piszczacym worku
int wyjdzZMenu = 0;
int ekranyUstawien = 0; //czy rozszerzone menu czy krutkie
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Ustawienie adresu ukladu na 0x27         A4 SDA        A5 SCL

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  lcd.print("0");
  pinMode(A0, INPUT_PULLUP); //przycisk dodawania sztuki A0
  pinMode(A1, INPUT_PULLUP); // przycisk odejmowania A1
  pinMode(A2, INPUT_PULLUP); //przycisk wyboru A2
  pinMode(A3, OUTPUT); //Konfiguracja A3 jako wyjście dla buzzera
  //modul na pinie A4 SDA  dla I2C
  //    i A5 SCL dla I2C
  //  wartoscImpulsu = analogRead(A6); // pin A6 czyta wartosc napiecia inpulsu
  wartoscZblizImp = analogRead(A7); //pin A7 z modulu zblizeniowego


}

void loop() {

  // wartoscImpulsu = analogRead(A6); //zczytuje impuls z licznika maszyny A6
  wartoscZblizImp = analogRead(A7); //zczytuje impuls z modulu zblizeniowego A7

  delay(opuznij); //daje małe opuźnienie żeby impuls był pojedyńczy
  //  Serial.println(wartoscZblizImp* (5.0 / 1024.0));


  if (dlugoscSygnal < 50)
    dlugoscSygnal++;

  if (wartoscZblizImp < zeroNapiecia) { //jak napiecie zaniknie to mozna znowu liczyc impuls
    impuls = 1;
    Serial.println(wartoscZblizImp * (5.0 / 1024.0));
  }
  if ((wartoscZblizImp * (5.0 / 1024.0) > napImpulsu) && impuls > 0 ) { //warunek minimalnego napiecia dla impulsu zeby dodac 1 impuls musi byc poprzedni zero
    impuls = 0;
    dlugoscSygnal = 0;

    Serial.println(wartoscZblizImp * (5.0 / 1024.0));
    wartoscZblizImp = 0;

  }

  if (digitalRead(A2) == LOW)   { //przycisk wyboru A2
    zmienEkrany();
    wyjdzZMenu = 0;

  }

  if (ekrany > 0) //jesli na innym ekranie menu to po czasie wyjdz do ekranu pierwszego
    if (wyjdzZMenu < 305)
      wyjdzZMenu++;

  wyswietl();
  buzerr();
}
void wyswietl() {
  pierwszaLinia();
  switch (ekrany)
  {
    case 0:             // bierzacza ilosc w paczce wlasnie robionej
      {
        if (digitalRead(A0) == LOW)   {
        }
        if (digitalRead(A1) == LOW)   {
        }
        drugaLinia("", ilePacz, " sztuk w paczce           ", 0);
        break;
      }
    case 1:                     // bierzaca ilosc sztuk w kartonie
      {
        if (digitalRead(A0) == LOW)   {
        }
        if (digitalRead(A1) == LOW)   {
        }
        drugaLinia("ost karon ", ileWOsta, "szt    ", ileKart);
        break;
      }


  }

}
void zmienEkrany() {
  delay(200);
  ekrany++;
  lcd.begin(16, 2);
  if (ekranyUstawien == 1)
    if (ekrany > 12)
      ekrany = 0;
  if (ekranyUstawien == 0)
    if (ekrany > 6)
      ekrany = 0;
}
void pierwszaLinia() {
  lcd.setCursor(0, 0);
  lcd.print(ileWszy);
  //  lcd.print("  ");
  //  lcd.print(dlugoscSygnal);
  //  lcd.print("  ");
  //  lcd.print(wyjdzZMenu);
  lcd.print(" szt wszystkich ");
}
void drugaLinia(String raz, long dwa, String trzy, long cztery) {
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
