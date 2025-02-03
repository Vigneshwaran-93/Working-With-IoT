import paho.mqtt.client as mqtt

# MQTT settings
broker = "localhost"
port = 1883
topic = "test/topic"

# Callback function for when the publisher connects to the broker
def on_connect(client, userdata, flags, rc):
    print(f"Connected with result code {rc}")

# Create a new MQTT client instance
publisher = mqtt.Client()

# Set the callback for connecting to the broker
publisher.on_connect = on_connect

# Connect to the broker
publisher.connect(broker, port, 60)

# Loop to maintain the connection
publisher.loop_start()

# Publisher loop for taking user input
while True:
    message = input("Enter message to publish (or 'exit' to quit): ")
    
    if message.lower() == 'exit':
        print("Exiting publisher...")
        break

    # Publish the message to the topic
    publisher.publish(topic, message)

# Stop the loop and disconnect
publisher.loop_stop()
publisher.disconnect()
