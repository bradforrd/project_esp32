#include "constants.h"

namespace Movement {
    enum class State {
        Idle,
        Moving
    };

    enum Direction {
        Forward,
        Backward
    };

    constexpr unsigned long MS_PER_ROTATION = 250;
    const int MOTORS[] = {
        MOTOR_FRONT_RIGHT_FORWARD, MOTOR_FRONT_RIGHT_BACKWARD,
        MOTOR_FRONT_LEFT_FORWARD, MOTOR_FRONT_LEFT_BACKWARD,
        MOTOR_REAR_RIGHT_FORWARD, MOTOR_REAR_RIGHT_BACKWARD,
        MOTOR_REAR_LEFT_FORWARD, MOTOR_REAR_LEFT_BACKWARD,
    };
    const size_t MOTORS_SIZE = sizeof(MOTORS) / sizeof(MOTORS[0]);

    State state = State::Idle;
    unsigned long endTime;

    void Move(Direction direction, float rotations) {
        // If motor is in moving state return, so loop() function won't be blocked
        if (state != State::Idle)
            return;

        unsigned long duration = rotations * MS_PER_ROTATION;
        endTime = millis() + duration;

        for (int i = 0; i < MOTORS_SIZE; i += 2) {
            switch (direction) {
                case Forward:
                    digitalWrite(MOTORS[i], HIGH); // Forward pin
                    digitalWrite(MOTORS[i + 1], LOW); // Backward pin
                    break;
                
                case Backward: 
                    digitalWrite(MOTORS[i], LOW); // Forward pin
                    digitalWrite(MOTORS[i + 1], HIGH); // Backward pin
                    break;   
            }
        }

        state = State::Moving;
        Serial.println("[DEBUG] Motors ON");
    }

    void Update() {
        if (state != State::Moving)
            return;

        if (millis() >= endTime) {
            // Stop motors
            for (int i = 0; i < MOTORS_SIZE; i++)
                digitalWrite(MOTORS[i], LOW);

            state = State::Idle;
            Serial.println("[DEBUG] Motors OFF");
        }
    }
}