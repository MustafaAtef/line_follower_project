#include <LiquidCrystal.h>
int rs= 12 , en=13, d0=5,d1=4,d2=3,d3=2;
LiquidCrystal  lcd (rs,en,d0,d1,d2,d3);

//Setting up motor pins 
// 1 -> rihgt motor
// 2 -> left motor
int motor1_vcc=7;
int motor1_gnd=8;
int motor1_enable=6;
int motor2_vcc=9;
int motor2_gnd=10;
int motor2_enable=11;

// Setting up IR sensors pins
int right_sensor = A0;
int left_sensor = A1;
int middle_sensor = A2;

const int motor_speed_1 = 150; // right
const int motor_speed_2 = 120; // left

// timer for all white to stop the robot
int time  = 0;
int duration = 0;
int timer_begin = 0;
int stopped = 0;

void setup() {
  //Serial.begin(9600);
  lcd.begin(16,2);
  lcd.setCursor(2,0);
  lcd.print("SATURN TEAM");
  pinMode(motor1_vcc,OUTPUT);
  pinMode(motor1_gnd,OUTPUT);
  pinMode(motor1_enable,OUTPUT);
  pinMode(motor2_gnd,OUTPUT);
  pinMode(motor2_vcc,OUTPUT);
  pinMode(motor2_enable,OUTPUT);
  pinMode(right_sensor, INPUT);
  pinMode(middle_sensor, INPUT);
  pinMode(left_sensor, INPUT);
}

void loop() {

  if (!stopped) {
    int right_read = digitalRead(right_sensor);
    int left_read = digitalRead(left_sensor);
    int middle_read = digitalRead(middle_sensor);
    // Serial.print(right_read);
    // Serial.print(" ");
    // Serial.print(middle_read);
    // Serial.print(" ");
    //   Serial.print(left_read);
    // Serial.println(" ");

    // Robot will go forward if both left and right sensors on white and middle on black or all the sensors on black (intersections)
    if ((right_read == 0 && middle_read == 1 && left_read == 0) || (right_read  == 1 && middle_read == 1 && left_read == 1))
    {
      //Serial.println("straight");
        timer_begin = 0;
      move_forward();
    } else if (right_read == 1 && middle_read == 0 && left_read == 0) // right
    {
      //Serial.println("right");
      move_right();
    } else if (right_read == 0 && middle_read == 0 && left_read == 1) // left
    {
      //Serial.println("left");
      move_left();
    } else if (right_read == 0 && middle_read == 0 && left_read == 0) // straight. if this conditoin last for more than 1 second stop the robot
    {
      if (timer_begin == 0) {
        time = millis();
        timer_begin = 1;
      }
      duration = millis() - time;
      if (duration >= 750) {
        //Serial.println("stopped");
        stop();
        stopped = 1;
        time = millis();
      }
      else {
        //Serial.println("straight on white");
        move_forward();
      }
    }
    else if (right_read == 1 && middle_read == 1 && left_read  == 0) // half circle right turn
    {
      //Serial.println("turn right");
      turn_right();
    } else if (right_read == 0 && middle_read == 1 && left_read == 1) // half circle left turn
    {
      //Serial.println("turn left");
      turn_left();
    }

  }
}


void move_forward() {
  digitalWrite(motor1_vcc, HIGH);
  digitalWrite(motor1_gnd, LOW);
  digitalWrite(motor2_vcc, HIGH);
  digitalWrite(motor2_gnd, LOW);   
  analogWrite(motor1_enable, motor_speed_1);
  analogWrite(motor2_enable, motor_speed_2); 
  delay(100);
}

void move_right() {
  timer_begin = 0;
  digitalWrite(motor1_vcc, LOW);
  digitalWrite(motor1_gnd, LOW);
  digitalWrite(motor2_vcc, HIGH);
  digitalWrite(motor2_gnd, LOW);
  analogWrite(motor2_enable, motor_speed_2);
  delay(80);
}

void move_left() {
  timer_begin = 0;
  digitalWrite(motor1_vcc, HIGH);
  digitalWrite(motor1_gnd, LOW);
  digitalWrite(motor2_vcc, LOW);
  digitalWrite(motor2_gnd, LOW);
  analogWrite(motor1_enable, motor_speed_1);
  delay(80);
}

void turn_right() {
  timer_begin = 0;
  digitalWrite(motor1_vcc, LOW);
  digitalWrite(motor1_gnd, HIGH);
  digitalWrite(motor2_vcc, HIGH);
  digitalWrite(motor2_gnd, LOW);
  analogWrite(motor1_enable, 100);
  analogWrite(motor2_enable, motor_speed_2);
  delay(400);
}

void turn_left() {
  timer_begin = 0;
  digitalWrite(motor1_vcc, HIGH);
  digitalWrite(motor1_gnd, LOW);
  digitalWrite(motor2_vcc, LOW);
  digitalWrite(motor2_gnd, HIGH);
  analogWrite(motor1_enable, motor_speed_1);
  analogWrite(motor2_enable, 100);
  delay(400);
}

void stop() {
  digitalWrite(motor1_vcc, LOW);
  digitalWrite(motor1_gnd, LOW);
  digitalWrite(motor2_vcc, LOW);
  digitalWrite(motor2_gnd, LOW);
}
