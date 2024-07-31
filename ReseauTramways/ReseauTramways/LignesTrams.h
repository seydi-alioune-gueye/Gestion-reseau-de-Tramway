#ifndef LIGNESTRAMS_H
#define LIGNESTRAMS_H

#include "ArretsTrams.h"
#include "Tramways.h"
#include "Coordonnees.h"
#include <string>

class Lignestrams
{
public:
    Lignestrams();
    ~Lignestrams();
    void ajouterTram(double vitesse);
    void enleverTram();
    void ajouterArret(std::string nom, double duree, int x, int y);
    void enleverArret();
    Tramways* getD_teteTram() const {
        return d_teteTram;
    }
    Arretstrams* getD_teteArret() const {
        return d_teteArret;
    }

    friend class Simulationtrams;
private:
    Arretstrams* d_teteArret;
    Arretstrams* d_arret;
    Tramways* d_teteTram;
    Tramways* d_tram;
};


#endif // LIGNESTRAMS_H
