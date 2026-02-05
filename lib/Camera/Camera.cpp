#include <Camera.h>

// Aktualne uhly
float panAngle = 90; // horizontal
float tiltAngle = 90; // vertical

/**
 * @param moveType "vertical" | "horizontal" - Ako sa kamera bude otacat (vertikalne alebo horizontalne)
 * @param angle O kolko stupnov sa ma otocit
 */
void moveCamera(Servo servo, String moveType, float angle) {
    if (moveType == "horizontal") {
        panAngle += angle;
        panAngle = constrain(panAngle, 0, 180); // panAngle nemoze byt menej ako 0 a viac ako 180
        servo.write(panAngle);
    }

    else if (moveType == "vertical") {
        tiltAngle += angle;
        tiltAngle = constrain(tiltAngle, 50, 120);
        servo.write(tiltAngle);
    }
}