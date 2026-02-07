#include <Arduino.h>
#include <Constants.h>
#include <Senzors.h>
#include <Motors.h>
#include <Internet.h>
#include <Servo.h>
#include <Camera.h>
#include "esp_camera.h"

TaskHandle_t Senzors;
TaskHandle_t Motors;

Servo servoPan;
Servo servoTilt;

bool pumpState = false;

WebServer server(80);

#define PWDN_GPIO_NUM 32
#define RESET_GPIO_NUM -1
#define XCLK_GPIO_NUM 0
#define SIOD_GPIO_NUM 26
#define SIOC_GPIO_NUM 27
#define Y9_GPIO_NUM 35
#define Y8_GPIO_NUM 34
#define Y7_GPIO_NUM 39
#define Y6_GPIO_NUM 36
#define Y5_GPIO_NUM 21
#define Y4_GPIO_NUM 19
#define Y3_GPIO_NUM 18
#define Y2_GPIO_NUM 5
#define VSYNC_GPIO_NUM 25
#define HREF_GPIO_NUM 23
#define PCLK_GPIO_NUM 22

camera_config_t config;

void initCamera() {
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;

    config.pin_d0 = Y2_GPIO_NUM;
    config.pin_d1 = Y3_GPIO_NUM;
    config.pin_d2 = Y4_GPIO_NUM;
    config.pin_d3 = Y5_GPIO_NUM;
    config.pin_d4 = Y6_GPIO_NUM;
    config.pin_d5 = Y7_GPIO_NUM;
    config.pin_d6 = Y8_GPIO_NUM;
    config.pin_d7 = Y9_GPIO_NUM;

    config.pin_xclk = XCLK_GPIO_NUM;
    config.pin_pclk = PCLK_GPIO_NUM;
    config.pin_vsync = VSYNC_GPIO_NUM;
    config.pin_href = HREF_GPIO_NUM;
    config.pin_sscb_sda = SIOD_GPIO_NUM;
    config.pin_sscb_scl = SIOC_GPIO_NUM;
    config.pin_pwdn = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;

    config.xclk_freq_hz = 20000000;
    config.pixel_format = PIXFORMAT_JPEG;

    config.frame_size = FRAMESIZE_VGA;   // 640x480
    config.jpeg_quality = 10;            // 10–15 je ideál
    config.fb_count = 2;

    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK) {
        Serial.printf("Camera init failed with error 0x%x\n", err);
        return;
    }
}

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
    .controller {
        position: absolute;
        top: 55%; left: 52%;
        transform: translate(-50%, -50%);
        img { transform: scale(1.4); z-index: 0; }
        .invisible {
            outline: solid #fff 1px;
            position: absolute;
            width: 50px; height: 40px;
            /*background: none; // DELETE !!!
            border: none;*/
            
        }
        .cam-container {
            position: absolute;
            background: #ffffff;
            top: 14%; left: 14%;
            width: 645px; height: 403px;
            img { width: 100%; height: 100%; }
        }
    }
