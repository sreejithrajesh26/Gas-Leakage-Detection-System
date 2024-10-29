#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// Initialize LCD object (I2C address 0x27, 16x2 display)
LiquidCrystal_I2C lcd(0x27, 16, 2);  
Servo myServo;

int gasSensor = A0;  // MQ6 sensor connected to A0
int buzzer = 7;      // Buzzer connected to pin 7
int led = 13;        // LED connected to pin 13
int gasThreshold = 250;  // Gas leakage threshold

bool leakDetected = false;  // Tracks if gas was detected
unsigned long leakStartTime = 0;  // Store when the gas was detected

void setup() {
  lcd.begin(16, 2);  // Initialize LCD
  lcd.backlight();   // Turn on LCD backlight

  pinMode(gasSensor, INPUT);  // MQ6 sensor as input
  pinMode(buzzer, OUTPUT);    // Buzzer as output
  pinMode(led, OUTPUT);       // LED as output

  myServo.attach(9);  // Attach servo to pin 9
  myServo.write(0);   // Set initial servo position to 0°

  // Display initialization message
  lcd.setCursor(0, 0);
  lcd.print("Gas Detector Init");
  delay(2000);
  lcd.clear();
}

void loop() {
  int gasValue = analogRead(gasSensor);  // Read gas sensor value

  // Display gas value on the LCD
  lcd.setCursor(0, 0);
  lcd.print("Gas Value: ");
  lcd.print(gasValue);

  if (gasValue > gasThreshold && !leakDetected) {
    // Gas detected: Activate alarm and start timer
    leakDetected = true;
    leakStartTime = millis();  // Record the start time

    digitalWrite(led, HIGH);   // Turn on LED
    myServo.write(120);         // Rotate servo to 90°
    digitalWrite(buzzer, HIGH);  // Turn on buzzer

    lcd.setCursor(0, 1);
    lcd.print("GAS LEAKED!    ");
  }

  if (leakDetected && millis() - leakStartTime >= 10000) {
    // After 10 seconds, deactivate LED and servo
    digitalWrite(led, LOW);  // Turn off LED
    myServo.write(0);        // Reset servo to 0°
    leakDetected = false;    // Reset leak status
  }

  // If gas value falls below the threshold, turn off buzzer
  if (gasValue <= gasThreshold) {
    digitalWrite(buzzer, LOW);  // Turn off buzzer
    lcd.setCursor(0, 1);
    lcd.print("Safe            ");
  }

  delay(500);  // Delay to prevent rapid updates
}
