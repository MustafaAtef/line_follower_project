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

const int motor_speed_1 = 255; // right
const int motor_speed_2 = 235; // left

// Number of intersections to stop at the last one
const int intersections = 3;
int done = 0;
// timer for increase done variable 
int time  = 0;
int duration = 0;


void setup() {
  pinMode(motor1_vcc,OUTPUT);
  pinMode(motor1_gnd,OUTPUT);
  pinMode(motor1_enable,OUTPUT);
  pinMode(motor2_gnd,OUTPUT);
  pinMode(motor2_vcc,OUTPUT);
  pinMode(motor2_enable,OUTPUT);
  pinMode(right_sensor, INPUT);
  pinMode(left_sensor, INPUT);
  time = millis();
}

void loop() {

  int right_read = analogRead(right_sensor);
  int left_read = analogRead(left_sensor);

  if (done != intersections) {
      if ((right_read > 100 && left_read > 100)) { // straight 
      move(motor_speed_1, motor_speed_2);
    } else if (right_read < 100 && left_read < 100) {
        duration = millis() - time;
      if (duration >= 1000) {
        done++;
        time = millis();
      }
      if (done == intersections) {
        digitalWrite(motor1_vcc, LOW);
        digitalWrite(motor1_gnd, LOW);
        digitalWrite(motor2_vcc, LOW);
        digitalWrite(motor2_gnd, LOW);
        analogWrite(motor1_enable, 0);
        analogWrite(motor2_enable, 0);
      } else move(motor_speed_1, motor_speed_2);
    }
    else if (right_read < 100 && left_read > 100) { // right
      move(-motor_speed_1, motor_speed_2);
    }
    else if (right_read > 100 && left_read < 100) { // left
      move(motor_speed_1, -motor_speed_2);
    }
  }

}

void move(int motor1, int motor2) { 
  if (motor1 > 0) {
    digitalWrite(motor1_vcc, HIGH);
    digitalWrite(motor1_gnd, LOW);
  } else {
    digitalWrite(motor1_vcc, LOW);
    digitalWrite(motor1_gnd, HIGH);
  }
  if (motor2 > 0) {
    digitalWrite(motor2_vcc, HIGH);
    digitalWrite(motor2_gnd, LOW);
  } else {
    digitalWrite(motor2_vcc, LOW);
    digitalWrite(motor2_gnd, HIGH);
  }

  if (motor1 > 0 && motor2 > 0) {
    analogWrite(motor1_enable, motor_speed_1);
     analogWrite(motor2_enable, motor_speed_2);
  } else {
    analogWrite(motor1_enable, 150);
    analogWrite(motor2_enable, 120);
  }
}
