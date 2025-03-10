// Pin Definitions
const int potPin = 6;         // Potentiometer for speed control
const int TOUCH_SENSOR_1 = 0; // Touch sensor for motor 1
const int TOUCH_SENSOR_2 = 1; // Touch sensor for motor 2
const int BUZZER_PIN = 16;    // Buzzer pin

// Motor Driver Pins
const int MOTOR_IN1 = 18;  // Motor 1 PWM
const int MOTOR_IN2 = 19;  // Motor 1 direction
const int MOTOR_IN3 = 20;  // Motor 2 PWM
const int MOTOR_IN4 = 21;  // Motor 2 direction

// LED Pins for speed indication
const int ledPins[] = {22, 23, 15, 17}; // LED pins

// Beep parameters
const int BEEP_DURATION = 100;  // Duration of each beep in milliseconds
const int BEEP_PAUSE = 100;     // Pause between beeps in milliseconds
const int NUM_BEEPS = 3;        // Number of beeps

// State tracking
bool motor1_running = false;
bool motor2_running = false;

void playBeepSequence() {
    for (int i = 0; i < NUM_BEEPS; i++) {
        digitalWrite(BUZZER_PIN, HIGH);
        delay(BEEP_DURATION);
        digitalWrite(BUZZER_PIN, LOW);
        if (i < NUM_BEEPS - 1) {  // Don't delay after last beep
            delay(BEEP_PAUSE);
        }
    }
}

void playCountdown() {
    int countdownTones[] = {200, 300, 400, 600}; // Frequencies for 3-2-1-GO
    const char* countdownText[] = {"3", "2", "1", "GO!"};

    for (int i = 0; i < 4; i++) {
        tone(BUZZER_PIN, countdownTones[i], 500); // Play countdown sound
        Serial.println(countdownText[i]); // Print countdown in Serial Monitor
        delay(800); // Pause between numbers
    }
    noTone(BUZZER_PIN); // Stop buzzer sound
}

void setup() {
    // Set up motor pins
    pinMode(MOTOR_IN1, OUTPUT);
    pinMode(MOTOR_IN2, OUTPUT);
    pinMode(MOTOR_IN3, OUTPUT);
    pinMode(MOTOR_IN4, OUTPUT);
    
    // Set up touch sensor pins
    pinMode(TOUCH_SENSOR_1, INPUT);
    pinMode(TOUCH_SENSOR_2, INPUT);
    
    // Set up buzzer pin
    pinMode(BUZZER_PIN, OUTPUT);
    digitalWrite(BUZZER_PIN, LOW);
    
    // Set up LED pins
    for (int i = 0; i < 4; i++) {
        pinMode(ledPins[i], OUTPUT);
        digitalWrite(ledPins[i], LOW);
    }
    
    // Initialize motors to stopped
    digitalWrite(MOTOR_IN2, LOW);  // Set direction
    digitalWrite(MOTOR_IN4, LOW);  // Set direction
    analogWrite(MOTOR_IN1, 0);     // Stop motor 1
    analogWrite(MOTOR_IN3, 0);     // Stop motor 2
    
    // Set ADC resolution for potentiometer
    analogReadResolution(12);
    
    Serial.begin(115200);
    Serial.println("Touch Control Motors with Countdown Starting...");
}

void loop() {
    // Read speed setting from potentiometer
    int potValue = analogRead(potPin);
    
    // Calculate speed based on potentiometer with adjusted ranges
    int speedValue;
    int activeLed;
    
    if (potValue < 875) {
        speedValue = 128;     // 50% speed (minimum speed)
        activeLed = 0;
    } else if (potValue < 1650) {
        speedValue = 170;     // ~67% speed
        activeLed = 1;
    } else if (potValue < 2425) {
        speedValue = 213;     // ~83% speed
        activeLed = 2;
    } else {
        speedValue = 255;     // 100% speed
        activeLed = 3;
    }
    
    // Update speed indicator LEDs
    for (int i = 0; i < 4; i++) {
        digitalWrite(ledPins[i], (i == activeLed) ? HIGH : LOW);
    }
    
    // Read touch sensors
    bool motor1_touch = digitalRead(TOUCH_SENSOR_1);  // Touch = HIGH
    bool motor2_touch = digitalRead(TOUCH_SENSOR_2);  // Touch = HIGH
    
    // Control Motor 1 with countdown and beeps
    if (motor1_touch && !motor1_running) {  // Touch detected and motor not already running
        playCountdown();                     // Play Mario Kart-style 3-2-1 countdown
        playBeepSequence();                 // Play beeps before starting
        analogWrite(MOTOR_IN1, speedValue); // Start motor
        motor1_running = true;
    } else if (!motor1_touch && motor1_running) {  // Touch released and motor running
        analogWrite(MOTOR_IN1, 0);         // Stop motor
        motor1_running = false;
    } else if (motor1_running) {           // Motor already running, just update speed
        analogWrite(MOTOR_IN1, speedValue);
    }
    
    // Control Motor 2 with countdown and beeps
    if (motor2_touch && !motor2_running) {  // Touch detected and motor not already running
        playCountdown();                     // Play Mario Kart-style 3-2-1 countdown
        playBeepSequence();                 // Play beeps before starting
        analogWrite(MOTOR_IN3, speedValue); // Start motor
        motor2_running = true;
    } else if (!motor2_touch && motor2_running) {  // Touch released and motor running
        analogWrite(MOTOR_IN3, 0);         // Stop motor
        motor2_running = false;
    } else if (motor2_running) {           // Motor already running, just update speed
        analogWrite(MOTOR_IN3, speedValue);
    }
    
    // Debug output
    Serial.print("Speed: "); Serial.print(speedValue);
    Serial.print(" Motor1: "); Serial.print(motor1_running ? "ON" : "OFF");
    Serial.print(" Motor2: "); Serial.println(motor2_running ? "ON" : "OFF");
    
    delay(100);  // Small delay to prevent serial flooding
}

