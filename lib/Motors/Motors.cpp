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

MotorDirection currentState = NULL;

// Funkcia, ktora vypne motory, ktore pridu ako argument do funkcie
void toggleMotors(int* motors, int count, bool state = false) {
    for (int i = 0; i < count; i++)
        digitalWrite(motors[i], state ? HIGH : LOW);
}

// Hlavna funkcia pre pohyb robota, ktora ma 2 argumenty [smer, pocet otacok kolesa]
void move(MotorDirection direction, float rotations) {
    // Ak sa smer, ktory pride do funkcie nerovna aktualnemu smeru, tak sa vypnu vsetky motory
    if (currentState != direction) {
        int backwardCount = sizeof(backwardMotors) / sizeof(backwardMotors[0]);
        toggleMotors(backwardMotors, backwardCount);

        int forwardCount = sizeof(forwardMotors) / sizeof(forwardMotors[0]);
        toggleMotors(forwardMotors, forwardCount);
    }

    // Motory, ktore sa maju pustit
    int[] motors = direction == Forward ? forwardMotors : backwardMotors;
    int count = sizeof(motors) / sizeof(motors[0]);

    toggleMotors(motors, count, true);
}