from flask import Flask, request, render_template
import json

app = Flask(__name__, static_folder='static', template_folder='C:\\Users\\vaibh\\OneDrive\\Documents\\Programs\\BTRACK\\github\\SIH_Btrack_Juniorscontrib\\server-side\\templates')
gps_data = {} ##"latitude": 28.417491437486206, "longitude": 77.05209745027312

@app.route('/update_gps', methods=['POST'])
def update_gps():
    global gps_data
    gps_data = request.json
    print("Received GPS data:", gps_data)
    return "GPS data received", 200

@app.route('/')
def display_map():
    return render_template('map.html', gps_data=gps_data) #type:ignore

if __name__ == '__main__':
    app.run(host='172.20.10.2', port=5000)
