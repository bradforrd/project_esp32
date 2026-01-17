#pragma once
#include <Arduino.h>

struct ProperData {
    const int* data;
    size_t size;
};

// Senzors
#define FireLeft 25
#define FireRight 26

#define DistanceInput 35
#define DistanceOutput 34

#define FallInput 33

// Motors
#define MOTOR_FRONT_RIGHT_FORWARD 12
#define MOTOR_FRONT_RIGHT_BACKWARD 13
#define MOTOR_FRONT_LEFT_FORWARD 14
#define MOTOR_FRONT_LEFT_BACKWARD 27

#define MOTOR_REAR_RIGHT_FORWARD 17
#define MOTOR_REAR_RIGHT_BACKWARD 16
#define MOTOR_REAR_LEFT_FORWARD 19
#define MOTOR_REAR_LEFT_BACKWARD 18

// Camera
#define CameraHorizontal 22
#define CameraVertical 21

// Pump
#define Pump 15

namespace Constants {
    static const int OUTPUTS[] = {
        MOTOR_FRONT_RIGHT_FORWARD, MOTOR_FRONT_RIGHT_BACKWARD,
        MOTOR_FRONT_LEFT_FORWARD, MOTOR_FRONT_LEFT_BACKWARD,
        MOTOR_REAR_RIGHT_FORWARD, MOTOR_REAR_RIGHT_BACKWARD,
        MOTOR_REAR_LEFT_FORWARD, MOTOR_REAR_LEFT_BACKWARD,
        Pump, DistanceOutput
    };

    static const int INPUTS[] = {
        FireLeft, FireRight, DistanceInput,
        FallInput,
        CameraHorizontal, CameraVertical
    };

    ProperData GetOutputs() {
        return { OUTPUTS, sizeof(OUTPUTS) / sizeof(OUTPUTS[0]) };
    }

    ProperData GetInputs() {
        return { INPUTS, sizeof(INPUTS) / sizeof(INPUTS[0]) };
    }
}