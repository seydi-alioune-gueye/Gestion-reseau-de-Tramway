#ifndef TRAMWAYS_H
#define TRAMWAYS_H

#include "Coordonnees.h"

class QPushButton;
class Arretstrams;

class Tramways
{
public:
    Tramways(double vMax, const Coordonnees& coor, Arretstrams* crt, Tramways* suivant = nullptr);
    double vitesseMax() const;
    double vitesseActuelle() const;
    void setVitesseActuelle(double vitesse);
    double distanceMinimale();
    double distanceArretSvt();
    bool sensDeplacement() const; // Vrai = Aller, Faux = Retour
    void setSensDeplacement();
    void deplacer(int v);

    Coordonnees coordonnees() const {
        return d_coor;
    }

    Tramways* getSuivant() const {
        return d_suivant;
    }

    friend class Lignestrams;
    friend class Simulationtram;
private:
    double d_vitesseMax;
    double d_vitesseActuelle;
    double d_distanceMin;   // Distance avec le tram suivant
    double d_temps;
    double d_distArretSvt;
    bool d_sens;
    Coordonnees d_coor;
    Tramways* d_suivant;
    Arretstrams* d_arret; // Arrêt courant si à l'arrêt sinon arrêt suivant
    QPushButton* d_tram;
};

#endif // TRAMWAYS_H
