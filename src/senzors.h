#include "constants.h"

namespace Senzors {
    const int trigDistance = DistanceOutput;
    const int echoDistance = DistanceInput;

    // Return cislo, vzdialenost (v cm)
    long ReadDistance() {
        digitalWrite(trigDistance, LOW);
        delayMicroseconds(2);
        digitalWrite(trigDistance, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigDistance, LOW);

        long duration = pulseIn(echoDistance, HIGH, 30000);

        if (duration == 0)
            return -1;

        return (duration * 0.034) / 2;
    }
}