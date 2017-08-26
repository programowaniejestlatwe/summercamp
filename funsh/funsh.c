/*
 * main.c
 *
 *  Created on: Aug 26, 2017
 *      Author: Piotr Pozniak, PJL, programowanie jest latwe
 *
 *  Przykladowa implementacja funsha
 */

// do rysowania na ekranie
#include <stdio.h>

// do przydzielania pamieci do funsha
#include <stdlib.h>

// do spowalniania czasu
#include <unistd.h>

/*
 * rozmiar planszy, po ktorej porusza sie waz,
 * moze byc dowolny rozmiar, dla ulatwienia przyjmijmy
 * 10x10
 */
#define ROZMIAR_PLANSZY_X 10
#define ROZMIAR_PLANSZY_Y 10

/*
 * rozmiar ekranu, po ktorym bedziemy rysowac (renderowac)
 * cala scene gry. nalezy pamietac, ze scena bedzie
 * posiadac ramke a poniewaz rysujemy po ekranie
 * terminala, kazda linia ekranu musi przejsc kursorem
 * do nowej linii, dlatego rozmiar ekranu to rozmiar
 * plansz powiekszony o 2 (ramka) i na X potrzebujemy
 * jeszcze jedno miejsce na nowa linie
 */
#define ROZMIAR_EKRANU_X 13
#define ROZMIAR_EKRANU_Y 12


// struktura naszego funsha, lista jednokierunkowa
typedef struct {
	// pozycja cialka na x,y
	int x, y;

	/*
	 *  wskaznik na nastepny element cialka.
	 *  koniec listy jest wtedy, gdy next = 0
	 */
	struct funsh_t *next;
} funsh_t;



/**
 * Funkcja, ktora czysci ekran. Ogolnie jest to dosc
 * skomplikowane zagadnienie i na wolnych wolnych komputerach
 * sprzed epoki najprawdopodobniej takie rozwiazanie
 * powodowaloby poklatkowe rysowanie calej gry.
 * My mamy superszybkie komputery, wiec po prostu
 * brutalnie bedziemy wciskac nowa linie 100 razy i to nam
 * przeczysci ekran.
 */
void czysc_ekran()
{
	// 99 nowych linii
	char nowelinie[100];

	// w petli wpisujemy do tablicy te nwoe linie
	for (int i = 0; i < 99; i++) {
		// nowa linia to \n, tutaj w pojedynczych
		// uszach, poniewaz to nie string tylko char!
		nowelinie[i] = '\n';
	}

	/*
	 * na koncu tablicy (99 od zera to 100 element)
	 * umieszczamy wartosc 0. String to ciag znakow (char)
	 * zakonczony zerem. jezeli pominiemy to zero,
	 * mozemy uzyskac nieobliczalny rezultat- pobaw sie.
	 */
	nowelinie[99] = 0;

	/*
	 * wyswietlamy nowe linie na ekran za jednym zamachem
	 * za pomoca printf.
	 */
	printf("%s", nowelinie);
}


/**
 * funkcja do odczekiwania na kolejna klatke.
 * tutaj bedzie czekac na nowy ruch. teraz, dla uproszczenia
 * za kazdym zem bedzie czekac jedna sekunde
 */
void czekaj_na_kolejna_klatke() {

	sleep(1);
}


/**
 * funkcja do, ktora tworzy kolejny element funsha,
 * czyli tworzy nowy element listy jednokierunkowej.
 * parametrami sa nowe x i y, ktore zostana wpisane
 * w nowa przydzielone cialo.
 * Funkcja zwraca wskaznik na funsh_t, czyli wskaznik
 * na nowe miejsce w pamieci.
 */
funsh_t *powieksz_fusha(int nowe_x, int nowe_y) {

	funsh_t *nowe_cialko;
//	printf("powiekszam funsha...\n");

	// alokujemy pamiec
	nowe_cialko = malloc(sizeof(funsh_t));

	// sprawdzamy czy sie udalo, jezeli nie, zwracamy 0
	if (!nowe_cialko) {
		return 0;
	}

	// ustaw pozycje cialka na podane x,y
	nowe_cialko->x = nowe_x;
	nowe_cialko->y = nowe_y;

	// ustaw wskaznik na nastepnik zawsze na zero!
	nowe_cialko->next = 0;

	// zwracamy wskaznik
	return nowe_cialko;
}


