
#define Thermo_pin 36 // ESP32 pin GIOP36 (ADC0)
#define BUZZ_Pin 23

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);

  pinMode(BUZZ_Pin, OUTPUT);
  digitalWrite(BUZZ_Pin, LOW);

  // set the ADC attenuation to 11 dB (up to ~3.3V input)
  analogSetAttenuation(ADC_11db);
}

void loop() {
  // reads the input on analog pin (value between 0 and 4095)
  int analogValue = analogRead(Thermo_pin);
  float tempF = (0.0507*analogValue) + 84.567;
  float tempC = (tempF-32.00)*(5.0/9.0);
  Serial.print("Analog Value = ");
  Serial.println(analogValue);
  Serial.print("Temp F = ");
  Serial.println(tempF);
  Serial.print("Temp C = ");
  Serial.println(tempC);

  if (tempF >= 158) {
   digitalWrite(BUZZ_Pin, HIGH);
   delay(1000);
   digitalWrite(BUZZ_Pin, LOW);
   delay(500);
  }

  delay(1000);
}