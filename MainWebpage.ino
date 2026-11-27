// This code is derived from the HelloServer Example 
// in the (ESP32) WebServer library .
//
// It hosts a webpage which has one temperature reading to display.
// The webpage is always the same apart from the reading which would change.
// The getTemp() function simulates getting a temperature reading.
// homePage.h contains 2 constant string literals which is the two parts of the
// webpage that never change.
// handleRoot() builds up the webpage by adding as a C++ String:
// homePagePart1 + getTemp() +homePagePart2 
// It then serves the webpage with the command:  
// server.send(200, "text/html", message);
// Note the text is served as html.
//
// Replace the code in the homepage.h file with your own website HTML code.
// 
// This example requires only an ESP32 and download cable. No other hardware is reuired.
// A wifi SSID and password is required.
// Written by: Natasha Rohan  12/3/23
// Adapted by: Oliver Brzezinski 9/11/26 
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <DHT.h>
#include <DFRobot_DHT11.h>
#include "homepage.h"

void setupWaterLevelSensor();
String getWaterLevel();

#define DHTPIN 16         // Pin connected to the SIG wire of Grove DHT11
#define DHTTYPE DHT11    // Telling the library you are using a DHT11
DHT dht(DHTPIN, DHTTYPE);
DFRobot_DHT11 DHT;

const char* ssid = "sand";
const char* password = "9znt1234";

WebServer server(80);

//temp function to simulate temp sensor
String getTemp() {
  float Temperature = dht.readTemperature();

  // Check if the sensor read failed
  if (isnan(Temperature)) {
    Serial.println("Error: Failed to read from DHT11 sensor!");
    return "Error (Check Sensor)"; 
  }

  // Convert the float to a String with 1 decimal place (matching your original "25.4" format)
  return String(Temperature, 1);
}

//temp function to get humidity reading
String getHumidity() {
  float Humidity = dht.readHumidity();
  
  // Check if the sensor read failed
  if (isnan(Humidity)) {
    Serial.println("Error: Failed to read humidity from DHT11 sensor!");
    return "Error (Check Sensor)";
  }

  //Convert the float to a string with no decimal place
  return String(Humidity, 0);
}


void handleRoot() {
  String message = homePagePart1 + getTemp() + homePagePart2;
  server.send(200, "text/html", message);
}

void handleTemp() {
  server.send(200, "text/plain", getTemp());
}

void handleHumidity() {
  server.send(200, "text/plain", getHumidity());
}

// 
void handleWaterLevel() {
  server.send(200, "text/plain", getWaterLevel());
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void setup(void) {

  Serial.begin(115200);
  dht.begin(); // dht 11
  setupWaterLevelSensor();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.on("/temp", handleTemp);
  server.on("/humidity", handleHumidity);
  server.on("/water", handleWaterLevel);
  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");


  
}

void loop(void) {

  server.handleClient();
  delay(2);//allow the cpu to switch to other tasks
}