/**
 * TODO tego na razie nie robimy.. waz bedzie isc
 * zawsze w prawo. jak chcesz aby szedl w dol, ustaw na
 * 2.
 * 0-> gora
 * 1-> prawo
 * 2-> dol
 * 3-> lewo
 */
int odczytaj_ruch_z_klawiatury() {

	//printf("ruch z klawiaury\n");
	return 1;
}


/**
 * funkcja, ktora przesunie glowe weza w odpowiednie miejsce
 * sprawdzi, czy waz nie wlazl w sciane a jak wszystko ok
 * to przesunie pozostala jego czesc za glowa.
 * Funckja zwroci -1 gdy waz uderzy w sciane a 0, gdy
 * wszystko zostanie poprawnie wykoanne
 */
int przesun_funshem(funsh_t *glowa, int kierunek) {

	//printf("przesuwam wezem\n");

	// tworzymy iterator
	funsh_t *it = glowa->next;

	/*
	 * kopiujemy pozycje glowy weza bo za moment
	 * bedziemy ja przesuwac a przeciez musimy ustawic
	 * kolejny element weza w to miejsce.
	 */

	int aktualny_x = glowa->x;
	int aktualny_y = glowa->y;

	/**
	 * tutaj ogromny blok warunkow, mozna to obsluzyc inaczej
	 * np switch, ale o tym kiedy indziej.
	 * po kolei sprawdzamy czy nasza glowa nie wychodzi
	 * poza rozmiar planszy. jezeli tak to zwracamy -1
	 *
	 */

	// idz do gory funshem
	if (kierunek == 0) {
		// sprawdz czy glowa nie wyjdzie poza gorna krawedz
		if (glowa->y == 0) {
			// nie moze byc mniej niz zero, game over
			return -1;
		}
		// wszystko ok, przesun do gowy
		glowa->y--;

	}
	// idz w prawo funshem
	else if (kierunek == 1) {
		// sprawdz czy glowa nie wyjdzie poza prawa krawedz
		if (glowa->x == ROZMIAR_PLANSZY_X-1) {
			return -1;
		}
		// wszystko ok, przesun glowe w prawo
		glowa->x++;
	}
	// idz w dol funshem
	else if (kierunek == 2) {
		// sprawdz czy glowa nie wyjdzie poza dolna krawedz
		if (glowa->y == ROZMIAR_PLANSZY_Y-1) {
			return -1;
		}
		// wszystko ok, przesun glowe w dol
		glowa->y++;

	}
	// idz w lewo
	else if (kierunek == 3) {
		// sprawdz czy glowa nie wyjdzie poza lewa krawedz
		if (glowa->x == 0) {
			return -1;
		}

		// wszystko ok, przesun glowe w lewo
		glowa->x--;
	}


	/*
	 * glowe przesunieto, teraz...
	 * przesun cielsko funsha za glowa.
	 * it- nasz iterator ustawilismy juz na nastepny
	 * element weza, jezeli jest niezerowy, bedziemy
	 * ustawiac mu kolejne wartosci
	 */

	while (it) {

		// zrob kopie pozycji framentu cialka
		int aktualny_x_cielska = it->x;
		int aktualny_y_cielska = it->y;

		// ustaw cialko na pozycje nastepnika
		it->x = aktualny_x;
		it->y = aktualny_y;

		// ustaw aktualny x, y na kopie cialka
		aktualny_x = aktualny_x_cielska;
		aktualny_y = aktualny_y_cielska;

		// przejdz do nastepnego fragmentu ciala
		it = it->next;
	}

	return 0;
}


/**
 * Funkcja, ktora rysuje nam cala scene gry na ekranie.
 * Zawsze jest to najtrudniejszy fragment kazdej gry,
 * duzo sie tutaj dzieje.
 * Po pierwsze tworzymy "bufor" naszego ekranu- tablice,
 * ktora beedzie trzymac w sobie ciag znakow.
 * kazdy ciag znakow to element planszy na ekranie.
 * puste przestrzenie to spacje, glowa to 'D', cialo
 * weza to gwiazdka a znaki |-_ utworza nam ramke planszy.
 * Do tego kazda linia planszy musi byc zakonczona
 * nowa linia \n aby wszystko poprawnie sie rysowalo.
 */
