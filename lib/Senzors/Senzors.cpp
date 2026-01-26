#include <Senzors.h>

/// <summary>
/// Subor (kniznica), ktora sa stara o senzory (predny a spodny)
/// </summary>

////////////////////////////
// Senzor na vzdialenost //
////////////////////////////

// Funkcia, ktora vrati vzdialenost medzi senzorom a objektom (prekazkou)
/*
    fix: need to fix whole function (returning -1.00f always :( )
*/
float getDistance() {
    // Zapne a vypne trigger na senzore (ziska potrebny udaj)
    digitalWrite(DistanceTrig, LOW);
    delayMicroseconds(2);
    digitalWrite(DistanceTrig, HIGH);
    delayMicroseconds(10);
    digitalWrite(DistanceTrig, LOW);

    // Vrati dlzku pulzu v mikrosekundach (dlzka pulzu sa mysli dlzka casu kedy prijde k objektu a naspat)
    long duration = pulseIn(DistanceEcho, HIGH, 30000);

    if (duration == 0) {
        return -1.0f; // nic nenamerane
    }

    // Prerata dlzku pulzu na vzdialenost (cm) [z internetu]
    float distance = duration * 0.034f / 2.0f; // Rychlost zvuku / 2

    Serial.printf("TRIG=%d ECHO=%d\n",
        digitalRead(DistanceTrig),
        digitalRead(DistanceEcho)
    );

    return distance;
}

//////////////////
// Dolny senzor //
//////////////////

// Vrati true ak ma pod sebou "zem"
bool isGrounded() {
    int value = digitalRead(Fall);

    return value == LOW;
}

//////////////////////
// Senzor na plamen //
//////////////////////

bool detectedFlame(String &side) {
    int left = digitalRead(FireLeft) == LOW;
    int right = digitalRead(FireRight) == LOW;

    if (left && right) {
        side = "both";
        return true;
    }

    if (left) {
        side = "left";
        return true;
    }

    if (right) {
        side = "right";
        return true;
    }

    side = "none";
    return false;
}