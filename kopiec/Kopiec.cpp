#include <iostream>
#include <cmath>
#include <random>
#include <iomanip>
#include "Kopiec.h"

using namespace std;

Kopiec::Kopiec() {
    this -> kopiec = nullptr;
    this -> rozmiar_kopca = 0;
    cr = cl = cp = "  ";
    cr[0] = 47; cr[1] = 123;                //przypisujemy konkretne znaki z tabeli kodu ASCII
    cl[0] = 92; cl[1] = 123;
    cp[0] = 124;
}

Kopiec::~Kopiec() {
    delete [] kopiec;
    rozmiar_kopca = 0;
}

int Kopiec::rodzic(int indeks) {
    return (indeks - 1) / 2;
}

int Kopiec::lewy_syn(int indeks) {
    return 2*indeks + 1;
}

int Kopiec::prawy_syn(int indeks) {
    return 2*indeks + 2;
}

void Kopiec::przywracanieKopca(int indeks) {

    int najwiekszy, lewy, prawy, bufor;                                     //zmienne lokalne
    lewy = lewy_syn(indeks);
    prawy = prawy_syn(indeks);
    if (lewy < rozmiar_kopca && kopiec[lewy] > kopiec[indeks]) {            //jesli lewy syn jest wiekszy
        najwiekszy = lewy;
    }
    else {
        najwiekszy = indeks;
    }
    if (prawy < rozmiar_kopca && kopiec[prawy] > kopiec[najwiekszy]) {      //jesli prawy syn jest najwiekszy
        najwiekszy = prawy;
    }
    if (najwiekszy != indeks) {
        bufor = kopiec[indeks];                                             //zamieniamy ze soba wartosci
        kopiec[indeks] = kopiec[najwiekszy];
        kopiec[najwiekszy] = bufor;
        przywracanieKopca(najwiekszy);
    }
}

void Kopiec::zbudujKopiec() {

    for (int i = floor(rozmiar_kopca/2); i >= 0; i--) {                 //przywracamy wlasnosc kopca calej strukturze
        przywracanieKopca(i);
    }
}

void Kopiec::kopiuj(const int *pierwotna, int *kopia, int wielkosc) {      //kopiujemy zawartosc jednej tablicy do drugiej
    for(int i = 0; i < wielkosc; i++) {
        kopia[i] = pierwotna[i];
    }
}

void Kopiec::wyswietl() {

    if (kopiec == nullptr) cout << endl << "Nie ma zadnych elementow do wyswietlenia!" << endl;
    else {
        cout << "Kopiec: ";
        for (int i = 0; i < rozmiar_kopca; i++) {                           //wyswietlamy kopiec w formie tablicy, a potem drzewiastej
            cout << kopiec[i] << " ";
        }
        cout << endl << endl;
        wyswietlKopiec();
    }
}

void Kopiec::wyswietlKopiec(string sp, string sn, int v) {                  //ta gotowa procedura pozwala na bardziej przejrzyste wyswietlenie kopca

    string s;
    if (v < rozmiar_kopca) {
        s = sp;
        if (sn == cr) s[s.length() - 2] = ' ';
        wyswietlKopiec(s + cp, cr, 2 * v + 2);
        s = s.substr(0, sp.length() - 2);
        cout << s << sn << kopiec[v] << endl;
        cout << endl;
        s = sp;
        if (sn == cl) s[s.length() - 2] = ' ';
        wyswietlKopiec(s + cp, cl, 2 * v + 1);
    }
}

void Kopiec::wyswietlKopiec() {                                             //wywolanie gotowej procedury
    wyswietlKopiec("", "", 0);
}

void Kopiec::dodaj(int wartosc) {

    if (kopiec == nullptr) {                                                //jesli dodajemy pierwszy element kopca
        rozmiar_kopca = 1;
        kopiec = new int [rozmiar_kopca];
        kopiec[0] = wartosc;
    }
    else {
        int *kopia = new int [rozmiar_kopca];
        kopiuj(kopiec, kopia, rozmiar_kopca);
        delete [] kopiec;
        rozmiar_kopca++;                                                    //zwiekszamy rozmiar kopca
        kopiec = new int [rozmiar_kopca];
        kopiuj(kopia, kopiec, rozmiar_kopca - 1);
        delete [] kopia;
        int i = rozmiar_kopca - 1;
        while (i > 0 && kopiec[rodzic(i)] < wartosc) {               //dodajemy argument na wlasciwa pozycje, tak aby zachowac wlasnosc kopca
            kopiec[i] = kopiec[rodzic(i)];
            i = rodzic(i);
        }
        kopiec[i] = wartosc;
    }
}

