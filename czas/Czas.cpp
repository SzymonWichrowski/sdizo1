#include <ntdef.h>
#include <profileapi.h>
#include "Czas.h"

using namespace std;

Czas::Czas() {
    this -> frequency;
    this -> start;
    this -> elapsed;

    QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);     //czestotliwosc impulsow licznika
}

long long int Czas::readQPC() {
                                                        //zaczerpniete ze strony prowadzacego
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    return ((long long int)count.QuadPart);
}

void Czas::czasStart() {
    start = readQPC();
}

void Czas::czasKoniec() {
    elapsed = readQPC() - start;
}

long long int Czas::getFrequency() {
    return frequency;
}

long long int Czas::getElapsed() {
    return elapsed;
}