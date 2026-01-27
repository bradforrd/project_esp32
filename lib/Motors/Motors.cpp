#include <Motors.h>

// Predne motory (piny, ktore ked su zapnute tak motor sa toci dopredu)
constexpr int forwardMotors[] = {
    FrontRightForward, FrontLeftForward,
    RearRightForward, RearLeftForward
};

// Zadne motory (piny, ktore ked su zapnute tak motor sa toci dozadu)
constexpr int backwardMotors[] = {
    FrontRightBackward, FrontLeftBackward,
    RearRightBackward, RearLeftBackward
};

// Funkcia, ktora vypne motory, ktore pridu ako argument do funkcie
void resetMotors(int* motors, int count) {
    for (int i = 0; i < count; i++)
        digitalWrite(motors[i], LOW);
}

// Hlavna funkcia pre pohyb robota, ktora ma 2 argumenty [smer, pocet otacok kolesa]
void move(MotorDirection direction, float rotations) {
    if (direction == Forward) {
        // Vypne vsetky backwardMotors
        int count = sizeof(backwardMotors) / sizeof(backwardMotors[0]);
        resetMotors(backwardMotors, count);


    }
}