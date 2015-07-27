const byte dir1 = 13;   // Connect DIR1 of motor driver to pin 13
const byte dir2 = 12;   // Connect DIR2 of motor driver to pin 12
const byte pwm1 = 11;   // Connect PWM1 of motor driver to pin 11
const byte pwm2 = 10;   // Connect PWM2 of motor driver to pin 10

void setup() {
  // Setting pin 0 - 7 as digital input pin
  for(byte i=0;i<=7;i++) {
    pinMode(i,INPUT);
  }
  
  // Setting pin 10 - 13 as digital output pin
  for(byte i=10;i<=13;i++) {
    pinMode(i,OUTPUT);
  }
  
  // Setting the initial condition of motors
  // make sure both PWM pins are LOW
  digitalWrite(pwm1,LOW);
  digitalWrite(pwm2,LOW);
  
  // State of DIR pins are depending on your physical connection
  // if your robot behaves strangely, try changing thses two values
  digitalWrite(dir1,LOW);
  digitalWrite(dir2,LOW);

}

void loop() {
  // Checking for junction crossing, if juction detected, 
  // keep moving forward
  if(digitalRead(2) && digitalRead(5))
  moveForward();
  
  // Checking for sensor number 1 and 2, if line detected, move left
  else if(digitalRead(1) || digitalRead(2))
  moveLeft();

  // Checking for sensor number 5 and 6, if line detected, move right
  else if(digitalRead(5) || digitalRead(6))
  moveRight();

  // Checking for sensors number 3 and 4, 
  // if line is detected by either of these sensor, move forward
  else if(digitalRead(3) || digitalRead(4))
  moveForward();

  // If no line is detected, stay at the position
  else
  wait();

  // Put some delay to avoid the robot jig while making a turn
  delay(100);

}


// The values work good in my case, you could use other values set
// to archieve a performance that satisfy you
void moveLeft() {
  // For robot to move left, right motor has to be faster than left motor
  analogWrite(pwm1,90);
  analogWrite(pwm2,10);
}

void moveRight() {
  // For robot to move right, left motor has to be faster than right motor
  analogWrite(pwm1,10);
  analogWrite(pwm2,90);
}

void moveForward() {
  // For robot to move forward, both motors have to be same speed
  analogWrite(pwm1,70);
  analogWrite(pwm2,70);
}

void wait() {
  // Function to makes the robot stay
  analogWrite(pwm1,0);
  analogWrite(pwm2,0);
}

