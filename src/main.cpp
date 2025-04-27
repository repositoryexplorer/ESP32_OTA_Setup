#include <WiFi.h>
#include <ArduinoOTA.h>

const char* ssid = "TwojaSiecWiFi";       // <-- wpisz swoją sieć
const char* password = "TwojeHasloWiFi";   // <-- wpisz hasło

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Błąd połączenia. Reset...");
    delay(5000);
    ESP.restart();
  }

  // --- Konfiguracja OTA ---
  ArduinoOTA.setHostname("ESP32-OTA"); // zmień jeśli chcesz

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH)
      type = "Firmware";
    else // U_SPIFFS
      type = "Filesystem";

    Serial.println("Start OTA: " + type);
  });

  ArduinoOTA.onEnd([]() {
    Serial.println("\nKoniec OTA");
  });

  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Postęp: %u%%\r", (progress * 100) / total);
  });

  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Błąd [%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Błąd autoryzacji");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Błąd rozpoczęcia");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Błąd połączenia");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Błąd odbioru");
    else if (error == OTA_END_ERROR) Serial.println("Błąd zakończenia");
  });

  ArduinoOTA.begin();
  Serial.println("OTA gotowe!");
  Serial.print("IP urządzenia: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  ArduinoOTA.handle();
}
