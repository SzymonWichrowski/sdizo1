#include <iostream>
#include <fstream>
#include <random>
#include "Menu.h"

using namespace std;

Menu::Menu() {                         //deklaracja konstruktora domyślnego klasy Menu
    this -> wybor = 0;
    this -> tablica = nullptr;
    this -> lista = nullptr;
    this -> kopiec = nullptr;
}
//menu glowne i ogolne funkcje

void Menu::menu() {

    cout << "-----------" << endl;
    cout << "MENU GLOWNE" << endl;
    cout << "-----------" << endl;
    cout << "Witaj w programie badania efektywnosci operacji dodawania, usuwania oraz wyszukiwania elementow w roznych strukturach danych\n";
    cout << "Do wyboru masz kilka ponizszych struktur. Mozesz tez zakonczyc dzialanie programu:\n";
    cout << endl;
    cout << "1) Tablica dynamiczna" << endl;
    cout << "2) Lista dwukierunkowa" << endl;
    cout << "3) Kopiec binarny" << endl;
    cout << "4) Zakoncz program" << endl;
    cout << endl;
    cout << "Wpisz numer przypisany do struktury, ktora chcesz przetestowac, badz do operacji, ktora chcesz wykonac, a nastepnie wcisnij klawisz ENTER." << endl;
    wyborMenu();
}

void Menu::wyborMenu() {                                //podzial implementacji menu na dwie osobne metody pozwala usunac niepotrzebne powtarzanie sie kodu

    cout << "Numer wybranej struktury lub operacji: ";
    if(!(cin >> wybor)) {                               //warunek sprawdzajacy, czy uzytkownik wpisal do zmiennej wlasciwy typ danych
        blad();                                         //komunikat bledu
    }
    else {                                              //jesli do zmiennej wpisano wlasciwy typ danych
        switch (wybor) {
            case 1:
                tablica = new Tablica();                //musimy stworzyc obiekt, nawet jesli ma wskazywac poczatkowo na NULL
                menuTablica();
                break;
            case 2:
                lista = new Lista();
                menuLista();
                break;
            case 3:
                kopiec = new Kopiec();
                menuKopiec();
                break;
            case 4:
                koniec();
                exit(0);
            default:                                    //wlasciwy typ danych, ale nie mamy w menu, opcji o tym numerze
                defaultWybor();
                wyborMenu();
                break;
        }
    }
}
void Menu::backToMenu() {
    system("cls");
    menu();
}

void Menu::blad() {
    koniec();
    cerr << "UWAGA! NASTAPIL BLAD!!! Uruchom program ponownie." << endl;
    exit(0);
}
void Menu::defaultWybor() {
    cout << "Niestety nie ma takiej opcji w naszym menu. Prosze sprobowac ponownie ;)" << endl;
    cout << endl;
}

void Menu::menuStruktura() {                                   //ogolne menu dla wszystkich struktur

    cout << "Operacje do wyboru:" << endl;
    cout << endl;
    cout << "1) Wczytanie danych z pliku\n"
            "2) Wstawienie losowych danych\n"
            "3) Wyswietlenie struktury\n"
            "4) Dodanie elementu\n"
            "5) Usuniecie elementu\n"
            "6) Wyszukanie elememtu\n"
            "7) Testowanie czasu operacji\n"
            "8) Powrot do menu glownego\n";
    cout << endl;
    cout << "Wpisz ponizej numer przypisany operacji, ktora chcesz wykonac, a nastepnie wcisnij klawisz ENTER." << endl;
}
//tablica dynamiczna

void Menu::menuTablica() {                                    //wyswietla menu obslugi tablicy
    system("cls");
    cout << "------------------------------------" << endl;
    cout << "MENU OPERACJI NA TABLICY DYNAMICZNEJ" << endl;
    cout << "------------------------------------" << endl;
    menuStruktura();
    wyborTablica();
}

void Menu::wyborTablica() {
    cout << "Numer wybranej operacji: ";
    if(!(cin >> wybor)) {
        blad();
    }
    else {
        switch (wybor) {
            case 1:
                wczytajTablice();
                wyborTablica();
                break;
            case 2:
                wylosujTablice();
                wyborTablica();
                break;
            case 3:
                wyswietlTablice();
                wyborTablica();
                break;
            case 4:
                menuDodawaniaTablica();
                break;
            case 5:
                menuUsuwaniaTablica();
                break;
            case 6:
                wyszukajTablica();
                wyborTablica();
                break;
            case 7:
                menuCzasTablica();
                break;
            case 8:
                backToMenu();
                break;
            default:
                defaultWybor();
                wyborTablica();
                break;
        }
    }
}

