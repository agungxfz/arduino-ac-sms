#include <SHT1x.h>
#include <LiquidCrystal.h>
#define dataPin 12
#define clockPin 11

#define A 10
#define B 9
#define C A4
#define D A5

#define E A3
#define L A2
#define G A1
#define H A0

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
SHT1x sht1x(dataPin, clockPin);
int pinRelay = 8, pinOnOff = 13, temp_set, index = 0;
String acStat, angka, lagi, lagian;
double temp_c, humidity;
int temp_intC = (int) temp_c;

void SHT11()
{
  temp_c = sht1x.readTemperatureC();
  humidity = sht1x.readHumidity();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp(C)  Humi(%)");
  lcd.setCursor(0, 1);
  lcd.print(temp_c, 2);
  lcd.setCursor(9, 1);
  lcd.print(humidity, 2);
}

void tempCtrl(double C, int S)
{
  if(C < (S - 2))
  {
    digitalWrite(pinRelay, LOW);
    acStat = "AC OFF";
  } 
  else if (C > (S + 2))
  {
    digitalWrite(pinRelay, HIGH);
    acStat = "AC ON";
  } else 
  {
  }
}

void soft_reset()
{
  //dangerous function
  asm volatile("jmp 0");
}

void setup() 
{
  Serial.begin(115200);
  //7-Segment #1 Satuan
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  //7-Segment #1 Puluhan
  pinMode(A5, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  
  pinMode(pinRelay, OUTPUT);
  pinMode(pinOnOff, OUTPUT);
  
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Welcome...");
  delay(1000);
  lcd.setCursor(0,0);
  lcd.print(" Ahsan Bil Haqi ");
  delay(2000);
  lcd.setCursor(0,1);
  lcd.print("   Elka ITATS   ");
  delay(2000);
  lcd.clear();
}

void loop() 
{
  SHT11();
  if(Serial.available())
  {
    String baca = Serial.readStringUntil('#');
    String lagi = Serial.readStringUntil('$');
    String angka = Serial.readStringUntil('@');
    
    if(lagi == "status")
    {
      Serial.print("STATUS >> ");
      Serial.print(acStat);
      Serial.print(" Suhu : ");
      Serial.print(temp_c);
      Serial.print(" C");
      Serial.print(" Kelembapan : ");
      Serial.print(humidity);
      Serial.print("%");
    } else if(lagi == "nyala")
    {
      acStat = "AC ON";
      digitalWrite(pinOnOff, HIGH);
      Serial.print("NYALA >> ");
      Serial.print(acStat);
      Serial.print(" Suhu : ");
      Serial.print(temp_c);
      Serial.print(" C");
      Serial.print(" Kelembapan : ");
      Serial.print(humidity);
      Serial.print("%");
    } else if(lagi == "mati")
    {
      acStat = "AC OFF";
      digitalWrite(pinOnOff, LOW);
      Serial.print("MATI >> ");
      Serial.print(acStat);
      Serial.print(" Suhu : ");
      Serial.print(temp_c);
      Serial.print(" C");
      Serial.print(" Kelembapan : ");
      Serial.print(humidity);
      Serial.print("%");
    } else if(lagi == "set")
    {
      temp_set = angka.toInt();
      Serial.print("ATUR SUHU >> ");
      Serial.print(acStat);
      Serial.print(" Set suhu pada nilai : ");
      Serial.print(temp_set);
      Serial.print(" C");
    } else {}
    
    Serial.flush();
  }
  tempCtrl(temp_c, temp_set);
  temp_intC = temp_c;
  Byte_2_BCD(A, B, C, D, E, L, G, H);
}
//====================2-DIGIT SEVEN SEGMENT d.i.y VOID : CONFIDENTIAL========================//
void Byte_2_BCD(int pinA1, int pinB1, int pinC1, int pinD1, int pinA2, int pinB2, int pinC2,int pinD2)
{
if(temp_intC == 0)
  {
    digitalWrite(pinA1, 0);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 0);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 1)
  {
    digitalWrite(pinA1, 0);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 1);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 2)
  {
    digitalWrite(pinA1, 0);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 0);
    digitalWrite(pinB2, 1);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 3)
  {
    digitalWrite(pinA1, 0);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 1);
    digitalWrite(pinB2, 1);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 4)
  {
    digitalWrite(pinA1, 0);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 0);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 1);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 5)
  {
    digitalWrite(pinA1, 0);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 1);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 1);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 6)
  {
    digitalWrite(pinA1, 0);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 0);
    digitalWrite(pinB2, 1);
    digitalWrite(pinC2, 1);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 7)
  {
    digitalWrite(pinA1, 0);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 1);
    digitalWrite(pinB2, 1);
    digitalWrite(pinC2, 1);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 8)
  {
    digitalWrite(pinA1, 0);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 0);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 1);
  }
