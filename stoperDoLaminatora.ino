#include <LiquidCrystal_I2C.h>
#include <Wire.h>
int ekrany = 0;
int wartoscImpulsu = 0;
int wartoscZblizImp = 0;
int popWartoscImpu  = 0;
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
  pinMode(A0, INPUT_PULLUP);                //przycisk dodawania sztuki A0
  pinMode(A1, INPUT_PULLUP);                // przycisk odejmowania A1
  pinMode(A2, INPUT_PULLUP);                //przycisk wyboru A2
  
  pinMode(A3, OUTPUT); //Konfiguracja A3 jako wyjście dla buzzera
  //modul na pinie A4 SDA  dla I2C
  //    i A5 SCL dla I2C
  //  wartoscImpulsu = analogRead(A6); // pin A6 czyta wartosc napiecia inpulsu
  wartoscZblizImp = analogRead(A7); //pin A7 z modulu zblizeniowego
}

void loop() {

  // wartoscImpulsu = analogRead(A6); //zczytuje impuls z licznika maszyny A6
  wartoscZblizImp = analogRead(A7); //zczytuje impuls z modulu zblizeniowego A7

  wyswietl();
  buzerr();
}
void wyswietl() {
  pierwszaLinia();
  switch (ekrany)
  {
    case 0:             {
        if (digitalRead(A0) == LOW)   {
        }
        if (digitalRead(A1) == LOW)   {
        }
        break;
      }
    case 1:              {
        if (digitalRead(A0) == LOW)   {
        }
        if (digitalRead(A1) == LOW)   {
        }
        break;
      }


  }

}
void zmienEkrany() {
  delay(50);
  ekrany++;
  lcd.begin(16, 2);
  if (ekranyUstawien == 1)
    if (ekrany > 3)
      ekrany = 0;
 }
void pierwszaLinia() {
  lcd.setCursor(0, 0);
  lcd.print(" tekst  ");
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
