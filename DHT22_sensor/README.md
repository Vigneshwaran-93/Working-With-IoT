# DHT22 Sensor Program

This program reads temperature and humidity data from a DHT22 sensor and sends the data to ThingSpeak using Wi-Fi.

## Features

- Reads temperature and humidity from a DHT22 sensor.
- Connects to Wi-Fi and sends the data to ThingSpeak.
- Data is sent every 20 seconds.
- Prints temperature and humidity readings to the Serial Monitor.

## Requirements

- **Hardware**:
  - DHT22 (AM2302) sensor
  - ESP32 or compatible Wi-Fi-enabled board

- **Libraries**:
  - `DHT` library for sensor communication.
  - `WiFi` library for Wi-Fi connection.
  - `HTTPClient` library for HTTP requests.

You can install the required libraries via the Arduino Library Manager.

## Setup Instructions

1. **Connect the DHT22 sensor** to your board:
   - Connect the `VCC` pin to 3.3V.
   - Connect the `GND` pin to ground.
   - Connect the `DATA` pin to GPIO2 (or any GPIO pin you choose, just update the code accordingly).

2. **Modify the code**:
   - Replace the `ssid` and `password` variables with your Wi-Fi credentials.
   - Replace `thingSpeakApiKey` with your ThingSpeak API key.

3. **Upload the code** to your ESP32 or compatible board.

4. **Open the Serial Monitor** to view the temperature and humidity readings. The data will also be uploaded to ThingSpeak.

## Code Explanation

- The program initializes the DHT22 sensor and connects to Wi-Fi.
- It reads temperature and humidity from the DHT22 sensor every 20 seconds.
- It sends the temperature and humidity data to ThingSpeak via an HTTP GET request.
- If the Wi-Fi is not connected or there's an error with the sensor, it will print an error message in the Serial Monitor.

## Points of Failure
- WiFi connection being lost temporally
- DHT sensor Freezing
- Sudden drop in request being sent
