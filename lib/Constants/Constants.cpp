#include <Constants.h>

// Vsetky inputy na robotovi (data zobrane z Constants.h)
constexpr int inputs[] = { FireLeft, FireRight, DistanceEcho, Fall, CameraHorizontal, CameraVertical };

// Vsetky outputy na robotovi (data zobrane z Constants.h)
constexpr int outputs[] = {
    FrontRightForward, FrontRightBackward, FrontLeftForward, FrontLeftBackward,
    RearRightForward, RearRightBackward, RearLeftForward, RearLeftBackward,
    Pump, DistanceTrig
};

Pins getAllPinsInRobot() {
    return { 
        inputs, sizeof(inputs) / sizeof(inputs[0]), 
        outputs, sizeof(outputs) / sizeof(outputs[0]) 
    };
}