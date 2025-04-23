#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MPU6050.h>

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

// Replace with your network credentials
const char* ssid = "Galaxy A22 5G";   //put your wifi's SSID here
const char* password = "edvf6460";    //[put your wifi's passworrf here.

// Initialize Telegram BOT
//using botFather
#define BOTtoken "7016459933:AAHxWryG-1s7HkVQIN_zRvf1kVgKVeeMBGM"  // your Bot Token (Get from Botfather)

// Use @myidbot to find out the chat ID of an individual or a group
// Also note that you need to click "start" on a bot before it can
// message you
#define CHAT_ID "1399335614"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

#define SDA_PIN 23
#define SCL_PIN 22

Adafruit_MPU6050 mpu;

void setup() {
  Serial.begin(115200);
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);

  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  bot.sendMessage(CHAT_ID, "Bot started up", "");
  
  pinMode(21,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,INPUT);

  
  Wire.begin(SDA_PIN, SCL_PIN);
  
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  float ax = a.acceleration.x;
  float ay = a.acceleration.y;
  float az = a.acceleration.z;

  float gx = g.gyro.x;
  float gy = g.gyro.y;
  float gz = g.gyro.z;
  int value = digitalRead(5);

  Serial.print("AccX: "); Serial.print(ax);
  Serial.print("\tAccY: "); Serial.print(ay);
  Serial.print("\tAccZ: "); Serial.print(az);
  Serial.print("\tGyroX: "); Serial.print(gx);
  Serial.print("\tGyroY: "); Serial.print(gy);
  Serial.print("\tGyroZ: "); Serial.println(gz);
  Serial.println(value);
  delay(100);
  if(ax<-5 || ax>5 || ay<-6 || ay>6){
    digitalWrite(21,HIGH);
    digitalWrite(4,HIGH);
    bot.sendMessage(CHAT_ID, "Fall Detected");
    Serial.println("Fall Detected! ");

  }
  else if(value == HIGH)
  {
    bot.sendMessage(CHAT_ID, "🔴🔴🔴Emergency Alert!");
    Serial.println("Emergency Alert!");
  }
  else {    digitalWrite(21,LOW);
           digitalWrite(4,LOW);

}
}
