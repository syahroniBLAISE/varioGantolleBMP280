//Library untuk buzzer
#include "Volume3.h"

//library untuk sensor
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

//library untuk LCD
#include <LiquidCrystal_I2C.h> //memasukan library LCD I2C

Adafruit_BMP280 bmp; // I2C
LiquidCrystal_I2C lcd(0x27 ,16,2);

//Variable test nada dari do re mi dst...
int nada[] = {
  0, 523, 587, 659, 698,  783, 880, 987, 1046, 1174,
  1318, 1396, 1567, 1769, 1975, 2093
};

//Variable pin
int buzzPin = 9; //dan ground
int amp = 12000;
int led = 2;//dan ground serta resistor 220 ohm
int sensitifitas = 5; //berarti rentang antara naik dan turun 5 dan -5

//keterangan
//vairabel data untuk BMP di (digital A4 untuk SDA dan A5 untuk SCL dan ground serta tegangan 3,3v)

void setup() {
//  settup led buzzer
  pinMode(led, OUTPUT);

//settup serial
  Serial.begin(9600); //serialnya sesuiakan dnegan baud di serial monitor
  Serial.println(F("BMP280 test"));

//settup LCD
  lcd.backlight();
  lcd.begin (); 

//cek apakah BMP terdeteksi
  if (!bmp.begin()) {
    Serial.println(F("tidak bisa menemukan perangkat BMP280, berarti installasi bermasalah"));
  while (1);
  }
}

void bunyi(int nadaKe, int lama)
{
  vol.tone(buzzPin, nada[nadaKe], amp);
  digitalWrite(2, LOW);
  delay(lama / 2);  
  digitalWrite(2, HIGH);
  delay(lama / 2);
}

void nadaDiam( int lama){
  vol.tone(buzzPin, nada[0], 3);
  delay(lama / 2);
}
void tesNada()
{
  for (int x = 0; x < 16; x++) {
    bunyi(x, 5000);
  }
}

void vario(int kondisi)
{
  if(kondisi >= sensitifitas){
      for (int x = 0; x < 2; x++) {
      bunyi(x, 1000);
    }
  }else if(kondisi < -sensitifitas){
    bunyi(15,1000);
  }else{
    vol.tone(buzzPin, nada[5], amp);
    }
   nadaDiam(100); 
}
void varioNada(int kondisi){  
      Serial.println(F("data Kondisi"));
      Serial.print(kondisi);
      Serial.println();
      vario(kondisi);
      delay(500);
}



//looping untuk BMp
void loop() {
  int Press = bmp.readPressure();
  int alti  = bmp.readAltitude();
  delay(500);
  int Press2 = bmp.readPressure();
  int alti2  = bmp.readAltitude();
  int kondisi = Press - Press2;

  varioNada(kondisi);
  lcd.clear();
  lcd.setCursor(0, 0); //baris pertama 
  lcd.print("ALT = ");  
  lcd.print(alti2); 
// Serial.print(bmp.readAltitude(1029)); // this should be adjusted to your local forcase

  lcd.setCursor(0, 1); //baris kedua    
  lcd.print(round(kondisi));  

  //untuk ketinggigian
  Serial.print(F("Ketinggian = "));

  Serial.print(alti); // untuk kalibrasi MDPL
  Serial.println();



//
//    //untuk temperatur
//  Serial.print(F("Temperature = "));
//  Serial.print(bmp.readTemperature());
//  Serial.println(" *C");
//  
//  //untuk tekanan
//  Serial.print(F("Pressure = "));
//  Serial.print(Press);
//  Serial.println(" Pa");

  


}
