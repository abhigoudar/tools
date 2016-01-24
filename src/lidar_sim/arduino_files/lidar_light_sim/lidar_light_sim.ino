int ranges[]={10,20,30,40,50};
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
 if(!sys_ok_flag){
  while (!Serial.available());
  start_check = String(Serial.read(), HEX);
  if(start_check == "9f")
   sys_ok_flag = true;
  else
   sys_ok_flag = false;
 }
 
 if(sys_ok_flag) {
  Serial.print(78, HEX);
  for(int i=0;i<5;i++)
   Serial.print(ranges[i]);
 }
  delay(100); 
  
}

