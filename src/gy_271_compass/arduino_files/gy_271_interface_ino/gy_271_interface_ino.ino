#include <Wire.h>

#define gy_271 0x1E
#define mode_reg 0x02
#define cont_mode 0x00
#define data_reg 0x03

int x,y,z;

void setup()
{
  Serial.begin(9600);
  while(!Serial);
  Wire.begin();
  Wire.beginTransmission(gy_271);
  Wire.write(mode_reg);
  Wire.write(cont_mode);
  Wire.endTransmission();
}

void loop()
{
  Wire.beginTransmission(gy_271);
  Wire.write(data_reg);
  Wire.endTransmission();
  
  Wire.requestFrom(gy_271, 6);
  
  if(Wire.available() >= 6){
    x = Wire.read() << 8;
    x |= Wire.read();
    y = Wire.read() << 8;
    y |= Wire.read();
    z = Wire.read() << 8;
    z |= Wire.read();
  }
  
  Serial.print(x);
  Serial.print(',');
  Serial.print(y);
  Serial.print(',');
  Serial.println(z);
  
  delay(500);
  
}
    