void Menu::wczytajTablice() {

    string nazwa_pliku;                         //zmienna lokalna, do ktorej uzytkownik wpisze nazwe pliku
    cout << endl;
    cout << "Wpisz nazwe pliku (wraz z rozszerzeniem!), z ktorego program ma wczytac dane." << endl;
    cout << "Nazwa pliku: ";
    cin >> nazwa_pliku;
    cout << endl;
    fstream plik;
    plik.open(nazwa_pliku, ios::in);   //komenda otwierania pliku w celu odczytu danych
    if(!plik.good()) {                          //warunek kiedy nie znaleziono pliku
        cout << "Nie znaleziono takiego pliku!" << endl;
        plik.close();                           //komenda zamkniecia pliku !!!
    }
    else {
        int liczba_element, element;                  //potrzebne do odczytu zmienne lokalne
        if(plik.is_open()) {                    //sprawdzamy, czy plik sie na pewno otworzyl
            plik >> liczba_element;
            if(plik.fail()) {                   //sprawdzamy, czy nie nastapil blad przy odczycie danych z pliku
                cout << "Nastapil blad przy odczycie danych z pliku!";
                plik.close();
            }
            else {                              //jesli nie bylo bledow
                if (liczba_element <= 0) {
                    cout << "Nie mozna utworzyc struktury dla takiej liczby elementow!" << endl;
                }
                else {
                    delete tablica;
                    tablica = new Tablica();
                    for(int i = 0; i < liczba_element; i++) {
                        if(!(plik >> element)) blad();
                        tablica -> dodaj_koniec(element);
                    }
                    plik.close();
                    cout << "Pomyslnie wczytano dane z pliku!" << endl;
                    cout << endl;
                }
            }
        }
        else { cout << "Nastapil blad przy otwarciu pliku!" << endl; }
    }
}

void Menu::wylosujTablice() {

    int ilosc;                  //zmienna lokalna dotyczaca ilosci elementow w nowej strukturze
    cout << endl << "Ile ilementow ma posiadac tablica? Wpisz ilosc i wcisnij klawisz ENTER." << endl;
    cout << "Ilosc elementow: ";
    if(!(cin >> ilosc)) blad();
    else {
        if(ilosc <= 0) cout << "Nie mozna utworzyc tablicy o podanym rozmiarze!" << endl;
        else {
            cout << endl;
            delete tablica;          //usuwamy do tej pory istniejaca tablice
            tablica = new Tablica();
            random_device rd;           //sposob generowania liczba pseudolosowych zaczerpniety z materialow na stronie prowadzacego
            mt19937 gen(rd());
            uniform_int_distribution<> dist(1, wylosuj_zakres);
            for (int i = 0; i < ilosc; i++) {
                tablica ->dodaj_koniec(dist(gen));      //kazdy nowy element dodajemy na ostatnia pozycje tablicy
            }
            cout << "Utworzono losowo tablice o podanym rozmiarze." << endl;
        }
    }
}

void Menu::wyswietlTablice() {
    cout << endl;
    cout << "---------------------------" << endl;
    cout << "AKTUALNA TABLICA DYNAMICZNA" << endl;
    cout << "---------------------------" << endl;
    tablica -> wyswietl();
    cout << endl;
}

void Menu::wyszukajTablica() {
    int wartosc;                                            //zmienna lokalna do ktorej uzytkownik wpisuje wartosc do znalezienia
    cout << endl;
    cout << "Wpisz wartosc elementu do znalezienia w tablicy, a nastepnie wcisnik klawisz ENTER." << endl;
    cout << "Element do znalezienia: ";
    if(!(cin >> wartosc)) blad();
    else {
        if(tablica -> wyszukaj(wartosc)) {
            cout << "Udalo sie! Znaleziono szukany element." << endl;
            tablica ->wyszukajIndeks(wartosc);
        }
        else {
            cout << "Nie znaleziono szukanej wartosci :( Nie ma jej w tablicy." << endl;
        }
        cout << endl;
        cout << "Wpisz ponizej numer przypisany operacji, ktora chcesz wykonac, a nastepnie wcisnij klawisz ENTER." << endl;
    }
}

void Menu::menuDodawaniaTablica() {
    system("cls");
    cout << "-----------------------------------------------" << endl;
    cout << "MENU DODAWANIA ELEMENTOW DO TABLICY DYNAMICZNEJ" << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "Dostepne tryby dodawania:" << endl;
    cout << endl;
    cout << "1) Dodanie elementu na poczatek tablicy" << endl;
    cout << "2) Dodanie elementu na koniec tablicy" << endl;
    cout << "3) Dodanie elementu do komorki tablicy o wskazanym indeksie" << endl;
    cout << "4) Wroc do menu tablicy dynamicznej" << endl;
    cout << endl;
    cout << "Wpisz numer przypisany do trybu dodawania elementu, ktory chcesz wykonac, a nastepnie wcisnij klawisz ENTER. Masz tez mozliwosc powrotu do poprzedniego menu.";
    wyborDodawaniaTablica();
}

