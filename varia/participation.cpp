#define USDL
#define UTTF
#include <graph2.h>
#include <ghutils.h>

int main() {

    vector <color> kolor;
    kolor.push_back(0xFFEDF8E9);
    kolor.push_back(0xFFBAE4B3);
    kolor.push_back(0xFF74C476);
    kolor.push_back(0xFF31A354);
    kolor.push_back(0xFF006D2C);

    const int liczba_zmiennych = 6;
    const int liczba_kategorii = 5;
    
    array <array<double,liczba_kategorii>, liczba_zmiennych> zmienne;

    array <string, liczba_zmiennych> nazwy;

    array <string, liczba_kategorii> kategorie = {"No answer", "Never", "Rarely", "Occasionally", "Frequently"};
    
    for (auto&zmienna: zmienne) {
        for (int i=0; i<liczba_kategorii; i++) {
            zmienna[i] = 0;
        }    
    }    
    
    double liczba_wierszy = 0;
    
    csvparser in1("contributor_types.csv",';');
    in1.next();
    for (int i =0; i <liczba_zmiennych; i++) {
        nazwy[i] = in1[i];
        }
    while (in1.next()) {
        liczba_wierszy++;
        for (int i = 0; i < liczba_zmiennych; i++) {
            zmienne[i][tonum(in1[i])]++;
        }
    }
    
    for (auto& zmienna: zmienne) {
        for (int i=0; i < liczba_kategorii; i++) {
            zmienna[i] = (zmienna[i]/liczba_wierszy);
        }    
    }

    vec starting = vec (0,0);
    int szerokosc = 100;
    int odstep = 20;
    double dlugosc_paska = 1500;	
    
    pic p;

    style f(0, 0xFF000000,0);
    font ff = makefont("DejaVuSans-Bold.ttf", ";font-family:'DejaVu Sans';font-weight:normal");
    
    svg_normalizer s("proba.svg");

    int nr = 0;
    for (auto&zmienna: zmienne) {

        p+= text(f,ff, starting - vec (20,-60), botright, 40, nazwy[nr]);
        for (int i=0; i <liczba_kategorii; i++) {
            style b(0xFF000000, kolor[i], 1);    
            p+= path(b, {starting, starting + vec (zmienna[i]*dlugosc_paska, 0), starting + vec (zmienna[i]*dlugosc_paska,szerokosc), starting + vec (0, szerokosc), starting});
            starting += vec (zmienna[i]*dlugosc_paska, 0);
        }
        nr++;
        starting = vec (0, nr*szerokosc+nr*odstep);
        }

    int max_opis = 0;
    
    for (int i=0; i <liczba_kategorii; i++) {
        if (ff->textsize(40, nazwy[i]).x > max_opis) {
            max_opis = ff->textsize(40, nazwy[i]).x;
        }   
    }    
    
    vec starting_legend = vec (-max_opis+20, 20+liczba_zmiennych*(szerokosc+odstep)); 
    
        for (int i =0; i<liczba_kategorii; i++) {
           style b(0xFF000000, kolor[i], 1);    
            p+= path(b, {starting_legend, starting_legend + vec (20, 0), starting_legend + vec (20,20), starting_legend + vec (0, 20), starting_legend});
            p+= text(f,ff, starting_legend + vec (40,-20), topleft, 40, kategorie[i]);
            starting_legend += vec (ff->textsize(40, kategorie[i]).x + 200, 0);
        }

        s += p;
  return 0;
}
