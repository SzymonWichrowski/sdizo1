#include "ElementListy.h"

using namespace std;

ElementListy::ElementListy(int klucz, ElementListy *poprzednik, ElementListy *nastepnik) {

    ElementListy::klucz = klucz;
    ElementListy::poprzednik = poprzednik;
    ElementListy::nastepnik = nastepnik;
}