const int potPin = 6;    // Potentiometer on GPIO9 (ADC1_CH8)
const int ledPins[] = {22, 23, 15, 17}; // LED pins

void setup() {
    // Initialize LED pins
    for (int i = 0; i < 4; i++) {
        pinMode(ledPins[i], OUTPUT);
    }
    
    // Set ADC resolution to 12 bits
    analogReadResolution(12);
}

void loop() {
    // Read the potentiometer value (ESP32-C6 has 12-bit ADC: 0-4095)
    int potValue = analogRead(potPin);
    
    // Map the pot value to 4 levels (0-3)
    // ESP32-C6 ADC range is 0-4095
    int ledIndex = map(potValue, 100, 3200, 0, 3);
    
    // Control the LEDs based on the potentiometer value
    for (int i = 0; i < 4; i++) {
        digitalWrite(ledPins[i], (i == ledIndex) ? HIGH : LOW);
    }
    
    delay(50); // Small delay to stabilize
}