void rysuj_gre(funsh_t *funsh) {

	// nasz bufor ekranu
	char ekran[ROZMIAR_EKRANU_Y][ROZMIAR_EKRANU_X];

	// wskaznik, iterator, na pierwszy element cialka
	// glowa jest rysowana osobno- ma inny symbol
	funsh_t *it = funsh->next;

	// czyszczenie ekranu
	/**
	 * na cala tablice wpisujemy spacje- puste pole
	 * a zakonczenie kazdej lini tworzy znak nowej linii
	 * \n
	 */
	for (int y = 0; y < ROZMIAR_EKRANU_Y; y++) {

		for (int x = 0; x < ROZMIAR_EKRANU_X; x++) {
			ekran[y][x] = ' ';
		}
		ekran[y][ROZMIAR_EKRANU_X-1] = '\n';
	}

	// teraz mamy juz czysty ekran, rysujemy ramke

	/* rysuj ramkę gora/dol
	 * ROZMIAR_EKRANU_X-1 poniewaz ostatni element to
	 * znak nowej linii
	 */
	for (int x = 0; x < ROZMIAR_EKRANU_X-1; x++) {
		ekran[0][x] = '-';
		ekran[ROZMIAR_EKRANU_Y-1][x] = '_';
	}

	// rysuj ramke lewo/prawo
	for (int y = 0; y < ROZMIAR_EKRANU_Y; y++) {
		ekran[y][0] = '|';

		// x-2 poniewaz ostatni x to nowa linia
		ekran[y][ROZMIAR_EKRANU_X-2] = '|';
	}

	/* umiesc glowe na ekranie
	 * y+1 i x+1 poniewaz wezem w pamieci przesuwamy
	 * po planszy a nasz ekran ma jeszcze ramke.
	 */
	ekran[funsh->y+1][funsh->x+1] = 'D';

	// rysuj pozostale cielsko
	while (it) {
		ekran[it->y+1][it->x+1] = '*';
		it = it->next;
	}

	/* tak samo jak przy czyszczeniu ekranu-
	 * nasz bufor ekranu musi byc zakonczony zerem
	 * jak kazdy prawilny string
	 */
	ekran[ROZMIAR_EKRANU_Y-1][ROZMIAR_EKRANU_X-1] = 0;

	// umieszczamy wszystko na ekranie
	printf("%s", ekran);
}




/**
 * Glowna funcja programu
 */
int main(int argc, char *argv[]) {

	/*
	 * lista jednokierunkowa, bedzie naszym calym funszem.
	 * gracz jest poczatkiem listy wiec bedzie to glowa
	 */
	funsh_t *gracz;

	/**
	 * abym mogl wskazac na koniec weza i stworzyc
	 * kolejne cialko
	 */
	funsh_t *koniec_funsha;

	/*
	 * tworze cialo weza, ustawiam go napozycji 3,2.
	 * moze byc gdziekolwiek indziej
	 */
	gracz = powieksz_fusha(3, 2);

	/**
	 * tutaj dla sportu, recznie powiekszylem funsha
	 * o kolejne czesci, zeby sprawdzic, czy
	 * dobrze zrobilem cala reszte- pobaw sie!
	 */
	gracz->next = powieksz_fusha(3, 1);
	koniec_funsha = gracz->next;
	koniec_funsha->next = powieksz_fusha(2, 1);

	// chcesz dodac kolejne?
	// koniec_funsha = koniec_funsha->next;
	// koniec_funsha->next = powieksz_fusha(1, 1);


	/*
	 * gra bedzie sie wykonywac tak dlugo, dopoki
	 * zmienna kontynuuj_gre = 1
	 */
	int kontynuuj_gre = 1;

	/* zmienna do przechowania kierunku, w ktorym
	 * idzie funsh
	 */
	int kierunek_funsha;


	/**
	 * glowna petla gry, tak dlugo, dopoki funsh
	 * nie wejdzie w sciane
	 */
	while (kontynuuj_gre) {

		// odczytaj ruch gracza z klawiatury
		kierunek_funsha = odczytaj_ruch_z_klawiatury();

		/**
		 * rusz funshem, jezeli ta funkcja zwroci -1
		 * znaczy, ze walnelismy w sciane....
		 */
		if (przesun_funshem(gracz, kierunek_funsha) == -1) {

			/**
			 * to spowoduje, ze przy kolejnym sprawdzeniu
			 * warunku glownej petli- zakonczy sie
			 */
			kontynuuj_gre = 0;
			// skok do sprawdzenia warunku petli
			continue;
		}

		// TODO jedzonko- innym razem!


		// rysuj
		czysc_ekran();
		rysuj_gre(gracz);
		czekaj_na_kolejna_klatke();
	}


	printf("\n\nGAME OVER!\n");
	return 0;
}
