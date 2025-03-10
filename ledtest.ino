// LED Pin Definitions
const int LED1 = 22;  // First LED
const int LED2 = 23;  // Second LED
const int LED3 = 15;  // Third LED
const int LED4 = 17;  // Fourth LED

void setup() {
  // Configure LED pins as outputs
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  
  // Initialize all LEDs to OFF
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  
  Serial.begin(115200);
  Serial.println("LED Test Starting...");
}

void loop() {
  // Pattern 1: Sequential
  Serial.println("Pattern 1: Sequential");
  
  // LED 1
  digitalWrite(LED1, HIGH);
  delay(500);
  digitalWrite(LED1, LOW);
  
  // LED 2
  digitalWrite(LED2, HIGH);
  delay(500);
  digitalWrite(LED2, LOW);
  
  // LED 3
  digitalWrite(LED3, HIGH);
  delay(500);
  digitalWrite(LED3, LOW);
  
  // LED 4
  digitalWrite(LED4, HIGH);
  delay(500);
  digitalWrite(LED4, LOW);
  
  delay(1000);  // Pause between patterns
  
  // Pattern 2: All ON then OFF
  Serial.println("Pattern 2: All ON/OFF");
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED4, HIGH);
  delay(1000);
  
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  delay(1000);
}