else if(temp_intC == 9)
  {
    digitalWrite(pinA1, 0);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 1);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 1);
  }
else if(temp_intC == 10)
  {
    digitalWrite(pinA1, 1);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 0);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 11)
  {
    digitalWrite(pinA1, 1);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 1);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 12)
  {
    digitalWrite(pinA1, 1);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 0);
    digitalWrite(pinB2, 1);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 13)
  {
    digitalWrite(pinA1, 1);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 1);
    digitalWrite(pinB2, 1);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 14)
  {
    digitalWrite(pinA1, 1);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 0);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 1);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 15)
  {
    digitalWrite(pinA1, 1);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 1);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 1);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 16)
  {
    digitalWrite(pinA1, 1);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 0);
    digitalWrite(pinB2, 1);
    digitalWrite(pinC2, 1);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 17)
  {
    digitalWrite(pinA1, 1);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 1);
    digitalWrite(pinB2, 1);
    digitalWrite(pinC2, 1);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 18)
  {
    digitalWrite(pinA1, 1);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 0);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 1);
  }
else if(temp_intC == 19)
  {
    digitalWrite(pinA1, 1);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 1);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 1);
  }
else if(temp_intC == 20)
  {
    digitalWrite(pinA1, 0);
    digitalWrite(pinB1, 1);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 0);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 21)
  {
    digitalWrite(pinA1, 0);
    digitalWrite(pinB1, 1);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 1);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 22)
  {
    digitalWrite(pinA1, 0);
    digitalWrite(pinB1, 1);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 0);
    digitalWrite(pinB2, 1);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 23)
  {
    digitalWrite(pinA1, 0);
    digitalWrite(pinB1, 1);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 1);
    digitalWrite(pinB2, 1);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 24)
  {
    digitalWrite(pinA1, 0);
    digitalWrite(pinB1, 1);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 0);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 1);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 25)
  {
    digitalWrite(pinA1, 0);
    digitalWrite(pinB1, 1);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 1);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 1);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 26)
  {
    digitalWrite(pinA1, 0);
    digitalWrite(pinB1, 1);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 0);
    digitalWrite(pinB2, 1);
    digitalWrite(pinC2, 1);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 27)
  {
    digitalWrite(pinA1, 0);
    digitalWrite(pinB1, 1);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 1);
    digitalWrite(pinB2, 1);
    digitalWrite(pinC2, 1);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 28)
  {
    digitalWrite(pinA1, 0);
    digitalWrite(pinB1, 1);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 0);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 1);
  }
else if(temp_intC == 29)
  {
    digitalWrite(pinA1, 0);
    digitalWrite(pinB1, 1);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 1);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 1);
  }
else if(temp_intC == 30)
  {
    digitalWrite(pinA1, 1);
    digitalWrite(pinB1, 1);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 0);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 31)
  {
    digitalWrite(pinA1, 1);
    digitalWrite(pinB1, 1);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 1);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 32)
  {
    digitalWrite(pinA1, 1);
    digitalWrite(pinB1, 1);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 0);
    digitalWrite(pinB2, 1);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 33)
  {
    digitalWrite(pinA1, 1);
    digitalWrite(pinB1, 1);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 1);
    digitalWrite(pinB2, 1);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 34)
  {
    digitalWrite(pinA1, 1);
    digitalWrite(pinB1, 1);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 0);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 1);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 35)
  {
    digitalWrite(pinA1, 1);
    digitalWrite(pinB1, 1);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 1);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 1);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 36)
  {
    digitalWrite(pinA1, 1);
    digitalWrite(pinB1, 1);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 0);
    digitalWrite(pinB2, 1);
    digitalWrite(pinC2, 1);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 37)
  {
    digitalWrite(pinA1, 1);
    digitalWrite(pinB1, 1);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 1);
    digitalWrite(pinB2, 1);
    digitalWrite(pinC2, 1);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 38)
  {
    digitalWrite(pinA1, 1);
    digitalWrite(pinB1, 1);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 0);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 1);
  }
else if(temp_intC == 39)
  {
    digitalWrite(pinA1, 1);
    digitalWrite(pinB1, 1);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 1);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 1);
  }
