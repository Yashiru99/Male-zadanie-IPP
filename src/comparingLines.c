#include "comparingLines.h"
#include "structures.h"
#include <string.h>
#include <stdbool.h>

bool isZero(word w1, word w2) {
    if (w1.isPositiveInteger && w1.positiveInteger == 0) {
        if (w2.isPositiveInteger && w2.positiveInteger == 0) {
            return true;
        }
        if (w2.isNegativeInteger && w2.negativeInteger == 0) {
            return true;
        }
        if (w2.isPointNumber && w2.pointNumber == 0) {
            return true;
        }
    }
    if (w1.isNegativeInteger && w1.negativeInteger == 0) {
        if (w2.isPositiveInteger && w2.positiveInteger == 0) {
            return true;
        }
        if (w2.isNegativeInteger && w2.negativeInteger == 0) {
            return true;
        }
        if (w2.isPointNumber && w2.pointNumber == 0) {
            return true;
        }
    }
    if (w1.isPointNumber && w1.pointNumber == 0) {
        if (w2.isPositiveInteger && w2.positiveInteger == 0) {
            return true;
        }
        if (w2.isNegativeInteger && w2.negativeInteger == 0) {
            return true;
        }
        if (w2.isPointNumber && w2.pointNumber == 0) {
            return true;
        }
    }
    return false;
}
// funkcja zwracająca true jezeli 2 slowa są takie same, false wpp, pierwsze
// sprawdzenie jest tylko dla zera
bool compareTwoWords(word w1, word w2) {
    if (isZero(w1, w2))
        return true;
    if (w1.isNegativeInteger && w2.isNegativeInteger) {
        return w1.negativeInteger == w2.negativeInteger;
    } else if (w1.isNegativeInteger && w2.isPointNumber) {
        return w1.negativeInteger == w2.pointNumber;
    } else if (w2.isNegativeInteger && w1.isPointNumber) {
        return w1.pointNumber == w2.isNegativeInteger;
    } else if (w1.isPositiveInteger && w2.isPositiveInteger) {
        return w1.positiveInteger == w2.positiveInteger;
    } else if (w1.isPositiveInteger && w2.isPointNumber) {
        return w1.positiveInteger == w2.pointNumber;
    } else if (w2.isPositiveInteger && w1.isPointNumber) {
        return w2.positiveInteger == w1.pointNumber;
    } else if (w1.isPointNumber && w2.isPointNumber) {
        return w1.pointNumber == w2.pointNumber;
    } else {
        return (strcmp(w1.letters, w2.letters) == 0);
    }
}

// funkcja analogiczna dla compareWords tylko dla linii
bool compareLines(line l1, line l2) {
    if (l1.numberOfWords == l2.numberOfWords) {
        for (int i = 0; i < l1.numberOfWords; i++) {
            if (!compareTwoWords(l1.words[i], l2.words[i])) {
                return false;
            }
        }
        return true;
    }
    return false;
}

