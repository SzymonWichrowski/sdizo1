#pragma once
#include "../czas/Czas.h"
#include <string>

class Tablica {                                                     //klasa tablicy dynamicznej

    public:
        Tablica();                                                  //konstruktor klasy Tablica
        ~Tablica();                                                 //destruktor klasy Tablica
        int getRozmiar() const;                                     //pobiera wartosc z prywatnego pola rozmiar_kopca
        void wyswietl();                                            //wyswietla tablice dynamiczna
        //dodawanie

        void dodaj_poczatek(int nowy);                              //dodaje argument na poczatek tablicy
        void dodaj_koniec(int nowy);                                //dodaje argument na koniec tabeli
        void dodaj_dowolnie(int nowy, int miejsce);                 //dodaje argument na wybrane dowolnie miejsce tabeli
        //usuwanie

        void usun_poczatek();                                       //usuwa pierwszy element tablicy
        void usun_koniec();                                         //usuwa ostatni element tablicy
        void usun_dowolnie(int miejsce);                            //usuwa element z wybranego przez uzytkownika miejsca
        //szukanie

        bool wyszukaj(int wartosc);                                 //szuka, czy argument wystepuje w tablicy
        void wyszukajIndeks(int wartosc);                           //szuka indeksu argumentu w tablicy
        //czas

        void czasDodawania();                       //wyznacza pomiary czasu dla operacji dodawania elementow do tablicy
        void czasUsuwania();                        //wyznacza pomiary czasu dla operacji usuwania elementow z tablicy
        void czasWyszukiwania();                    //wyznacza pomiary czasu dla operacji wyszukiwania wartosci w tablicy

    private:
        int rozmiar;                                                //rozmiar_kopca tablicy
        int *tab;                                                   //zmienna wskaznikowa przechowujaca adres pierwszego elementu tablicy

        Czas czas;                                                  //obiekt klasy Czas, ktory bedzie potrzebny do mierzenia czasu operacji
        const int zakres_testowania = 10000;
        const int proby = 10;                                       //ilosc prob wykonania danej operacji na roznych losowych tablicach

        static void kopiuj(const int *pierwotna, int *kopia, int wielkosc);      //tworzy kopie tablicy pierwotnej o tej samej wielkosci

        void wylosujTablice(int rozmiar);                           //tworzy losowo tablice o podanym rozmiarze

        void czasDodawania_poczatek();                              //wyswietla wyniki ponizszej metody
        double czasDodawania_poczatek(int roz);                     //sredni czas przy wielokrotnym dodawaniu elementu na poczatek tablicy
        void czasDodawania_koniec();                                //wyswietla wyniki ponizszej metody
        double czasDodawania_koniec(int roz);                       //sredni czas przy wielokrotnym dodawaniu elementu na koniec tablicy
        void czasDodawania_dowolnie();
        double czasDodawania_dowolnie(int roz);

        void czasUsuwania_poczatek();
        double czasUsuwania_poczatek(int roz);
        void czasUsuwania_koniec();
        double czasUsuwania_koniec(int roz);
        void czasUsuwania_dowolnie();
        double czasUsuwania_dowolnie(int roz);

        double czasWyszukiwnia(int roz);

        void czasWyniki(double *pomiary);
};