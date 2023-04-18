#include <iostream>
#include <random>
#include <iomanip>
#include "Tablica.h"

using namespace std;

Tablica::Tablica() {
    this -> rozmiar = 0;                                //poczatkowo w zmiennej rozmiar przechowujemy wartosc zero
    this -> tab = nullptr;                              //poczatkowo wskaznik jest pusty
}

Tablica::~Tablica() {
    delete [] tab;
    rozmiar = 0;
}

int Tablica::getRozmiar() const {
    return rozmiar;
}

void Tablica::wyswietl() {
    if(tab == nullptr) cout << endl << "Nie ma zadnych elementow do wyswietlenia!" << endl;
    else {
        cout << endl;
        cout << "Tablica: ";
        for (int i = 0; i < rozmiar; i++) {
            cout << tab[i] << "   ";
        }
        cout << endl;
    }
}

bool Tablica::wyszukaj(int wartosc) {
    bool trueOrfalse = false;
    if(tab == nullptr) trueOrfalse = false;
    else {
        for (int i = 0; i < rozmiar; i++) {
            if(tab[i] == wartosc) {
                trueOrfalse = true;
                break;
            }
        }
    }
    return trueOrfalse;
}

void Tablica::wyszukajIndeks(int wartosc) {                    //uwaga: jesli w tablicy wartosci sie powtarzaja, wyswietla pierwsza znaleziona pozycje
    for (int i = 0; i < rozmiar; i++) {
        if(tab[i] == wartosc) {
            cout << "Wybrana wartosc znajduje sie na pozycji nr " << i << ".(liczac od 0)" << endl;
            break;
        }
    }
}


void Tablica::dodaj_poczatek(int nowy) {                //trzeba rozwazyc przypadek, gdy nie istnieje jeszcze zadna tablica!

    if(tab == nullptr) {                                //jesli wskaznik na pierwszy element tablicy, jest pusty, to nie ma tablicy
        rozmiar = 1;                                    //po utworzeniu nowej tablicy, przez dodanie jednego elementu, bedzie ona miala rozmiar=1
        tab = new int [rozmiar];
        tab[0] = nowy;
    }
    else {
       int *kopia = new int [rozmiar];                  //zmienna wskaznikowa lokalna potrzebna do operacji
       kopiuj(tab, kopia, rozmiar);     //tworzenie aktualnej kopii
       delete [] tab;                                   //usuwanie tablicy z przed dodania elementu
       rozmiar++;                                       //inkrementujemy rozmiar bo nowa tablica musi byc wieksza od poprzedniej
       tab = new int [rozmiar];
       tab[0] = nowy;
       for(int i = 1; i < rozmiar; i++) {
           tab[i] = kopia[i-1];
       }
       delete [] kopia;
    }
}

void Tablica::dodaj_koniec(int nowy) {

    if(tab == nullptr) {
        rozmiar = 1;
        tab = new int [rozmiar];
        tab[0] = nowy;
    }
    else {
        int *kopia = new int [rozmiar];
        kopiuj(tab, kopia, rozmiar);
        delete [] tab;
        rozmiar++;
        tab = new int [rozmiar];
        kopiuj(kopia, tab, rozmiar-1);     //dane zapisane w kopii zapisujemy do nowej tablicy
        tab[rozmiar-1] = nowy;
        delete [] kopia;
    }
}

void Tablica::dodaj_dowolnie(int nowy, int miejsce) {           //niestety nie uzyjemy switcha, bo zmienna rozmiar nie moze byc argumentem case
                                                                //zostaja nam if-y
    if(miejsce == 0) { dodaj_poczatek(nowy); }                  //dla indeksu zero wykona sie dodaj_poczatek
    else if(miejsce == rozmiar)  { dodaj_koniec(nowy); }        //dla indeksu ostatniej komorki wykona sie dodaj_koniec
    else{                                                       //warunek dla wartosci nieskrajnych
        int *kopia = new int [rozmiar];
        kopiuj(tab, kopia, rozmiar);
        delete [] tab;
        rozmiar++;
        tab = new int [rozmiar];
        for (int i = 0; i < rozmiar; i++) {
            if(i < miejsce) {                                   //jesli indeks mniejszy niz nowego elementu to nic nie zmieniamy
                tab[i] = kopia[i];
            }
            else if(i > miejsce) {
                tab[i] = kopia[i-1];
            }
            else {
                tab[i] = nowy;
            }
        }
        delete [] kopia;
    }
}

