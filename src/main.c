/*
Krotki opis działania: Program wczytuje getlinem() całe linie, następnie funkcjami getword i getActualLine
wczytuje linie jako odpowiednią strukturę: linia składa się z tablicy słow, slowo jest struktuurą ktora
ma w sobie zaszyte wszystkie informacje ktore mogą być potrzebne przy sortowaniu slow, tj. czy to numer, jezeli tak to jaki?(dodatni/ujemny/moze double?)
po wczytaniu linii jako tablicy slow nastepuje parsowanie, czyli po prostu zamiana slow na liczby wszedfzie tam gdzie jest to mozliwe
nastepnie mamy sortowanie za pomocą q_sort w czasie O(nlog(n)), co do zasady najpierw mamy liczby, potem slowa
jak juz posortujemy to staramy sie wypisac tym samym "sortując" linie w czsie O(n^2), nie zmieniamy ich połozenia
tylko zapisujemy sobie ktore zostaly uzyte, a ktore nie.
*/

#define _GNU_SOURCE
#include "comparingLines.h"
#include "parsing.h"
#include "structures.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// funkcje dublujące pamięć tablic

// funkcja dostaje wskaźnik na tablicę liter oraz aktualną wielkość tablicy
// wielkość musi być postaci 2^k, gdzie k >= 0
void doubleSizeOfWord(char **arrayOfChar, int *size) {
    (*size) *= 2;
    (*arrayOfChar) = (char *)realloc((*arrayOfChar), *size * sizeof(char));
    if(*arrayOfChar == NULL)exit(1);

}

// analogiczna funkcja do doubleSizeWord, tylko dostaje wskaźnik na tablicę
// struktury: word
void doubleLineSize(word **arrayOfWord, size_t *size) {
    (*size) *= 2;
    (*arrayOfWord) = realloc((*arrayOfWord), (*size) * sizeof(word));
    if(*arrayOfWord == NULL)exit(1);
}

// funkcja dostaje wskaźnik do tablicy struktury: line
void doubleLinesSize(line **arrayOfLines, size_t *size) {
    (*size) *= 2;
    (*arrayOfLines) = realloc((*arrayOfLines), (*size) * sizeof(line));
    if(*arrayOfLines == NULL)exit(1);
    
}
// funkcja dostająca literę, a zwracająca true jezeli jest to bialy znak
bool isWhiteSpaceOrEnd(char c) {
    return (c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == '\r' ||
            c == '\xff' || c == '\n' || c == '\000');
}

// funkcja ktora dostaje tablice liter, indeks poczatkowy(start) oraz wartosc Boolowska
// isError, modyfikuje ona start tak zeby indeks w tablicy wyjsciowej byl
// odpowiednio przesuniety na kolejną puste pole, zmienia wartosc isError na true wtw
// gdy trafiamy na znak zle zdefiniowany
word getWord(const char *letters, size_t *start, bool *isError) {
    word res;
    int size = 1;
    int length = 0;
    char *currentWord = malloc(sizeof(char) * size);
    if(currentWord == NULL)exit(1);
    
    char c = letters[*start];
    while (!isWhiteSpaceOrEnd(c)) {
        if (c < 33 || c > 126) {
            *isError = true;
            free(currentWord);
            res.letters = NULL;
            res.length = 0;
            return res;
        }
        currentWord[length] = tolower(c);
        length++;
        (*start)++;
        if (length >= size) {
            doubleSizeOfWord(&currentWord, &size);
        }
        c = letters[*start];
    }

    currentWord[length] = '\0';
    res.length = length;
    res.letters = currentWord;
    res.isNegativeInteger = false;
    res.isPositiveInteger = false;
    res.isPointNumber = false;

    return res;
}