void Menu::menuUsuwaniaTablica() {
    system("cls");
    cout << "---------------------------------------------" << endl;
    cout << "MENU USUWANIA ELEMENTOW Z TABLICY DYNAMICZNEJ" << endl;
    cout << "---------------------------------------------" << endl;
    cout << "Dostepne tryby usuwania:" << endl;
    cout << endl;
    cout << "1) Usuwanie elementu z poczatku tablicy" << endl;
    cout << "2) Usuwania elementu z konca tablicy" << endl;
    cout << "3) Usuwanie elementu tablicy o wskazanym indeksie" << endl;
    cout << "4) Wroc do menu tablicy dynamicznej" << endl;
    cout << endl;
    cout << "Wpisz numer przypisany do trybu usuwania elementu, ktory chcesz wykonac, a nastepnie wcisnij klawisz ENTER. Masz tez mozliwosc powrotu do poprzedniego menu.";
    wyborUsuwaniaTablica();
}

void Menu::wyborDodawaniaTablica() {

    int element;                                //zmienna lokalna do ktorej uzytkownik wpisze wartosc
    cout << endl << "Wybrany tryb: ";
    if(!(cin >> wybor))  blad();
    cout << endl;
    switch(wybor) {
        case 1:                                //dodawanie na poczatek tablicy
            cout << "Wpisz element, ktory zostanie dodany do tablicy. Uwaga: musi to byc liczba calkowita!" << endl;
            cout << "Element do dodania: ";
            if(!(cin >> element)) blad();
            tablica -> dodaj_poczatek(element);
            cout << "Dodano element do tablicy. Ponownie wybierz jeden z dostepnych trybow albo wroc do poprzedniego menu." << endl;
            wyborDodawaniaTablica();
            break;
        case 2:                                //dodawanie na koniec tablicy
            cout << "Wpisz element, ktory zostanie dodany do tablicy. Uwaga: musi to byc liczba calkowita!" << endl;
            cout << "Element do dodania: ";
            if(!(cin >> element)) blad();
            tablica -> dodaj_koniec(element);
            cout << "Dodano element do tablicy. Ponownie wybierz jeden z dostepnych trybow albo wroc do poprzedniego menu." << endl;
            wyborDodawaniaTablica();
            break;
        case 3:                                //dodawanie w dowolnym miejscu w tablicy
            cout << "Wpisz element, ktory zostanie dodany do tablicy. Uwaga: musi to byc liczba calkowita!" << endl;
            cout << "Element do dodania: ";
            if(!(cin >> element)) blad();
            int indeks;                        //zmienna lokalna do ktorej uzytkownik wpisze wartosc
            cout << "Wpisz indeks pozycji tabeli, na ktorej ma sie pojawic ten element." << endl;
            cout << "Indeks pozycji nowego elementu: ";
            cin >> indeks;
            if(indeks <= tablica -> getRozmiar() && indeks >= 0) {
                tablica -> dodaj_dowolnie(element, indeks);
                cout << "Dodano element do tablicy. Ponownie wybierz jeden z dostepnych trybow albo wroc do poprzedniego menu." << endl;
                wyborDodawaniaTablica();
            }
            else if(indeks > tablica -> getRozmiar() || indeks < 0) {
                cout << "Nieprawidlowy indeks! Ponownie wybierz tryb dodawania albo wroc do poprzedniego menu." << endl;
                wyborDodawaniaTablica();
            }
            else blad();
            break;
        case 4:                                //powrot do poprzedniego menu
            menuTablica();
            break;
        default:
            defaultWybor();
            wyborDodawaniaTablica();
            break;
    }
}

void Menu::wyborUsuwaniaTablica() {

    cout << endl << "Wybrany tryb: ";
    if(!(cin >> wybor))  blad();
    cout << endl;
    switch(wybor) {
        case 1:                                //usuwamy z poczatku tablicy
            tablica -> usun_poczatek();
            cout << "Ponownie wybierz jeden z dostepnych trybow albo wroc do poprzedniego menu." << endl;
            wyborUsuwaniaTablica();
            break;
        case 2:
            tablica -> usun_koniec();
            cout << "Ponownie wybierz jeden z dostepnych trybow albo wroc do poprzedniego menu." << endl;
            wyborUsuwaniaTablica();
            break;
        case 3:
            int indeks;                        //zmienna lokalna, do ktorej uzytkownik wpisuje indeks elementu do usuniecia
            cout << "Wpisz indeks elementu do usuniecia." << endl;
            cout << "Indeks elementu: ";
            cin >> indeks;
            if(indeks <= tablica -> getRozmiar() && indeks >= 0) {
                tablica ->usun_dowolnie(indeks);
                cout << "Ponownie wybierz jeden z dostepnych trybow albo wroc do poprzedniego menu." << endl;
                wyborUsuwaniaTablica();
            }
            else if(indeks > tablica -> getRozmiar() || indeks < 0) {
                cout << "Nieprawidlowy indeks! Ponownie wybierz tryb usuwania albo wroc do poprzedniego menu." << endl;
                wyborUsuwaniaTablica();
            }
            else blad();
            break;
        case 4:
            menuTablica();
            break;
        default:
            defaultWybor();
            wyborUsuwaniaTablica();
            break;
    }
}

