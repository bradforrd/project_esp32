#include "constants.h"

namespace Senzors {
    // Return cislo, vzdialenost (v cm)
    long ReadDistance() {
        digitalWrite(DistanceOutput, LOW);
        delayMicroseconds(2);
        digitalWrite(DistanceOutput, HIGH);
        delayMicroseconds(10);
        digitalWrite(DistanceOutput, LOW);

        // Timeout nastaveny na 20ms, aby sa program zbytocne nezablokoval
        long duration = pulseIn(DistanceInput, HIGH, 20000);

        if (duration == 0)
            return -1;

        return duration * 0.034 / 2;
    }
}