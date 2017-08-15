// uzyjemy funkcji z bilbioteki dostarczanej do jezyka
#include <stdio.h>

// powyzsze omowie na warsztatach :)


/**
 * Hello ;)
 * Główna funkcja programu. Uruchamiając nasz program,
 * system operacyjny uruchomi tę funkcję.
 * Funkcja przyjmuje dwa argumenty:
 * int argc - ilosc elementów w tablicy argv
 * char * argv[]- to tak naprawdę tablica tablic- ten zapis
 * wytlumacze na warsztatach. W tej zmiennej beda przechowywane
 * parametry, z jakimi zostal uruchomiony nasz program.
 * Nie musimy o tym mowic w tym momencie :)
 *
 * Funkcja zwraca typ int.
 */
int main(int argc, char *argv[]) {

	int i = 0;
	int a = 0; // nie ma definicji wartosci, co tam sie kryje??

	// za pomoca biblioteki stdio mozemy uzyc funkcji printf
	printf("Hello pjl!\n"); // \n znak specjalny- nowa linia

	/*
	 * %d oznacza, ze pod tym bedzie "decimal" czyli
	 * jakas liczba calkowita, odsylam do dokumentacji:
	 * http://www.cplusplus.com/reference/cstdio/printf/
	 */
	printf("i= %d\n\n", i); // dwie nowe linie

	// a co ma a? ]:->
	printf("a= %d\n", a);
	// a moze miec teraz cokolwiek....
	// cokolwiek znajdzie sie w pamieci, dlatego zawsze
	// warto inicjalizowac zmienne, chociazby zerem


	// tutaj zwracamy do systemu wartosc. Mozemy zwrocic
	// cokolwiek. przyjelo sie, ze poprawnie wykonany
	// program zwraca zero do systemu.
	return 0;
}
