#ifndef ARRETSTRAMS_H
#define ARRETSTRAMS_H

#include "Coordonnees.h"
#include <string>

class QLabel;

class Arretstrams
{
public:
    Arretstrams(std::string nom, double duree, const Coordonnees& coor,
                Arretstrams* suivant = nullptr, Arretstrams* precedent = nullptr);




    double getduree() const; // Renvoie le temps d'arret minimum sur l'arrêt
    std::string getnom() const;// Renvoie le nom de l'arrêt
    Arretstrams* getArretSuivant() const; // Renvoie l'arrêt suivant
    Arretstrams* getArretPrecedent() const;  // Renvoie l'arrêt précédent
    Coordonnees getcoordonnees() const;// renvoie la position de l'arret


    double distanceArretSuivant() const;
    double distanceArretPrecedent() const;
    friend class Lignestrams;
    friend class Simulationtram;
    friend class Tramways;

private:
    std::string d_nom; // Nom de l'arrêt
    double d_duree; // Temps que met un tram à l'arrêt
    Coordonnees d_coor; // Coordonnées de l'arrêt sur l'écran
    Arretstrams* d_suivant; // Un pointeur vers l'arrêt suivant
    Arretstrams* d_precedent;// un pointeur vers l'arret precedent
    QLabel* d_arret;
    QLabel* d_coordonnees;
};

#endif // ARRETSTRAMS_H*/
