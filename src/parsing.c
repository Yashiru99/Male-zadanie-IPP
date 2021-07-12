#include "structures.h"
#include <math.h>
#include <string.h>
bool isNumber(word *w){
    return w->isNegativeInteger || w->isPositiveInteger || w->isPointNumber;
}
//funkcja porównująca słowa, długa, bo słowa są w bardzo niejednoznaczny sposób zdefiniowne
int compareNumbers(word *w1, word *w2){
    // 2 dodatnie
    if(w1 -> isPositiveInteger && w2 -> isPositiveInteger){
        if(w1->positiveInteger > w2->positiveInteger){
            return 1;
        }
        else if(w1->positiveInteger < w2->positiveInteger){
            return -1;
        }
        return 0;
    }
    // 2 ujemne
    if(w1 -> isNegativeInteger && w2->isNegativeInteger){
        if(w1->negativeInteger > w2->isNegativeInteger){
            return 1;
        }
        else if(w1->negativeInteger < w2->negativeInteger){
            return -1;
        }
        return 0;
    }
    // dodatni i ujemny
    if(w1->isNegativeInteger && w2->isPositiveInteger){
        if(w1->negativeInteger == 0 && w2->positiveInteger == 0){
            return 0;
        }
        return -1;
    }
    if(w1->isPositiveInteger && w2->isNegativeInteger){
        if(w1->positiveInteger == 0 && w2->negativeInteger == 0){
            return 0;
        }
        return 1;
    }
    // dodatni i zmiennoprzecinkowa
    if(w1->isPointNumber && w2->isPositiveInteger){
        if(w1->pointNumber > w2->pointNumber){
            return 1;
        }
        else if(w1->pointNumber < w2->pointNumber){
            return -1;
        }
        return 0;
    }
    // ujemna i zmiennoprzecinkowa
    if(w1->isPointNumber && w2->isNegativeInteger){
        if(w1->pointNumber > w2->negativeInteger){
            return 1;
        }
        else if(w1->pointNumber < w2->negativeInteger){
            return -1;
        }
        return 0;
    }
    if(w1->isPositiveInteger && w2->isPointNumber){
        if(w1->positiveInteger > w2->pointNumber){
            return 1;
        }
        else if(w1->positiveInteger < w2->pointNumber){
            return -1;
        }
        return 0;
    }
    if(w1->isNegativeInteger && w2 -> isPointNumber){
        if(w1->negativeInteger > w2->pointNumber){
            return 1;
        }
        else if(w1->negativeInteger < w2->pointNumber){
            return -1;
        }
        return 0;
    }
    // 2 zmiennoprzecinkowe
    if(w1->isPointNumber && w2->isPointNumber){
        if(w1->pointNumber > w2->pointNumber){
            return 1;
        }
        else if(w1->pointNumber < w2->pointNumber){
            return -1;
        }
        return 0;
    }
    return 0;
}
// funkcja ktora jest porownywatorem dla funkcji sortującej
int structCmp(const void *a, const void *b) {
    word *firstWord = (word *)a;
    word *secondWord = (word *)b;
    if(isNumber(firstWord) && isNumber(secondWord)){
        return compareNumbers(firstWord, secondWord); // gdy 2 są numerem to odpowiednio je ze sobą porównujemy
    }
    else if(isNumber(firstWord)){
        return -1; // musimy ustalic kolejność w parze uporządkowanej liczba - słowo
    }
    else if(isNumber(secondWord)){
        return 1;
    }
    else{
        return strcmp(firstWord->letters, secondWord->letters);
    }
}

void sortStructsExample(line *l, int numberOfWords) {
    qsort(l->words, numberOfWords, sizeof(word), structCmp);
}

// funkcja pomocnicze wyłuskujące to czego nie łapie stroud(), tj. bardzo duzych
// liczb i symbolu "nan"
bool isInfinity(char *letters, double value) {
    if (isinf(value)) {
        return !strcmp(letters, "+inf") || !strcmp(letters, "-inf") ||
               !strcmp(letters, "inf");
    }
    return false;
}

