// Projekt konsolowej strony obslugujacej klijentow linii MPK
//

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;


void czekaj_na_klawisz() {
	getchar();
}


void wyswietl(vector<string>tab) {
	for (int i = 0; i < tab.size(); i++)
	{
		cout << tab[i] << " ";
	}
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
	cout << "Wybierz akcje:" << endl;

	cout << "1. Wyswietl wszystkie linie" << endl;
	cout << "2. Wyswietl rozklad linii" << endl;
	cout << "3. Wyswietl liste przystankow" << endl;
	cout << "4. Wyswietl rozklad przystanku" << endl;
	cout << "5. Pokaz polaczenia" << endl;
	cout << "6. Wyswietl mape miasta" << endl;
	cout << "7. Zaloguj sie na konto administratora" << endl;
	cout << "8. Zamknij system" << endl;
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
	string typ_autobusu;

	Linia(int t_nr_linii, int t_ile_przystankow, string t_typ_autobusu, vector<string>nazwy_przystankow) //podajemy nr linii, przez ile przystankow przejezdza, jaki jest typ autobusu
	{
		nr_linii = t_nr_linii;
		ile_przystankow = t_ile_przystankow;
		typ_autobusu = t_typ_autobusu;
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
		cout << nr_linii << " " << typ_autobusu << " ";
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
		cout << endl << "Nr  Typ autobusu Przystanki" << endl;
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
		if (!czyJestPoloczenie)
			cout << endl << "Nie ma polaczen miedzy przystankami" << endl;

		cout << endl;

	}
};






int main()
{
	MPK MPK_Olsztyn("Olsztyn");

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
			dane_z_pliku_linie[i + 2],			  //typ autobusu
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
			break;
		case '7':
			czekaj_na_klawisz();
			break;
		}
		wyswietl_menu_glowne();
		znak = getchar();
	}


	return 0;
}

