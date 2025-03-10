// Pin Definitions
const int potPin = 6;         // Potentiometer for speed control
const int TOUCH_SENSOR_1 = 0; // Touch sensor for motor 1
const int TOUCH_SENSOR_2 = 1; // Touch sensor for motor 2

// Motor Driver Pins
const int MOTOR_IN1 = 18;  // Motor 1 PWM
const int MOTOR_IN2 = 19;  // Motor 1 direction
const int MOTOR_IN3 = 20;  // Motor 2 PWM
const int MOTOR_IN4 = 21;  // Motor 2 direction

// LED Pins for speed indication
const int ledPins[] = {22, 23, 15, 17}; // LED pins

// Audio pin for beeper
const int AUDIO_PIN = 2;  // Audio amplifier pin (changed from pin 16)

// Motor state tracking
bool motorsRunning = false;
bool previousTouchState = false;
unsigned long beepStartTime = 0;
int beepCount = 0;
bool beepSequenceActive = false;

void setup() {
    // Set up motor pins
    pinMode(MOTOR_IN1, OUTPUT);
    pinMode(MOTOR_IN2, OUTPUT);
    pinMode(MOTOR_IN3, OUTPUT);
    pinMode(MOTOR_IN4, OUTPUT);
    
    // Set up touch sensor pins
    pinMode(TOUCH_SENSOR_1, INPUT);
    pinMode(TOUCH_SENSOR_2, INPUT);
    
    // Set up audio pin
    pinMode(AUDIO_PIN, OUTPUT);
    digitalWrite(AUDIO_PIN, LOW); // Ensure audio is off at startup
    
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
    Serial.println("Touch Control Motors with Speed Dial Starting...");
    Serial.println("Both touch sensors must be pressed simultaneously to operate motors.");
}

void loop() {
    // Read speed setting from potentiometer
    int potValue = analogRead(potPin);
    
    // Calculate speed based on potentiometer
    int speedValue;
    int activeLed;
    
    if (potValue < 875) {
        speedValue = 64;      // 25% speed
        activeLed = 0;
    } else if (potValue < 1650) {
        speedValue = 128;     // 50% speed
        activeLed = 1;
    } else if (potValue < 2425) {
        speedValue = 192;     // 75% speed
        activeLed = 2;
    } else {
        speedValue = 255;     // 100% speed
        activeLed = 3;
    }
    
    // Update speed indicator LEDs
    for (int i = 0; i < 4; i++) {
        digitalWrite(ledPins[i], (i == activeLed) ? HIGH : LOW);
    }
    
    // Read touch sensors - both must be pressed
    bool touch1 = digitalRead(TOUCH_SENSOR_1) == HIGH;
    bool touch2 = digitalRead(TOUCH_SENSOR_2) == HIGH;
    bool bothTouched = touch1 && touch2;
    
    // Check for state change - both sensors just pressed
    if (bothTouched && !previousTouchState && !motorsRunning && !beepSequenceActive) {
        // Start beep sequence
        beepSequenceActive = true;
        beepCount = 0;
        beepStartTime = millis();
        Serial.println("Starting beep sequence - both touch sensors pressed");
    }
    
    // Handle beep sequence
    if (beepSequenceActive) {
        handleBeepSequence(speedValue);
    }
    
    // If motors are running but touch sensors released, stop motors
    if (motorsRunning && !bothTouched) {
        stopMotors();
        motorsRunning = false;
        Serial.println("Motors stopped - touch sensors released");
    }
    
    // Update previous touch state
    previousTouchState = bothTouched;
    
    // Debug output
    Serial.print("Speed: "); Serial.print(speedValue);
    Serial.print(" Touch1: "); Serial.print(touch1 ? "ON" : "OFF");
    Serial.print(" Touch2: "); Serial.print(touch2 ? "ON" : "OFF");
    Serial.print(" Motors: "); Serial.println(motorsRunning ? "ON" : "OFF");
    
    delay(50);  // Small delay to prevent serial flooding
}

void handleBeepSequence(int speedValue) {
    unsigned long currentTime = millis();
    unsigned long elapsedTime = currentTime - beepStartTime;
    
    // Check if both touch sensors are still pressed
    bool touch1 = digitalRead(TOUCH_SENSOR_1) == HIGH;
    bool touch2 = digitalRead(TOUCH_SENSOR_2) == HIGH;
    bool bothTouched = touch1 && touch2;
    
    if (!bothTouched) {
        // If sensors released, abort sequence and turn off audio
        digitalWrite(AUDIO_PIN, LOW);
        beepSequenceActive = false;
        Serial.println("Touch sensors released - beep sequence aborted");
        return;
    }
    
    // Each beep cycle is 500ms (250ms on, 250ms off)
    int beepCycle = (elapsedTime / 250) % 2;
    int currentBeep = elapsedTime / 500;
    
    if (currentBeep < 3) {
        // We're in the first three beeps - only activate audio if both sensors are touched
        digitalWrite(AUDIO_PIN, beepCycle == 0 ? HIGH : LOW);
        
        // Update beep count if we just finished a beep
        if (beepCycle == 1 && currentBeep > beepCount) {
            beepCount = currentBeep;
            Serial.print("Beep "); Serial.println(beepCount + 1);
        }
    } else {
        // Beep sequence complete
        digitalWrite(AUDIO_PIN, LOW);
        beepSequenceActive = false;
        
        // Start motors as both sensors are still pressed
        startMotors(speedValue);
        motorsRunning = true;
        Serial.println("Motors started after beep sequence");
    }
}

void startMotors(int speed) {
    analogWrite(MOTOR_IN1, speed);  // Start motor 1
    analogWrite(MOTOR_IN3, speed);  // Start motor 2
}

void stopMotors() {
    analogWrite(MOTOR_IN1, 0);  // Stop motor 1
    analogWrite(MOTOR_IN3, 0);  // Stop motor 2
}