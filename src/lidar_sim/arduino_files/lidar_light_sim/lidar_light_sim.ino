int ranges[]={10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10};
#define size_of_int  2 // 2 bytes
String start_check;
boolean sys_ok_flag = false;
void setup()
{
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  while(!Serial);
  if(!Serial)
    exit(0);
}

void loop()
{
 digitalWrite(13,HIGH);
 if(!sys_ok_flag){
  start_check = String(Serial.read(), HEX);
  if(start_check == "9f"){
   sys_ok_flag = true;
   digitalWrite(13,LOW);
  }
  else
   sys_ok_flag = false;
 }
 if(sys_ok_flag) { 
  Serial.print(78,HEX); 
   for(int i=0;i<sizeof(ranges)/size_of_int;i++){
   Serial.print(',');
   Serial.print(ranges[i]);
  }
  Serial.print(',');
  Serial.print(79,HEX);
  Serial.print('\n');
 }
  delay(100); 
}

