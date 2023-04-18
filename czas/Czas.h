#pragma once
class Czas {

    public:
        Czas();                             //konstruktor domyslny klasy Czas
        void czasStart();                          //rozpoczyna mierzenie czasu
        void czasKoniec();                         //konczy mierzenie czasu
       // double czas();                       //wyswietla wynik mierzenia czasu
       long long int getFrequency();
       long long int getElapsed();

    private:
        long long int frequency;
        long long int start;
        long long int elapsed;

        static long long int readQPC();            //zwraca liczbe impulsow licznika
};