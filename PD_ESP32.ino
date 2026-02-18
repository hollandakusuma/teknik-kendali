// =============================
// PIN CONFIGURATION
// =============================

// Ultrasonic Left
#define TRIG_L 5
#define ECHO_L 18

// Ultrasonic Right
#define TRIG_R 17
#define ECHO_R 16

// Motor Left
#define ENA 25
#define IN1 26
#define IN2 27

// Motor Right
#define ENB 14
#define IN3 12
#define IN4 13

// =============================
// CONTROL PARAMETERS
// =============================

float Kp = 2.0;
float Kd = 0.5;

float error = 0;
float previous_error = 0;
float derivative = 0;
float control = 0;

int baseSpeed = 150;

unsigned long previousTime = 0;

// =============================
// FUNCTION: READ ULTRASONIC
// =============================

float readUltrasonic(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2.0; // cm

  return distance;
}

// =============================
// FUNCTION: SET MOTOR SPEED
// =============================

void setMotor(int leftSpeed, int rightSpeed) {
  leftSpeed = constrain(leftSpeed, 0, 255);
  rightSpeed = constrain(rightSpeed, 0, 255);

  // Left Motor Forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, leftSpeed);

  // Right Motor Forward
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, rightSpeed);
}

// =============================
// SETUP
// =============================

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_L, OUTPUT);
  pinMode(ECHO_L, INPUT);
  pinMode(TRIG_R, OUTPUT);
  pinMode(ECHO_R, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  previousTime = millis();
}

// =============================
// LOOP
// =============================

void loop() {

  float distanceLeft = readUltrasonic(TRIG_L, ECHO_L);
  float distanceRight = readUltrasonic(TRIG_R, ECHO_R);

  error = distanceRight - distanceLeft;

  unsigned long currentTime = millis();
  float dt = (currentTime - previousTime) / 1000.0;
  previousTime = currentTime;

  derivative = (error - previous_error) / dt;

  control = Kp * error + Kd * derivative;

  int leftMotorSpeed = baseSpeed + control;
  int rightMotorSpeed = baseSpeed - control;

  setMotor(leftMotorSpeed, rightMotorSpeed);

  previous_error = error;

  // Debugging
  Serial.print("Left: ");
  Serial.print(distanceLeft);
  Serial.print(" | Right: ");
  Serial.print(distanceRight);
  Serial.print(" | Error: ");
  Serial.print(error);
  Serial.print(" | Control: ");
  Serial.println(control);

  delay(50);
}