void Tablica::usun_poczatek() {                                //trzeba rozwazyc przypadek, gdy nie istnieje jeszcze zadna tablica!

    if(tab == nullptr) {
        cout << "Nie ma zadnych elementow do usuniecia!" << endl;
    }
    else if(rozmiar == 1) {                                    //kiedy tablica ma tylko jeden element
        delete [] tab;
        rozmiar = 0;
        cout << "Usunieto jedyny elememt tablicy." << endl;
    }
    else {
        int *kopia = new int [rozmiar];
        kopiuj(tab, kopia, rozmiar);
        delete [] tab;
        rozmiar--;                                             //skoro usuwamy element tablicy to jej rozmiar musi byc mniejszy
        tab = new int [rozmiar];
        for (int i = 0; i < rozmiar; i++) {
            tab[i] = kopia[i+1];
        }
        delete [] kopia;
        cout << "Usunieto pierwszy element tablicy." << endl;
    }
}

void Tablica::usun_koniec() {

    if(tab == nullptr) {
        cout << "Nie ma zadnych elementow do usuniecia!" << endl;
    }
    else if(rozmiar == 1) {
        delete [] tab;
        rozmiar = 0;
        cout << "Usunieto jedyny element tablicy!" << endl;
    }
    else {
        int *kopia = new int [rozmiar];
        kopiuj(tab, kopia, rozmiar);
        delete [] tab;
        rozmiar--;
        tab = new int [rozmiar];
        for (int i = 0; i < rozmiar; i++) {
            tab[i] = kopia[i];
        }
        delete [] kopia;
        cout << "Usunieto ostatni element tablicy" << endl;
    }
}

void Tablica::usun_dowolnie(int miejsce) {

    if(miejsce == 0) usun_poczatek();
    else if(miejsce == (rozmiar-1)) usun_koniec();
    else {
        int *kopia = new int [rozmiar];
        kopiuj(tab, kopia, rozmiar);
        delete [] tab;
        rozmiar--;
        tab = new int [rozmiar];
        for (int i = 0; i < rozmiar; i++) {
            if(i < miejsce) {
                tab[i] = kopia[i];
            }
            else {                                              //przypisujemy wartosci tak jakby element kopia[i] nie istnial
                tab[i] = kopia[i+1];
            }
        }
        delete [] kopia;
        cout << "Usunieto element z wybranej pozycji" << endl;
    }
}

void Tablica::kopiuj(const int *pierwotna, int *kopia, int wielkosc) {
    for(int i = 0; i < wielkosc; i++) {
        kopia[i] = pierwotna[i];
    }
}

//pomiary czasu

void Tablica::czasDodawania() {
    cout << "-----------------------------------------------------------------------------------" << endl;
    cout << "POMIARY CZASU DLA OPERACJI ZWIAZANYCH Z DODAWANIEM ELEMENTOW DO TABLICY DYNAMICZNEJ" << endl;
    cout << "-----------------------------------------------------------------------------------" << endl;
    cout << endl;
    czasDodawania_poczatek();
    cout << endl;
    czasDodawania_koniec();
    cout << endl;
    czasDodawania_dowolnie();
    cout << endl;
}

void Tablica::czasUsuwania() {
    cout << "---------------------------------------------------------------------------------" << endl;
    cout << "POMIARY CZASU DLA OPERACJI ZWIAZANYCH Z USUWANIEM ELEMENTOW Z TABLICY DYNAMICZNEJ" << endl;
    cout << "---------------------------------------------------------------------------------" << endl;
    cout << endl;
    czasUsuwania_poczatek();
    cout << endl;
    czasUsuwania_koniec();
    cout << endl;
    czasUsuwania_dowolnie();
    cout << endl;
}

