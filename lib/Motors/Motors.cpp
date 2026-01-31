#include <Motors.h>

constexpr int MOTOR_COUNT = 4;

// Predne motory (piny, ktore ked su zapnute tak motor sa toci dopredu)
constexpr int forwardMotors[MOTOR_COUNT] = {
    FrontRightForward, FrontLeftForward,
    RearRightForward, RearLeftForward
};

// Zadne motory (piny, ktore ked su zapnute tak motor sa toci dozadu)
constexpr int backwardMotors[MOTOR_COUNT] = {
    FrontRightBackward, FrontLeftBackward,
    RearRightBackward, RearLeftBackward
};

// Motory, ktore maju byt spustene, ked robot chce ist doprava
constexpr int rightMotors[MOTOR_COUNT] = {
    FrontRightBackward, RearRightBackward,
    FrontLeftForward, RearLeftForward
};

// Motory, ktore maju byt spustene, ked robot chce ist dolava
constexpr int leftMotors[MOTOR_COUNT] = {
    FrontLeftBackward, FrontRightForward,
    RearLeftBackward, RearRightForward
};

MotorDirection currentState;

// Funkcia, ktora vypne motory, ktore pridu ako argument do funkcie
void toggleMotors(const int* motors, int count, bool state = false) {
    for (int i = 0; i < count; i++)
        digitalWrite(motors[i], state ? HIGH : LOW);
}

// Hlavna funkcia pre pohyb robota, ktora ma 1 argument (smer)
void move(MotorDirection direction) {
    if (currentState != direction) {
        toggleMotors(backwardMotors, 4);
        toggleMotors(forwardMotors, 4);
        toggleMotors(rightMotors, 4);
        toggleMotors(leftMotors, 4);
    }

    const int* motors = nullptr;

    switch (direction) {
        case Forward:
            motors = forwardMotors;
            break;
        case Backward:
            motors = backwardMotors;
            break;
        case Right:
            motors = rightMotors;
            break;
        case Left:
            motors = leftMotors;
            break;
    }

    currentState = direction;
    toggleMotors(motors, MOTOR_COUNT, true);
};