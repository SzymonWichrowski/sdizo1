#pragma once                                //dyrektywa, dzieki ktorej nie nastepuje redefiniowanie klas
#include "../tablica_dynamiczna/Tablica.h"
#include "../lista_dwukierunkowa/Lista.h"
#include "../kopiec/Kopiec.h"

class Menu {                                //klasa menu glownego
    public:
        Menu();                             //konstruktor domyslny klasy Menu
        void menu();                        //wyswietla menu glowne programu

    private:
    int wybor;                              //zmienna, do ktorej zapisujemy wybor uzytkownika
    const int wylosuj_zakres = 10000;

    Tablica *tablica;                       //wskaznik na obiekt klasy Tablica
    Lista *lista;                           //wskaznik na obiekt klasy Lista
    Kopiec *kopiec;

    static void menuStruktura();            //ogolne menu dla wszystkich struktur
    void backToMenu();                      //ponownie wyswietla menu poczatkowe
    void wyborMenu();                       //obsluguje wybor uzytkownika dotyczacy glownego menu programu

    void menuTablica();                     //wyswietla menu tablicy
    void wyborTablica();                    //obsluguje wybor uzytkownika dotyczacy menu tablicy
    void menuDodawaniaTablica();            //wyswietla menu dodawania elementow do tablicy
    void wyborDodawaniaTablica();           //obsluguje wybor uzytkownika dotyczacy menu dodawania do tablicy
    void menuUsuwaniaTablica();             //wyswietla menu usuwania elementow z tablicy
    void wyborUsuwaniaTablica();            //obsluguje wybor uzytkownika dotyczacy menu usuwania z tablicy
    void wczytajTablice();                  //wczytuje dane z pliku do tablicy
    void wylosujTablice();                  //tworzy tablice z losowymi wartosciami z gory ustalonego przedzialu
    void wyswietlTablice();                 //wyswietla aktualna tablice dynamiczna
    void wyszukajTablica();                 //wyszukiwanie elementu tablilcy wybranego przez uzytkownika
    void menuCzasTablica();                 //menu przeprowadzania pomiarow czasu dla operacji tablic dynamicznych
    void wyborCzasTablica();                //przeprowadza pomiar czasu dla operacji tablicy dynamicznej

    void menuLista();                       //wyswietla menu listy
    void wyborLista();                      //obsluguje wybor uzytkownika dotyczacy menu listy
    void menuDodawaniaLista();              //wyswietla menu dodawania elementow do listy
    void wyborDodawaniaLista();             //obsluguje wybor uzytkownika dotyczacy menu dodawania do listy
    void wczytajListe();                    //wczytuje dane z pliku do listy
    void wylosujListe();                    //tworzy liste z losowymi wartosciami z gory ustalonego przedzialu
    void wyswietlListe();                   //wyswietla aktualna liste dwukierunkowa
    void wyszukajLista();                   //wyszukiwanie elementu listy o wybranym przez uzytkownika kluczu
    void menuUsuwaniaLista();               //wyswietla menu usuwania elementow z listy
    void wyborUsuwaniaLista();              //obsluguje wybor uzytkownika dotyczacy menu usuwania z listy
    void menuCzasLista();                   //menu przeprowadzania pomiarow czasu dla operacji list dwukierunkowych
    void wyborCzasLista();                  //przeprowadza pomiar czasu dla operacji listy dwukierunkowej

    void menuKopiec();                      //wyswietla menu kopca
    void wyborKopiec();                     //obsluguje wybor uzytkownika dotyczacy menu kopca
    void wczytajKopiec();                   //wczytuje dane z pliku do kopca
    void wylosujKopiec();                   //tworzy kopiec z losowymi wartosciami z gory ustalonego przedzialu
    void wyswietlKopiec();                  //wyswietla aktualny kopiec binarny
    void wyszukajKopiec();                  //wyszukiwanie elementu kopca o wybranej przez uzytkownika wartosci
    void dodawanieKopiec();                 //dodawanie elementu do kopca
    void usuwanieKopiec();                  //usuwanie elementu z kopca
    void menuCzasKopiec();                  //menu przeprowadzania pomiarow czasu dla operacji kopca binarnego
    void wyborCzasKopiec();                 //przeprowadza pomiar czasu dla operacji kopca binarnego

    static void defaultWybor();             //operacje wykonane po wyborze przez uzytkownika numeru z poza menu
    void blad();                            //tresc komunikatu bledu wyboru przez uzytkownika niedozwolonej wartosci

    void koniec();                          //koniec programu

};