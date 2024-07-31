#ifndef SIMULATIONTRAM_H
#define SIMULATIONTRAM_H

#include <QWidget>
#include <vector>
#include <string>
#include <QPainter>
#include "LignesTrams.h"

class QLabel;
class QPushButton;
class QHBoxLayout;
class QTimer;
class QSpinBox;

class Simulationtram : public QWidget
{
    Q_OBJECT

public:
    Simulationtram(const std::vector<Lignestrams>& lignes, QWidget *parent = nullptr);
private:
    std::vector<Lignestrams> d_lignes;
    int d_duree; // Stocke la durée de la simulation
    QLabel* d_texte;
    QPushButton* d_btnInit;
    QPushButton* d_btnSimul;
    QHBoxLayout* panneau_gauche;
    QTimer* d_temps;
    QSpinBox* d_CaseDuree;

    void Vue_creeInterface();
    void Vue_creeArret();
    void Vue_creeTram();
    void lecture_Fichier(const QString& fichier);
    void Tram_A_L_Arret(Tramways* &t);
    void Tram_Entre_L_Arret(Tramways* &t);
    void Vue_affiche_Simulation();

private slots:
    void onSimuler();
    void onInitialiser();
    void onQuitter();

};



class CarteTrams : public QWidget {
    Q_OBJECT

public:
    explicit CarteTrams(QWidget *parent = nullptr) : QWidget(parent) {}

    void setLignes(const std::vector<Lignestrams>& lignes) {
        d_lignes = lignes;
        update(); // Force la mise à jour du widget pour redessiner avec les nouvelles données
    }

protected:
    void paintEvent(QPaintEvent * /*event*/) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);

        // Dessiner les arrêts
        for (const auto& ligne : d_lignes) {
            const Arretstrams* crt = ligne.getD_teteArret();
            while (crt) {
                painter.drawEllipse(QPointF(crt->getcoordonnees().getX(), crt->getcoordonnees().getY()), 5, 5);
                crt = crt->getArretSuivant(); // Suppose qu'il y a un getter pour d_suivant
            }
        }

        for (const auto& ligne : d_lignes) {
            const Arretstrams* crt = ligne.getD_teteArret();
            while (crt) {
                painter.setPen(Qt::white); // Définir la couleur de la ligne
                const Arretstrams* next = crt->getArretSuivant();
                if (next) {
                    painter.drawLine(crt->getcoordonnees().getX(), crt->getcoordonnees().getY(),
                                     next->getcoordonnees().getX(), next->getcoordonnees().getY());
                }
                painter.setPen(Qt::NoPen); // Désactiver le dessin du contour pour les arrêts
                painter.setBrush(Qt::green);
                painter.drawEllipse(QPointF(crt->getcoordonnees().getX(), crt->getcoordonnees().getY()), 5, 5);
                crt = next;
            }
        }

        // Dessiner les trams
        for (const auto& ligne : d_lignes) {
            const Tramways* crt = ligne.getD_teteTram();
            while (crt) {
                painter.setBrush(Qt::green);
                // Assurez-vous que Tramways a une méthode coordonnees()
                painter.drawRect(crt->coordonnees().getX(), crt->coordonnees().getY(), 10, 10);
                crt = crt->getSuivant(); // Suppose qu'il y a un getter pour d_suivant
            }
        }
    }


private:
    std::vector<Lignestrams> d_lignes;
};


#endif // SIMULATIONTRAM_H
