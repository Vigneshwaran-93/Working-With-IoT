# MQTT Publisher and Subscriber Example

This repository contains a simple example of using MQTT for message publishing and subscribing with Python. It uses the `paho-mqtt` library to create a publisher and subscriber that communicate over a local MQTT broker (e.g., Mosquitto).

## Prerequisites

- Python 3.x
- Mosquitto (or any other MQTT broker) installed and running on localhost (port 1883).
- `paho-mqtt` library installed.

## Setup

### Update your system
``` bash
sudo apt update && sudo apt upgrade -y
```
### Install Mosquitto and Mosquitto clients
``` bash
sudo apt install -y mosquitto mosquitto-clients
```
### Start Mosquitto service
``` bash
sudo systemctl start mosquitto
```
### Enable Mosquitto to start on boot
```bash
sudo systemctl enable mosquitto
```
### Install dependencies
```bash
pip install -r requirements.txt
```

### Run Pub and Sub Program
```bash
python mqtt_publisher.py
```
```bash
python mqtt_subscriber.py