// funkcja zwracaja całą linię, dostaje 2 boolowskie wartośći ktore
// zmieniaja wartosc tylko w przypadku wystapienia bledu(nieodpowiedni znak)
// lub konca tj. EOF.
// Funkcja zwraca wskaźnik na linie, gdy wystepuja koniec lub jest błąd zwraca
// NULL(dlatego tez zdecydowałem się alokować linię, pomimo iz pozniej wyłuskuje z niej wartość)
// NULL jest bardzo naturalną interpretacją(dla mnie) linii podczas gdy występuje błąd lub jest koniec
line *getActualLine(bool *isEnd, bool *isError) {
    char *linePointer = NULL;
    size_t length = 0;
    int numberOfLetters;
    numberOfLetters = getline(&linePointer, &length, stdin);
    if(linePointer == NULL || errno == ENOMEM) exit(1);
    if (numberOfLetters == -1) {
        free(linePointer);
        (*isEnd = true);
        return NULL;
    }
    if (linePointer[0] == '#' || linePointer[0] == '\n') {
        free(linePointer);
        return NULL;
    }
    line *result = malloc(sizeof(line));
    if(result == NULL) exit(1);
    size_t numberOfWords = 0;
    size_t size = 1;

    result->words = malloc(sizeof(word) * size);
    if(result->words == NULL)exit(1);
    for (size_t i = 0; i < (size_t)numberOfLetters; i++) {
        if (!isWhiteSpaceOrEnd(linePointer[i])) {
            result->words[numberOfWords] = getWord(linePointer, &i, isError);
            if (*isError) {
                for (size_t j = 0; j < numberOfWords; j++) {
                    free(result->words[j].letters);
                }
                free(result->words);
                free(result);
                free(linePointer);
                return NULL;
            }
            numberOfWords++;
            if (numberOfWords >= size) {
                doubleLineSize(&(result->words), &size);
            }
        }
    }

    free(linePointer);
    result->numberOfWords = numberOfWords;
    return result;
}

// Funkcja drukująca wszystkie linie ktore są podobne w jednym wierszu
void printLines(line *ArrayOfLines, int numberOfLines) {
    for (int i = 0; i < numberOfLines; i++) {
        if (!ArrayOfLines[i].isUsed) {
            printf("%d", ArrayOfLines[i].id);
            for (int j = i + 1; j < numberOfLines; j++) {
                if (!ArrayOfLines[j].isUsed &&
                    compareLines(ArrayOfLines[i], ArrayOfLines[j])) {
                    ArrayOfLines[j].isUsed = true;
                    printf(" %d", ArrayOfLines[j].id);
                }
            }
            ArrayOfLines[i].isUsed = true;
            putchar('\n');
        }
    }
}

// funkcja zwalnijąca pamięć po procesie przypisania
void freeWordsAndLines(line *ArrayOfLines, int number) {
    for (int i = 0; i < number; i++) {
        for (int j = 0; j < ArrayOfLines[i].numberOfWords; j++) {
            free(ArrayOfLines[i].words[j].letters);
        }
        free(ArrayOfLines[i].words);
    }
}

// funkcja pomocnicza drukująca linie, nieużywana ale zostawiona gdybyś chciał coś sprawdzić
void printLine(line l){
    for(int i = 0; i < l.numberOfWords; i++){
        printf("%s ", l.words[i].letters);
    }
    putchar('\n');
}

// Funkcja wykonująca głowne zadanie, czyta wszystkie linie, następnie wrzuca
// je do tablicy o nazwie ArrayOfLines, parsuje, porownuje oraz czysci pamięć
void readAllLines() {
    size_t size = 1;
    size_t number = 1;
    size_t index = 0;
    bool isEnd = false;
    bool isError;

    line *ArrayOfLines = malloc(sizeof(line) * size);
    if(ArrayOfLines == NULL)exit(1);
    line *l = NULL;
    while (!isEnd) {
        isError = false;
        l = getActualLine(&isEnd, &isError);
        if (isError && l == NULL) {
            fprintf(stderr, "ERROR %zu\n", number);
        }
        if (l != NULL) {
            l->isUsed = false;
            l->id = number;
            ArrayOfLines[index] = *l;
            index++;
            if (index >= size) {
                doubleLinesSize(&ArrayOfLines, &size);
            }
        }
        free(l);
        number++;
    }
    for (size_t i = 0; i < index; i++){
        parseLine(&ArrayOfLines[i]);
        sortStructsExample(&ArrayOfLines[i], ArrayOfLines[i].numberOfWords);
    }

    printLines(ArrayOfLines, index);
    freeWordsAndLines(ArrayOfLines, index);
    free(ArrayOfLines);
}

int main() {
    readAllLines();
}
