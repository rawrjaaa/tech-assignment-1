#include <WiFi.h>
#include <HTTPClient.h>

// Konstan untuk WiFi credentials
const char *WIFI_SSID = "RUANG 202";
const char *WIFI_PASS = "sman1malang";

// Pin assignments
int sensor_input = 34;

// Fungsi untuk membaca data analog dari air quality sensor
int get_air_quality_data() {
  int analog_data = analogRead(sensor_input);
  Serial.print("Air Quality: ");
  Serial.println(analog_data);
  delay(300);  // Allow sensor to stabilize
  return analog_data;
}

// Fungsi untuk mengirim data ke Flask API
void send_data_to_flask(int air_quality) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin("http://10.10.4.55:5000/api/data");  // Ganti dengan IP server Flask Anda
    http.addHeader("Content-Type", "application/json");

    String json_data = "{\"air_quality\": " + String(air_quality) + "}";
    int httpResponseCode = http.POST(json_data);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
}

void loop() {
  delay(1000);
  send_data_to_flask(get_air_quality_data());
  delay(5000);
}
