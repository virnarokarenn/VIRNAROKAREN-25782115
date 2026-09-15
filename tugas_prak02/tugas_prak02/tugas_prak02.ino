#include <DHT.h>

#define DHTPIN D7
#define DHTTYPE DHT22

const byte ldrPin = A0;
const byte relayPin = D6;
const byte ledPin = D1;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);

  pinMode(relayPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  // Kondisi awal: Relay dan LED mati
  digitalWrite(relayPin, HIGH);
  digitalWrite(ledPin, LOW);

  dht.begin();
}

void loop() {
  // Membaca sensor
  int ldrValue = analogRead(ldrPin);
  float temperature = dht.readTemperature();

  // Mengecek apakah DHT berhasil dibaca
  if (isnan(temperature)) {
    Serial.println("Gagal membaca sensor DHT!");
    delay(2000);
    return;
  }

  // Menampilkan hasil sensor
  Serial.print("Suhu: ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Intensitas Cahaya (ADC): ");
  Serial.println(ldrValue);

  // Rule Engine
  // Relay aktif jika suhu > 34 C ATAU LDR < 300
  if (temperature > 34 || ldrValue < 300) {

    // Relay Active-Low
    digitalWrite(relayPin, LOW);
    digitalWrite(ledPin, HIGH);

    Serial.println("Peringatan: Aktuator Aktif!");

  } else {

    // Kondisi aman
    digitalWrite(relayPin, HIGH);
    digitalWrite(ledPin, LOW);

    Serial.println("Kondisi Aman");
  }

  Serial.println("----------------------");

  delay(2000);
}