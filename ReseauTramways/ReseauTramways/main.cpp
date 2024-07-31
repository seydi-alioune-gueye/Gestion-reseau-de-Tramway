#include "Simulationtram.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::vector<Lignestrams>lignes;
    Simulationtram w(lignes);
    w.show();
    return a.exec();
}
