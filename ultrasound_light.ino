// библиотека для работы I²C
#include <Wire.h>
// библиотеку для модуля VL6180X
#include <SparkFun_VL6180X.h>
// адрес датчика приближения по умолчанию
#define VL6180X_ADDRESS 0x29
// создаём объект для работы с модулем
VL6180x sensor(VL6180X_ADDRESS);
 
void setup_lx()
{
  while (sensor.VL6180xInit()) {
    Serial.println("Failed to initalize");
    delay(1000);
  }
  sensor.VL6180xDefautSettings();
}
 
int ul_2()
{
  Serial.print("Light = ");
  Serial.print(sensor.getAmbientLight(GAIN_1));
  Serial.print(" Lx\t\t");
  return sensor.getAmbientLight(GAIN_1);
}
