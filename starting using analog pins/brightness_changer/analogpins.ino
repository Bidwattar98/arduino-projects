
int redpin = A4; // how do we know the difference between digital and analog ? by putting capital 'A' 

void setup(){
  pinMode(redpin, OUTPUT);
}

void loop(){
  analogWrite(redpin, 244);
  delay(1000);
  analogWrite(redpin, 40);
  delay(1000);
  
}