void Menu::menuCzasTablica() {
    system("cls");
    cout << "----------------------------------------------------" << endl;
    cout << "MENU POMIAROW CZASU DLA OPERACJI TABLIC DYNAMICZNYCH" << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "Dostepne rodzaje pomiarow:" << endl;
    cout << "1) Pomiary operacji dodawania elementow do tablicy" << endl;
    cout << "2) Pomiary operacji usuwania elementow z tablicy" << endl;
    cout << "3) Pomiary operacji wyszukiwania elementu w tablicy" << endl;
    cout << "4) Wroc do menu tablicy dynamicznej" << endl;
    cout << endl;
    cout << "Wpisz numer przypisany do rodzaju pomiaru, ktory chcesz przeprowadzic, a nastepnie wcisnij klawisz ENTER. Masz tez mozliwosc powrotu do poprzedniego menu." << endl;
    wyborCzasTablica();
}

void Menu::wyborCzasTablica() {
    cout << "Rodzaj pomiaru: ";
    if(!(cin >> wybor)) blad();
    cout << endl;
    switch(wybor) {
        case 1:
            tablica -> czasDodawania();
            cout << "Ponownie wybierz jeden z dostepnych rodzai pomiarow albo wroc do poprzedniego menu." << endl;
            wyborCzasTablica();
            break;
        case 2:
            tablica -> czasUsuwania();
            cout << "Ponownie wybierz jeden z dostepnych rodzai pomiarow albo wroc do poprzedniego menu." << endl;
            wyborCzasTablica();
            break;
        case 3:
            tablica -> czasWyszukiwania();
            cout << "Ponownie wybierz jeden z dostepnych rodzai pomiarow albo wroc do poprzedniego menu." << endl;
            wyborCzasTablica();
            break;
        case 4:
            menuTablica();
        default:
            defaultWybor();
            wyborCzasTablica();
            break;
    }
}
//lista dwukierunkowa

void Menu::menuLista() {
    system("cls");
    cout << "--------------------------------------" << endl;
    cout << "MENU OPERACJI NA LISCIE DWUKIERUNKOWEJ" << endl;
    cout << "--------------------------------------" << endl;
    menuStruktura();
    wyborLista();
}

void Menu::wyborLista() {
    cout << "Numer wybranej operacji: ";
    if(!(cin >> wybor)) {
        blad();
    }
    else {
        switch (wybor) {
            case 1:
                wczytajListe();
                wyborLista();
                break;
            case 2:
                wylosujListe();
                wyborLista();
                break;
            case 3:
                wyswietlListe();
                wyborLista();
                break;
            case 4:
                menuDodawaniaLista();
                break;
            case 5:
                menuUsuwaniaLista();
                break;
            case 6:
                wyszukajLista();
                wyborLista();
                break;
            case 7:
                menuCzasLista();
                break;
            case 8:
                backToMenu();
                break;
            default:
                defaultWybor();
                wyborLista();
                break;
        }
    }
}

void Menu::wczytajListe() {

    string nazwa_pliku;                         //zmienna lokalna, do ktorej uzytkownik wpisze nazwe pliku
    cout << endl;
    cout << "Wpisz nazwe pliku (wraz z rozszerzeniem!), z ktorego program ma wczytac dane." << endl;
    cout << "Nazwa pliku: ";
    cin >> nazwa_pliku;
    cout << endl;
    fstream plik;
    plik.open(nazwa_pliku, ios::in);   //komenda otwierania pliku w celu odczytu danych
    if(!plik.good()) {                          //warunek kiedy nie znaleziono pliku
        cout << "Nie znaleziono takiego pliku!" << endl;
        plik.close();                           //komenda zamkniecia pliku !!!
    }
    else {
        int liczba_element, element;                  //potrzebne do odczytu zmienne lokalne
        if(plik.is_open()) {                    //sprawdzamy, czy plik sie na pewno otworzyl
            plik >> liczba_element;
            if(plik.fail()) {                   //sprawdzamy, czy nie nastapil blad przy odczycie danych z pliku
                cout << "Nastapil blad przy odczycie danych z pliku!";
                plik.close();
            }
            else {                              //jesli nie bylo bledow
                if (liczba_element <= 0) {
                    cout << "Nie mozna utworzyc struktury dla takiej liczby elementow!" << endl;
                }
                else {
                    delete lista;
                    lista = new Lista();
                    for (int i = 0; i < liczba_element; i++) {
                        if(!(plik >> element)) blad();
                        lista -> dodaj_koniec(element);
                    }
                    plik.close();
                    cout << "Pomyslnie wczytano dane z pliku!" << endl;
                    cout << endl;
                }
            }
        }
        else { cout << "Nastapil blad przy otwarciu pliku!" << endl; }
    }
}

