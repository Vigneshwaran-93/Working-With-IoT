#This is a simple Flask program to relay the information received by the ESP32 and show the latest 100 received changes.

from flask import Flask, request, jsonify, render_template
import csv
import os
from datetime import datetime
import time
from flask_cors import CORS

app = Flask(__name__)

CORS(app)

# API key for verification
API_KEY = "key"

# CSV file to store the color states
CSV_FILE = "phase_states.csv"

# Initialize the CSV file if it doesn't exist
if not os.path.exists(CSV_FILE):
    with open(CSV_FILE, mode='w', newline='') as file:
        writer = csv.writer(file)
        writer.writerow(["Timestamp", "Phase 1 (R)", "Phase 2 (Y)", "Phase 3 (B)", "DATA"])

# Route to receive the POST request from the ESP8266
@app.route('/receive', methods=['POST'])
def receive_data():
    # Verify API Key
    #time.sleep(5)
    if request.headers.get('apiKey') != API_KEY:
        return jsonify({"error": "Unauthorized"}), 403

    # Get the JSON data from the request
    data = request.get_json()
    print(data)
    # Ensure the data is valid
    if not data or not all(key in data for key in ("R", "Y", "B", "D")):
        return jsonify({"error": "Invalid data"}), 400

    # Get the current timestamp
    timestamp = datetime.now().strftime('%Y-%m-%d %H:%M:%S')

    # Get the phase states (0 or 1 for each phase)
    phase_1 = data["R"]
    phase_2 = data["Y"]
    phase_3 = data["B"]
    data = data["D"]

    # Save the data to CSV
    with open(CSV_FILE, mode='a', newline='') as file:
        writer = csv.writer(file)
        writer.writerow([timestamp, phase_1, phase_2, phase_3,data])

    # Return a success response
    return jsonify({"message": "Data received successfully"}), 200

# Route to display the data in a table
@app.route('/')
def index():
    # Read the data from the CSV file
    with open(CSV_FILE, mode='r') as file:
        reader = csv.reader(file)
        rows = list(reader)

    # Remove the header row (index 0) for sorting
    header = rows[0]
    rows = rows[1:]

    # Sort rows by timestamp (newest first)
    rows.sort(key=lambda x: x[0], reverse=True)
    data=rows[0][-1]
    # Pass the data to the template to display in an HTML table
    return render_template('index.html', rows=rows, header=header, data=data)
if __name__ == '__main__':
    app.run(host='0.0.0.0', port=7577, debug=True)