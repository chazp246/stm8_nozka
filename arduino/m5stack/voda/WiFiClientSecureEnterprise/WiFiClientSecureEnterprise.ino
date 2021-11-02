/*|----------------------------------------------------------|*/
/*|WORKING EXAMPLE FOR HTTPS CONNECTION                      |*/
/*|TESTED BOARDS: Devkit v1 DOIT, Devkitc v4                 |*/
/*|CORE: June 2018                                           |*/
/*|----------------------------------------------------------|*/
//wifi knihovny
//#include <WiFi.h>
#include <WiFiClientSecure.h>
#include "esp_wpa2.h"
#include <Wire.h>
#include <PubSubClient.h> //mqtt knihovna
#include <M5Stack.h> //knihovna pro vývojovou desku

#define EAP_IDENTITY "rpimereni1" //wifi idedntita
#define EAP_PASSWORD "Teplom2r1" //wifi heslo

const char* mqtt_server = "ipd020.gw2.pvfree.net";  // IP mqtt serveru
const char* flow_topic = "home/boiler/flow"; 
const char* mqtt_username = "pi"; // MQTT jmeno
const char* mqtt_password = "raspberry"; // MQTT heslo
const char* clientID = "client_meric"; // MQTT ID přezdívka
//proměnné pro samotný program
float f = 0;
unsigned long minule = 0;
int minule_btn = 0;
int btn = 0;

WiFiClient wificlient; //inicializace wifi a mqtt

PubSubClient client(mqtt_server, 1883, wificlient); //propojení wifi a pubsubclient

const char* ssid = "eduroam"; //wifi SSID
int counter = 0;

const char* test_root_ca = \
                           "-----BEGIN CERTIFICATE-----\n" \
                           "MIIDrzCCApegAwIBAgIQCDvgVpBCRrGhdWrJWZHHSjANBgkqhkiG9w0BAQUFADBh\n" \
                           "MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\n" \
                           "d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBD\n" \
                           "QTAeFw0wNjExMTAwMDAwMDBaFw0zMTExMTAwMDAwMDBaMGExCzAJBgNVBAYTAlVT\n" \
                           "MRUwEwYDVQQKEwxEaWdpQ2VydCBJbmMxGTAXBgNVBAsTEHd3dy5kaWdpY2VydC5j\n" \
                           "b20xIDAeBgNVBAMTF0RpZ2lDZXJ0IEdsb2JhbCBSb290IENBMIIBIjANBgkqhkiG\n" \
                           "9w0BAQEFAAOCAQ8AMIIBCgKCAQEA4jvhEXLeqKTTo1eqUKKPC3eQyaKl7hLOllsB\n" \
                           "CSDMAZOnTjC3U/dDxGkAV53ijSLdhwZAAIEJzs4bg7/fzTtxRuLWZscFs3YnFo97\n" \
                           "nh6Vfe63SKMI2tavegw5BmV/Sl0fvBf4q77uKNd0f3p4mVmFaG5cIzJLv07A6Fpt\n" \
                           "43C/dxC//AH2hdmoRBBYMql1GNXRor5H4idq9Joz+EkIYIvUX7Q6hL+hqkpMfT7P\n" \
                           "T19sdl6gSzeRntwi5m3OFBqOasv+zbMUZBfHWymeMr/y7vrTC0LUq7dBMtoM1O/4\n" \
                           "gdW7jVg/tRvoSSiicNoxBN33shbyTApOB6jtSj1etX+jkMOvJwIDAQABo2MwYTAO\n" \
                           "BgNVHQ8BAf8EBAMCAYYwDwYDVR0TAQH/BAUwAwEB/zAdBgNVHQ4EFgQUA95QNVbR\n" \
                           "TLtm8KPiGxvDl7I90VUwHwYDVR0jBBgwFoAUA95QNVbRTLtm8KPiGxvDl7I90VUw\n" \
                           "DQYJKoZIhvcNAQEFBQADggEBAMucN6pIExIK+t1EnE9SsPTfrgT1eXkIoyQY/Esr\n" \
                           "hMAtudXH/vTBH1jLuG2cenTnmCmrEbXjcKChzUyImZOMkXDiqw8cvpOp/2PV5Adg\n" \
                           "06O/nVsJ8dWO41P0jmP6P6fbtGbfYmbW0W5BjfIttep3Sp+dWOIrWcBAI+0tKIJF\n" \
                           "PnlUkiaY4IBIqDfv8NZ5YBberOgOzW6sRBc4L0na4UU+Krk2U886UAb3LujEV0ls\n" \
                           "YSEY1QSteDwsOoBrp+uvFRTp2InBuThs4pFsiv9kuXclVzDAGySj4dzp30d8tbQk\n" \
                           "CAUw7C29C79Fv1C5qfPrmAESrciIxpg0X40KPMbp1ZWVbd4=\n" \
                           "-----END CERTIFICATE-----\n";
// You can use x.509 client certificates if you want
//const char* test_client_key = "";   //to verify the client
//const char* test_client_cert = "";  //to verify the client


//připojení MQTT
void connect_MQTT() {
while (WiFi.status() != WL_CONNECTED) {

    
Serial.println();
  Serial.print("Connecting to network: ");
  Serial.println(ssid);
  WiFi.disconnect(true);  //disconnect form wifi to set new wifi connection
  WiFi.mode(WIFI_STA); //init wifi mode
  esp_wifi_sta_wpa2_ent_set_identity((uint8_t *)EAP_IDENTITY, strlen(EAP_IDENTITY)); //provide identity
  esp_wifi_sta_wpa2_ent_set_username((uint8_t *)EAP_IDENTITY, strlen(EAP_IDENTITY)); //provide username --> identity and username is same
  esp_wifi_sta_wpa2_ent_set_password((uint8_t *)EAP_PASSWORD, strlen(EAP_PASSWORD)); //provide password
  esp_wpa2_config_t config = WPA2_CONFIG_INIT_DEFAULT(); //set config settings to default
  esp_wifi_sta_wpa2_ent_enable(&config); //set config settings to enable function
  WiFi.begin(ssid); //connect to wifi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    counter++;
    if (counter >= 60) { //after 30 seconds timeout - reset board
      ESP.restart();
    }
  }
  //wificlient.setCACert(test_root_ca);
  //client.setCertificate(test_client_key); // for client verification
  //client.setPrivateKey(test_client_cert);  // for client verification
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address set: ");
  Serial.println(WiFi.localIP()); //print LAN IP

  }
  if (client.connect(clientID, mqtt_username, mqtt_password)) {
    Serial.println("Connected to MQTT Broker!");
  }
  else {
    Serial.println("Connection to MQTT Broker failed...");
  }
}

//odeslání hodnot
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
//  M5.begin(false, false, true); dělá to blbosti
  pinMode(2, INPUT_PULLUP);
  Serial.begin(115200);
  delay(10);
  
  connect_MQTT();
}
void loop() {
  client.loop(); 

//pokud nepůjde wifi 30 sec tak se esp restartuje
  while (WiFi.status() != WL_CONNECTED) { //during lost connection, print dots
    delay(500);
    Serial.print(".");
    counter++;
    if (counter >= 60) { //30 seconds timeout - reset board
      ESP.restart();
    }
  }
  
//odesílání každých 10 sec
 if (millis() - minule > 10000) {
    minule = millis();
    send_MQTT(f);
    f = 0;
  }
//nastupná/sestupná hrana
  btn = digitalRead(2);
  if (btn != minule_btn) {
    if (btn == HIGH) {
      f = f + 1;
    }
  }

  minule_btn = btn;
}
