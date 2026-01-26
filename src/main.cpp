#include <Arduino.h>
#include <Constants.h>
#include <Senzors.h>

TaskHandle_t Senzors;

void definePins(const int* pins, int count, bool isInput) {
    for (int i = 0; i < count; i++) {
        pinMode(pins[i], isInput ? INPUT : OUTPUT);
        //digitalWrite(pins[i], LOW); // Kazdy pin rovno nech vypne (cerpadlo je zapnute od zaciatku)

        // DEBUG
        Serial.printf("Turning off pin: %d\n", pins[i]);
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

void setup() {
    Serial.begin(115200);

    // Definovanie kazdeho pinu v robotovi (funkcia, ktora vrati inputy a outputy)
    const Pins pins = getAllPinsInRobot();
    
    definePins(pins.inputs.pins, pins.inputs.count, true);
    definePins(pins.outputs.pins, pins.outputs.count, false);

    xTaskCreatePinnedToCore(loopSenzors, "SenzorsFunc", 10000, NULL, 1, &Senzors, 0);
}

void loop() {
    
}