#pragma once
#include "ElementListy.h"
#include "../czas/Czas.h"

class Lista {    //klasa dotyczacza listy dwukierunkowej

    public:
    Lista();                                        //konstruktor klasy Lista
    ~Lista();                                       //destruktor klasy Lista
    int getRozmiar();                               //zwraca rozmiar listy
    void wyswietl();                                //wyswietla liste od poczatku i od konca
    //dodawanie

    void dodaj_poczatek(int nowy_klucz);                //dodaje argument na poczatek listy
    void dodaj_koniec(int nowy_klucz);                  //dodaje argument na koniec listy
    void dodaj_dowolnie(int nowy_klucz, int miejsce);   //dodaje argument na wybrane dowolnie miejsce listy
    //usuwanie

    void usun_poczatek();                               //usuwa glowe
    void usun_koniec();                                 //usuwa ogon
    void usun_dowolnie(int miejsce);                    //usuwa argument z wybranego miejsca listy
    //szukanie

    bool wyszukaj(int szukana);                           //szuka w liscie elementu o wybranym kluczu
    void wyszukajIndeks(int szukana);                     //szuka indeksu argumentu na liscie
    //czas

    void czasDodawania();                       //wyznacza pomiary czasu dla operacji dodawania elementow do listy
    void czasUsuwania();                        //wyznacza pomiary czasu dla operacji usuwania elementow z listy
    void czasWyszukiwania();                    //wyznacza pomiary czasu dla operacji wyszukiwania wartosci w liscie

    private:
    int rozmiar;                                    //zmienna przechowujaca rozmiar listy
    ElementListy *glowa;                            //wskaznik na pierwszy element listy
    ElementListy *ogon;                             //wskaznik na ostatni element listy
    ElementListy *aktualny;                         //wskaznik na aktualny element(ten wskaznik ma charaktrer pomocniczy
                                                                                    //przyda sie przy wielu operacjach)

    const int zakres_testowania = 1000000;
    const int proby = 10;                           //ilosc prob wykonania danej operacji na roznych losowych listach
    Czas czas;

    void wylosujListe(int roz);                             //tworzy losowo liste o podanym rozmiarze

    void czasDodawania_poczatek();                      //wyswietla wyniki ponizszej metody
    double czasDodawania_poczatek(int roz);             //sredni czas przy wielokrotnym dodawaniu elementu na poczatek listy
    void czasDodawania_koniec();                        //wyswietla wyniki ponizszej metody
    double czasDodawania_koniec(int roz);               //sredni czas przy wielokrotnym dodawaniu elementu na koniec listy
    void czasDodawania_dowolnie();                      //wyswietla wyniki ponizszej metody
    double czasDodawania_dowolnie(int roz);             //sredni czas przy wielokrotnym dodawaniu elementu na wybrana pozycje listy

    void czasUsuwania_poczatek();                       //wyswietla wyniki ponizszej metody
    double czasUsuwania_poczatek(int roz);              //sredni czas przy wielokrotnym usuwaniu elementu z poczatku listy
    void czasUsuwania_koniec();                         //wyswietla wyniki ponizszej metody
    double czasUsuwania_koniec(int roz);                //sredni czas przy wielokrotnym usuwaniu elementu z konca listy
    void czasUsuwania_dowolnie();                       //wyswietla wyniki ponizszej metody
    double czasUsuwania_dowolnie(int roz);              //sredni czas przy wielokrotnym usuwaniu elementu z wybranej pozycji listy

    double czasWyszukiwnia(int roz);                    //sredni czas przy wielokrotnym wyszukiwaniu elementu listy

    void czasWyniki(double *pomiary);
};