else if(temp_intC == 40)
  {
    digitalWrite(pinA1, 0);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 1);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 0);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 41)
  {
    digitalWrite(pinA1, 0);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 1);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 1);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 42)
  {
    digitalWrite(pinA1, 0);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 1);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 0);
    digitalWrite(pinB2, 1);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 43)
  {
    digitalWrite(pinA1, 0);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 1);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 1);
    digitalWrite(pinB2, 1);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 44)
  {
    digitalWrite(pinA1, 0);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 1);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 0);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 1);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 45)
  {
    digitalWrite(pinA1, 0);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 1);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 1);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 1);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 46)
  {
    digitalWrite(pinA1, 0);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 1);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 0);
    digitalWrite(pinB2, 1);
    digitalWrite(pinC2, 1);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 47)
  {
    digitalWrite(pinA1, 0);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 1);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 1);
    digitalWrite(pinB2, 1);
    digitalWrite(pinC2, 1);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 48)
  {
    digitalWrite(pinA1, 0);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 1);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 0);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 1);
  }
else if(temp_intC == 49)
  {
    digitalWrite(pinA1, 0);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 1);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 1);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 1);
  }
else if(temp_intC == 50)
  {
    digitalWrite(pinA1, 1);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 1);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 0);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 51)
  {
    digitalWrite(pinA1, 1);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 1);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 1);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 52)
  {
    digitalWrite(pinA1, 1);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 1);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 0);
    digitalWrite(pinB2, 1);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 53)
  {
    digitalWrite(pinA1, 1);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 1);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 1);
    digitalWrite(pinB2, 1);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 54)
  {
    digitalWrite(pinA1, 1);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 1);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 0);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 1);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 55)
  {
    digitalWrite(pinA1, 1);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 1);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 1);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 1);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 56)
  {
    digitalWrite(pinA1, 1);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 1);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 0);
    digitalWrite(pinB2, 1);
    digitalWrite(pinC2, 1);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 57)
  {
    digitalWrite(pinA1, 1);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 1);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 1);
    digitalWrite(pinB2, 1);
    digitalWrite(pinC2, 1);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 58)
  {
    digitalWrite(pinA1, 1);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 1);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 0);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 1);
  }
else if(temp_intC == 59)
  {
    digitalWrite(pinA1, 1);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 1);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 1);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 1);
  }
else if(temp_intC == 60)
  {
    digitalWrite(pinA1, 0);
    digitalWrite(pinB1, 1);
    digitalWrite(pinC1, 1);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 0);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 61)
  {
    digitalWrite(pinA1, 0);
    digitalWrite(pinB1, 1);
    digitalWrite(pinC1, 1);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 1);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 62)
  {
    digitalWrite(pinA1, 0);
    digitalWrite(pinB1, 1);
    digitalWrite(pinC1, 1);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 0);
    digitalWrite(pinB2, 1);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 63)
  {
    digitalWrite(pinA1, 0);
    digitalWrite(pinB1, 1);
    digitalWrite(pinC1, 1);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 1);
    digitalWrite(pinB2, 1);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 64)
  {
    digitalWrite(pinA1, 0);
    digitalWrite(pinB1, 1);
    digitalWrite(pinC1, 1);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 0);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 1);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 65)
  {
    digitalWrite(pinA1, 0);
    digitalWrite(pinB1, 1);
    digitalWrite(pinC1, 1);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 1);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 1);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 66)
  {
    digitalWrite(pinA1, 0);
    digitalWrite(pinB1, 1);
    digitalWrite(pinC1, 1);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 0);
    digitalWrite(pinB2, 1);
    digitalWrite(pinC2, 1);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 67)
  {
    digitalWrite(pinA1, 0);
    digitalWrite(pinB1, 1);
    digitalWrite(pinC1, 1);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 1);
    digitalWrite(pinB2, 1);
    digitalWrite(pinC2, 1);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 68)
  {
    digitalWrite(pinA1, 0);
    digitalWrite(pinB1, 1);
    digitalWrite(pinC1, 1);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 0);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 1);
  }
else if(temp_intC == 69)
  {
    digitalWrite(pinA1, 0);
    digitalWrite(pinB1, 1);
    digitalWrite(pinC1, 1);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 1);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 1);
  }
