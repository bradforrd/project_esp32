#include <Arduino.h>
#include <Constants.h>

void definePins(const int* pins, bool isInput) {
    int count = sizeof(pins) / sizeof(pins[0]);

    for (int i = 0; i < count; i++)
        pinMode(pins[i], isInput ? INPUT : OUTPUT);
}

void setup() {
  // Definovanie kazdeho pinu v robotovi (funkcia, ktora vrati inputy a outputy)
  const Pins pins = getAllPinsInRobot();
  
  definePins(pins.inputs, true);
  definePins(pins.outputs, false);
}

void loop1() {
    Serial.printf("Hey, I'm looping 1");
}

void loop() {
    Serial.printf("Hey, I'm main looping");
}