#include <Arduino.h>
#include "Constants.h"

// Vsetky inputy na robotovi (data zobrane z Constants.h)
constexpr int inputs[] = { FireLeft, FireRight, DistanceEcho, Fall, CameraHorizontal, CameraVertical };

// Vsetky outputy na robotovi (data zobrane z Constants.h)
constexpr int outputs[] = {
    FrontRightForward, FrontRightBackward, FrontLeftForward, FrontLeftBackward,
    RearRightForward, RearRightBackward, RearLeftForward, RearLeftBackward,
    Pump, DistanceTrig
};

// CHANGE!!!

struct PinData {
    const int* inputs; 
    const int* outputs;
};

PinData GetAllPinsInRobot() {
    return { inputs, outputs };
}