void Kopiec::usun_korzen() {

    if (kopiec == nullptr) cout << "Nie ma elementu do usuniecia!" << endl;
    if (rozmiar_kopca == 1) {
        delete [] kopiec;
        rozmiar_kopca = 0;
        cout << "Usunieto jedyny element kopca." << endl;
    }
    else {
        int *kopia = new int [rozmiar_kopca];
        kopiuj(kopiec, kopia, rozmiar_kopca);
        delete [] kopiec;
        rozmiar_kopca--;                                                    //zmniejszamy rozmiar kopca, z zamiarem pozbycia sie korzenia
        kopiec = new int [rozmiar_kopca];
        kopiec[0] = kopia[rozmiar_kopca];                                   //w miejsce korzenia wpisujemy ostatni element w skopiowanej tablicy
        for (int i = 1; i < rozmiar_kopca; i++) {
            kopiec[i] = kopia[i];                                           //indeksy pozostalych elementow pozostaja bez zmian
        }
        delete [] kopia;
        przywracanieKopca(0);                                         //przywracamy wlasnosc kopca; znajdujemy odpowiednie miejsce dla aktualnego korzenia
        cout << "Usunieto korzen kopca." << endl;
    }
}

bool Kopiec::wyszukaj(int szukana) {
    bool trueOrfalse = false;
    if (kopiec == nullptr) trueOrfalse = false;
    else {
        for (int i = 0; i < rozmiar_kopca; i++) {
            if (kopiec[i] == szukana) {
                trueOrfalse = true;
                break;
            }
        }
    }
    return trueOrfalse;
}

void Kopiec::wyszukajIndeks(int szukana) {
    for (int i = 0; i < rozmiar_kopca; i++) {
        if (kopiec[i] == szukana) {
            cout << "Szukana wartosc znajduje sie na " << i << " pozycji.(indeksujac od zera)" << endl;
            break;
        }
    }
}

void Kopiec::wylosuj(int rozmiar, int zakres) {
    rozmiar_kopca = rozmiar;
    kopiec = new int [rozmiar_kopca];
    random_device rd;           //sposob generowania liczba pseudolosowych zaczerpniety z materialow na stronie prowadzacego
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, zakres);
    for (int i = 0; i < rozmiar_kopca; i++) {
        kopiec[i] = dist(gen);
    }
}

void Kopiec::pobierz(int *tab, int rozmiar) {
    rozmiar_kopca = rozmiar;
    kopiec = new int [rozmiar_kopca];
    kopiuj(tab, kopiec, rozmiar);
}
//czas

void Kopiec::wylosujKopiec(int roz) {

    if(kopiec != nullptr) {
        delete [] kopiec;                                       //usuwamy dotychczasowy kopiec
        rozmiar_kopca = 0;
    }
    wylosuj(roz, zakres_testowania);
    zbudujKopiec();
}

void Kopiec::czasDodawania() {
    cout << "------------------------------------------------------------------" << endl;
    cout << "POMIARY CZASU DLA OPERACJI DODAWANIA ELEMENTOW DO KOPCA BINARNEGO" << endl;
    cout << "------------------------------------------------------------------" << endl;
    cout << endl;
    cout << "Pomiary czasu na kopcach o roznym rozmiarze:" << endl;
    cout << endl;
    double pomiary[7];
    pomiary[0] = czasDodawania(10000);
    pomiary[1] = czasDodawania(50000);
    pomiary[2] = czasDodawania(100000);
    pomiary[3] = czasDodawania(250000);
    pomiary[4] = czasDodawania(500000);
    pomiary[5] = czasDodawania(750000);
    pomiary[6] = czasDodawania(1000000);
    czasWyniki(pomiary);
}

double Kopiec::czasDodawania(int roz) {

    int nowy;
    double czas_suma = 0;                                               //poczatkowo musi byc przypisana wartosc zero
    for (int i = 0; i < proby; i++) {                                   //proby to ilosc losowych kopcow na ktorych wyprobujemy operacje
        wylosujKopiec(roz);                                             //przy kazdej iteracji generujemy nowa losowa populacje
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(1, zakres_testowania);
        nowy = dist(gen);
        czas.czasStart();
        dodaj(nowy);                                             //operacja ktorej czas mierzymy
        czas.czasKoniec();
        czas_suma = czas_suma + (1000000.0 * czas.getElapsed()) / czas.getFrequency();         //dodajemy do zmiennej kolejne rezultaty mierzenia czasu [ms]
    }
    return czas_suma/proby;
}

