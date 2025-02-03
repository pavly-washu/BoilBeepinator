#include <esp_now.h>
#include <WiFi.h>

#define VIBRATION_MOTOR 23
#define RED_LED 3
#define GREEN_LED 22

typedef struct struct_message {
  float temperature;
} struct_message;

struct_message incomingData;

void OnDataRecv(const esp_now_recv_info_t *info, const uint8_t *data, int len) {
  Serial.println("ESP-NOW Data Received!");


  Serial.print("Received data from MAC: ");
  for (int i = 0; i < 6; i++) {
    Serial.printf("%02X", info->src_addr[i]);
    if (i < 5) Serial.print(":");
  }
  Serial.println();

  memcpy(&incomingData, data, sizeof(incomingData));

  Serial.print("Temperature Received: ");
  Serial.println(incomingData.temperature);


  digitalWrite(GREEN_LED, HIGH);
  delay(500); 
  digitalWrite(GREEN_LED, LOW);


  if (incomingData.temperature == 79.567) {
    Serial.println("Sensor error detected! :(");
    digitalWrite(RED_LED, HIGH);
  } else {
    digitalWrite(RED_LED, LOW);
  }


  if (incomingData.temperature >= 93) {
    Serial.println("High Temp Detected! Motor ON");
    digitalWrite(VIBRATION_MOTOR, HIGH);
    delay(2000);
    digitalWrite(VIBRATION_MOTOR, LOW);
    delay(1000);
    Serial.println("Motor OFF!!");
  } else {
    Serial.println("Temperature is below 100°C. No vibration.");
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  pinMode(VIBRATION_MOTOR, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  
  digitalWrite(VIBRATION_MOTOR, LOW);
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW Init Failed :(");
    return;
  }
  Serial.println("ESP-NOW Initialized :)");

  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {

}
