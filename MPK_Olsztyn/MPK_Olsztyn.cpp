// Projekt konsolowej strony obslugujacej klijentow linii MPK
//

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

bool zalogowano = false;

void czekaj_na_klawisz() {
	getchar();
}


void wyswietl(vector<string>tab) {
	for (int i = 0; i < tab.size(); i++)
	{
		cout << tab[i] << " ";
	}
}

bool czyNalezyString(vector<string>tab,string nazwa,int od_ilu_zaczac,int o_ile_inkrementowac) {
	for (int i = od_ilu_zaczac; i < tab.size(); i+=o_ile_inkrementowac)
	{
		if (tab[i] == nazwa)
			return true;
	}
	return false;
}

bool StringToBool(string napis)
{
	if (napis == "false" || napis == "0" || napis == "nieczynny")
		return false;
	return true;
}

vector<string>wczytywanie_wyrazow_do_wektora(string lokalizacja_pliku) {
	vector<string>wynik;
	ifstream plik;
	plik.open(lokalizacja_pliku, ios::in);
	if (plik.good()) {
		while (!plik.eof()) {
			string wyraz;
			plik >> wyraz;
			wynik.push_back(wyraz);
		}
	}
	else {
		cout << "Dostep do pliku jest niemozliwy" << endl;
	}
	plik.close();
	return wynik;
}

void wyswietl_menu_glowne()
{
	if (!zalogowano) {
		cout << "Wybierz akcje:" << endl;

		cout << "1. Wyswietl wszystkie linie" << endl;
		cout << "2. Wyswietl rozklad linii" << endl;
		cout << "3. Wyswietl liste przystankow" << endl;
		cout << "4. Wyswietl rozklad przystanku" << endl;
		cout << "5. Pokaz polaczenia pomiedzy przystankami" << endl;
		cout << "6. Wyswietl mape miasta" << endl;
		cout << "7. Zaloguj sie na konto administratora" << endl;
		cout << "8. Zamknij system" << endl << endl;
	}
	else {
		cout << "Wybierz akcje:" << endl;

		cout << "1. Wyswietl wszystkie linie" << endl;
		cout << "2. Wyswietl rozklad linii" << endl;
		cout << "3. Wyswietl liste przystankow" << endl;
		cout << "4. Wyswietl rozklad przystanku" << endl;
		cout << "5. Pokaz polaczenia pomiedzy przystankami" << endl;
		cout << "6. Wyswietl mape miasta" << endl;
		cout << "7. Dodaj nowy przystanek" << endl;
		cout << "8. Dodaj nowa linie" << endl;
		cout << "9. Dodaj nowy rozklad przystanku" << endl;
		cout << "0. Wyloguj sie" << endl << endl;
	}
}

struct Rozklad{
	int linia;
	string godzina_odjazdu;
	string w_ktora_strone;
};

vector<string>dane_z_pliku_rozklady = wczytywanie_wyrazow_do_wektora("rozklad_przystankow.txt"); //Wczytywanie danych z pliku przystanki txt i zapisywanie ich do tablicy struktur rozklad



class Przystanek {
	static int licznik;
public:

	string adres;
	string nazwa;
	bool  czyCzynny;
	int id;
	vector<Rozklad>rozklady;

	Przystanek(string t_nazwa, string t_adres, bool t_czyCzynny) {
		licznik++;
		id = licznik;
		nazwa = t_nazwa;
		adres = t_adres;
		czyCzynny = t_czyCzynny;
		//wczytywanie z pliku danych o rozkladzie linii
		for (int i = 0; i < dane_z_pliku_rozklady.size(); i+=4)
		{
			if (nazwa == dane_z_pliku_rozklady[i]){
				Rozklad rozklad;
				rozklad.linia = atoi(dane_z_pliku_rozklady[i + 1].data());
				rozklad.godzina_odjazdu = dane_z_pliku_rozklady[i + 2];
				rozklad.w_ktora_strone = dane_z_pliku_rozklady[i + 3];
				rozklady.push_back(rozklad);
			}
		}
	}

	void wyswietl_rozklad() {
		for (int i = 0; i < rozklady.size(); i++)
		{
			cout << "Linia " << rozklady[i].linia;
			if (rozklady[i].w_ktora_strone != "Koncowy")
				cout << " wyjezdza o godzinie " << rozklady[i].godzina_odjazdu << " w kierunku " << rozklady[i].w_ktora_strone << endl;
			else
				cout << " przyjezdza o godzinie " << rozklady[i].godzina_odjazdu << " Przystanek koncowy " << endl;
		}
		cout << endl;
	}

	void wypisz() {
		cout << id << ". " << nazwa << " " << adres << " ";
		if (czyCzynny){
			cout << "czynny";
		}
		else {
			cout << "nieczynny";
		}
		cout << endl;
	}

};
int Przystanek::licznik = 0;

