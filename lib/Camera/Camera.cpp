#include <Camera.h>

// Aktualne uhly
float panAngle = 90; // horizontal
float tiltAngle = 20; // vertical

/**
 * @param moveType "vertical" | "horizontal" - Ako sa kamera bude otacat (vertikalne alebo horizontalne)
 * @param angle O kolko stupnov sa ma otocit
 */
void moveCamera(Servo servo, String moveType, float angle) {
    if (moveType == "horizontal") {
        panAngle += angle;
        panAngle = constrain(panAngle, 60, 135);
        servo.write(panAngle);
    }

    else if (moveType == "vertical") {
        tiltAngle += angle;
        tiltAngle = constrain(tiltAngle, 0, 60);
        servo.write(tiltAngle);
    }
}