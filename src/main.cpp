#include <Arduino.h>
#include <Constants.h>
#include <Senzors.h>
#include <Motors.h>
#include <Internet.h>

TaskHandle_t Senzors;
TaskHandle_t Motors;

WebServer server(80);

void handleRoot() {
  String page = R"rawliteral(

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="preconnect" href="https://fonts.googleapis.com">
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
    <link href="https://fonts.googleapis.com/css2?family=Inter:ital,opsz,wght@0,14..32,100..900;1,14..32,100..900&display=swap" rel="stylesheet">
    <title>JUBAR BOT</title>
</head>
<style>
    html {
        background: linear-gradient(135deg, #1e293b, #334155);
        width: 100%;
        height: 100%;
    }
    body {
        color: #ffffff;
        padding: 0 150px;
    }
    * {
        margin: 0;
        padding: 0;
        box-sizing: border-box;
        font-family: Inter;
    }
    .nav-title {
        display: flex;
        align-items: center;
        justify-content: center;
        flex-direction: column;
        font-size: 30px;
        width: fit-content;
        margin: 30px auto;
        padding: 15px;
        position: relative;
        p { font-size: 25px; color: #a8a8a8; }
    }
    .nav-title::after {
        content: '';
        position: absolute;
        bottom: 0px;
        left: 50%;
        height: 2px;
        width: 80%;
        background: linear-gradient(#2dd4bf, #34d399);
        transform: translateX(-50%);
        filter: drop-shadow(0 0 10px #2dd4bf);
    }
    .nav-title::before {
        content: '';
        position: absolute;
        top: 0; left: 0;
        height: 10px;
        width: 10px;
        background: linear-gradient(#2dd4bf, #34d399);
        filter: drop-shadow(0 0 10px #2dd4bf);
        clip-path: polygon(0 0, 0% 100%, 100% 0%);
    }
    .controls {
        border: solid #34d399 1px;
        width: 550px;
        padding: 10px 20px;
        background: #34d39925;
        border-radius: 7px;
        box-shadow: 0 0 50px #34d39925;
        h1 { color: #2dd4bf; filter: drop-shadow(0 0 30px #2dd4bf); };
        .container {
            display: flex;
            flex-direction: column;
            gap: 10px;
            align-items: center;
            justify-content: center;
            margin: 10px 0;
            .control-button {
                color: #2dd4bf;
                background-color: #2dd4bf50;
                border: none;
                padding: 15px 0;
                font-size: 22px;
                cursor: pointer;
                transition: all 0.3s;
                width: 100%;
            }
            .control-button:not(div) { width: 75%; }
            .control-button:hover { background-color: #2dd4bf75; transform: scale(1.05); }
            div { display: flex; gap: 10px; width: 100%; }
        }
    }
</style>
<body>
    <div class="nav-title">
        <h1>JUBAR BOT</h1>
        <p>Jednoduchý hasičský robot</p>
    </div>
    <div class="controls">
        <h1>Ovládanie</h1>
        <div class="container">
            <button class="control-button" onclick="fetch('/motorForward')">Vpred</button>
            <div>
                <button class="control-button" onclick="fetch('/motorLeft')">Vľavo</button>
                <button class="control-button" onclick="fetch('/motorRight')">Vpravo</button>
            </div>
            <button class="control-button" onclick="fetch('/motorBackward')">Dozadu</button>
        </div>
    </div>
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

void definePins(const int* pins, int count, bool isInput) {
    for (int i = 0; i < count; i++) {
        pinMode(pins[i], isInput ? INPUT : OUTPUT);
        //digitalWrite(pins[i], LOW); // Kazdy pin rovno nech vypne (cerpadlo je zapnute od zaciatku)

        // DEBUG
        Serial.printf("Turning off pin: %d\n", pins[i]);
    }
}

void toggleMotors(MotorDirection direction) {
    server.send(200, "text/plain", "OK");
    
    move(direction);
}

void setup() {
    Serial.begin(115200);

    // Definovanie kazdeho pinu v robotovi (funkcia, ktora vrati inputy a outputy)
    const Pins pins = getAllPinsInRobot();
    
    definePins(pins.inputs.pins, pins.inputs.count, true);
    definePins(pins.outputs.pins, pins.outputs.count, false);

    // Pripojenie ESP do WiFi / vytvorenie AP
    connectToWiFi();

    // xTaskCreatePinnedToCore(loopSenzors, "SenzorsFunc", 10000, NULL, 1, &Senzors, 0);
    // xTaskCreatePinnedToCore(loopMotors, "MotorsFunc", 10000, NULL, 1, &Motors, 1);

    server.on("/", handleRoot);
    server.on("/motorForward", []() { toggleMotors(Forward); });
    server.on("/motorLeft", []() { toggleMotors(Left); });
    server.on("/motorRight", []() { toggleMotors(Right); });
    server.on("/motorBackward", []() { toggleMotors(Backward); });

    server.begin();
}

void loop() {
    server.handleClient();
}