#include "LignesTrams.h"
#include <QPushButton>

Lignestrams::Lignestrams() : d_teteArret{nullptr}, d_arret{d_teteArret},
    d_teteTram{nullptr}, d_tram{d_teteTram}
{}

void Lignestrams::ajouterArret(std::string nom, double duree, int x, int y)
{
    Arretstrams *nc = new Arretstrams{nom, duree, {x, y}};

    if (d_teteArret)
    {
        d_arret->d_suivant = nc;
        nc->d_suivant = nullptr;
        nc->d_precedent = d_arret;
        d_arret = nc;
    }else
    {
        d_teteArret = nc;
        d_arret = d_teteArret;
    }
}

void Lignestrams::ajouterTram(double vitesse)
{
    Tramways *nc = new Tramways{vitesse, d_teteArret->d_coor, d_teteArret};

    if (d_teteTram)
    {
        d_tram->d_suivant = nc;
        nc->d_suivant = nullptr;
        d_tram = nc;
    }else
    {
        d_teteTram = nc;
        d_tram = d_teteTram;
    }
}

void Lignestrams::enleverTram() {
    while (d_teteTram) {
        Tramways *temp = d_teteTram;
        d_teteTram = d_teteTram->d_suivant;
        temp = nullptr;
    }
    d_tram = nullptr;
}

void Lignestrams::enleverArret() {
    while (d_teteArret) {
        Arretstrams *temp = d_teteArret;
        d_teteArret = d_teteArret->d_suivant;
        temp = nullptr;
    }
    d_arret = nullptr;
}


Lignestrams::~Lignestrams()
{
    enleverTram();
    enleverArret();
}

