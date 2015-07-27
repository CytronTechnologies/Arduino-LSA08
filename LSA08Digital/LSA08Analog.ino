const byte analogPin = 0;   // Connect AN output of LSA08 to analog pin 0
const byte junctionPulse = 4;   // Connect JPULSE of LSA08 to pin 4
const byte dir1 = 13;   // Connect DIR1 of motor driver to pin 13
const byte dir2 = 12;   // Connect DIR2 of motor driver to pin 12
const byte pwm1 = 11;   // Connect PWM1 of motor driver to pin 11
const byte pwm2 = 10;   // Connect PWM2 of motor driver to pin 10
int readVal,positionVal;    // Variables to store analog and line position value
unsigned int junctionCount = 0;   // Variable to store junction count value

void setup() {
  pinMode(junctionPulse,INPUT);

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
  if(digitalRead(junctionPulse)) {
    while(digitalRead(junctionPulse)) {
      moveForward();
    }
    // Increment junction count by 1 after the junction
    // You can do whatever you want with the junction count
    junctionCount++;
  }

  readVal = analogRead(analogPin);    // Read value from analog pin

  // Convert voltage level into line position value
  positionVal = ((float)readVal/921)*70;

  // Line at left when 0 - 18, move left
  if(positionVal <= 18)
  moveLeft();

  // Line at middle when 19 - 52, move forward
  else if(positionVal <= 52)
  moveForward();

  // Line at right when 53 - 70, move right
  else if(positionVal <= 70)
  moveRight();

  // If no line is detected, stay at the position
  else
  wait();

  // Put some delay to avoid the robot jig while making a turn

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

