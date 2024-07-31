#ifndef COORDONNEES_H
#define COORDONNEES_H

class Coordonnees
{
public:
    Coordonnees(int x, int y);
    int getX() const;
    int getY() const;
    void deplaceX(int action, bool sens = true);
    void deplaceY(int action, bool sens = true);
private:
    int d_x;
    int d_y;
};

#endif // COORDONNEES_H