void Menu::wylosujListe() {

    int ilosc;                  //zmienna lokalna dotyczaca ilosci elementow w nowej strukturze
    cout << endl << "Ile ilementow ma posiadac lista? Wpisz ilosc i wcisnij klawisz ENTER." << endl;
    cout << "Ilosc elementow: ";
    if(!(cin >> ilosc)) blad();
    else {
        if(ilosc <= 0) cout << "Nie mozna utworzyc listy o podanym rozmiarze!" << endl;
        else {
            cout << endl;
            delete lista;               //usuwamy do tej pory istniejaca liste
            lista = new Lista();
            random_device rd;           //sposob generowania liczba pseudolosowych zaczerpniety z materialow na stronie prowadzacego
            mt19937 gen(rd());
            uniform_int_distribution<> dist(1, wylosuj_zakres);
            for (int i = 0; i < ilosc; i++) {
                lista -> dodaj_koniec(dist(gen));      //kazdy nowy element dodajemy na ostatnia pozycje listy
            }
            cout << "Utworzono losowo liste o podanym rozmiarze." << endl;
        }
    }
}

void Menu::wyswietlListe() {
    cout << endl;
    cout << "----------------------------" << endl;
    cout << "AKTUALNA LISTA DWUKIERUNKOWA" << endl;
    cout << "----------------------------" << endl;
    lista -> wyswietl();
    cout << endl;
}

void Menu::wyszukajLista() {

    int wartosc;                                            //zmienna lokalna do ktorej uzytkownik wpisuje wartosc do znalezienia
    cout << endl;
    cout << "Wpisz wartosc elementu do znalezienia w liscie, a nastepnie wcisnik klawisz ENTER." << endl;
    cout << "Element do znalezienia: ";
    if(!(cin >> wartosc)) blad();
    else {
        if(lista -> wyszukaj(wartosc)) {
            cout << "Udalo sie! Znaleziono szukany element." << endl;
            lista -> wyszukajIndeks(wartosc);
        }
        else {
            cout << "Nie znaleziono szukanej wartosci :( Nie ma jej w liscie." << endl;
        }
        cout << endl;
        cout << "Wpisz ponizej numer przypisany operacji, ktora chcesz wykonac, a nastepnie wcisnij klawisz ENTER." << endl;
    }
}

void Menu::menuDodawaniaLista() {
    system("cls");
    cout << "------------------------------------------------" << endl;
    cout << "MENU DODAWANIA ELEMENTOW DO LISTY DWUKIERUNKOWEJ" << endl;
    cout << "------------------------------------------------" << endl;
    cout << "Dostepne tryby dodawania:" << endl;
    cout << endl;
    cout << "1) Dodanie elementu na poczatek listy" << endl;
    cout << "2) Dodanie elementu na koniec listy" << endl;
    cout << "3) Dodanie elementu do listy w dowolnym/wybranym miejscu" << endl;
    cout << "4) Wroc do menu listy dwukierunkowej" << endl;
    cout << endl;
    cout << "Wpisz numer przypisany do trybu dodawania elementu, ktory chcesz wykonac, a nastepnie wcisnij klawisz ENTER. Masz tez mozliwosc powrotu do poprzedniego menu.";
    wyborDodawaniaLista();
}



