int led = 13;
int encoder_input_pin = 12;
byte encoder_data;
void setup() {                
  pinMode(led, OUTPUT);
  pinMode(encoder_input_pin, INPUT);
}

void loop() {
  encoder_data = digitalRead(encoder_input_pin);
  
  if(encoder_data)
   digitalWrite(led,HIGH);
  else
   digitalWrite(led, LOW);
  
}
