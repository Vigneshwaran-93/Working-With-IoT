# A simple flask program to relay the information for the receiver

from flask import Flask, request, jsonify

app = Flask(__name__)

# This will store the latest received data
latest_data = ""

# Function to handle POST request and store the data
@app.route('/', methods=['GET', 'POST'])
def receive_data():
    global latest_data

    if request.method == 'POST':
        # Handling incoming JSON data and updating latest_data
        json_data = request.get_json()
        if json_data and 'data' in json_data:
            latest_data = json_data['data']
            return jsonify({"message": "Success"}), 200
        #else:
        #    return 404
    # For GET requests, just return the latest_data as plain text
    if request.method == 'GET':
        return latest_data

if __name__ == '__main__':
    app.run(host='0.0.0.0', debug=True, port=7580)