vector<Przystanek>przystanki;

class Linia {
public:

	int nr_linii;
	int ile_przystankow;
	vector<string>ktore_przystanki;
	string srodek_komunikacji;

	Linia(int t_nr_linii, int t_ile_przystankow, string t_srodek_komunikacji, vector<string>nazwy_przystankow) //podajemy nr linii, przez ile przystankow przejezdza, jaki jest srodek komunikacji
	{
		nr_linii = t_nr_linii;
		ile_przystankow = t_ile_przystankow;
		srodek_komunikacji = t_srodek_komunikacji;
		for (int i = 0; i < ile_przystankow; i++)
		{
			ktore_przystanki.push_back(nazwy_przystankow[i]);
		}
	}

	bool czyNalezyNazwa(string nazwa, vector<Przystanek>tab)
	{
		for (int i = 0; i < tab.size(); i++)
		{
			if (nazwa == tab[i].nazwa)
				return true;
		}
		return false;
	}

	void droga_z_glownego_przystanku(){
		cout << endl << "Droga glowna:" << endl;
		for (int i = 0; i < ktore_przystanki.size(); i++)
		{
			cout << ktore_przystanki[i];
			if (i != ktore_przystanki.size() - 1)
				cout << " -> ";
		}
		cout << endl;
	}
	void droga_powrotna(){
		cout << endl << "Droga powrotna:" << endl;
		for (int i = ktore_przystanki.size(); i > 0; i--)
		{
			cout << ktore_przystanki[i - 1];
			if (i != 1)
				cout << " -> ";
		}
		cout << endl;
	}

	void wyswietl_rozklad(){
		droga_z_glownego_przystanku();
		cout << endl ;
		droga_powrotna();
		cout << endl;
	}

	void wypisz() {
		cout << nr_linii << " " << srodek_komunikacji << " ";
		wyswietl(ktore_przystanki);
		cout << endl;
	}
};

class MPK{
public:
	string miasto;
	vector<Linia>linie;
	MPK(string t_miasto) {
		miasto = t_miasto;
	}

	void wyswietl_liste_linii() {
		cout << endl << "Nr  Sr.kom. Przystanki" << endl;
		for (int i = 0; i < linie.size(); i++)
		{
			linie[i].wypisz();
		}
		cout << endl;
	}
	void wyswietl_rozklad_lini() {
		czekaj_na_klawisz();
		cout << endl << "Podaj nr linii, ktora chcesz zobaczyc" << endl;
		int nr_linii;
		cin >> nr_linii;
		bool czyJestLinia = false;
		for (int i = 0; i < linie.size(); i++)
		{
			if (nr_linii == linie[i].nr_linii) {
				linie[i].wyswietl_rozklad();
				czyJestLinia = true;
			}
		}
		if (!czyJestLinia)
			cout << "Taka linia nie istnieje" << endl;
	}
	void wyswietl_liste_przystankow() {
		cout << endl;
		for (int i = 0; i<przystanki.size(); i++)
		{
			przystanki[i].wypisz();
		}
		cout << endl << endl;
	}

	bool czyJestPrzystanek(string nazwa_przystanku){
		for (int i = 0; i < przystanki.size(); i++)
		{
			if (nazwa_przystanku == przystanki[i].nazwa) {
				return true;
			}
		}
		return false;
	}

	void wyswietl_rozklad_przystanku() {
		czekaj_na_klawisz();
		cout << endl << "Podaj nazwe przystanku, ktorej rozklad chcesz zobaczyc" << endl;
		string nazwa_przystanku;
		cin >> nazwa_przystanku;

		if (czyJestPrzystanek(nazwa_przystanku)) {
			for (int i = 0; i < przystanki.size(); i++)
			{
				if (nazwa_przystanku==przystanki[i].nazwa)
					przystanki[i].wyswietl_rozklad();
			}
		}
		else
			cout << "Taki przystanek nie istnieje" << endl << endl;
	}

	void polaczenia() {
		czekaj_na_klawisz();
		bool czyJestPoloczenie = false;
		cout << endl << "Podaj przystanki, ktorych polaczenie chcesz zobaczyc" << endl;
		string przystanek1, przystanek2;
		cin >> przystanek1; 
		cin >> przystanek2;
		if(przystanek1!=przystanek2) //nie sprawdzac dla takich samych przystankow
			for (int i = 0; i < linie.size(); i++)
			{
				for (int j = 0; j < linie[i].ile_przystankow; j++)
				{
					if (linie[i].ktore_przystanki[j] == przystanek1) {
						for (int k = 0; k < linie[i].ile_przystankow; k++)
						{
							if (linie[i].ktore_przystanki[k] == przystanek2) {
								if (!czyJestPoloczenie)
									cout << "Przez te dwa przystanki jada linie nr: ";
								cout << linie[i].nr_linii << " ";
								czyJestPoloczenie = true;
							}
						}
					}
				}
			}
		else 
			cout << endl << "Podano dwa takie same przystanki" << endl;

		if (!czyJestPoloczenie)
			cout << endl << "Nie ma polaczen miedzy przystankami" << endl;

		cout << endl;

	}
};

