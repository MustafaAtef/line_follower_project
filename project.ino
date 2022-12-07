int motor1_vcc=7;
int motor1_gnd=8;
int motir1_enable=6;
int motor2_vcc=9;
int motor2_gnd=10;
int motor2_enable=11;

int right_sensor = A0;
int left_sensor = A1;

const int motor_speed_1 = 150; // right
const int motor_speed_2 = 120; // left

const int intersections = 3;
int done = 0;


void setup() {
  pinMode(motor1_vcc,OUTPUT);
  pinMode(motor1_gnd,OUTPUT);
  pinMode(motir1_enable,OUTPUT);
  pinMode(motor2_gnd,OUTPUT);
  pinMode(motor2_vcc,OUTPUT);
  pinMode(motor2_enable,OUTPUT);
  pinMode(right_sensor, INPUT);
  pinMode(left_sensor, INPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int right_read = analogRead(right_sensor);
  int left_read = analogRead(left_sensor);

  // Serial.print(right_read);
  // Serial.print(" ");

  // Serial.println(left_read);
  if (done != 3) {
      if ((right_read > 100 && left_read > 100)) { // straight 
      move(motor_speed_1, motor_speed_2);
    } else if (right_read < 100 && left_read < 100) {
        done++;
        move(motor_speed_1, motor_speed_2);
      if (done == 3) {
        digitalWrite(motor1_vcc, LOW);
        digitalWrite(motor1_gnd, LOW);
        digitalWrite(motor2_vcc, LOW);
        digitalWrite(motor2_gnd, LOW);
        analogWrite(motir1_enable, 0);
        analogWrite(motor2_enable, 0);
      }
      delay(1000);
    }
    else if (right_read < 100 && left_read > 100) {
      move(-motor_speed_1, motor_speed_2);
    }
    else if (right_read > 100 && left_read < 100) {
      move(motor_speed_1, -motor_speed_2);
    }
    Serial.println(done);
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

  analogWrite(motir1_enable, motor_speed_1);
  analogWrite(motor2_enable, motor_speed_2);

}