void Kopiec::czasUsuwania() {
    cout << "--------------------------------------------------------------------------" << endl;
    cout << "POMIARY CZASU DLA OPERACJI USUWANIA ELEMENTOW (KORZENIA) Z KOPCA BINARNEGO" << endl;
    cout << "--------------------------------------------------------------------------" << endl;
    cout << endl;
    cout << "Pomiary czasu na kopcach o roznym rozmiarze:" << endl;
    cout << endl;
    double pomiary[7];
    cout << "UWAGA: wystapia dodatkowe powiadomienia o usunieciu elementow. Prosze nie zwracac na nie uwagi!" << endl;
    pomiary[0] = czasUsuwania(10000);
    pomiary[1] = czasUsuwania(50000);
    pomiary[2] = czasUsuwania(100000);
    pomiary[3] = czasUsuwania(250000);
    pomiary[4] = czasUsuwania(500000);
    pomiary[5] = czasUsuwania(750000);
    pomiary[6] = czasUsuwania(1000000);
    cout << "Koniec dodatkowych powiadomien!" << endl;
    czasWyniki(pomiary);
}

double Kopiec::czasUsuwania(int roz) {

    double czas_suma = 0;                                           //poczatkowo musi byc przypisana wartosc zero
    for (int i = 0; i < proby; i++) {                               //proby to ilosc losowych kopcow na ktorych wyprobujemy operacje
        wylosujKopiec(roz);                                        //przy kazdej iteracji generujemy nowa losowa populacje
        czas.czasStart();
        usun_korzen();                                            //operacja ktorej czas mierzymy
        czas.czasKoniec();
        czas_suma = czas_suma + (1000000.0 * czas.getElapsed()) / czas.getFrequency();         //dodajemy do zmiennej kolejne rezultaty mierzenia czasu [ms]
    }
    return czas_suma/proby;
}

void Kopiec::czasWyszukiwania() {
    cout << "------------------------------------------------------------------" << endl;
    cout << "POMIARY CZASU DLA OPERACJI WYSZUKIWANIA ELEMENTOW W KOPCU BINARNYM" << endl;
    cout << "------------------------------------------------------------------" << endl;
    cout << endl;
    cout << "Pomiary czasu na kopcach o roznym rozmiarze:" << endl;
    cout << endl;
    double pomiary[7];
    pomiary[0] = czasWyszukiwania(10000);
    pomiary[1] = czasWyszukiwania(50000);
    pomiary[2] = czasWyszukiwania(100000);
    pomiary[3] = czasWyszukiwania(250000);
    pomiary[4] = czasWyszukiwania(500000);
    pomiary[5] = czasWyszukiwania(750000);
    pomiary[6] = czasWyszukiwania(1000000);
    czasWyniki(pomiary);
}

double Kopiec::czasWyszukiwania(int roz) {

    int szukana;
    bool odp;
    double czas_suma = 0;
    for (int i = 0; i < proby; i++) {
        wylosujKopiec(roz);
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(1, zakres_testowania);
        szukana = dist(gen);
        czas.czasStart();
        odp = wyszukaj(szukana);
        czas.czasKoniec();
        czas_suma = czas_suma + (1000000.0 * czas.getElapsed()) / czas.getFrequency();
    }
    return czas_suma/proby;
}

void Kopiec::czasWyniki(double *pomiary) {

    cout << "1) dla 10000 elementow: " << setprecision(3) << pomiary[0] << " us" << endl;
    cout << "2) dla 50000 elementow: " << setprecision(3) << pomiary[1] << " us" << endl;
    cout << "3) dla 100000 elementow: " << setprecision(3) << pomiary[2] << " us" << endl;
    cout << "4) dla 250000 elementow: " << setprecision(3) << pomiary[3] << " us" << endl;
    cout << "5) dla 500000 elementow: " << setprecision(3) << pomiary[4] << " us" << endl;
    cout << "6) dla 750000 elementow: " << setprecision(3) << pomiary[5] << " us" << endl;
    cout << "7) dla 1000000 elementow: " << setprecision(3) << pomiary[6] << " us" << endl;
    cout << endl;
}
