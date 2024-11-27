#include <WiFi.h>
#include <HTTPClient.h>

// WiFi credentials
const char* ssid = "Your_SSID";
const char* password = "Your_PASSWORD";

// Server endpoint
const char* flagUrl = "http://<SERVER_IP>:3000/check-flag";

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi!");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(flagUrl);
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Response: " + response);

      // Parse response
      if (response.indexOf("\"flag\":true") > -1) {
        Serial.println("Flag is true. Unlocking...");
        // Unlock mechanism (e.g., GPIO control)
        unlockLock();
      }
    } else {
      Serial.print("Error on HTTP request: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  }

  delay(2000); // Poll every 2 seconds
}

void unlockLock() {
  // Control GPIO pin to unlock (Example: Relay)
  int lockPin = 5; // Replace with your pin
  pinMode(lockPin, OUTPUT);
  digitalWrite(lockPin, HIGH); // Unlock
  delay(5000);                 // Keep unlocked for 5 seconds
  digitalWrite(lockPin, LOW);  // Lock again
}