void Tablica::czasWyszukiwania() {
    cout << "------------------------------------------------------------------------" << endl;
    cout << "POMIARY CZASU DLA OPERACJI WYSZUKIWANIA ELEMENTOW Z TABLICY DYNAMICZNEJ" << endl;
    cout << "-------------------------------------------------------------------------" << endl;
    cout << endl;
    cout << "Pomiary czasu na tablicach o roznych rozmiarach:" << endl;
    cout << endl;
    double pomiary[7];
    pomiary[0] = czasWyszukiwnia(1000);
    pomiary[1] = czasWyszukiwnia(1500);
    pomiary[2] = czasWyszukiwnia(2000);
    pomiary[3] = czasWyszukiwnia(3000);
    pomiary[4] = czasWyszukiwnia(4000);
    pomiary[5] = czasWyszukiwnia(5500);
    pomiary[6] = czasWyszukiwnia(7500);

    czasWyniki(pomiary);
}

void Tablica::wylosujTablice(int roz) {

    delete [] tab;          //usuwamy do tej pory istniejaca tablice
    tab = new int [rozmiar];
    random_device rd;           //sposob generowania liczba pseudolosowych zaczerpniety z materialow na stronie prowadzacego
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, zakres_testowania);
    for (int i = 0; i < roz; i++) {
        int random = dist(gen);
        dodaj_koniec(random);      //kazdy nowy element dodajemy na ostatnia pozycje tablicy
    }
}

void Tablica::czasDodawania_poczatek() {

    cout << "Pomiary czasu dla operacji dodawania elementu na poczatek tablicy:" << endl;
    cout << "(na tablicach o roznym rozmiarze)" << endl;
    cout << endl;

    double pomiary[7];
    pomiary[0] = czasDodawania_poczatek(1000);
    pomiary[1] = czasDodawania_poczatek(1500);
    pomiary[2] = czasDodawania_poczatek(2000);
    pomiary[3] = czasDodawania_poczatek(3000);
    pomiary[4] = czasDodawania_poczatek(4000);
    pomiary[5] = czasDodawania_poczatek(5500);
    pomiary[6] = czasDodawania_poczatek(7500);

    czasWyniki(pomiary);
}

double Tablica::czasDodawania_poczatek(int roz) {

    double czas_suma = 0;                                           //poczatkowo musi byc przypisana wartosc zero
    for (int i = 0; i < proby; i++) {                               //proby to ilosc losowych tablic na ktorych wyprobujemy operacje
        wylosujTablice(roz);                                        //przy kazdej iteracji generujemy nowa losowa populacje
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(1, zakres_testowania);
        czas.czasStart();
        dodaj_poczatek(dist(gen));                         //operacja ktorej czas mierzymy
        czas.czasKoniec();
        czas_suma = czas_suma + (1000000.0 * czas.getElapsed()) / czas.getFrequency();         //dodajemy do zmiennej kolejne rezultaty mierzenia czasu [ms]
    }
    return czas_suma/proby;
}

void Tablica::czasDodawania_koniec() {

    cout << "Pomiary czasu dla operacji dodawania elementu na koniec tablicy:" << endl;
    cout << "(na tablicach o roznym rozmiarze)" << endl;
    cout << endl;

    double pomiary[7];
    pomiary[0] = czasDodawania_koniec(1000);
    pomiary[1] = czasDodawania_koniec(1500);
    pomiary[2] = czasDodawania_koniec(2000);
    pomiary[3] = czasDodawania_koniec(3000);
    pomiary[4] = czasDodawania_koniec(4000);
    pomiary[5] = czasDodawania_koniec(5500);
    pomiary[6] = czasDodawania_koniec(7500);

    czasWyniki(pomiary);
}

double Tablica::czasDodawania_koniec(int roz) {

    double czas_suma = 0;                                           //poczatkowo musi byc przypisana wartosc zero
    for (int i = 0; i < proby; i++) {                               //proby to ilosc losowych tablic na ktorych wyprobujemy operacje
        wylosujTablice(roz);                                        //przy kazdej iteracji generujemy nowa losowa populacje
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(1, zakres_testowania);
        czas.czasStart();
        dodaj_koniec(dist(gen));                         //operacja ktorej czas mierzymy
        czas.czasKoniec();
        czas_suma = czas_suma + (1000000.0 * czas.getElapsed()) / czas.getFrequency();         //dodajemy do zmiennej kolejne rezultaty mierzenia czasu [ms]
    }
    return czas_suma/proby;
}

