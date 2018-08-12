#include "ultrasonic_sensor.h"

//Variables
int ENA = 8;
int ENB = 9;
int motor_1A = 7;
int motor_1B = 6;
int motor_2A = 5;
int motor_2B = 4;

int prevDistance = -1;

unsigned long previousMillis = 0;

const long interval = 1000; 

const double LIMIT = 0.55;

int directionCar = -1;
int prevDirectionCar = -1;

void motor1(boolean reverse)
{
  if (reverse)
  {
    digitalWrite(motor_1A, HIGH);
    digitalWrite(motor_1B, LOW);

    digitalWrite(ENA, HIGH);
  }
  else 
  {
    digitalWrite(motor_1A, LOW);
    digitalWrite(motor_1B, HIGH);

    digitalWrite(ENA, HIGH);
  }
}

void motor2(boolean reverse)
{
  if (reverse)
  {
    digitalWrite(motor_2A, HIGH);
    digitalWrite(motor_2B, LOW);

    digitalWrite(ENB, HIGH);
  }
  else 
  {
    digitalWrite(motor_2A, LOW);
    digitalWrite(motor_2B, HIGH);

    digitalWrite(ENB, HIGH);
  }
}

int getRandomDirection()
{
  int randomDir = random(0, 1);
  return randomDir;
}

void motor(int dir)
{
  //RIGHT
  if (dir == 0)
  {
    motor1(false);
  }
  //LEFT
   else if (dir == 1)
  {
    motor2(false);
  }
  //REVERSE
   else if (dir == 2)
  {
    motor1(true);
    motor2(true);
  }

  prevDirectionCar = directionCar;
  directionCar = dir;
}

void brake() {
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
}

void setup() {
  Serial.begin(9600);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(motor_1A, OUTPUT);
  pinMode(motor_1B, OUTPUT);

  pinMode(motor_2A, OUTPUT);
  pinMode(motor_2B, OUTPUT);

  setup_sensor();
}

void loop() {
  double distance = getMetersDistance();
  int roundedDistance = distance;
  unsigned long currentMillis = millis();

  if (roundedDistance == prevDistance && (currentMillis - previousMillis) >= interval)
  {
    previousMillis = currentMillis;
    
    motor1(true); 
    motor2(true); 

    int dir = getRandomDirection();

    brake();

    motor(dir);

    Serial.println("Reveresed and changed direction.");
  }

  if (distance < LIMIT)
  {
    int dir = getRandomDirection();

    brake();

    motor(dir);

    Serial.println("Changed Direction");

  }
  else {
    motor1(false);
    motor2(false);

    Serial.println("FORWARD");
  }

  prevDistance = distance;
}

