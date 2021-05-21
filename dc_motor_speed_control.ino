int en = 5; //needs to be in pwm~ for analogwrite
int in1 = 8;
int in2 = 7;
int dir; //"text receiver"
int s;
bool flag; //to avoid unnecessary loops for println

void setup()
{
  //set control pins to outputs
  pinMode(en, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  //initial conditions
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  s = -1;
  //for serial communication with the bluetooth module
  Serial.begin(9600); //38400 Default UART
  while (! Serial);
  Serial.println("Begin");
}

void loop()
{
  if (Serial.available() > 0) {
    dir = Serial.read();
    s = Serial.parseInt();
    flag = false; //reset the initial condition
    //Serial.println(dir);
    //Serial.println(s);
  }
  //if 'F' is received, the motor will move forward
  if (dir == 'F') {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    if (!flag) {
      Serial.println("Forward");
      flag = true;
    }
  } else if (dir == 'R') { //Reverse
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    if (!flag) {
      Serial.println("Reverse");
      flag = true;
    }
  } else if (dir == 'S') { //Stop
    digitalWrite(in1, HIGH);
    digitalWrite(in2, HIGH);
    analogWrite(en, 0);
    if (!flag) {
      Serial.println("Stop");
      //Serial.println("Setting speed to: 0");
      flag = true;
    }
  } else if (s > 0 && s <= 255 && !flag) {
    Serial.print("Setting speed to: ");
    Serial.println(s);
    analogWrite(en, s);
    flag = true;
  }

  delay(10);
}