void Menu::wyborDodawaniaLista() {

    int element;                                //zmienna lokalna do ktorej uzytkownik wpisze wartosc
    cout << endl << "Wybrany tryb: ";
    if(!(cin >> wybor))  blad();
    cout << endl;
    switch(wybor) {
        case 1:                                //dodawanie na poczatek listy
            cout << "Wpisz element, ktory zostanie dodany do listy. Uwaga: musi to byc liczba calkowita!" << endl;
            cout << "Element do dodania: ";
            if(!(cin >> element)) blad();
            lista -> dodaj_poczatek(element);
            cout << "Dodano element do listy. Ponownie wybierz jeden z dostepnych trybow albo wroc do poprzedniego menu." << endl;
            wyborDodawaniaLista();
            break;
        case 2:                                //dodawanie na koniec listy
            cout << "Wpisz element, ktory zostanie dodany do listy. Uwaga: musi to byc liczba calkowita!" << endl;
            cout << "Element do dodania: ";
            if(!(cin >> element)) blad();
            lista -> dodaj_koniec(element);
            cout << "Dodano element do listy. Ponownie wybierz jeden z dostepnych trybow albo wroc do poprzedniego menu." << endl;
            wyborDodawaniaLista();
            break;
        case 3:                                //dodawanie w dowolnym miejscu w liscie
            cout << "Wpisz element, ktory zostanie dodany do listy. Uwaga: musi to byc liczba calkowita!" << endl;
            cout << "Element do dodania: ";
            if(!(cin >> element)) blad();
            int indeks;                        //zmienna lokalna do ktorej uzytkownik wpisze wartosc
            cout << "Wpisz indeks pozycji na liscie, ktora ma zajmowac ten element." << endl;
            cout << "Indeks pozycji nowego elementu: ";
            cin >> indeks;
            if(indeks <= lista -> getRozmiar() && indeks >= 0) {
                lista -> dodaj_dowolnie(element, indeks);
                cout << "Dodano element do listy. Ponownie wybierz jeden z dostepnych trybow albo wroc do poprzedniego menu." << endl;
                wyborDodawaniaLista();
            }
            else if(indeks > lista -> getRozmiar() || indeks < 0) {
                cout << "Nieprawidlowy indeks! Ponownie wybierz tryb dodawania albo wroc do poprzedniego menu." << endl;
                wyborDodawaniaLista();
            }
            else blad();
            break;
        case 4:                                //powrot do poprzedniego menu
            menuLista();
            break;
        default:
            defaultWybor();
            wyborDodawaniaLista();
            break;
    }
}

void Menu::menuUsuwaniaLista() {
    system("cls");
    cout << "---------------------------------------------" << endl;
    cout << "MENU USUWANIA ELEMENTOW Z LISTY DWUKIERUNKOWEJ" << endl;
    cout << "---------------------------------------------" << endl;
    cout << "Dostepne tryby usuwania:" << endl;
    cout << endl;
    cout << "1) Usuwanie elementu z poczatku listy" << endl;
    cout << "2) Usuwania elementu z konca listy" << endl;
    cout << "3) Usuwanie elementu listy z dowolnego/wybranego miejsca" << endl;
    cout << "4) Wroc do menu listy dwukierunkowej" << endl;
    cout << endl;
    cout << "Wpisz numer przypisany do trybu usuwania elementu, ktory chcesz wykonac, a nastepnie wcisnij klawisz ENTER. Masz tez mozliwosc powrotu do poprzedniego menu.";
    wyborUsuwaniaLista();
}

void Menu::wyborUsuwaniaLista() {

    cout << endl << "Wybrany tryb: ";
    if(!(cin >> wybor))  blad();
    cout << endl;
    switch(wybor) {
        case 1:                                //usuwamy z poczatku listy
            lista -> usun_poczatek();
            cout << "Ponownie wybierz jeden z dostepnych trybow albo wroc do poprzedniego menu." << endl;
            wyborUsuwaniaLista();
            break;
        case 2:                                //usuwamy z konca listy
            lista -> usun_koniec();
            cout << "Ponownie wybierz jeden z dostepnych trybow albo wroc do poprzedniego menu." << endl;
            wyborUsuwaniaLista();
            break;
        case 3:
            int indeks;                        //zmienna lokalna, do ktorej uzytkownik wpisuje indeks elementu do usuniecia
            cout << "Wpisz indeks elementu do usuniecia." << endl;
            cout << "Indeks elementu: ";
            cin >> indeks;
            if(indeks <= lista -> getRozmiar() && indeks >= 0) {
                lista ->usun_dowolnie(indeks);
                cout << "Ponownie wybierz jeden z dostepnych trybow albo wroc do poprzedniego menu." << endl;
                wyborUsuwaniaLista();
            }
            else if(indeks > lista -> getRozmiar() || indeks < 0) {
                cout << "Nieprawidlowy indeks! Ponownie wybierz tryb usuwania albo wroc do poprzedniego menu." << endl;
                wyborUsuwaniaLista();
            }
            else blad();
            break;
        case 4:
            menuLista();
            break;
        default:
            defaultWybor();
            wyborUsuwaniaLista();
            break;
    }
}

