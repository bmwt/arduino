#include "HX711.h"
#include "SSD1306.h"
#include "WiFi.h"
#include "PubSubClient.h"
HX711 scale;
SSD1306  display(0x3c, 5, 4);

const char* ssid = "peace";
const char* password = "hailbrak";

char* topic = "home_weightduino";
char* server = "10.1.0.42";

void callback(char* topic, byte* payload, unsigned int length) {
  // handle message arrived
}

WiFiClient wifiClient;
PubSubClient client(server, 1883, callback, wifiClient);


void setup() {
  Serial.begin(115200);
  Serial.println("Weightduino");
  display.init();
  display.flipScreenVertically();
  
  Serial.println("Initializing the scale");
  display.setFont(ArialMT_Plain_16);
  display.clear();
  display.drawString(0, 26, "Initializing Scale");
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(10, 128, String(millis()));
  display.display();

  // data pins from HX711 connected to 25 and 26 on esp.  default gain (128)
  scale.begin(25, 26);
  Serial.println("Pre-Callibration:");
  Serial.print("raw ADC reading (1): ");
  Serial.println(scale.read());
  Serial.print("raw ADC reading (average of 20)");
  Serial.println(scale.read_average(20));
  Serial.print("raw ADC minus tare (average of 5, tare not yet set): ");
  Serial.println(scale.get_value(5));
  Serial.print("raw ADC minus tare, divided by scale (average of 5, not yet set): ");
  Serial.println(scale.get_units(5), 1);
  //set scaling factor
  scale.set_scale(11366.f);
  // use the following to re-calibrate.  RAW_WEIGHT % KNOWN_WEIGHT = SCALE_FACTOR
  // scale.set_scale(1.f); 
  scale.tare();
  Serial.print("raw ADC minus tare (average of 5): ");
  Serial.println(scale.get_value(5));
  Serial.print("raw ADC minus tare, divided by scale (average of 5): ");
  Serial.println(scale.get_units(5), 1);
  Serial.println("Connecting to wifi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
       delay(500);
       Serial.print(".");
  }

}

void displayWeight(float weight) {
   // we only care about 1 digit after decimal
   String weightString = String(weight, 1);
   String displayString = weightString + " lbs";
   display.clear();
   display.setTextAlignment(TEXT_ALIGN_LEFT);
   display.setFont(ArialMT_Plain_16);
   display.drawString(0, 0, "Weightduino 0.1");
   display.setFont(ArialMT_Plain_24);
   display.drawString(0, 18, displayString);
   display.display();
   Serial.println(displayString);
   
}

void loop() {

   
  scale.power_up();
  float weight = scale.get_units(20);
  displayWeight(abs(weight));
  if (weight > 20)
  { 
    float weight_record = scale.get_units(20);
    Serial.print("I would record: ");
    Serial.println(weight_record);
    if (!client.connected())
      {
      //client.connect("clientID", "mqtt_username", "mqtt_password");
      client.connect("home-weightduino");
      client.publish("home/weightduino/alive", "I'm alive!");
      }
    client.connect("home-weightduino");
    client.publish("home/weightduino/weight", String(weight_record).c_str(), true);
    displayWeight(abs(weight_record));
    delay(10000);
  }
  
  scale.power_down();             // put the ADC in sleep mode
  delay(1000);
}


