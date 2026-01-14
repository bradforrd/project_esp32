#include <Arduino.h>
#include "constants.h"
#include "movement.h"

void DefinePins(ProperData pins, bool input) {
    for (int i = 0; i < pins.size; i++)
      pinMode(pins.data[i], input ? INPUT : OUTPUT);
}

// Get rid of issues (electronics)
void FixStartIssues(ProperData pins) {
  for (int i = 0; i < pins.size; i++)
    digitalWrite(pins.data[i], LOW);
}

void setup() {
  // Define every pin in robot
  const ProperData inputs = Constants::GetInputs();
  const ProperData outputs = Constants::GetOutputs();

  DefinePins(inputs, true);
  DefinePins(outputs, false);

  const int _issues[] = { Pump, MOTOR_FRONT_LEFT_FORWARD };
  const ProperData issues = { _issues, sizeof(_issues) / sizeof(_issues[0]) };

  FixStartIssues(issues);
}

void loop() {
  Movement::Update();
}