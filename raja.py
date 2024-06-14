from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/api/data', methods=['POST'])
def receive_data():
    data = request.json
    if not data:
        return jsonify({'error': 'No data provided'}), 400

    air_quality = data.get('air_quality')

    if air_quality is None:
        return jsonify({'error': 'Incomplete data provided'}), 400

    # Proses data di sini
    print(f"Air Quality: {air_quality}")

    return jsonify({'message': 'Data received successfully'}), 200

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