void Menu::menuCzasLista() {
    system("cls");
    cout << "----------------------------------------------------" << endl;
    cout << "MENU POMIAROW CZASU DLA OPERACJI LIST DWUKIERUNKOWYCH" << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "Dostepne rodzaje pomiarow:" << endl;
    cout << "1) Pomiary operacji dodawania elementow do listy" << endl;
    cout << "2) Pomiary operacji usuwania elementow z listy" << endl;
    cout << "3) Pomiary operacji wyszukiwania elementu w liscie" << endl;
    cout << "4) Wroc do menu listy dwukierunkowej" << endl;
    cout << endl;
    cout << "Wpisz numer przypisany do rodzaju pomiaru, ktory chcesz przeprowadzic, a nastepnie wcisnij klawisz ENTER. Masz tez mozliwosc powrotu do poprzedniego menu." << endl;
    wyborCzasLista();
}

void Menu::wyborCzasLista() {
    cout << "Rodzaj pomiaru: ";
    if(!(cin >> wybor)) blad();
    cout << endl;
    switch(wybor) {
        case 1:
            lista -> czasDodawania();
            cout << "Ponownie wybierz jeden z dostepnych rodzai pomiarow albo wroc do poprzedniego menu." << endl;
            wyborCzasLista();
            break;
        case 2:
            lista -> czasUsuwania();
            cout << "Ponownie wybierz jeden z dostepnych rodzai pomiarow albo wroc do poprzedniego menu." << endl;
            wyborCzasLista();
            break;
        case 3:
            lista -> czasWyszukiwania();
            cout << "Ponownie wybierz jeden z dostepnych rodzai pomiarow albo wroc do poprzedniego menu." << endl;
            wyborCzasLista();
            break;
        case 4:
            menuLista();
        default:
            defaultWybor();
            wyborCzasLista();
            break;
    }
}

void Menu::menuKopiec() {
    system("cls");
    cout << "--------------------------------" << endl;
    cout << "MENU OPERACJI NA KOPCU BINARNYM" << endl;
    cout << "--------------------------------" << endl;
    menuStruktura();
    wyborKopiec();
}

void Menu::wyborKopiec() {

    cout << "Numer wybranej operacji: ";
    if(!(cin >> wybor)) blad();
    else {
        switch (wybor) {
            case 1:
                wczytajKopiec();
                wyborKopiec();
                break;
            case 2:
                wylosujKopiec();
                wyborKopiec();
                break;
            case 3:
                wyswietlKopiec();
                wyborKopiec();
                break;
            case 4:
                dodawanieKopiec();
                wyborKopiec();
                break;
            case 5:
                usuwanieKopiec();
                wyborKopiec();
                break;
            case 6:
                wyszukajKopiec();
                wyborKopiec();
                break;
            case 7:
                menuCzasKopiec();
                break;
            case 8:
                backToMenu();
                break;
            default:
                defaultWybor();
                wyborKopiec();
                break;
        }
    }
}

void Menu::wyswietlKopiec() {
    cout << endl;
    cout << "------------------------" << endl;
    cout << "AKTUALNY KOPIEC BINARNY" << endl;
    cout << "------------------------" << endl;
    cout << endl;
    kopiec -> wyswietl();
    cout << endl;
}

void Menu::wczytajKopiec() {

    string nazwa_pliku;                         //zmienna lokalna, do ktorej uzytkownik wpisze nazwe pliku
    cout << endl;
    cout << "Wpisz nazwe pliku (wraz z rozszerzeniem!), z ktorego program ma wczytac dane." << endl;
    cout << "Nazwa pliku: ";
    cin >> nazwa_pliku;
    cout << endl;
    fstream plik;
    plik.open(nazwa_pliku, ios::in);   //komenda otwierania pliku w celu odczytu danych
    if(!plik.good()) {                          //warunek kiedy nie znaleziono pliku
        cout << "Nie znaleziono takiego pliku!" << endl;
        plik.close();                           //komenda zamkniecia pliku !!!
    }
    else {
        int liczba_element, element;                  //potrzebne do odczytu zmienne lokalne
        if(plik.is_open()) {                    //sprawdzamy, czy plik sie na pewno otworzyl
            plik >> liczba_element;
            if(plik.fail()) {                   //sprawdzamy, czy nie nastapil blad przy odczycie danych z pliku
                cout << "Nastapil blad przy odczycie danych z pliku!" << endl;
                plik.close();
            }
            else {                              //jesli nie bylo bledow
                if (liczba_element <= 0) {
                    cout << "Nie mozna utworzyc struktury dla takiej liczby elementow!" << endl;
                }
                else {
                    delete kopiec;
                    kopiec = new Kopiec();
                    int *tab = new int [liczba_element];
                    for(int i = 0; i < liczba_element; i++) {
                        if(!(plik >> element)) blad();
                        tab[i] = element;
                    }
                    plik.close();
                    kopiec ->pobierz(tab, liczba_element);
                    kopiec -> zbudujKopiec();
                    delete [] tab;
                    cout << "Pomyslnie wczytano dane z pliku!" << endl;
                    cout << endl;
                }
            }
        }
        else { cout << "Nastapil blad przy otwarciu pliku!" << endl; }
    }

}