void Tablica::czasDodawania_dowolnie() {

    cout << "Pomiary czasu dla operacji dodawania elementu w dowolnym(losowym) miejscu tablicy:" << endl;
    cout << "(na tablicach o roznym rozmiarze)" << endl;
    cout << endl;

    double pomiary[7];
    pomiary[0] = czasDodawania_dowolnie(1000);
    pomiary[1] = czasDodawania_dowolnie(1500);
    pomiary[2] = czasDodawania_dowolnie(2000);
    pomiary[3] = czasDodawania_dowolnie(3000);
    pomiary[4] = czasDodawania_dowolnie(4000);
    pomiary[5] = czasDodawania_dowolnie(5500);
    pomiary[6] = czasDodawania_dowolnie(7500);

    czasWyniki(pomiary);
}

double Tablica::czasDodawania_dowolnie(int roz) {

    int nowy, miejsce;
    double czas_suma = 0;                                           //poczatkowo musi byc przypisana wartosc zero
    for (int i = 0; i < proby; i++) {                               //proby to ilosc losowych tablic na ktorych wyprobujemy operacje
        wylosujTablice(roz);                                        //przy kazdej iteracji generujemy nowa losowa populacje
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(1, zakres_testowania);
        nowy = dist(gen);
        uniform_int_distribution<> dist2(0, roz-1);
        miejsce = dist2(gen);
        czas.czasStart();
        dodaj_dowolnie(nowy, miejsce);                         //operacja ktorej czas mierzymy
        czas.czasKoniec();
        czas_suma = czas_suma + (1000000.0 * czas.getElapsed()) / czas.getFrequency();         //dodajemy do zmiennej kolejne rezultaty mierzenia czasu [ms]
    }
    return czas_suma/proby;
}

void Tablica::czasUsuwania_poczatek() {

    cout << "Pomiary czasu dla operacji usuwania elementu z poczatku tablicy:" << endl;
    cout << "(na tablicach o roznym rozmiarze)" << endl;
    cout << endl;

    double pomiary[7];
    cout << "UWAGA: wystapia dodatkowe powiadomienia o usunieciu elementow. Prosze nie zwracac na nie uwagi!" << endl;
    pomiary[0] = czasUsuwania_poczatek(1000);
    pomiary[1] = czasUsuwania_poczatek(1500);
    pomiary[2] = czasUsuwania_poczatek(2000);
    pomiary[3] = czasUsuwania_poczatek(3000);
    pomiary[4] = czasUsuwania_poczatek(4000);
    pomiary[5] = czasUsuwania_poczatek(5500);
    pomiary[6] = czasUsuwania_poczatek(7500);
    cout << "Koniec dodatkowych powiadomien!" << endl;
    cout << endl;
    cout << "Wyniki pomiarow:" << endl;
    czasWyniki(pomiary);
}

double Tablica::czasUsuwania_poczatek(int roz) {

    double czas_suma = 0;                                           //poczatkowo musi byc przypisana wartosc zero
    for (int i = 0; i < proby; i++) {                               //proby to ilosc losowych tablic na ktorych wyprobujemy operacje
        wylosujTablice(roz);                                        //przy kazdej iteracji generujemy nowa losowa populacje
        czas.czasStart();
        usun_poczatek();                                            //operacja ktorej czas mierzymy
        czas.czasKoniec();
        czas_suma = czas_suma + (1000000.0 * czas.getElapsed()) / czas.getFrequency();         //dodajemy do zmiennej kolejne rezultaty mierzenia czasu [ms]
    }
    return czas_suma/proby;
}

void Tablica::czasUsuwania_koniec() {

    cout << "Pomiary czasu dla operacji usuwania elementu z konca tablicy:" << endl;
    cout << "(na tablicach o roznym rozmiarze)" << endl;
    cout << endl;

    double pomiary[7];
    cout << "UWAGA: wystapia dodatkowe powiadomienia o usunieciu elementow. Prosze nie zwracac na nie uwagi!" << endl;
    pomiary[0] = czasUsuwania_koniec(1000);
    pomiary[1] = czasUsuwania_koniec(1500);
    pomiary[2] = czasUsuwania_koniec(2000);
    pomiary[3] = czasUsuwania_koniec(3000);
    pomiary[4] = czasUsuwania_koniec(4000);
    pomiary[5] = czasUsuwania_koniec(5500);
    pomiary[6] = czasUsuwania_koniec(7500);
    cout << "Koniec dodatkowych powiadomien!" << endl;
    cout << endl;
    cout << "Wyniki pomiarow:" << endl;
    czasWyniki(pomiary);
}

