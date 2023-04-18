#include <iostream>
#include <random>
#include <iomanip>
#include "Lista.h"

using namespace std;

Lista::Lista() {
    this -> rozmiar = 0;
    this -> glowa = nullptr;
    this -> ogon = nullptr;
    this -> aktualny = nullptr;
}

Lista::~Lista() {

    if (glowa != nullptr) {
        for (int i = 0; i < rozmiar; i++) {
            aktualny = glowa -> nastepnik;          //przypisuje naastepnik jako aktualny element (poczatkowo nastepnik glowy)
            delete glowa;                           //usuwamy aktualnie pierwszy element w liscie
            glowa = aktualny;                       //po ostatnim wywolaniu petli wszystkie wskazniki beda nullptr
        }
        rozmiar = 0;
    }
}

void Lista::wyswietl() {
    if (glowa == nullptr) {
        cout << endl << "Nie ma zadnych elementow do wyswietlenia!" << endl;
    }
    else {
        aktualny = glowa;                       //na poczatek aktualnym elementem bedzie glowa
        cout << endl << "Lista: ";
        for (int i = 0; i < rozmiar; i++) {
            cout << aktualny -> klucz << " ";
            aktualny = aktualny -> nastepnik;   //przypisujemy nastepnik jako aktualny element
        }
        aktualny = ogon;                        //na poczatku aktualnym elementem bedzie ogon
        cout << endl << "Lista od tylu: ";
        for (int i = 0; i < rozmiar; i++) {
            cout << aktualny -> klucz << " ";
            aktualny = aktualny ->poprzednik;   //przypisujemy poprzednik jako aktualny element
        }
        cout << endl;
    }
}

bool Lista::wyszukaj(int szukana) {
    bool trueOrfalse = false;
    if(glowa == nullptr) trueOrfalse = false;
    else {
        aktualny = glowa;
        for (int i = 0; i < rozmiar; i++) {
            if (aktualny -> klucz == szukana) {             //sprawdzamy, czy aktualny element ma szukany klucz
                trueOrfalse = true;                         //jesli tak to zwracamy true i przerywamy petle for
                break;
            }
            aktualny = aktualny -> nastepnik;               //nastepnie sprawdzamy nastepnika
        }
    }
    return trueOrfalse;
}

void Lista::wyszukajIndeks(int szukana) {

    aktualny = glowa;
    for (int i = 0; i < rozmiar; i++) {
        if (aktualny -> klucz == szukana) {
            cout << "Wybrana wartosc znajduje sie na pozycji nr " << i << ".(liczac od zera)" << endl;
            break;
        }
        aktualny = aktualny -> nastepnik;
    }
}

void Lista::dodaj_poczatek(int nowy_klucz) {

    if (glowa == nullptr) {                     //sprawdzamy czy lista ma juz jakies elementy
        glowa = new ElementListy(nowy_klucz, nullptr, nullptr);
        ogon = glowa;                           //lista ma tylko jeden element, czyli glowa jest rownoczesnie ogonem
    }
    else {
        aktualny = glowa;                       //zapamietujemy glowe poprzez dodatkowy wskaznik
        glowa = new ElementListy(nowy_klucz, nullptr, aktualny);
        aktualny -> poprzednik = glowa;         //poprzednikiem aktualnego elementu ma byc glowa (jego nastepnik sie nie zmienia)
    }
    rozmiar++;
}

void Lista::dodaj_koniec(int nowy_klucz) {

    if (glowa == nullptr) {
        ogon = new ElementListy(nowy_klucz, nullptr, nullptr);
        glowa = ogon;
    }
    else {
        aktualny = ogon;                        //zapamietujemy ogon poprzez dodatkowy wskaznik
        ogon = new ElementListy(nowy_klucz, aktualny, nullptr);
        aktualny -> nastepnik = ogon;           //nastepnikiem aktualnego elementu ma byc ogon (jego poprzednik sei nie zmienia)
    }
    rozmiar++;
}