// funkcja parsująca całą linię, tj. zmieniająca tam gdzie jest to mozliwe słowo
// na liczbę, jako argument potrzebuje tylko linii ktorą modyfikuje
void parseLine(line *l){
    long long negativeValue;
    unsigned long long positiveValue;
    long double pointValue;
    char *endPointer;
    if(l == NULL)return;
    for(int i = 0; i < l -> numberOfWords; i++) {
        // Ujemna linia => tylko o podstawie 10 lub zmiennoprzecinkowa
        if (l->words[i].letters[0] == '-') {
            negativeValue = strtoll(l->words[i].letters, &endPointer, 10);
            if (*endPointer == '\0') {
                l->words[i].isNegativeInteger = true;
                l->words[i].negativeInteger = negativeValue;
            }
            else if(l->words[i].letters[1] != '\0' && l->words[i].letters[2] != 'x' && l->words[i].letters[2] != 'X'){
                pointValue = strtod(l->words[i].letters, &endPointer);
                if (*endPointer == '\0') {
                    if (isInfinity(l->words[i].letters, pointValue)){
                        //jeżeli to naprawdę nieskończoność to wczytujemy
                        l->words[i].isPointNumber = true;
                        l->words[i].pointNumber = pointValue;
                    }
                    else if (pointValue != INFINITY && !isnan(pointValue)){
                        l->words[i].isPointNumber = true;
                        l->words[i].pointNumber = pointValue;
                    }
                }
            }
        }
        //tylko dodatnie => o podstawie 10 lub zmiennoprzecinkowa
        else if(l->words[i].letters[0] == '+'){
            positiveValue = strtoull(l->words[i].letters, &endPointer, 10);
            if (*endPointer == '\0') {
                l->words[i].isPositiveInteger = true;
                l->words[i].positiveInteger = positiveValue;
            }
            else if(l->words[i].letters[1] != '\0' && l->words[i].letters[2] != 'x' && l->words[i].letters[2] != 'X'){
                pointValue = strtod(l->words[i].letters, &endPointer);
                if (*endPointer == '\0') {
                    if (isInfinity(l->words[i].letters, pointValue)){
                        //jeżeli to naprawdę nieskończoność to wczytujemy
                        l->words[i].isPointNumber = true;
                        l->words[i].pointNumber = pointValue;
                    }
                    else if (pointValue != INFINITY && !isnan(pointValue)){
                        l->words[i].isPointNumber = true;
                        l->words[i].pointNumber = pointValue;
                    }
                }
            }
        }
        else{
            // potencjalna liczba osemkowa lub 16-stkowa
            if(l->words[i].letters[0] == '0'){
                positiveValue = strtoull(l->words[i].letters, &endPointer, 8);
                if (*endPointer == '\0') {
                    l->words[i].isPositiveInteger = true;
                    l->words[i].positiveInteger = positiveValue;
                }
                else{
                    if(l->words[i].letters[1] == 'x' || l->words[i].letters[1] == 'X'){
                        if(l->words[i].letters[2] == '\0'){
                            l->words[i].isPositiveInteger = true;
                            l->words[i].positiveInteger = 0;
                        }
                        else{
                            positiveValue = strtoull(l->words[i].letters, &endPointer, 16);
                            if (*endPointer == '\0') {
                                l->words[i].isPositiveInteger = true;
                                l->words[i].positiveInteger = positiveValue;
                            }
                        }
                    }
                    else{
                        positiveValue = strtoull(l->words[i].letters, &endPointer, 10);
                        if (*endPointer == '\0') {
                            l->words[i].isPositiveInteger = true;
                            l->words[i].positiveInteger = positiveValue;
                        }
                        else{
                            pointValue = strtod(l->words[i].letters, &endPointer);
                            if (*endPointer == '\0') {
                                if (isInfinity(l->words[i].letters, pointValue)){
                                    //jeżeli to naprawdę nieskończoność to wczytujemy
                                    l->words[i].isPointNumber = true;
                                    l->words[i].pointNumber = pointValue;
                                }
                                else if (pointValue != INFINITY && !isnan(pointValue)){
                                    l->words[i].isPointNumber = true;
                                    l->words[i].pointNumber = pointValue;
                                }
                            }
                        }

                    }
                }
            }
            else{
                positiveValue = strtoull(l->words[i].letters, &endPointer, 10);
                if (*endPointer == '\0') {
                    l->words[i].isPositiveInteger = true;
                    l->words[i].positiveInteger = positiveValue;
                }
                else if(l->words[i].letters[1] != '\0' && l->words[i].letters[2] != 'x' && l->words[i].letters[2] != 'X') {
                    pointValue = strtod(l->words[i].letters, &endPointer);
                    if (*endPointer == '\0') {
                        if (isInfinity(l->words[i].letters, pointValue)){
                            //jeżeli to naprawdę nieskończoność to wczytujemy
                            l->words[i].isPointNumber = true;
                            l->words[i].pointNumber = pointValue;
                        }
                        else if (pointValue != INFINITY && !isnan(pointValue)){
                            l->words[i].isPointNumber = true;
                            l->words[i].pointNumber = pointValue;
                        }
                    }
                }
                }
            }
        }
    }

