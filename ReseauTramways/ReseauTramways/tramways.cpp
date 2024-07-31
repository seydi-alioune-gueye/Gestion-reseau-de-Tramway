#include "Tramways.h"
#include "ArretsTrams.h"
#include <cmath>
#include <QPushButton>

Tramways::Tramways(double vMax, const Coordonnees& coor, Arretstrams* crt, Tramways* suivant) :
    d_vitesseMax{vMax}, d_vitesseActuelle{0}, d_distanceMin{0}, d_temps{0},
    d_distArretSvt{0}, d_sens{true}, d_coor{coor}, d_suivant{suivant}, d_arret{crt}
{}

double Tramways::vitesseMax() const
{ return d_vitesseMax; }

double Tramways::vitesseActuelle() const
{ return d_vitesseActuelle; }

void Tramways::setVitesseActuelle(double vitesse)
{ d_vitesseActuelle = vitesse; }

double Tramways::distanceMinimale()
{
    double x = 0, y = 0;

    if (d_suivant != nullptr)
    {
        x = std::pow((d_suivant->d_coor.getX() - d_coor.getX()), 2);
        y = std::pow((d_suivant->d_coor.getY() - d_coor.getY()), 2);
    }

    d_distanceMin = std::sqrt(x + y);
    return d_distanceMin;
}

double Tramways::distanceArretSvt()
{
    double x = 0, y = 0;

    Coordonnees coor = d_arret->getcoordonnees();

    if (d_arret != nullptr)
    {
        x = std::pow((coor.getX() - d_coor.getX()), 2);
        y = std::pow((coor.getY() - d_coor.getY()), 2);
    }

    d_distArretSvt = std::sqrt(x + y);
    return d_distArretSvt;
}

/*Coordonnees Tramways::coordonnees() const // A réexaminer ???
{ return {d_coor.getX(), d_coor.getY()}; }
*/
bool Tramways::sensDeplacement() const
{ return d_sens; }

void Tramways::setSensDeplacement()
{
    d_sens = !d_sens;
}

void Tramways::deplacer(int v)
{
    d_coor.deplaceX(v, d_sens);
    d_tram->move(d_coor.getX(), d_coor.getY());
}

