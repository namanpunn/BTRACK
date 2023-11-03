#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "VaibhaviPhone";
const char* password = "vaibhav$123";
const char* serverUrl = "http://172.20.10.2:5000/update_gps";

void setup() {
  Serial.begin(115200);
  // Serial1.begin(115200, SERIAL_8N1, 2, 3); // Configure Serial1 for GPS data at 9600 baud

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Initialize the A9G board (using AT commands)
  // Serial1.write("AT+GPS=1");

  // delay(1000);

  // Serial.println(Serial1.read());

  // delay(20000);
  // Serial.println("End of 100 Seconds");
  // Send appropriate AT commands to enable GPS on the A9G board
  // Serial1.println("AT+GPRSD=100");
  // delay(10000);
  // Serial.println("End of 10 seconds");
  // if (Serial1.available()) {
  //   char line = Serial1.read();
  //   // if (line.startsWith("$GNGGA")){
  //   Serial.println("RAW FORM OF DATA (NEMA FORMAT): "); Serial.print(line);
  //   // }
  // }
  // Serial1.println("AT+GPRSD=0");
  // Serial.println("end of AT+GPRSD=0");
  checkGPSDataAndSend();
}

void loop() {
  // Serial1.println("AT+GPRSD=10");
  // Serial.println(Serial1.read());
  // checkGPSDataAndSend();
  // Add other loop functionality if needed
  // Serial.println("Start of 30 seconds");
  // delay(3000);
  // Serial.println("End of 30 seconds");
  // Serial1.println("AT+GPRSD=0");
}

void checkGPSDataAndSend() {
  // while (Serial1.available()) {
  //   String line = Serial1.readStringUntil('\n');
  //   if (line.startsWith("$GNGGA")) {
  //     // Extract GPS data and send to the server
  //     Serial.println(line);
  String line = "$GPGGA,200155.181,2825.235,N,07703.065,E,1,12,1.0,0.0,M,0.0,M,,*60";
  processGPSData(line);
    // }
  // }
}

void processGPSData(String data) {
  // Parse GPS data and extract latitude and longitude
  // Example GPGGA format: $GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47

  Serial.println("now processing data");

  // Find the position of the first comma
  int firstComma = data.indexOf(',');

  // Find the position of the second comma
  int secondComma = data.indexOf(',', firstComma + 1);

  // Extract latitude in the GPGGA format (ddmm.mmmm)
  String latitudeGPGGA = data.substring(firstComma + 1, secondComma);

  // Extract the hemisphere (N or S)
  char hemisphereLat = data.charAt(secondComma + 1);

  // Convert latitude to degrees format
  float latitude = latitudeGPGGA.substring(0, 2).toFloat() + latitudeGPGGA.substring(2).toFloat() / 60.0;
  if (hemisphereLat == 'S') {
    latitude = -latitude;
  }

  // Find the position of the fourth comma
  int fourthComma = data.indexOf(',', secondComma + 1);

  // Extract longitude in the GPGGA format (dddmm.mmmm)
  String longitudeGPGGA = data.substring(secondComma + 1, fourthComma);

  // Extract the hemisphere (E or W)
  char hemisphereLon = data.charAt(fourthComma + 1);

  // Convert longitude to degrees format
  float longitude = longitudeGPGGA.substring(0, 2).toFloat() + longitudeGPGGA.substring(2).toFloat() / 60.0;
  if (hemisphereLon == 'W') {
    longitude = -longitude;
  }

  // float latitude = 12.1312
  // float longitude = 11.1312

  Serial.print("Latitude: ");
  Serial.println(latitude);
  Serial.print("Longitude: ");
  Serial.println(longitude);
  // float latitude = 12.3456;
  // float longitude = -78.9101;

  // Create JSON payload
  String jsonPayload = "{\"latitude\":" + String(latitude) + ",\"longitude\":" + String(longitude) + "}"; // Init the JSON payload, prep to send to server.

  // Send the GPS data to the server
  HTTPClient http;
  http.begin(serverUrl);
  http.addHeader("Content-Type", "application/json"); // JSON POST payload format
  int httpResponseCode = http.POST(jsonPayload);
  
  if (httpResponseCode == 200) {
    String response = http.getString();
    Serial.println("HTTP Response code: " + String(httpResponseCode));
    Serial.println(response);
  } 
  else {
    Serial.print("Error in HTTP request: ");
    Serial.println(httpResponseCode);
  }
  http.end();
}