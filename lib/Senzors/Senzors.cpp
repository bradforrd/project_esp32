#include <Arduino.h>
#include <Constants.h>

/// <summary>
/// Subor (kniznica), ktora sa stara o senzory (predny a spodny)
/// </summary>

////////////////////////////
// Senzor na vzdialenost //
////////////////////////////

// Funkcia, ktora vrati vzdialenost medzi senzorom a objektom (prekazkou)
float getDistance() {
    // Zapne a vypne trigger na senzore (ziska potrebny udaj)
    digitalWrite(DistanceTrig, LOW);
    delayMicroseconds(2);
    digitalWrite(DistanceTrig, HIGH);
    delayMicroseconds(10);
    digitalWrite(DistanceTrig, LOW);

    // Vrati dlzku pulzu v mikrosekundach (dlzka pulzu sa mysli dlzka casu kedy prijde k objektu a naspat)
    long duration = pulseIn(DistanceEcho, HIGH);

    // Prerata dlzku pulzu na vzdialenost (cm) [z internetu]
    float distance = duration * 0.034f / 2; // Rychlost zvuku / 2

    return distance;
}

//////////////////
// Dolny senzor //
//////////////////

