#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "name";        // 🔹 Replace with your WiFi SSID
const char* password = "pass"; // 🔹 Replace with your WiFi password
const char* serverName = "address";
String apiKey = "key";  // 🔹 Replace with your actual API key

int r = 0, y = 0, b = 0;

void sendRequest(int R, int Y, int B) {
    HTTPClient http;
    WiFiClient client;

    http.begin(client, serverName);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("apiKey", apiKey);

    String jsonPayload = "{\"R\": \"" + String(R) + "\", \"Y\": \"" + String(Y) + "\", \"B\": \"" + String(B) + "\"}";
    Serial.print("Sending JSON: ");
    Serial.println(jsonPayload);

    int httpResponseCode = http.POST(jsonPayload);
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);

    http.end();
}

void setup() {
    Serial.begin(9600);
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi");
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nWiFi connected");
}

void loop() {
    r++; y++; b++;
    Serial.print("R: "); Serial.print(r);
    Serial.print(" | Y: "); Serial.print(y);
    Serial.print(" | B: "); Serial.println(b);

    sendRequest(r, y, b);
    
    delay(10000); // Wait 10 seconds
}