double Tablica::czasUsuwania_koniec(int roz) {

    double czas_suma = 0;                                           //poczatkowo musi byc przypisana wartosc zero
    for (int i = 0; i < proby; i++) {                               //proby to ilosc losowych tablic na ktorych wyprobujemy operacje
        wylosujTablice(roz);                                        //przy kazdej iteracji generujemy nowa losowa populacje
        czas.czasStart();
        usun_koniec();                                            //operacja ktorej czas mierzymy
        czas.czasKoniec();
        czas_suma = czas_suma + (1000000.0 * czas.getElapsed()) / czas.getFrequency();         //dodajemy do zmiennej kolejne rezultaty mierzenia czasu [ms]
    }
    return czas_suma/proby;
}

void Tablica::czasUsuwania_dowolnie() {

    cout << "Pomiary czasu dla operacji usuwania elementu z dowolnego(losowego) miejsca tablicy:" << endl;
    cout << "(na tablicach o roznym rozmiarze)" << endl;
    cout << endl;

    double pomiary[7];
    cout << "UWAGA: wystapia dodatkowe powiadomienia o usunieciu elementow. Prosze nie zwracac na nie uwagi!" << endl;
    pomiary[0] = czasUsuwania_dowolnie(1000);
    pomiary[1] = czasUsuwania_dowolnie(1500);
    pomiary[2] = czasUsuwania_dowolnie(2000);
    pomiary[3] = czasUsuwania_dowolnie(3000);
    pomiary[4] = czasUsuwania_dowolnie(4000);
    pomiary[5] = czasUsuwania_dowolnie(5500);
    pomiary[6] = czasUsuwania_dowolnie(7500);
    cout << "Koniec dodatkowych powiadomien!" << endl;
    cout << endl;
    cout << "Wyniki pomiarow:" << endl;
    czasWyniki(pomiary);

}

double Tablica::czasUsuwania_dowolnie(int roz) {

    int miejsce;
    double czas_suma = 0;                                           //poczatkowo musi byc przypisana wartosc zero
    for (int i = 0; i < proby; i++) {                               //proby to ilosc losowych tablic na ktorych wyprobujemy operacje
        wylosujTablice(roz);                                        //przy kazdej iteracji generujemy nowa losowa populacje
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(0, roz-1);
        miejsce = dist(gen);
        czas.czasStart();
        usun_dowolnie(miejsce);                         //operacja ktorej czas mierzymy
        czas.czasKoniec();
        czas_suma = czas_suma + (1000000.0 * czas.getElapsed()) / czas.getFrequency();         //dodajemy do zmiennej kolejne rezultaty mierzenia czasu [ms]
    }
    return czas_suma/proby;
}

double Tablica::czasWyszukiwnia(int roz) {

    int szukana;
    bool odp;
    double czas_suma = 0;
    for (int i = 0; i < proby; i++) {
        wylosujTablice(roz);
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

void Tablica::czasWyniki(double *pomiary) {

    cout << "1) dla 1000 elementow: " << setprecision(3) << pomiary[0] << " us" << endl;
    cout << "2) dla 1500 elementow: " << setprecision(3) << pomiary[1] << " us" << endl;
    cout << "3) dla 2000 elementow: " << setprecision(3) << pomiary[2] << " us" << endl;
    cout << "4) dla 3000 elementow: " << setprecision(3) << pomiary[3] << " us" << endl;
    cout << "5) dla 4000 elementow: " << setprecision(3) << pomiary[4] << " us" << endl;
    cout << "6) dla 5500 elementow: " << setprecision(3) << pomiary[5] << " us" << endl;
    cout << "7) dla 7500 elementow: " << setprecision(3) << pomiary[6] << " us" << endl;
    cout << endl;
}