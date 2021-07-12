#!/bin/bash

# sprawdzenie ilości przekazywanych argumentów
if [ "$#" -ne 2 ] ; then
  echo -e "nieprawidłowa ilość argumentów";
  exit 1;
fi;

plik="src/$1";
testy=$2;

# testowanie
for i in "$testy"/*.in;
do echo -n "Plik $plik ";
./"$plik" < "$i" > "wynik.out" 2> "wynik.err"
valgrind --error-exitcode=123 --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all ./"$plik" < "$i" >/dev/null 2>/dev/null
if [ $? -eq 0 ] ; then
 # brak problemów z pamięcią
 if diff "wynik.out" "${i%in}out" && diff "wynik.err" "${i%in}err"; then
        echo -e "\e[32m jest okej! \e[0m";
    else 
        echo -e "\e[31m nie jest okej(nieodpowiedni output) \e[0m";
    fi;
else
  # nieodpowiedni output
    echo -e "\e[31m nie jest okej(problemy z pamięcią) \e[0m";
fi

# sprzątanie skryptu po sobie
rm wynik.out wynik.err;
done

