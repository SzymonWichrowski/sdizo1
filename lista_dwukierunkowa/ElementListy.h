#pragma once
class ElementListy {

    public:
    ElementListy(int klucz, ElementListy *poprzednik, ElementListy *nastepnik);

    int klucz;
    ElementListy *poprzednik;
    ElementListy *nastepnik;
};