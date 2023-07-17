#include <HardwareSerial.h>

#define RX_PIN 26
#define TX_PIN 27
#define LedPin 12
#define ModemPower 23

HardwareSerial gsmSerial(1);

void setup()
{
  Serial.begin(115200);
  while (!Serial) {} // Bekleme
  
  pinMode(ModemPower, OUTPUT);
  digitalWrite(ModemPower, HIGH); // Modem güç kaynağını etkinleştir
  pinMode(LedPin, OUTPUT);
  digitalWrite(LedPin, LOW);

  gsmSerial.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);
  delay(1000);
  gsmSerial.println("AT");
  delay(1000);
  gsmSerial.println("AT+CLIP=1"); // Gelen çağrı numarasını ekrana yazdır
  delay(1000);
  gsmSerial.println("AT+CPAS=2"); // Otomatik çağrı kabul (2 saniye sonra açıyor direkt açmak için ATA)
  delay(1000);
  gsmSerial.println("AT+DDET=1"); // DTMF ton algılama özelliğini etkinleştir
  delay(1000);
  gsmSerial.println("+DTMF: 2");

  
}

void loop()
{
  
  
  while (gsmSerial.available())
  {
    char c = gsmSerial.read();
    Serial.write(c);
    if (c == '*')
    {
      digitalWrite(LedPin, HIGH); // Ledi yak
    }
    if (c == '#')
    {
      digitalWrite(LedPin, LOW); // Ledi söndür
    }
  }
}
