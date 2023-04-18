#pragma once
#include "../czas/Czas.h"

class Kopiec {      //klasa dotyczaca kopca

    public:
    Kopiec();                                   //konstruktor klasy Kopiec
    ~Kopiec();
    void wyswietl();                            //wyswietla kopiec
    void dodaj(int wartosc);                    //dodaje element do kopca
    void usun_korzen();                         //usuwa korzen
    bool wyszukaj(int szukana);                 //szuka w kopcu wartosc wybrana przez uzytkownika
    void wyszukajIndeks(int szukana);           //wyznacza indeks szukanej wartosci
    void zbudujKopiec();                        //budowanie kopca
    void wylosuj(int rozmiar, int zakres);      //tworzymy losowo tablice o podannym rozmiarze oraz stalym zakresie liczbowym
    void pobierz(int *tab, int rozmiar);        //pobiera wypelniona tablice i jej rozmiar oraz przekopiowuje ja jako kopiec
    void czasDodawania();
    void czasUsuwania();
    void czasWyszukiwania();

    private:
    int *kopiec;                                //wskaznik na pierwszy element tablicy/kopca, czyli korzen
    int rozmiar_kopca;                          //zmienna przechowujaca liczbe elementow kopca przechowywanych w tablicy
    const int proby = 10;
    const int zakres_testowania = 1000000;
    Czas czas;
    std::string cr, cl, cp;                                                     //ciagi znakowe potrzebne do wyswietlenia kopca

    int rodzic(int indeks);                     //zwraca indeks rodzica wezla, ktorego indeks podano w argumencie
    int lewy_syn(int indeks);                   //zwraca indeks lewego syna wezla, ktorego indeks podano w argumencie
    int prawy_syn(int indeks);                  //zwraca indeks prawego syna wezla, ktorego indeks podano w argumencie
    void przywracanieKopca(int indeks);         //przywraca wlasnosci kopca
    static void kopiuj(const int *pierwotna, int *kopia, int wielkosc);         //tworzy kopie tablicy pierwotnej o tej samej wielkosci
    void wyswietlKopiec(std::string sp, std::string sn, int v);                 //gotowa procedura do wyswietlenia kopca
    void wyswietlKopiec();
    void wylosujKopiec(int roz);                                                //tworzy losowy kopiec do testow
    void czasWyniki(double *pomiary);
    double czasDodawania(int roz);
    double czasUsuwania(int roz);
    double czasWyszukiwania(int roz);
};