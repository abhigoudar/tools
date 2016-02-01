#include <Servo.h>
#include <Wire.h>

#define LIDARLite_ADDRESS 0x62 // Default I2C Address of LIDAR-Lite.
#define RegisterMeasure 0x00 // Register to write to initiate ranging.
#define MeasureValue 0x04 // Value to initiate ranging.
#define RegisterHighLowB 0x8f // Register to get both High and Low bytes in 1 call.


Servo myservo;

int scan_data;
byte servo_pin=3;
int pos=0;
String start_check;
volatile double encoder_data = 0;
bool sys_ok_flag = false;
int reading;

void setup() {    
  Wire.begin(); 
  Serial.begin(9600);
  while(!Serial);
  myservo.attach(servo_pin);
  attachInterrupt(0, increment_encoder, CHANGE);
}
void loop() {
  if(!sys_ok_flag){
  start_check = String(Serial.read(), HEX);
  if(start_check == "9f"){
   sys_ok_flag = true;
  }
  else
   sys_ok_flag = false;
 }
  if(sys_ok_flag) { 
  pos = 0;
  myservo.write(pos);
  delay(10);
  Serial.print(78, HEX);
  for(pos = 1; pos <180; pos += 1)   
  {                                   
    myservo.write(pos); 
    Serial.print(',');
    Serial.print(float(get_range_data()*0.01));
  } 
  Serial.print(',');
  Serial.print(79,HEX);
  Serial.print('\n');
  delay(100);
  pos = 180;
  Serial.print(78, HEX);
  for(pos = 180; pos>=1; pos-=1)      
  {                                
    myservo.write(pos);               
    Serial.print(',');
    Serial.print(float(get_range_data()*0.01));
  } 
  Serial.print(',');
  Serial.print(79,HEX);  
  Serial.print('\n');
 }
 sys_ok_flag = false;
}
void increment_encoder(){
 encoder_data = (encoder_data + 1);
}

int get_range_data()
{
 Wire.beginTransmission((int)LIDARLite_ADDRESS); 
 Wire.write((int)RegisterMeasure); 
 Wire.write((int)MeasureValue); 
 Wire.endTransmission();
 delay(20); 

 Wire.beginTransmission((int)LIDARLite_ADDRESS); 
 Wire.write((int)RegisterHighLowB); 
 Wire.endTransmission(); 
 delay(20); 
 
 Wire.requestFrom((int)LIDARLite_ADDRESS, 2); 
 if(2 <= Wire.available()) 
   {
     reading = Wire.read(); 
     reading = reading << 8; 
     reading |= Wire.read(); 
   }
  return reading;
}
