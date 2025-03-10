// Motor Driver Pin Definitions
const int MOTOR_IN1 = 18;  // Driver input 1
const int MOTOR_IN2 = 19;  // Driver input 2
const int MOTOR_IN3 = 20;  // Driver input 3
const int MOTOR_IN4 = 21;  // Driver input 4

void setup() {
  // Configure motor driver pins as outputs
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);
  pinMode(MOTOR_IN3, OUTPUT);
  pinMode(MOTOR_IN4, OUTPUT);
  
  // Initialize all pins to LOW
  digitalWrite(MOTOR_IN1, LOW);
  digitalWrite(MOTOR_IN2, LOW);
  digitalWrite(MOTOR_IN3, LOW);
  digitalWrite(MOTOR_IN4, LOW);
  
  // Start serial for debugging
  Serial.begin(115200);
  Serial.println("Motor Test Starting...");
}

void loop() {
  // Test Motor 1 Forward
  Serial.println("Motor 1 Forward");
  digitalWrite(MOTOR_IN1, HIGH);
  digitalWrite(MOTOR_IN2, LOW);
  delay(2000);
  
  // Stop Motor 1
  digitalWrite(MOTOR_IN1, LOW);
  digitalWrite(MOTOR_IN2, LOW);
  delay(1000);
  
  // Test Motor 2 Forward
  Serial.println("Motor 2 Forward");
  digitalWrite(MOTOR_IN3, HIGH);
  digitalWrite(MOTOR_IN4, LOW);
  delay(2000);
  
  // Stop Motor 2
  digitalWrite(MOTOR_IN3, LOW);
  digitalWrite(MOTOR_IN4, LOW);
  delay(1000);
  
  // Test Both Motors Forward
  Serial.println("Both Motors Forward");
  digitalWrite(MOTOR_IN1, HIGH);
  digitalWrite(MOTOR_IN2, LOW);
  digitalWrite(MOTOR_IN3, HIGH);
  digitalWrite(MOTOR_IN4, LOW);
  delay(2000);
  
  // Stop Both Motors
  digitalWrite(MOTOR_IN1, LOW);
  digitalWrite(MOTOR_IN2, LOW);
  digitalWrite(MOTOR_IN3, LOW);
  digitalWrite(MOTOR_IN4, LOW);
  delay(1000);
}