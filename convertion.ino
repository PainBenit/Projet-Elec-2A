#include <LiquidCrystal.h>
#include <stdlib.h>


const int pin_RS = 8; 
const int pin_EN = 9; 
const int pin_d4 = 4; 
const int pin_d5 = 5; 
const int pin_d6 = 6; 
const int pin_d7 = 7;
int menu = 0; 
LiquidCrystal lcd( pin_RS,  pin_EN,  pin_d4,  pin_d5,  pin_d6,  pin_d7);


void setup() {
  // initialize serial communication at 9600 bits per second:
Serial.begin(9600);
lcd.begin(16,2);

}

String converteur (int selecteur)
{
  String Value;
  String Reception;
  long X;
  int n =0;
  switch(selecteur)
  {
    case 0: Value = String(select_dec(),HEX); break;
    case 1: Value = String(select_dec(),BIN); break;
    case 2:
    Reception=select_bin(); 
    for(n=0; n<Reception.length();n++)
    {
      X = X+Reception[n]*pow(2,n);
    }
    Value = String(X,HEX);
    break;
    case 3:   Reception=select_bin(); 
    for(n=0; n<Reception.length();n++)
    {
      X = X+Reception[n]*pow(2,n);
    }
    Value = String(X,HEX);
    break;
    case 4: Value = String(select_hex(),BIN); break;
    case 5: Value = String(select_hex(),DEC); break;

  }
  return Value;
};
  
  String select_bin()
  {
    String value = "";
    long digit = 0;
    while (value.length() < 10)
    {
         lcd.clear();
         delay(10);
         digit = analogRead(A5);
         digit = ((digit - 50)/500); 
         lcd.print(value);
         lcd.setCursor(value.length() + 2, 0);
         lcd.print(digit);
         delay(50);
         if (analogRead(A0) < 2)
         {
            value = value + String(digit);
            delay(250);
         }
         Serial.println(value);
         if(analogRead(A0) < 1000 && analogRead(A0) > 10)
         {
          break;
         }
    }
    lcd.clear();
    delay(10);
    
    Serial.print(value.toInt());
    }
  
  long select_dec()
  { 
    long digit = 0;   
    String value = "";
    while (value.length() < 8)
    {
         lcd.clear();
         delay(10);
         digit = analogRead(A5);
         digit = ((digit - 50)/100); 
         lcd.print(value);
         lcd.setCursor(value.length() + 2, 0);
         lcd.print(digit);
         delay(50);
         if (analogRead(A0) < 2)
         {
            value = value + String(digit);
            delay(250);
         }
         if(analogRead(A0) < 1000 && analogRead(A0) > 10)
         {
          break;
         }         
         Serial.println(value);
    }
    lcd.clear();
    delay(10);
    return value.toInt();
  }
  
  long select_hex()
  {
    long digit = 0;
    String value = "";
    String digithex = "";
    while(value.length() < 8)
    {
         lcd.clear();
         delay(10);
         digit = analogRead(A5);
         digit = ((digit - 50)/63); 
         if (digit > 9)
            {
                switch(digit)
                  {
                    case 10: digithex = 'A'; break;
                    case 11: digithex = 'B'; break;
                    case 12: digithex = 'C'; break;
                    case 13: digithex = 'D'; break;
                    case 14: digithex = 'E'; break;
                    case 15: digithex = 'F'; break;
                  }
            }
         else
             {
              digithex = String(digit);
             }
         lcd.print(value);
         lcd.setCursor(value.length() + 3, 0);
         lcd.print(digithex);
         delay(50);
         if (analogRead(A0) < 2)
         {
            value = value + digithex;
            delay(250);
         }

         if(analogRead(A0) < 1000 && analogRead(A0) > 10)
         {
          break;
         }
         Serial.println(value);
    }
    lcd.clear();
    delay(10);
    
    Serial.print(value.toInt());
    return value.toInt();
  }



// the setup routine runs once when you press reset:




// the loop routine runs over and over again forever:
void loop() 
{
  lcd.setCursor(0, 0);
  // read the input on analog pin 0:
  long sensorValue = analogRead(A0); 
  
  menu = analogRead(A5);
  menu = ((menu - 50)/170);
  switch (menu)
    {
      case 0: lcd.print("Dec -> Hex"); break;
      case 1: lcd.print("Dec -> Bin"); break;
      case 2: lcd.print("Bin -> Hex"); break;
      case 3: lcd.print("Bin -> Dec"); break;
      case 4: lcd.print("Hex -> Bin"); break;
      case 5: lcd.print("Hex -> Dec"); break;
    }
  
  if (sensorValue < 2)
  {
    delay(100);
    switch (menu)
    {
      case 0: lcd.print(converteur(menu));delay (4000); break;
      case 1: lcd.print(converteur(menu));delay (4000); break;
      case 2: lcd.print(converteur(menu));delay (4000); break;
      case 3: lcd.print(converteur(menu));delay (4000); break;
      case 4: lcd.print(converteur(menu));delay (4000); break;
      case 5: lcd.print(converteur(menu));delay (4000); break;
    }
  }
  
  
  
  delay(100);
  lcd.clear();
  delay(10);
}
