#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <stdbool.h>
#include <stdlib.h>

// struktura do trzymania informacji o konkretnym słowie
// bool rozpoznaje czy mamy doczynienia z liczbą czy z nieliczbą
typedef struct {
    char *letters;
    int length;
    long long negativeInteger;
    bool isNegativeInteger;
    unsigned long long positiveInteger;
    bool isPositiveInteger;
    long double pointNumber;
    bool isPointNumber;
} word;

// id odpowiada za numer linii
// boolisUsed jest wykorzystywane przy wypisuwywaniu samych linii
typedef struct {
    int id;
    bool isUsed;
    word *words;
    int numberOfWords;
} line;
#endif