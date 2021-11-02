
#include <PubSubClient.h> // Connect and publish to the MQTT broker
#include <M5Stack.h>
// Code for the ESP32
#include <WiFi.h> // Enables the ESP32 to connect to the local network (via WiFi)

// WiFi
const char* ssid = "doma";                 // Your personal network SSID
const char* wifi_password = "nasewifireee"; // Your personal network password

// MQTT
const char* mqtt_server = "ipd020.gw2.pvfree.net";  // IP of the MQTT broker
const char* flow_topic = "home/boiler/flow";
const char* mqtt_username = "pi"; // MQTT username
const char* mqtt_password = "raspberry"; // MQTT password
const char* clientID = "client_meric"; // MQTT client ID
//proměnné pro samotný program
float f = 0;
unsigned long minule = 0;
int minule_btn = 0;
int btn = 0;
// Initialise the WiFi and MQTT Client objects
WiFiClient wifiClient;
// 1883 is the listener port for the Broker
PubSubClient client(mqtt_server, 1883, wifiClient);


// Custom function to connet to the MQTT broker via WiFi
void connect_MQTT() {
  Serial.print("Connecting to ");
  Serial.println(ssid);

  // Connect to the WiFi
  WiFi.begin(ssid, wifi_password);

  // Wait until the connection has been confirmed before continuing
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Debugging - Output the IP Address of the ESP8266
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Connect to MQTT Broker
  // client.connect returns a boolean value to let us know if the connection was successful.
  // If the connection is failing, make sure you are using the correct MQTT Username and Password (Setup Earlier in the Instructable)
  if (client.connect(clientID, mqtt_username, mqtt_password)) {
    Serial.println("Connected to MQTT Broker!");
  }
  else {
    Serial.println("Connection to MQTT Broker failed...");
  }
}

void send_MQTT(float f) {
  String fs = "Flow: " + String((float)f) + " l/s ";

  if (client.publish(flow_topic, String(f).c_str())) {
    Serial.println("Poslano");
  }
  else {
    client.connect(clientID, mqtt_username, mqtt_password);
    Serial.println("Připojení se nepovedlo");
    delay(10);
    client.publish(flow_topic, String(f).c_str());
    Serial.println("Poslano");
  }
}
void setup() {
  M5.Power.begin();
  M5.begin(false, false);
  connect_MQTT();
  pinMode(2, INPUT_PULLUP);
}

void loop() {
  if (millis() - minule > 10000) {
    minule = millis();
    send_MQTT(f);
    f = 0;
  }
  btn = digitalRead(2);
  if (btn != minule_btn) {
    if (btn == HIGH) {
      f = f + 1;
    }
  }

  minule_btn = btn;


}
