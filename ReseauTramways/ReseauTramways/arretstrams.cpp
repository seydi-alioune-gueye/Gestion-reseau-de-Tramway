#include "ArretsTrams.h"
#include <cmath>

Arretstrams::Arretstrams(std::string nom, double duree, const Coordonnees& coor,
                         Arretstrams* suivant, Arretstrams* precedent) :
    d_nom{nom}, d_duree{duree}, d_coor{coor},
    d_suivant{suivant}, d_precedent{precedent}
{}

std::string Arretstrams::getnom() const
{
    return d_nom;
}

double Arretstrams::getduree() const
{
    return d_duree;
}

Coordonnees Arretstrams::getcoordonnees() const
{
    return {d_coor.getX(), d_coor.getY()};
}


Arretstrams *Arretstrams::getArretSuivant() const
{
    return d_suivant;
}

Arretstrams *Arretstrams::getArretPrecedent() const
{
    return d_precedent;
}

double Arretstrams::distanceArretSuivant() const
{
    if (d_suivant == nullptr) {
        // Traitement pour l'arrêt en fin de liste.
        return -1.0; // Par exemple: retourner -1 pour indiquer qu'il n'y a pas d'arrêt suivant.
    }

    // Calculer la distance jusqu'à l'arrêt suivant.
    return sqrt(pow(d_suivant->getcoordonnees().getX() - d_coor.getX(), 2) +
                pow(d_suivant->getcoordonnees().getY() - d_coor.getY(), 2));

}

double  Arretstrams::distanceArretPrecedent() const
{

    // Si l'arrêt est en tête de liste (pas d'arrêt précédent), retournez 0

    if (d_precedent == nullptr) {
        // Traitement pour l'arrêt en tête de liste.
        return 0.0;
    }

    // Calculer la distance  jusqu'à l'arrêt précédent.
    return sqrt(pow(d_precedent->getcoordonnees().getX() - d_coor.getX(), 2) +
                pow(d_precedent->getcoordonnees().getY() - d_coor.getY(), 2));
}
