#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <HTTPClient.h>

// WiFi Credentials
const char* ssid = "Meetvyas";
const char* password = "meet2004";

// ThingSpeak API
const char* server = "http://api.thingspeak.com/update";
const char* apiKey = "JZ8S60YP8RSBRDS0";  // Replace with your ThingSpeak Write API Key

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Sensor Pins
#define LDR_PIN     34
#define MQ2_PIN     35
#define LM35_PIN    32
#define FLAME_PIN   33

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");


  // OLED Setup
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for I2C OLED
    Serial.println(F("OLED not found"));
    while (true);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // Sensor Pins
  pinMode(FLAME_PIN, INPUT);

  display.println("IoT Industry Protection");
  display.println("System Starting...");
  display.display();
  delay(2000);
}

void loop() {
  int ldr = analogRead(LDR_PIN);
  int gas = analogRead(MQ2_PIN);
  int tempADC = analogRead(LM35_PIN);
  float voltage = (tempADC / 2095.0) * 3.3;
  float temperature = voltage * 100.0; // LM35 → 10mV per °C
  int flame = digitalRead(FLAME_PIN);

  // Print to Serial
  Serial.print("Temp: "); Serial.print(temperature); Serial.print(" °C | ");
  Serial.print("Gas: "); Serial.print(gas); Serial.print(" | ");
  Serial.print("LDR: "); Serial.print(ldr); Serial.print(" | ");
  Serial.print("Flame: "); Serial.println(flame == LOW ? "DETECTED" : "SAFE");
 
   if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(server) + "?api_key=" + apiKey +
                 "&field1=" + String(temperature) +
                 "&field2=" + String(gas) +
                 "&field3=" + String(ldr) +
                 "&field4=" + String(flame == LOW ? 1 : 0);  // 1 = flame

    http.begin(url);
    int httpCode = http.GET();
    if (httpCode > 0) {
      Serial.println("Data sent to ThingSpeak.");
    } else {
      Serial.println("Failed to send data.");
    }
    http.end();
  } else {
    Serial.println("WiFi not connected.");
  }
  // Print to OLED
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("IoT Industry Protection");
  display.print("Temp: "); display.print(temperature); display.println(" C");
  display.print("Gas: "); display.println(gas);
  display.print("LDR: "); display.println(ldr);
  display.print("Flame: ");
  display.println(flame == LOW ? "Flame DETECTED" : "SAFE");
  display.display();

  delay(2000);
}
