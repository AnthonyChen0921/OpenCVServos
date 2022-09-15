#include <WiFi.h>
#include <PubSubClient.h>
#include <ESP32Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position


// Replace the next variables with your SSID/Password combination
const char* ssid = "Chika";
const char* password = "888666zhang";

// Add your MQTT Broker IP address, example:
//const char* mqtt_server = "192.168.4.52";
const char* mqtt_server = "192.168.4.52";

WiFiClient espClient;
PubSubClient client(espClient);
//long lastMsg = 0;
char msg[50];
int value = 0;
long lastMsg = 0;
const char* device_name = "ESP32";
const char* myTopic = "Led";

float temperature = 24;
float humidity = 55;

// LED Pin
const int ledPin = 4;
const int led2Pin = 18;
bool flash = true;
// Servo Pin
const int ServoPin = 5;

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  pinMode(ledPin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  myservo.attach(ServoPin);  
}

void setup_wifi() {
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    attempts++;
    if(attempts > 3){
      ESP.restart();
    }
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // Feel free to add more if statements to control more GPIOs with MQTT
  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off". 
  // Changes the output state according to the message
  if (String(topic) == myTopic) {
    Serial.print("Changing output to ");
    if(messageTemp == "on"){
      client.publish(myTopic,"Message Received at ESP32");
      Serial.println("on");
      digitalWrite(ledPin, HIGH);
      for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position
      }
      digitalWrite(ledPin, LOW);
    }
    else if(messageTemp == "off"){
      Serial.println("off");
      digitalWrite(ledPin, HIGH);
      for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position
      }
      digitalWrite(ledPin, LOW);
    }
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(device_name)) {
      Serial.println("connected");
      // Subscribe
      client.subscribe(myTopic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  long now = millis();
  if (now - lastMsg > 1000) {
    lastMsg = now;
    if(flash){
      digitalWrite(led2Pin, HIGH);
      flash = !flash;
    } else {
      digitalWrite(led2Pin, LOW);
      flash = !flash;
    }
  }
  //String tesmpString = "Hello world";
  /*  long now = millis();
  if (now - lastMsg > 5000) {
    lastMsg = now;
    Serial.print("Temperature: ");
    Serial.println(tempString);
    client.publish("esp32/temperature", tempString);
    Serial.print("Humidity: ");
    Serial.println(humString);
    client.publish("esp32/humidity", humString);
  } */
  
}
