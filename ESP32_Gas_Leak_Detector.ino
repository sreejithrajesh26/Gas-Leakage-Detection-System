#define BLYNK_TEMPLATE_ID "TMPL3-74NMujS"
#define BLYNK_TEMPLATE_NAME "GAS LEAK"
#define BLYNK_AUTH_TOKEN "3VVmL5-IdmvqqBPP60RT7P_7DbnekNLf"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h>  // Use ESP32-compatible Servo library

// WiFi credentials
char ssid[] = "Motog22";        // Your WiFi SSID
char pass[] = "sree20004";       // Your WiFi password

Servo gasServo;
int servoPin = 23;  // GPIO pin for the servo motor

void setup() {
  Serial.begin(115200);  // Start serial communication for debugging

  // Attach the servo motor to the specified pin
  gasServo.attach(servoPin);
  gasServo.write(0);  // Initialize servo to 0° (closed position)

  // Connect to WiFi
  connectToWiFi();

  // Start Blynk
  Blynk.config(BLYNK_AUTH_TOKEN);  // Configures Blynk without blocking
  while (Blynk.connect() == false) {
    Serial.println("Trying to connect to Blynk...");
    delay(1000);
  }
}

void connectToWiFi() {
  WiFi.begin(ssid, pass);
  Serial.print("Connecting to WiFi");

  int attempt = 0;
  while (WiFi.status() != WL_CONNECTED && attempt < 20) {  // Try for 20 attempts
    delay(500);
    Serial.print(".");
    attempt++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected to WiFi!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nFailed to connect to WiFi. Check your credentials or signal strength.");
    // Optional: restart ESP32 if WiFi connection fails
    ESP.restart();
  }
}

// Blynk function to control the servo motor via virtual pin V0
BLYNK_WRITE(V0) {
  int state = param.asInt();  // Read the button state from Blynk (0 or 1)

  if (state == 1) {
    gasServo.write(90);  // Rotate to 90° (open regulator)
    Serial.println("Gas regulator opened.");
  } else {
    gasServo.write(0);  // Reset to 0° (close regulator)
    Serial.println("Gas regulator closed.");
  }
}

void loop() {
  Blynk.run();  // Maintain connection with Blynk server
}