void Menu::dodawanieKopiec() {

    int element;
    cout << "Wpisz element, ktory zostanie dodany do kopca. Uwaga: musi to byc liczba calkowita!" << endl;
    cout << "Element do dodania: ";
    if(!(cin >> element)) blad();
    kopiec -> dodaj(element);
    cout << "Dodano element do kopca. Ponownie wybierz jedna z dostepnych operacji." << endl;
}

void Menu::usuwanieKopiec() {

    kopiec -> usun_korzen();
    cout << "Ponownie wybierz jedna z dostepnych operacji." << endl;
}

void Menu::wyszukajKopiec() {

    int wartosc;                                            //zmienna lokalna do ktorej uzytkownik wpisuje wartosc do znalezienia
    cout << endl;
    cout << "Wpisz wartosc elementu do znalezienia w kopcu, a nastepnie wcisnik klawisz ENTER." << endl;
    cout << "Element do znalezienia: ";
    if(!(cin >> wartosc)) blad();
    else {
        if(kopiec -> wyszukaj(wartosc)) {
            cout << "Udalo sie! Znaleziono szukany element." << endl;
            kopiec -> wyszukajIndeks(wartosc);
        }
        else {
            cout << "Nie znaleziono szukanej wartosci :( Nie ma jej w kopcu." << endl;
        }
        cout << endl;
        cout << "Wpisz ponizej numer przypisany operacji, ktora chcesz wykonac, a nastepnie wcisnij klawisz ENTER." << endl;
    }
}

void Menu::wylosujKopiec() {

    int ilosc;                  //zmienna lokalna dotyczaca ilosci elementow w nowej strukturze
    cout << endl << "Ile ilementow ma posiadac kopiec? Wpisz ilosc i wcisnij klawisz ENTER." << endl;
    cout << "Ilosc elementow: ";
    if(!(cin >> ilosc)) blad();
    else {
        if(ilosc <= 0) cout << "Nie mozna utworzyc kopca o podanym rozmiarze!" << endl;
        else {
            cout << endl;
            delete kopiec;               //usuwamy do tej pory istniejacy kopiec
            kopiec = new Kopiec();
            kopiec -> wylosuj(ilosc, wylosuj_zakres);
            kopiec -> zbudujKopiec();
            cout << "Utworzono losowo kopiec o podanym rozmiarze." << endl;
        }
    }
}

void Menu::menuCzasKopiec() {
    system("cls");
    cout << "-------------------------------------------------" << endl;
    cout << "MENU POMIAROW CZASU DLA OPERACJI KOPCA BINARNEGO" << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "Dostepne rodzaje pomiarow:" << endl;
    cout << "1) Pomiary operacji dodawania elementow do kopca" << endl;
    cout << "2) Pomiary operacji usuwania elementow z kopca" << endl;
    cout << "3) Pomiary operacji wyszukiwania elementu w kopcu" << endl;
    cout << "4) Wroc do menu kopca binarnego" << endl;
    cout << endl;
    cout << "Wpisz numer przypisany do rodzaju pomiaru, ktory chcesz przeprowadzic, a nastepnie wcisnij klawisz ENTER. Masz tez mozliwosc powrotu do poprzedniego menu." << endl;
    wyborCzasKopiec();
}

void Menu::wyborCzasKopiec() {
    cout << "Rodzaj pomiaru: ";
    if(!(cin >> wybor)) blad();
    cout << endl;
    switch(wybor) {
        case 1:
            kopiec -> czasDodawania();
            cout << "Ponownie wybierz jeden z dostepnych rodzai pomiarow albo wroc do poprzedniego menu." << endl;
            wyborCzasKopiec();
            break;
        case 2:
            kopiec -> czasUsuwania();
            cout << "Ponownie wybierz jeden z dostepnych rodzai pomiarow albo wroc do poprzedniego menu." << endl;
            wyborCzasKopiec();
            break;
        case 3:
            kopiec -> czasWyszukiwania();
            cout << "Ponownie wybierz jeden z dostepnych rodzai pomiarow albo wroc do poprzedniego menu." << endl;
            wyborCzasKopiec();
            break;
        case 4:
            menuKopiec();
        default:
            defaultWybor();
            wyborCzasKopiec();
            break;
    }
}

void Menu::koniec() {                          //zwalniamy pamiec przed koncem programu
    delete tablica;
    delete lista;
    delete kopiec;
}