MPK MPK_Olsztyn("Olsztyn");

bool logowanie() {

	vector<string>dane = wczytywanie_wyrazow_do_wektora("hasla.txt");
	cout << endl << "Podaj nazwe uzytkownika: " << endl;
	string nazwa_uzytkownika;
	cin >> nazwa_uzytkownika;

	if (czyNalezyString(dane, nazwa_uzytkownika, 0, 2)) {
		cout <<  endl << "Podaj haslo" << endl;
		string haslo;
		cin >> haslo;
		if (czyNalezyString(dane, haslo, 1, 2)) {
			cout << endl << "Zalogowano" << endl;
			return true;
		}
		else {
			cout << endl << "Zle haslo" << endl;
			return false;
		}
	}
	else {
		cout << endl << "Nie ma takiego uzytkownika" << endl;
		return false;
	}
	return false;
}

Przystanek nowy_przystanek() {
	Przystanek wynik("","",0);

	cout << endl << "Podaj nazwe przystanku" << endl;
	cin >> wynik.nazwa;

	cout << endl << "Podaj adres przystanku" << endl;
	cin >> wynik.adres;

	cout << endl << "Czy przystanek jest czynny (Podaj 0 jesli nie lub 1 jesli tak)" << endl;
	cin >> wynik.czyCzynny;

	return wynik;
}

Linia nowa_linia() {
	vector<string>nazwy_przystankow;
	Linia wynik(0, 0, "", nazwy_przystankow);

	cout << endl << "Podaj nr nowej linii" << endl;
	cin >> wynik.nr_linii;

	cout << endl << "Ile przystankow ma miec nowa linia" << endl;
	cin >> wynik.ile_przystankow;
	cout << endl << wynik.ile_przystankow << endl;

	cout << endl << "Jaki srodek komunikacji posiada ta linia" << endl;
	cin >> wynik.srodek_komunikacji;

	for (int i = 0; i < wynik.ile_przystankow; i++)
	{
		string nazwa_przystanku;
		if (i == 0)
			cout << "Podaj przystanek poczatkowy" << endl;
		else if(i==wynik.ile_przystankow-1)
			cout << "Podaj przystanek koncowy" << endl;
		else
			cout << "Podaj przystanek nr " << i+1 << endl;

		cin >> nazwa_przystanku;
		wynik.ktore_przystanki.push_back(nazwa_przystanku);
	}

	return wynik;
}

void nowy_rozklad(string nazwa_przystanku) {
	Rozklad rozklad;

	cout << endl << "Jaka linia przejezdza przez ten przystanek" << endl;
	cin >> rozklad.linia;

	cout << endl << "O ktorej godzinie linia przejezdza przez ten przystanek" << endl;
	cin >> rozklad.godzina_odjazdu;

	cout << endl << "Czy jest to przystanek koncowy linii " << rozklad.linia <<  "? (Wpisz 1 jesli tak lub 0 jesli nie)" << endl;
	bool yorn;
	cin >> yorn;
	if (yorn)
		rozklad.w_ktora_strone = "Koncowy";
	else {
		for (int i = 0; i < MPK_Olsztyn.linie.size(); i++)
		{
			if (rozklad.linia == MPK_Olsztyn.linie[i].nr_linii) {
				cout << "Jesli to glowna trasa wpisz 1 jesli powrotna wpisz 0" << endl;
				cin >> yorn;
				if (yorn) 
					rozklad.w_ktora_strone = MPK_Olsztyn.linie[i].ktore_przystanki[MPK_Olsztyn.linie[i].ile_przystankow - 1]; //przypisuje ostatni przystanek danej linii zmiennej w_ktora_strone
				else
					rozklad.w_ktora_strone = MPK_Olsztyn.linie[i].ktore_przystanki[0]; //przypisuje pierwszy przystanek danej linii zmiennej w_ktora_strone
				break;
			}

		}
	}
	//TO DO sprawdzic tam, gdzie przystanki, rozklady, linie moga nie istniec
	for (int i = 0; i < przystanki.size(); i++)
	{
		if (nazwa_przystanku == przystanki[i].nazwa) {
			przystanki[i].rozklady.push_back(rozklad);
			break;
		}
	}
}

