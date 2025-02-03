#!/bin/bash

# Update the system
echo "Updating system packages..."
sudo apt update && sudo apt upgrade -y

# Install Mosquitto
echo "Installing Mosquitto MQTT broker..."
sudo apt install -y mosquitto mosquitto-clients

# Enable Mosquitto to start on boot
echo "Enabling Mosquitto service to start on boot..."
sudo systemctl enable mosquitto

# Start the Mosquitto service
echo "Starting Mosquitto service..."
sudo systemctl start mosquitto

# Check the Mosquitto service status
echo "Checking Mosquitto service status..."
sudo systemctl status mosquitto

# Optionally, allow Mosquitto through the firewall if using UFW (Uncomplicated Firewall)
echo "Configuring firewall to allow Mosquitto (port 1883)..."
sudo ufw allow 1883/tcp

# Display the Mosquitto version
echo "Mosquitto installation complete. Checking version..."
mosquitto -v

# Test the installation (this should not be necessary but helpful to verify)
echo "Testing MQTT connection..."
mosquitto_pub -t "test/topic" -m "Hello, MQTT!" &> /dev/null
if [ $? -eq 0 ]; then
    echo "Mosquitto is working correctly! Message published."
else
    echo "Something went wrong with Mosquitto setup. Please check the logs."
fi

echo "Setup complete! MQTT broker is running on port 1883."