else if(temp_intC == 70)
  {
    digitalWrite(pinA1, 1);
    digitalWrite(pinB1, 1);
    digitalWrite(pinC1, 1);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 0);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 71)
  {
    digitalWrite(pinA1, 1);
    digitalWrite(pinB1, 1);
    digitalWrite(pinC1, 1);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 1);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 72)
  {
    digitalWrite(pinA1, 1);
    digitalWrite(pinB1, 1);
    digitalWrite(pinC1, 1);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 0);
    digitalWrite(pinB2, 1);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 73)
  {
    digitalWrite(pinA1, 1);
    digitalWrite(pinB1, 1);
    digitalWrite(pinC1, 1);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 1);
    digitalWrite(pinB2, 1);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 74)
  {
    digitalWrite(pinA1, 1);
    digitalWrite(pinB1, 1);
    digitalWrite(pinC1, 1);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 0);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 1);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 75)
  {
    digitalWrite(pinA1, 1);
    digitalWrite(pinB1, 1);
    digitalWrite(pinC1, 1);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 1);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 1);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 76)
  {
    digitalWrite(pinA1, 1);
    digitalWrite(pinB1, 1);
    digitalWrite(pinC1, 1);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 0);
    digitalWrite(pinB2, 1);
    digitalWrite(pinC2, 1);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 77)
  {
    digitalWrite(pinA1, 1);
    digitalWrite(pinB1, 1);
    digitalWrite(pinC1, 1);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 1);
    digitalWrite(pinB2, 1);
    digitalWrite(pinC2, 1);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 78)
  {
    digitalWrite(pinA1, 1);
    digitalWrite(pinB1, 1);
    digitalWrite(pinC1, 1);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 0);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 1);
  }
else if(temp_intC == 79)
  {
    digitalWrite(pinA1, 1);
    digitalWrite(pinB1, 1);
    digitalWrite(pinC1, 1);
    digitalWrite(pinD1, 0);
    
    digitalWrite(pinA2, 1);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 1);
  }
else if(temp_intC == 80)
  {
    digitalWrite(pinA1, 0);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 1);
    
    digitalWrite(pinA2, 0);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 81)
  {
    digitalWrite(pinA1, 0);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 1);
    
    digitalWrite(pinA2, 1);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 82)
  {
    digitalWrite(pinA1, 0);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 1);
    
    digitalWrite(pinA2, 0);
    digitalWrite(pinB2, 1);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 83)
  {
    digitalWrite(pinA1, 0);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 1);
    
    digitalWrite(pinA2, 1);
    digitalWrite(pinB2, 1);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 84)
  {
    digitalWrite(pinA1, 0);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 1);
    
    digitalWrite(pinA2, 0);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 1);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 85)
  {
    digitalWrite(pinA1, 0);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 1);
    
    digitalWrite(pinA2, 1);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 1);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 86)
  {
    digitalWrite(pinA1, 0);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 1);
    
    digitalWrite(pinA2, 0);
    digitalWrite(pinB2, 1);
    digitalWrite(pinC2, 1);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 87)
  {
    digitalWrite(pinA1, 0);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 1);
    
    digitalWrite(pinA2, 1);
    digitalWrite(pinB2, 1);
    digitalWrite(pinC2, 1);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 88)
  {
    digitalWrite(pinA1, 0);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 1);
    
    digitalWrite(pinA2, 0);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 1);
  }
else if(temp_intC == 89)
  {
    digitalWrite(pinA1, 0);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 1);
    
    digitalWrite(pinA2, 1);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 1);
  }
else if(temp_intC == 90)
  {
    digitalWrite(pinA1, 1);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 1);
    
    digitalWrite(pinA2, 0);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 91)
  {
    digitalWrite(pinA1, 1);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 1);
    
    digitalWrite(pinA2, 1);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 92)
  {
    digitalWrite(pinA1, 1);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 1);
    
    digitalWrite(pinA2, 0);
    digitalWrite(pinB2, 1);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 93)
  {
    digitalWrite(pinA1, 1);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 1);
    
    digitalWrite(pinA2, 1);
    digitalWrite(pinB2, 1);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 94)
  {
    digitalWrite(pinA1, 1);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 1);
    
    digitalWrite(pinA2, 0);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 1);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 95)
  {
    digitalWrite(pinA1, 1);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 1);
    
    digitalWrite(pinA2, 1);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 1);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 96)
  {
    digitalWrite(pinA1, 1);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 1);
    
    digitalWrite(pinA2, 0);
    digitalWrite(pinB2, 1);
    digitalWrite(pinC2, 1);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 97)
  {
    digitalWrite(pinA1, 1);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 1);
    
    digitalWrite(pinA2, 1);
    digitalWrite(pinB2, 1);
    digitalWrite(pinC2, 1);
    digitalWrite(pinD2, 0);
  }
else if(temp_intC == 98)
  {
    digitalWrite(pinA1, 1);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 1);
    
    digitalWrite(pinA2, 0);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 1);
  }
else if(temp_intC == 99)
  {
    digitalWrite(pinA1, 1);
    digitalWrite(pinB1, 0);
    digitalWrite(pinC1, 0);
    digitalWrite(pinD1, 1);
    
    digitalWrite(pinA2, 1);
    digitalWrite(pinB2, 0);
    digitalWrite(pinC2, 0);
    digitalWrite(pinD2, 1);
  }
 }