int main()
{
	//Odczyt danych z plikow

	vector<string>dane_z_pliku_przystanki = wczytywanie_wyrazow_do_wektora("przystanki.txt"); //Wczytywanie danych z pliku przystanki txt i zapisywanie ich do tablicy obiektow przystanek
	for (int i = 0; i < dane_z_pliku_przystanki.size(); i += 3)
	{
		Przystanek przystanek(dane_z_pliku_przystanki[i],				   //Nazwa przystanku
			dane_z_pliku_przystanki[i + 1],				   //adres
			StringToBool(dane_z_pliku_przystanki[i + 2])); //czyCzynny
		przystanki.push_back(przystanek);
	}

	vector<string>dane_z_pliku_linie = wczytywanie_wyrazow_do_wektora("linie.txt"); //wczytywanie z pliku danych o liniach

	for (int i = 0; i < dane_z_pliku_linie.size(); i += atoi(dane_z_pliku_linie[i + 1].data()) + 3)
	{
		vector<string>nazwy_przystankow;
		for (int j = 0; j < atoi(dane_z_pliku_linie[i + 1].data()); j++) //zapisujemy do pustego wektora wszystkie przystanki danej linii
		{
			nazwy_przystankow.push_back(dane_z_pliku_linie[i + j + 3]); // Nazwy przystankow zaczynaja sie 4 wyrazem w linii czyli i+3 i wykonuje sie tyle razy ile jest przystankow (dane_z_pliku_linie[i+1])
		}
		Linia linia(atoi(dane_z_pliku_linie[i].data()),   //nr linii
			atoi(dane_z_pliku_linie[i + 1].data()), //ilosc przystankow
			dane_z_pliku_linie[i + 2],			  //srodek komunikacji
			nazwy_przystankow);					  //jakie przystanki

		MPK_Olsztyn.linie.push_back(linia);
	}



	cout << "Witam na stronie MPK.pl" << endl << endl;
	wyswietl_menu_glowne();
	char znak;
	znak = getchar();

	while (znak != '8') {
		switch (znak) {
		case '1':
			MPK_Olsztyn.wyswietl_liste_linii();
			czekaj_na_klawisz();
			czekaj_na_klawisz();
			break;
		case '2':
			MPK_Olsztyn.wyswietl_rozklad_lini();
			czekaj_na_klawisz();
			czekaj_na_klawisz();
			break;
		case '3':
			MPK_Olsztyn.wyswietl_liste_przystankow();
			czekaj_na_klawisz();
			czekaj_na_klawisz();
			break;
		case '4':
			MPK_Olsztyn.wyswietl_rozklad_przystanku();
			czekaj_na_klawisz();
			czekaj_na_klawisz();
		case '5':
			MPK_Olsztyn.polaczenia();
			czekaj_na_klawisz();
			czekaj_na_klawisz();
			break;
		case '6':
			czekaj_na_klawisz();
			czekaj_na_klawisz();
			break;
		case '7':
			zalogowano = logowanie();
			wyswietl_menu_glowne();
			znak = getchar();
			if (zalogowano)
			{
				while (znak != '0') {
					switch (znak) {
					case '1':
						MPK_Olsztyn.wyswietl_liste_linii();
						czekaj_na_klawisz();
						czekaj_na_klawisz();
						break;
					case '2':
						MPK_Olsztyn.wyswietl_rozklad_lini();
						czekaj_na_klawisz();
						czekaj_na_klawisz();
						break;
					case '3':
						MPK_Olsztyn.wyswietl_liste_przystankow();
						czekaj_na_klawisz();
						czekaj_na_klawisz();
						break;
					case '4':
						MPK_Olsztyn.wyswietl_rozklad_przystanku();
						czekaj_na_klawisz();
						czekaj_na_klawisz();
						break;
					case '5':
						MPK_Olsztyn.polaczenia();
						czekaj_na_klawisz();
						czekaj_na_klawisz();
						break;
					case '6':
						czekaj_na_klawisz();
						czekaj_na_klawisz();
						break;
					case '7':
						przystanki.push_back(nowy_przystanek());
						cout << endl << "Dodano nowy przystanek" << endl;
						czekaj_na_klawisz();
						czekaj_na_klawisz();
						break;
					case '8':
						MPK_Olsztyn.linie.push_back(nowa_linia());
						cout << endl << "Dodano nowa linie" << endl;
						czekaj_na_klawisz();
						czekaj_na_klawisz();
						break;
					case '9':
						string nazwa_przystanku;
						cout << endl << "Podaj nazwe przystanku do ktorego chcesz dodac nowy rozklad" << endl;
						cin >> nazwa_przystanku;
						nowy_rozklad(nazwa_przystanku);
						cout << endl << "Dodano nowy rozklad" << endl;
						czekaj_na_klawisz();
						czekaj_na_klawisz();
						break;
					}
					wyswietl_menu_glowne();
					znak = getchar();
				}
				zalogowano = false;
				czekaj_na_klawisz();
			}
			break;
		}
		wyswietl_menu_glowne();
		znak = getchar();
	}


	return 0;
}

