import paho.mqtt.client as mqtt

# MQTT settings
broker = "localhost"
port = 1883
topic = "test/topic"

# Callback function for when a message is received
def on_message(client, userdata, msg):
    print(f"Received message: {msg.payload.decode()} on topic: {msg.topic}")

# Callback function for when the subscriber connects to the broker
def on_connect(client, userdata, flags, rc):
    print(f"Connected with result code {rc}")
    # Subscribe to the topic
    client.subscribe(topic)

# Create a new MQTT client instance
subscriber = mqtt.Client()

# Set the callbacks for connecting and receiving messages
subscriber.on_connect = on_connect
subscriber.on_message = on_message

# Connect to the broker
subscriber.connect(broker, port, 60)

# Loop to maintain the connection and listen for messages
subscriber.loop_start()

# Keep the subscriber running until user interrupts
try:
    while True:
        pass
except KeyboardInterrupt:
    print("Exiting subscriber...")

# Stop the loop and disconnect
subscriber.loop_stop()
subscriber.disconnect()