void Lista::dodaj_dowolnie(int nowy_klucz, int miejsce) {

    if (miejsce == 0) dodaj_poczatek(nowy_klucz);
    else if (miejsce == rozmiar) dodaj_koniec(nowy_klucz);
    else {
        if (miejsce < rozmiar/2) {                  //sprawdzamy, w ktorej polowie listy jest "miejsce", aby operacja byla optymalna
            aktualny = glowa;                       //przypadek, gdy jest blizej glowy niz ogona
            for (int i = 1; i < miejsce; i++) {     //chcemy żeby aktualnym elementem byl poprzednik wstawianej wartosci
                aktualny = aktualny -> nastepnik;   //przypisujemy do aktualnego elementu jego nastepnik
            }
        }
        else {
            aktualny = ogon;                        //przypadek, gdy jest blizej ogona niz glowy
            for (int i = 0; i < rozmiar - miejsce; i++) {
                aktualny = aktualny -> poprzednik;  //przypisujemy do aktualnego elementu jego poprzednik
            }
        }
        auto *nowy_element = new ElementListy(nowy_klucz, aktualny, aktualny -> nastepnik);
        aktualny -> nastepnik -> poprzednik = nowy_element;
        aktualny -> nastepnik = nowy_element;
        rozmiar++;
    }
}

void Lista::usun_poczatek() {

    if (glowa == nullptr) cout << "Nie ma zadnych elementow do usuniecia!" << endl;
    if (rozmiar == 1) {
        glowa = nullptr;
        ogon = nullptr;
        rozmiar = 0;
        aktualny = nullptr;
        cout << "Usunieto jedyny element listy!" << endl;
    }
    else {
        aktualny = glowa -> nastepnik;      //ustawiamy drugi elememt listy jako aktualny
        delete glowa;
        aktualny -> poprzednik = nullptr;
        glowa = aktualny;
        rozmiar--;
        cout << "Usunieto pierwszy element listy" << endl;
    }
}

void Lista::usun_koniec() {

    if (glowa == nullptr) cout << "Nie ma zadnych elementow do usuniecia!" << endl;
    if (rozmiar == 1) {
        glowa = nullptr;
        ogon = nullptr;
        rozmiar = 0;
        aktualny = nullptr;
        cout << "Usunieto jedyny element listy!" << endl;
    }
    else {
        aktualny = ogon -> poprzednik;      //ustawiamy przedostatni element jako aktualny
        delete ogon;
        aktualny -> nastepnik = nullptr;
        ogon = aktualny;
        rozmiar--;
        cout << "Usunieto ostatni element listy" << endl;
    }
}

void Lista::usun_dowolnie(int miejsce) {

    if(miejsce == 0) usun_poczatek();
    else if(miejsce == (rozmiar-1)) usun_koniec();
    else {
        if (miejsce < rozmiar/2) {
            aktualny = glowa;
            for (int i = 1; i < miejsce; i++) {
                aktualny = aktualny -> nastepnik;
            }
        }
        else {
            aktualny = ogon;
            for (int i = 0; i < rozmiar - miejsce - 1; i++) {
                aktualny = aktualny -> poprzednik;
            }
        }
        aktualny -> poprzednik -> nastepnik = aktualny -> nastepnik;
        aktualny -> nastepnik -> poprzednik = aktualny -> poprzednik;
        delete aktualny;
        rozmiar--;
        cout << "Usunieto element z wybranej pozycji" << endl;
    }
}

int Lista::getRozmiar() {
    return rozmiar;
}
//pomiary czasu

void Lista::wylosujListe(int roz) {

    if (glowa != nullptr) {                         //usuwamy istniejaca do tej pory liste
        for (int i = 0; i < rozmiar; i++) {
            aktualny = glowa -> nastepnik;          //przypisuje naastepnik jako aktualny element (poczatkowo nastepnik glowy)
            delete glowa;                           //usuwamy aktualnie pierwszy element w liscie
            glowa = aktualny;                       //po ostatnim wywolaniu petli wszystkie wskazniki beda nullptr
        }
        rozmiar = 0;
    }
    random_device rd;           //sposob generowania liczba pseudolosowych zaczerpniety z materialow na stronie prowadzacego
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, zakres_testowania);
    for (int i = 0; i < roz; i++) {
        int random = dist(gen);
        dodaj_koniec(random);      //kazdy nowy element dodajemy na koniec listy
    }
}

