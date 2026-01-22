#pragma once
#include <Arduino.h>

/// <summary>
/// Tato kniznica sluzi na nastavenie robota,
/// kazdy jeden pin a ostatne potrebne veci, ako napriklad
/// SSID a heslo k access pointu robota
/// </summary>

/////////////
// Senzory //
/////////////

// Plamen
#define FireLeft 25
#define FireRight 26

// Vzdialenost
#define DistanceTrig 34
#define DistanceEcho 4

// Dolny (detekuje, ci robot je na rovnej ploche)
#define Fall 33

////////////
// Motory //
////////////

// Predne motory
#define FrontRightForward 23
#define FrontRightBackward 13
#define FrontLeftForward 14
#define FrontLeftBackward 27

// Zadne motory
#define RearRightForward 17
#define RearRightBackward 16
#define RearLeftForward 19
#define RearLeftBackward 18

////////////
// Kamera //
////////////

#define CameraHorizontal 22
#define CameraVertical 21

//////////////
// Cerpadlo //
//////////////

#define Pump 5

/// <summary>
/// Pomocne funkcie
/// </summary>

// Struktura, pre samotne piny (outputy alebo input), ktora obsahuje piny a ich pocet (velkost pola)
struct PinData {
    const int* pins;
    const int count;
};

// Struktura, ktora obsahuje inputy a outputy (tuto strukturu vrati funkcia GetAllPinsInRobot)
struct Pins {
    const PinData inputs;
    const PinData outputs;
};

Pins getAllPinsInRobot();