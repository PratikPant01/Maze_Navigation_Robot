// code for maze navigating robot

// pins in arduino for the IR sensors
const int irpin1 = 8;  // Forward IR sensor
const int irpin2 = 12; // Left IR sensor
const int irpin3 = 13; // Right IR sensor

// pins in arduino for the motor control
const int mtr_R1 = 2;
const int mtr_R2 = 3;
const int mtr_L1 = 4;
const int mtr_L2 = 5;

// pins in arduino for enablers of motor driver l239d
const int enA = 10; // PWM pin for right motor
const int enB = 9;  // PWM pin for left motor

// initial value of the ir reading set as high
int irRead1 = HIGH;
int irRead2 = HIGH;
int irRead3 = HIGH;

void setup() 
{
  // initial setup of ir, motor and enablers
  pinMode(irpin1, INPUT);
  pinMode(irpin2, INPUT);
  pinMode(irpin3, INPUT);
  pinMode(mtr_R1, OUTPUT);
  pinMode(mtr_R2, OUTPUT);
  pinMode(mtr_L1, OUTPUT);
  pinMode(mtr_L2, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  // serial baud value 9600
  Serial.begin(9600);
}

// Motor control functions

// turn right
void right() 
{
  digitalWrite(mtr_L1, LOW);
  digitalWrite(mtr_L2, HIGH);
  digitalWrite(mtr_R1, LOW);
  digitalWrite(mtr_R2, LOW);
  analogWrite(enA, 100); // Set speed for right motor
  analogWrite(enB, 0);   // Stop left motor
}

// turn left
void left() 
{
  digitalWrite(mtr_R1, HIGH);
  digitalWrite(mtr_R2, LOW);
  digitalWrite(mtr_L1, LOW);
  digitalWrite(mtr_L2, LOW);
  analogWrite(enA, 0);   // Stop right motor
  analogWrite(enB, 120); // Set speed for left motor
}

// move forward
void forward() 
{
  digitalWrite(mtr_R1, HIGH);
  digitalWrite(mtr_R2, LOW);
  digitalWrite(mtr_L1, LOW);
  digitalWrite(mtr_L2, HIGH);
  analogWrite(enA, 150); // Set speed for right motor
  analogWrite(enB, 150); // Set speed for left motor
}

// pause
void halt() 
{
  digitalWrite(mtr_R1, LOW);
  digitalWrite(mtr_R2, LOW);
  digitalWrite(mtr_L1, LOW);
  digitalWrite(mtr_L2, LOW);
  analogWrite(enA, 0); // Stop right motor
  analogWrite(enB, 0); // Stop left motor
}

// continuous loop of functions
void loop() 
{
  // reading real time values from the ir sensors and storing in respective variables
  irRead1 = digitalRead(irpin1); // Forward IR sensor
  irRead2 = digitalRead(irpin2); // Left IR sensor
  irRead3 = digitalRead(irpin3); // Right IR sensor
  
  // Navigation logic based on IR sensor readings

  // when no obstacle is detected in front
  if (irRead1 == HIGH) 
  {
    forward(); // Move forward if the forward IR sensor detects no obstacle
  } 

  // when there is obstacle in the front but no obstacle in the left
  else if (irRead2 == HIGH && irRead1== LOW) 
  {
    halt();
    delay(500);
    left(); // Turn left if the right IR sensor detects an obstacle
    delay(500); // Continue turning left for 0.5 second
  }

  // when there is obstacle in the front but no obstacle in the right
  else if (irRead3 == HIGH && irRead1== LOW) 
  {
    halt();
    delay(500);
    right(); // Turn right if the left IR sensor detects an obstacle
    delay(500); // Continue turning right for 0.5 second
  }

  // when all ir sensors detect obstacle in the front, right and left then stop
  else 
  {
    while(digitalRead(irpin1) == LOW && digitalRead(irpin2) == LOW && digitalRead(irpin3)== LOW)
    {halt(); 
    }
    delay(1000);// Stop the car if all sensors detect obstacles on all the sides
  }
}
