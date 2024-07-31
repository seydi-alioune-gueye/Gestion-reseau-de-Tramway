#include "Coordonnees.h"

Coordonnees::Coordonnees(int x, int y) : d_x{x}, d_y{y}
{}

int Coordonnees::getX() const
{ return d_x; }

int Coordonnees::getY() const
{ return d_y; }

void Coordonnees::deplaceX(int action, bool sens)
{
    if (sens)
        d_x += action;
    else
        d_x -= action;
}

void Coordonnees::deplaceY(int action, bool sens)
{
    if (sens)
        d_y += action;
    else
        d_y -= action;
}
