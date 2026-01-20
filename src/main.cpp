#include <Arduino.h>
#include <Constants.h>

// Funkcia, ktora zadefinuje kazdy pin v robotovi
template <size_t N>
void definePins(const int (&pins)[N], bool isInput) {
  for (int pin : pins)
    pinMode(pin, isInput ? INPUT : OUTPUT);
}

void setup() {
  // Definovanie kazdeho pinu v robotovi (input | output)
  auto [ inputs, outputs ] = GetAllPinsInRobot();

  definePins(inputs, true);
  definePins(outputs, false);
}

void loop() {
  
}