void Lista::czasDodawania() {
    cout << "------------------------------------------------------------------------------------" << endl;
    cout << "POMIARY CZASU DLA OPERACJI ZWIAZANYCH Z DODAWANIEM ELEMENTOW DO LISTY DWUKIERUNKOWEJ" << endl;
    cout << "------------------------------------------------------------------------------------" << endl;
    cout << endl;
    czasDodawania_poczatek();
    cout << endl;
    //czasDodawania_koniec();
    cout << endl;
    //czasDodawania_dowolnie();
    cout << endl;
}

void Lista::czasDodawania_poczatek() {

    cout << "Pomiary czasu dla operacji dodawania elementu na poczatek listy:" << endl;
    cout << "(na listach o roznym rozmiarze)" << endl;
    cout << endl;

    double pomiary[7];
    pomiary[0] = czasDodawania_poczatek(10000);
    pomiary[1] = czasDodawania_poczatek(50000);
    pomiary[2] = czasDodawania_poczatek(100000);
    pomiary[3] = czasDodawania_poczatek(250000);
    pomiary[4] = czasDodawania_poczatek(500000);
    pomiary[5] = czasDodawania_poczatek(750000);
    pomiary[6] = czasDodawania_poczatek(1000000);

    czasWyniki(pomiary);
}

double Lista::czasDodawania_poczatek(int roz) {

    double czas_suma = 0;                                           //poczatkowo musi byc przypisana wartosc zero
    for (int i = 0; i < proby; i++) {                               //proby to ilosc losowych list na ktorych wyprobujemy operacje
        wylosujListe(roz);                                          //przy kazdej iteracji generujemy nowa losowa populacje
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(1, zakres_testowania);
        czas.czasStart();
        dodaj_poczatek(dist(gen));                     //operacja ktorej czas mierzymy
        czas.czasKoniec();
        czas_suma = czas_suma + (1000000.0 * czas.getElapsed()) / czas.getFrequency();         //dodajemy do zmiennej kolejne rezultaty mierzenia czasu [ms]
    }
    return czas_suma/proby;
}

void Lista::czasDodawania_koniec() {

    cout << "Pomiary czasu dla operacji dodawania elementu na koniec listy:" << endl;
    cout << "(na listach o roznym rozmiarze)" << endl;
    cout << endl;

    double pomiary[7];
    pomiary[0] = czasDodawania_koniec(10000);
    pomiary[1] = czasDodawania_koniec(50000);
    pomiary[2] = czasDodawania_koniec(100000);
    pomiary[3] = czasDodawania_koniec(250000);
    pomiary[4] = czasDodawania_koniec(500000);
    pomiary[5] = czasDodawania_koniec(750000);
    pomiary[6] = czasDodawania_koniec(1000000);
    czasWyniki(pomiary);
}

