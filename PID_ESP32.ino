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
// PID PARAMETERS
// =============================

float Kp = 2.0;
float Ki = 0.05;
float Kd = 0.5;

float error = 0;
float prevError = 0;
float integral = 0;
float derivative = 0;

float setpoint = 0;   // target selisih kiri-kanan = 0

float baseSpeed = 150;

unsigned long lastTime = 0;
float dt = 0.01;

// =============================
// ULTRASONIC FUNCTION
// =============================

long readUltrasonic(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000); // timeout 30ms
  long distance = duration * 0.034 / 2;
  return distance;
}

// =============================
// MOTOR CONTROL
// =============================

void setMotor(int leftSpeed, int rightSpeed) {

  leftSpeed = constrain(leftSpeed, 0, 255);
  rightSpeed = constrain(rightSpeed, 0, 255);

  // Motor Left forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  ledcWrite(0, leftSpeed);

  // Motor Right forward
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  ledcWrite(1, rightSpeed);
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

  ledcSetup(0, 5000, 8);  // channel 0
  ledcAttachPin(ENA, 0);

  ledcSetup(1, 5000, 8);  // channel 1
  ledcAttachPin(ENB, 1);

  lastTime = millis();
}

// =============================
// LOOP
// =============================

void loop() {

  unsigned long currentTime = millis();
  dt = (currentTime - lastTime) / 1000.0;
  lastTime = currentTime;

  long leftDist = readUltrasonic(TRIG_L, ECHO_L);
  long rightDist = readUltrasonic(TRIG_R, ECHO_R);

  // =============================
  // ERROR CALCULATION
  // =============================

  error = (leftDist - rightDist) - setpoint;

  // Integral accumulation
  integral += error * dt;

  // Anti-windup clamp
  integral = constrain(integral, -100, 100);

  // Derivative
  derivative = (error - prevError) / dt;

  // PID output
  float control = Kp * error + Ki * integral + Kd * derivative;

  // =============================
  // MOTOR ADJUSTMENT
  // =============================

  int leftMotor = baseSpeed - control;
  int rightMotor = baseSpeed + control;

  setMotor(leftMotor, rightMotor);

  prevError = error;

  // =============================
  // DEBUG SERIAL
  // =============================

  Serial.print("L: ");
  Serial.print(leftDist);
  Serial.print(" R: ");
  Serial.print(rightDist);
  Serial.print(" Error: ");
  Serial.print(error);
  Serial.print(" Control: ");
  Serial.println(control);

  delay(10);
}
