#include <LiquidCrystal_I2C.h>
#include <Wire.h>
unsigned long poczatekMilisekund = 0;
unsigned long koniecMilisekund = 0;
int ekrany = 0;
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Ustawienie adresu ukladu na 0x27         A4 SDA        A5 SCL

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  lcd.print("0");
  pinMode(A0, INPUT_PULLUP);                //przycisk dodawania sztuki A0    -   lewy
  pinMode(A1, INPUT_PULLUP);                // przycisk odejmowania A1      - środkowy
  pinMode(A2, INPUT_PULLUP);                //przycisk wyboru A2            -prawy

  pinMode(A3, OUTPUT); //Konfiguracja A3 jako wyjście dla buzzera
  //modul na pinie A4 SDA  dla I2C
  //    i A5 SCL dla I2C
  //  wartoscImpulsu = analogRead(A6); // pin A6 czyta wartosc napiecia inpulsu
//  wartoscZblizImp = analogRead(A7); //pin A7 z modulu zblizeniowego
}

void loop() {
  wyswietl();
//  buzerr();
}
void wyswietl() {
  poczatekMilisekund = millis();
  pierwszaLinia(millis());
  switch (ekrany)
  {
    case 0:             {
        if (digitalRead(A0) == LOW)   {
          koniecMilisekund=millis()-poczatekMilisekund;
          drugaLinia("poczatek ", poczatekMilisekund, " koniec ", koniecMilisekund);
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
  ekrany++;
  delay(100);
  if (ekrany>3)
  ekrany=0;
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
