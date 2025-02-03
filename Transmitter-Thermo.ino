#include <esp_now.h>
#include <WiFi.h>

#define Thermo_pin 36
#define RED_LED 3 //used for debugging temp probe
#define GREEN_LED 22

uint8_t receiverMAC[] = {0x88, 0x13, 0xBF, 0x6F, 0xA6, 0x7C};

typedef struct struct_message {
  float temperature;
} struct_message;

struct_message myData;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("ESP-NOW Send Status: ");
  if (status == ESP_NOW_SEND_SUCCESS) {
    Serial.println("Success");
    digitalWrite(GREEN_LED, HIGH);
    delay(500);
    digitalWrite(GREEN_LED, LOW);
  } else {
    Serial.println("Fail");
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW Init Failed");
    return;
  }
  esp_now_register_send_cb(OnDataSent);

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, receiverMAC, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }

}

void loop() {
  int analogValue = analogRead(Thermo_pin);
  Serial.println(analogValue);
  float tempF = (0.0507*analogValue) + 79.567;
  float tempC = (tempF-32.00)*(5.0/9.0);

  Serial.print("Temperature: ");
  Serial.print(tempC);
  Serial.print("C  |  ");
  Serial.print(tempF);
  Serial.println("F");

  if (tempC == -127) {
    digitalWrite(RED_LED, HIGH);
    Serial.println("Sensor error detected!");
  } else {
    digitalWrite(RED_LED, LOW);
  }

  myData.temperature = tempC;
  esp_err_t result = esp_now_send(receiverMAC, (uint8_t *)&myData, sizeof(myData));

  Serial.print("ESP-NOW Send Attempt: ");
  Serial.println(result == ESP_OK ? "Success" : "Fail");

  delay(1000);
}
