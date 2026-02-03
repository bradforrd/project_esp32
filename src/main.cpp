#include <Arduino.h>
#include <Constants.h>
#include <Senzors.h>
#include <Motors.h>
#include <Internet.h>
#include <LittleFS.h>

TaskHandle_t Senzors;
TaskHandle_t Motors;

WebServer server(80);

void handleRoot() {
  String page = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<title>AC Motor</title>
<style>
body { font-family: Arial; text-align: center; margin-top: 50px; }
button { font-size: 30px; padding: 20px 40px; }
</style>
</head>
<body>
<h1>Ovládanie AC motora</h1>
<button onclick="fetch('/motors')">SPUSTIŤ</button>
<button onclick="fetch('/off')">STOP</button>
</body>
</html>
)rawliteral";

  server.send(200, "text/html", page);
}

void loopSenzors(void * params) {
    while (true) {
        // Vzdialenost (predny senzor)
        float distance = getDistance();
        Serial.printf("Distance: %.2f cm\n", distance);
        
        // Dolny senzor (pad)
        Serial.println(isGrounded() ? "On ground" : "Falldown detected");

        // Plamen
        String side;
        if (detectedFlame(side))
            Serial.println("Flame detected on side: " + side);
        else
            Serial.println("Flame was not detected!");

        vTaskDelay(pdMS_TO_TICKS(1000)); // nemoze tu byt delay(), pretoze to je thread (vlakno)
    }
}

/*
void loopMotors(void * params) {
    while (true) {
        
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
*/

void definePins(const int* pins, int count, bool isInput) {
    for (int i = 0; i < count; i++) {
        pinMode(pins[i], isInput ? INPUT : OUTPUT);
        //digitalWrite(pins[i], LOW); // Kazdy pin rovno nech vypne (cerpadlo je zapnute od zaciatku)

        // DEBUG
        Serial.printf("Turning off pin: %d\n", pins[i]);
    }
}

void toggleMotors() {
    move(Forward);
}

void setup() {
    Serial.begin(115200);

    if(!LittleFS.begin()){
        Serial.println("An Error has occurred while mounting LittleFS");
        return;
    }

    // Definovanie kazdeho pinu v robotovi (funkcia, ktora vrati inputy a outputy)
    const Pins pins = getAllPinsInRobot();
    
    definePins(pins.inputs.pins, pins.inputs.count, true);
    definePins(pins.outputs.pins, pins.outputs.count, false);

    // Pripojenie ESP do WiFi / vytvorenie AP
    connectToWiFi();

    // xTaskCreatePinnedToCore(loopSenzors, "SenzorsFunc", 10000, NULL, 1, &Senzors, 0);
    // xTaskCreatePinnedToCore(loopMotors, "MotorsFunc", 10000, NULL, 1, &Motors, 1);

    server.on("/", handleRoot);
    server.on("/motors", toggleMotors);

    server.begin();
}

void loop() {
    server.handleClient();
}