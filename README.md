---
title: 'Project documentation template'
disqus: hackmd
---

Male zadanie IPP
===

Polecenie
---

Należy napisać program wyszukujący w tekście grupy podobnych wierszy.

Program czyta wiersz po wierszu ze standardowego wejścia. Program ignoruje wiersze zaczynające się znakiem # i niezawierające żadnego słowa. Po wczytaniu i przetworzeniu wszystkich wierszy z wejścia program wypisuje na standardowe wyjście grupy wierszy podobnych, w każdym wierszu jedna grupa. Dane wyjściowe mają zostać posortowane rosnąco według numerów wierszy. Wiersze są numerowane od jedynki. Numerowane są wszystkie wiersze, również te ignorowane i błędne.

#### Dokładniejsza specyfikacja słów:

Wiersz tekstu składa się ze słów oddzielonych białymi znakami. Białe znaki mogą też występować na początku i na końcu wiersza. Słowo składa się z ciągu znaków o kodach ASCII od 33 do 126. Białe znaki są to znaki reprezentowane w języku C jako ' ', '\t', '\n', '\v', '\f', '\r', czyli znaki o kodach ASCII odpowiednio 32, 9, 10, 11, 12, 13. Wiersz kończy się (na ogół) znakiem przejścia do nowej linii, czyli znakiem '\n'. Słowo może być liczbą bądź nieliczbą. Słowo jest liczbą, jeśli reprezentuje:

* liczbę całkowitą zapisaną dziesiętnie (rozpoznawane wartości z przedziału przynajmniej od -9223372036854775808 do 18446744073709551615), np. 42, -1, 09, +2, 0, -0, +0, -02;
* liczbę całkowitą nieujemną zapisaną szesnastkowo (rozpoznawane wartości przynajmniej do 18446744073709551615), np. 0X0001, 0XABC;
* liczbę całkowitą nieujemną zapisaną ósemkowo (rozpoznawane wartości przynajmniej do 18446744073709551615), np. 0177, 0001;
* liczbę zmiennoprzecinkową, np. 0.25, .33, -1E-1, INF, -INF.


Jak testować działanie programu.
---

Wystarczy wejść w katalog "src", następnie skompilować program poleceniem __make__ , w celu testowania używać skryptu bashowego: __test.sh__ z odpowiednimi argumentami tj:
__bash test.sh similar_lines testy__

Skrypt testuje zarówno output programu jak i poprawność pamięci.