</style>
<body>
    <div class="nav-title">
        <h1>ESP32 robot</h1>
        <p>S funkciou hasenia plameňa</p>
    </div>
    <div class="controller">
        <img src="https://i.postimg.cc/RFCkPJG2/controller.png" />
        <div class="right-side">
            <button onclick="fetch('motorForward')" id="up" class="invisible" style="clip-path: polygon(49% 100%, 100% 38%, 100% 0, 0 0, 0% 38%); bottom: 39%; right: 0%;"></button>
            <button onclick="fetch('motorBackward')" id="down" class="invisible" style="clip-path: polygon(50% 0%, 100% 51%, 100% 100%, 0 100%, 0 52%); bottom: 29%; right: 0%;"></button>
            <button onclick="fetch('motorRight')" id="right" class="invisible" style="clip-path: polygon(16% 51%, 55% 0, 100% 0, 100% 100%, 57% 100%); bottom: 34%; right: -2%;"></button>
            <button onclick="fetch('motorLeft')" id="left" class="invisible" style="clip-path: polygon(74% 51%, 39% 0, 0 0, 0 100%, 44% 100%); bottom: 34%; right: 2%;"></button>
        </div>
        <div class="left-side">
            <button onclick="fetch('cameraUp')" id="up" class="invisible" style="clip-path: polygon(49% 100%, 100% 38%, 100% 0, 0 0, 0% 38%); bottom: 39%; left: -8.5%;"></button>
            <button onclick="fetch('cameraDown')" id="down" class="invisible" style="clip-path: polygon(50% 0%, 100% 51%, 100% 100%, 0 100%, 0 52%); bottom: 29%; left: -8.5%;"></button>
            <button onclick="fetch('cameraRight')" id="right" class="invisible" style="clip-path: polygon(16% 51%, 55% 0, 100% 0, 100% 100%, 57% 100%); bottom: 34%; left: -6%;"></button>
            <button onclick="fetch('cameraLeft')" id="left" class="invisible" style="clip-path: polygon(74% 51%, 39% 0, 0 0, 0 100%, 44% 100%); bottom: 34%; left: -10.5%;"></button>
        </div>
        <div class="pump-button">
            <button onclick="fetch('pump')" class="invisible" style="clip-path: circle(50% at 50% 50%); top: 23%; left: -7%; transform: scale(1.6);"></button>
            <button onclick="fetch('pump')" class="invisible" style="clip-path: circle(50% at 50% 50%); top: 23%; left: 94%; transform: scale(1.6);"></button>
        </div>
        <div class="cam-container">
            <!-- CAM VIEW -->
            <img src="/stream" />
        </div>
    </div>
</body>
</html>

)rawliteral";

  server.send(200, "text/html", page);
}

void handleStream() {
    WiFiClient client = server.client();

    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: multipart/x-mixed-replace; boundary=frame");
    client.println();

    while (client.connected()) {
        camera_fb_t *fb = esp_camera_fb_get();
        if (!fb) continue;

        client.println("--frame");
        client.println("Content-Type: image/jpeg");
        client.printf("Content-Length: %u\n\n", fb->len);
        client.write(fb->buf, fb->len);
        client.println();

        esp_camera_fb_return(fb);
        delay(30); // 30 FPS
    }
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

void togglePump() {
    server.send(200, "text/plain", "OK");
    pumpState = !pumpState;

    digitalWrite(Pump, pumpState ? HIGH : LOW);
}

void setup() {
    Serial.begin(115200);

    // Definovanie kazdeho pinu v robotovi (funkcia, ktora vrati inputy a outputy)
    const Pins pins = getAllPinsInRobot();
    
    definePins(pins.inputs.pins, pins.inputs.count, true);
    definePins(pins.outputs.pins, pins.outputs.count, false);

    // Serva na kameru
    servoPan.attach(CameraHorizontal);
    servoTilt.attach(CameraVertical);

    // Pripojenie ESP do WiFi / vytvorenie AP
    connectToWiFi();

    initCamera();

    // xTaskCreatePinnedToCore(loopSenzors, "SenzorsFunc", 10000, NULL, 1, &Senzors, 0);
    // xTaskCreatePinnedToCore(loopMotors, "MotorsFunc", 10000, NULL, 1, &Motors, 1);

    server.on("/", handleRoot);

    server.on("/motorForward", []() { toggleMotors(Forward); });
    server.on("/motorLeft", []() { toggleMotors(Left); });
    server.on("/motorRight", []() { toggleMotors(Right); });
    server.on("/motorBackward", []() { toggleMotors(Backward); });

    server.on("/cameraUp", []() { moveCamera(servoTilt, "vertical", -10); });
    server.on("/cameraDown", []() { moveCamera(servoTilt, "vertical", 10); });
    server.on("/cameraRight", []() { moveCamera(servoPan, "horizontal", -25); });
    server.on("/cameraLeft", []() { moveCamera(servoPan, "horizontal", 25); });

    server.on("/pump", []() { togglePump(); });

    server.on("/stream", HTTP_GET, handleStream);

    server.begin();
}

void loop() {
    server.handleClient();
}