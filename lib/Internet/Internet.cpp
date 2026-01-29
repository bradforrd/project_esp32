#include <Internet.h>

// Vytvorenie AP
void createAP() {
    Serial.println("Creating access point...");

    WiFi.softAP(Wifi_SSID, Wifi_Password);
    IPAddress IP = WiFi.softAPIP();
    
    Serial.print("AP IP address: ");
    Serial.println(IP);
}

// Funkcia, ktora pripoji ESP na WiFi
void connectToWiFi() {
    WiFi.mode(WIFI_STA); // nastavenie wifi modu do sta
    WiFi.disconnect(); // odpoji sa z wifi, pre lepsi scan

    Serial.println("Scanning networks");
    int networks = WiFi.scanNetworks();

    // Ak sa nenasli ziadne siete, tak vytvori AP
    if (networks == 0) {
        Serial.println("No networks found.");
        createAP();
    } else {
        Serial.print(networks);
        Serial.println(" networks found");

        for (int i = 0; i < networks; i++) {
            if (WiFi.SSID(i) == Wifi_SSID) {
                WiFi.begin(Wifi_SSID, Wifi_Password);
                Serial.println("\nConnecting");

                while (WiFi.status() != WL_CONNECTED) {
                    Serial.print(".");
                    delay(100);
                }

                Serial.println("\nConnected to the WiFi network");
                Serial.print("Local ESP32 IP: ");
                Serial.println(WiFi.localIP());

                return;
            }
        }

        createAP();
    }
}