double Lista::czasDodawania_koniec(int roz) {

    double czas_suma = 0;                                           //poczatkowo musi byc przypisana wartosc zero
    for (int i = 0; i < proby; i++) {                               //proby to ilosc losowych list na ktorych wyprobujemy operacje
        wylosujListe(roz);                                        //przy kazdej iteracji generujemy nowa losowa populacje
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

void Lista::czasDodawania_dowolnie() {

    cout << "Pomiary czasu dla operacji dodawania elementu w dowolnym(losowym) miejscu listy:" << endl;
    cout << "(na listach o roznym rozmiarze)" << endl;
    cout << endl;

    double pomiary[7];
    pomiary[0] = czasDodawania_dowolnie(10000);
    pomiary[1] = czasDodawania_dowolnie(50000);
    pomiary[2] = czasDodawania_dowolnie(100000);
    pomiary[3] = czasDodawania_dowolnie(250000);
    pomiary[4] = czasDodawania_dowolnie(500000);
    pomiary[5] = czasDodawania_dowolnie(750000);
    pomiary[6] = czasDodawania_dowolnie(1000000);
    czasWyniki(pomiary);
}

double Lista::czasDodawania_dowolnie(int roz) {

    int nowy, miejsce;
    double czas_suma = 0;                                               //poczatkowo musi byc przypisana wartosc zero
    for (int i = 0; i < proby; i++) {                                   //proby to ilosc losowych list na ktorych wyprobujemy operacje
        wylosujListe(roz);                                              //przy kazdej iteracji generujemy nowa losowa populacje
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(1, zakres_testowania);
        nowy = dist(gen);
        uniform_int_distribution<> dist2(0, roz-1);                //losujemy pozycje
        miejsce = dist2(gen);
        czas.czasStart();
        dodaj_dowolnie(nowy, miejsce);                         //operacja ktorej czas mierzymy
        czas.czasKoniec();
        czas_suma = czas_suma + (1000000.0 * czas.getElapsed()) / czas.getFrequency();         //dodajemy do zmiennej kolejne rezultaty mierzenia czasu [ms]
    }
    return czas_suma/proby;
}

void Lista::czasUsuwania() {
    cout << "----------------------------------------------------------------------------------" << endl;
    cout << "POMIARY CZASU DLA OPERACJI ZWIAZANYCH Z USUWANIEM ELEMENTOW Z LISTY DWUKIERUNKOWEJ" << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
    cout << endl;
    czasUsuwania_poczatek();
    cout << endl;
    czasUsuwania_koniec();
    cout << endl;
    czasUsuwania_dowolnie();
    cout << endl;
}

void Lista::czasUsuwania_poczatek() {

    cout << "Pomiary czasu dla operacji usuwania elementu z poczatku listy:" << endl;
    cout << "(na listach o roznym rozmiarze)" << endl;
    cout << endl;

    double pomiary[7];
    cout << "UWAGA: wystapia dodatkowe powiadomienia o usunieciu elementow. Prosze nie zwracac na nie uwagi!" << endl;
    pomiary[0] = czasUsuwania_poczatek(10000);
    pomiary[1] = czasUsuwania_poczatek(50000);
    pomiary[2] = czasUsuwania_poczatek(100000);
    pomiary[3] = czasUsuwania_poczatek(250000);
    pomiary[4] = czasUsuwania_poczatek(500000);
    pomiary[5] = czasUsuwania_poczatek(750000);
    pomiary[6] = czasUsuwania_poczatek(1000000);
    cout << "Koniec dodatkowych powiadomien!" << endl;
    cout << endl;
    cout << "Wyniki pomiarow:" << endl;
    czasWyniki(pomiary);
}

double Lista::czasUsuwania_poczatek(int roz) {

    double czas_suma = 0;                                           //poczatkowo musi byc przypisana wartosc zero
    for (int i = 0; i < proby; i++) {                               //proby to ilosc losowych list na ktorych wyprobujemy operacje
        wylosujListe(roz);                                        //przy kazdej iteracji generujemy nowa losowa populacje
        czas.czasStart();
        usun_poczatek();                                            //operacja ktorej czas mierzymy
        czas.czasKoniec();
        czas_suma = czas_suma + (1000000.0 * czas.getElapsed()) / czas.getFrequency();         //dodajemy do zmiennej kolejne rezultaty mierzenia czasu [ms]
    }
    return czas_suma/proby;
}

void Lista::czasUsuwania_koniec() {

    cout << "Pomiary czasu dla operacji usuwania elementu z konca listy:" << endl;
    cout << "(na listach o roznym rozmiarze)" << endl;
    cout << endl;

    double pomiary[7];
    cout << "UWAGA: wystapia dodatkowe powiadomienia o usunieciu elementow. Prosze nie zwracac na nie uwagi!" << endl;
    pomiary[0] = czasUsuwania_koniec(10000);
    pomiary[1] = czasUsuwania_koniec(50000);
    pomiary[2] = czasUsuwania_koniec(100000);
    pomiary[3] = czasUsuwania_koniec(250000);
    pomiary[4] = czasUsuwania_koniec(500000);
    pomiary[5] = czasUsuwania_koniec(750000);
    pomiary[6] = czasUsuwania_koniec(1000000);
    cout << "Koniec dodatkowych powiadomien!" << endl;
    cout << endl;
    cout << "Wyniki pomiarow:" << endl;
    czasWyniki(pomiary);
}

double Lista::czasUsuwania_koniec(int roz) {

    double czas_suma = 0;                                           //poczatkowo musi byc przypisana wartosc zero
    for (int i = 0; i < proby; i++) {                               //proby to ilosc losowych tablic na ktorych wyprobujemy operacje
        wylosujListe(roz);                                        //przy kazdej iteracji generujemy nowa losowa populacje
        czas.czasStart();
        usun_koniec();                                            //operacja ktorej czas mierzymy
        czas.czasKoniec();
        czas_suma = czas_suma + (1000000.0 * czas.getElapsed()) / czas.getFrequency();         //dodajemy do zmiennej kolejne rezultaty mierzenia czasu [ms]
    }
    return czas_suma/proby;
}

void Lista::czasUsuwania_dowolnie() {

    cout << "Pomiary czasu dla operacji usuwania elementu z dowolnego(losowego) miejsca listy:" << endl;
    cout << "(na listach o roznym rozmiarze)" << endl;
    cout << endl;

    double pomiary[7];
    cout << "UWAGA: wystapia dodatkowe powiadomienia o usunieciu elementow. Prosze nie zwracac na nie uwagi!" << endl;
    pomiary[0] = czasUsuwania_dowolnie(10000);
    pomiary[1] = czasUsuwania_dowolnie(50000);
    pomiary[2] = czasUsuwania_dowolnie(100000);
    pomiary[3] = czasUsuwania_dowolnie(250000);
    pomiary[4] = czasUsuwania_dowolnie(500000);
    pomiary[5] = czasUsuwania_dowolnie(750000);
    pomiary[6] = czasUsuwania_dowolnie(1000000);
    cout << "Koniec dodatkowych powiadomien!" << endl;
    cout << endl;
    cout << "Wyniki pomiarow:" << endl;
    czasWyniki(pomiary);
}

double Lista::czasUsuwania_dowolnie(int roz) {

    int miejsce;
    double czas_suma = 0;                                           //poczatkowo musi byc przypisana wartosc zero
    for (int i = 0; i < proby; i++) {                               //proby to ilosc losowych list na ktorych wyprobujemy operacje
        wylosujListe(roz);                                          //przy kazdej iteracji generujemy nowa losowa populacje
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(0, roz-1);
        miejsce = dist(gen);
        czas.czasStart();
        usun_dowolnie(miejsce);                                     //operacja ktorej czas mierzymy
        czas.czasKoniec();
        czas_suma = czas_suma + (1000000.0 * czas.getElapsed()) / czas.getFrequency();         //dodajemy do zmiennej kolejne rezultaty mierzenia czasu [ms]
    }
    return czas_suma/proby;
}

void Lista::czasWyszukiwania() {

    cout << "-------------------------------------------------------------------------" << endl;
    cout << "POMIARY CZASU DLA OPERACJI WYSZUKIWANIA ELEMENTOW Z LISTY DWUKIERUNKOWEJ" << endl;
    cout << "-------------------------------------------------------------------------" << endl;
    cout << endl;
    cout << "Pomiary czasu na listach o roznym rozmiarze:" << endl;
    cout << endl;
    double pomiary[7];
    pomiary[0] = czasWyszukiwnia(10000);
    pomiary[1] = czasWyszukiwnia(50000);
    pomiary[2] = czasWyszukiwnia(100000);
    pomiary[3] = czasWyszukiwnia(250000);
    pomiary[4] = czasWyszukiwnia(500000);
    pomiary[5] = czasWyszukiwnia(750000);
    pomiary[6] = czasWyszukiwnia(1000000);
    czasWyniki(pomiary);
}

double Lista::czasWyszukiwnia(int roz) {

    int szukana;
    bool odp;
    double czas_suma = 0;
    for (int i = 0; i < proby; i++) {
        wylosujListe(roz);
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

void Lista::czasWyniki(double *pomiary) {

    cout << "1) dla 10000 elementow: " << setprecision(3) << pomiary[0] << " us" << endl;
    cout << "2) dla 50000 elementow: " << setprecision(3) << pomiary[1] << " us" << endl;
    cout << "3) dla 100000 elementow: " << setprecision(3) << pomiary[2] << " us" << endl;
    cout << "4) dla 250000 elementow: " << setprecision(3) << pomiary[3] << " us" << endl;
    cout << "5) dla 500000 elementow: " << setprecision(3) << pomiary[4] << " us" << endl;
    cout << "6) dla 750000 elementow: " << setprecision(3) << pomiary[5] << " us" << endl;
    cout << "7) dla 100000 elementow: " << setprecision(3) << pomiary[6] << " us" << endl;
    cout << endl;
}

