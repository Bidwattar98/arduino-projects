void setup(){
  pinMode(7, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(9, OUTPUT);
}

int greenport = 7;
int yelloport = 4;
int redport = 9;

void loop(){
  digitalWrite(greenport, HIGH);
  delay(5000);
  digitalWrite(greenport, LOW);

  digitalWrite(yelloport,HIGH);
  delay(1000);
  digitalWrite(yelloport, LOW);

  digitalWrite(redport,HIGH);
  delay(5000);
  digitalWrite(redport, LOW);

  digitalWrite(yelloport,HIGH);
  delay(1000);
  digitalWrite(yelloport, LOW);

}














