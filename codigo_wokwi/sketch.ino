#include <PubSubClient.h>
#include <EspMQTTClient.h>
#include <ArduinoJson.h>
#include <DHTesp.h>

#define DHT_PIN 15

float controle_temp;

DHTesp dhtSensor;
DynamicJsonDocument dados(1024);

EspMQTTClient client(
  "Wokwi-GUEST", 
  "",             
  "mqtt.tago.io", 
  "Default",      
  "cc545dc0-340f-4b79-a01f-03cd9165b019",
  "Esp8266"     
);

void mensagemRecebida(const String &topico) {}

void onConnectionEstablished() {
  client.subscribe("topic", mensagemRecebida);
}

void setup() {
  Serial.begin(115200);
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);
}

void loop() {
  client.loop();

  TempAndHumidity data = dhtSensor.getTempAndHumidity();
  float temp = data.temperature;

  String status;

  if (temp < 20) {
    status = "Baixa";
  } else if (temp >= 20 && temp <= 26) {
    status = "Normal";
  } else {
    status = "Alta";
  }

  dados[0]["variable"] = "Temperatura";
  dados[0]["value"] = temp;
  dados[0]["unit"] = "°C";
  dados[0]["status"] = status;

  String dadosJson;
  serializeJson(dados, dadosJson);

  if (controle_temp != temp) {
    Serial.println(dadosJson);
    client.publish("temperaturaAlterada", dadosJson);
    controle_temp = temp;
  }

}