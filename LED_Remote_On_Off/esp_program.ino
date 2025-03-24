#include <WiFi.h>
#include <Firebase_ESP_Client.h>

// Wi-Fi credentials
#define WIFI_SSID "name"
#define WIFI_PASSWORD "password"

/* 2. Define the API Key */
#define API_KEY "key"

/* 3. Define the RTDB URL */
#define DATABASE_URL "url" 

/* 4. Define the user Email and password that alreadey registerd or added in your project */
#define USER_EMAIL "mail"
#define USER_PASSWORD "pass"

// LED pins (using GPIO numbers)
#define LED_D4 4  // GPIO 4 (D4)
#define LED_D5 5  // GPIO 5 (D5)

// Firebase objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
unsigned long sendDataPrevMillis = 0;

void setup() {
  // Start Serial for debugging
  Serial.begin(115200);

  // Initialize LED pins as outputs
  pinMode(LED_D4, OUTPUT);
  pinMode(LED_D5, OUTPUT);
  digitalWrite(LED_D4, LOW); // Start with LEDs off
  digitalWrite(LED_D5, LOW);

  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
    Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the user sign in credentials */
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  // Comment or pass false value when WiFi reconnection will control by your code or third party library e.g. WiFiManager
  Firebase.reconnectNetwork(true);

  // Since v4.4.x, BearSSL engine was used, the SSL buffer need to be set.
  // Large data transmission may require larger RX buffer, otherwise connection issue or data read time out can be occurred.
  fbdo.setBSSLBufferSize(4096 /* Rx buffer size in bytes from 512 - 16384 */, 1024 /* Tx buffer size in bytes from 512 - 16384 */);

  // Limit the size of response payload to be collected in FirebaseData
  fbdo.setResponseSize(2048);

  Firebase.begin(&config, &auth);

  Firebase.setDoubleDigits(5);

  config.timeout.serverResponse = 10 * 1000;

  // Optional: Ensure onboard LED (GPIO 2) stays off if it's causing issues
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
}

void loop() {
  // Check if Firebase is ready
   if (Firebase.ready() && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0))
    {
    // Read LED_D4 state
    if (Firebase.RTDB.getString(&fbdo, "/LED_D4")) {
      String ledState = fbdo.stringData();
      Serial.print("LED_D4 (GPIO 4): ");
      Serial.println(ledState);
      if (ledState == "ON") {
        digitalWrite(LED_D4, HIGH);
      } else if (ledState == "OFF") {
        digitalWrite(LED_D4, LOW);
      }
    } else {
      Serial.println("Failed to get LED_D4: " + fbdo.errorReason());
    }

    // Read LED_D5 state
    if (Firebase.RTDB.getString(&fbdo, "/LED_D5")) {
      String ledState = fbdo.stringData();
      Serial.print("LED_D5 (GPIO 5): ");
      Serial.println(ledState);
      if (ledState == "ON") {
        digitalWrite(LED_D5, HIGH);
      } else if (ledState == "OFF") {
        digitalWrite(LED_D5, LOW);
      }
    } else {
      Serial.println("Failed to get LED_D5: " + fbdo.errorReason());
    }
    }else{
    Serial.println(fbdo.errorReason().c_str());
   }
  

  // Increase delay to slow down loop and reduce rapid toggling
  delay(1000); // Check every 1 second instead of 500ms
}