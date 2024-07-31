#include "Simulationtram.h"
#include <QPushButton>
#include <QBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QSpinBox>
#include <QTimer>
#include <QMessageBox>
#include <string>
#include <QDomDocument>
#include <QFile>


Simulationtram::Simulationtram(const std::vector<Lignestrams>& lignes, QWidget *parent)
    : QWidget{parent}, d_lignes{lignes}, d_duree{60}
{
    setWindowTitle("Simulation d'un réseau de tramways");
    resize(1000, 500);
    // setMaximumSize(1370, 700);
  //  setMinimumSize(1370, 700);

    Vue_creeInterface();
    lecture_Fichier("C:/Users/Lenovo/Desktop/Portfolio 2024/ReseauTramways/ReseauTramways/reseau.xml");
    Vue_creeArret();
    Vue_creeTram();
}

void Simulationtram::Vue_creeInterface()
{
    auto mainLayout = new QVBoxLayout{this}; // Layout principal directement sur 'this'

    auto customWidget = new QWidget{}; // Création d'un widget personnalisé
    auto customLayout = new QVBoxLayout{}; // Layout pour les éléments du widget personnalisé
    customLayout->setAlignment(Qt::AlignTop | Qt::AlignHCenter); // Alignement centré horizontalement

    d_texte = new QLabel{"Cliquer sur initialiser pour commencer la simulation"};
    customLayout->addWidget(d_texte);

    auto line = new QFrame{}; // Ligne séparatrice
    line->setFrameStyle(QFrame::HLine | QFrame::Sunken);
    customLayout->addWidget(line);

    customWidget->setLayout(customLayout); // Assignation du layout personnalisé

    auto controlsWidget = new QWidget{}; // Widget pour les contrôles en bas
    auto controlsLayout = new QHBoxLayout{}; // Layout horizontal pour les contrôles
    controlsLayout->setAlignment(Qt::AlignBottom | Qt::AlignCenter); // Alignement central

    auto durationLabel = new QLabel{"Durée en secondes de la simulation : "};
    d_CaseDuree = new QSpinBox{};
    d_CaseDuree->setRange(5, 120);
    d_CaseDuree->setValue(100);
    d_btnInit = new QPushButton{"Initialiser"};
    d_btnInit->setStyleSheet("background-color: #c0116f; color: white;");
    d_btnSimul = new QPushButton{"Simuler"};
    d_btnSimul->setDisabled(true);
    auto quitButton = new QPushButton{"Quitter"};

    controlsLayout->addWidget(durationLabel);
    controlsLayout->addWidget(d_CaseDuree);
    controlsLayout->addWidget(d_btnInit);
    controlsLayout->addWidget(d_btnSimul);
    controlsLayout->addWidget(quitButton);
    controlsWidget->setLayout(controlsLayout); // Assignation du layout aux contrôles

    mainLayout->addWidget(customWidget); // Ajout des widgets au layout principal
    mainLayout->addWidget(controlsWidget);

    this->setLayout(mainLayout); // Définition du layout principal sur 'this'

    // Connexion des signaux et des slots
    connect(d_btnSimul, &QPushButton::clicked, this, &Simulationtram::onSimuler);
    connect(d_btnInit, &QPushButton::clicked, this, &Simulationtram::onInitialiser);
    connect(quitButton, &QPushButton::clicked, this, &Simulationtram::onQuitter);

    d_temps = new QTimer{this};
    connect(d_temps, &QTimer::timeout, this, &Simulationtram::Vue_affiche_Simulation);
}



void Simulationtram::lecture_Fichier(const QString& fichier) {
    QFile file(fichier);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Impossible d'ouvrir le fichier pour la lecture.";
        return;
    }

    QDomDocument document;
    if (!document.setContent(&file)) {
        qDebug() << "Impossible de charger le document XML.";
        file.close();
        return;
    }
    file.close();

    QDomElement root = document.documentElement();
    QDomNodeList lignes = root.elementsByTagName("ligne");

    for (int i = 0; i < lignes.count(); ++i) {
        QDomElement ligne = lignes.item(i).toElement();
        Lignestrams nouvelleLigne;

        // Lecture des arrêts
        QDomNodeList arrets = ligne.firstChildElement("arrets").elementsByTagName("arret");
        for (int j = 0; j < arrets.count(); ++j) {
            QDomElement arret = arrets.item(j).toElement();
            std::string nom = arret.attribute("nom").toStdString();
            int duree = arret.attribute("duree").toInt();
            int x = arret.attribute("x").toInt();
            int y = arret.attribute("y").toInt();
            nouvelleLigne.ajouterArret(nom, duree, x, y);
        }

        // Lecture des trams
        QDomNodeList trams = ligne.firstChildElement("trams").elementsByTagName("tram");
        for (int k = 0; k < trams.count(); ++k) {
            QDomElement tram = trams.item(k).toElement();
            int vitesse = tram.attribute("vitesse").toInt();
            nouvelleLigne.ajouterTram(vitesse);
        }

        d_lignes.push_back(nouvelleLigne);
    }
}


void Simulationtram::Vue_creeArret()
{
    for (unsigned i = 0; i < d_lignes.size(); i++)
    {
        Arretstrams *crt = d_lignes[i].getD_teteArret();

        while (crt)
        {
            crt->d_arret = new QLabel(QString::fromStdString(crt->d_nom), this);
            crt->d_arret->move(crt->d_coor.getX(), crt->d_coor.getY());
            crt->d_arret->setVisible(false);

            crt->d_coordonnees = new QLabel(QString::number(crt->d_coor.getX()) + ", " + QString::number(crt->d_coor.getY()), this);
            crt->d_coordonnees->move(crt->d_coor.getX(), crt->d_coor.getY() + 15); // Décalage pour afficher en dessous
            crt->d_coordonnees->setVisible(false);

            crt = crt->d_suivant;
        }
    }
}

void Simulationtram::Vue_creeTram()
{
    for (unsigned i = 0; i < d_lignes.size(); i++)
    {
        Tramways *crt = d_lignes[i].getD_teteTram();

        while (crt)
        {
            crt->d_tram = new QPushButton{this};
            crt->d_tram->setGeometry(crt->d_coor.getX(), crt->d_coor.getY(), 23, 12);
            crt->d_tram->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #dfb505, stop:1 red);");
            crt->d_tram->setVisible(false);

            crt = crt->d_suivant;
        }
    }
}

void Simulationtram::Tram_A_L_Arret(Tramways *&t)
{
    // Si la duree que doit mettre le tram à l'arret est ecoulee
    if (t->d_temps >= t->d_arret->getduree())
    {
        //On change l'arrêt courant
        if (t->sensDeplacement())
        {
            if (t->d_arret->d_suivant)
            {
                t->d_arret = t->d_arret->d_suivant;
            }
            else
            {
                t->d_arret = t->d_arret->d_precedent;
                t->setSensDeplacement();

                t->d_tram->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 red, stop:1 #dfb505);");
            }
        }else
        {
            if (t->d_arret->d_precedent)
            {
                t->d_arret = t->d_arret->d_precedent;
            }
            else
            {
                t->d_arret = t->d_arret->d_suivant;
                t->setSensDeplacement();

                t->d_tram->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #dfb505, stop:1 red);");
            }
        }

        // Vérifie la distance avec le tram suivant
        if (t->distanceMinimale() >= 30 || !t->d_suivant)
        {
            t->setVitesseActuelle(t->vitesseMax());
            t->deplacer(t->vitesseActuelle());
            t->d_temps = 0;
        }

    }else
    {
        t->d_temps++;

        t->d_tram->setStyleSheet("background-color: red;");
    }
}

void Simulationtram::Tram_Entre_L_Arret(Tramways *&t)
{
    // Vérifie la distance avec le tram suivant
    if (t->distanceMinimale() >= 30 || !t->d_suivant)
    {
        if (t->vitesseActuelle() > t->distanceArretSvt())
        {
            t->setVitesseActuelle(0);
            t->deplacer(t->distanceArretSvt());
        }else
        {
            t->setVitesseActuelle(t->vitesseMax());
            t->deplacer(t->vitesseActuelle());
        }

        if (t->sensDeplacement())
            t->d_tram->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #dfb505, stop:1 red);");
        else
            t->d_tram->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 red, stop:1 #dfb505);");
    }
}

void Simulationtram::Vue_affiche_Simulation()
{
    d_duree -= 33;  // On décremente la durée d' 1/30 de seconde

    for (unsigned i = 0; i < d_lignes.size(); i++)
    {
        Tramways* crt = d_lignes[i].getD_teteTram();

        while (crt)
        {
            // Vérifie si tram est à l'arrêt
            if (crt->d_coor.getX() == crt->d_arret->d_coor.getX())
            {
                Tram_A_L_Arret(crt);
            }else
            {
                Tram_Entre_L_Arret(crt);
            }

            crt = crt->d_suivant;
        }
    }

    if (d_duree <= 0) // Si durée écoulée on stop le timer
    {
        d_temps->stop();
        d_texte->setText("Fin de la simulation");
        d_CaseDuree->setDisabled(false);
        d_btnSimul->setDisabled(false);
    }
}

void Simulationtram::onSimuler()
{

    d_texte->setText("Simulation en cours...");
    d_btnSimul->setDisabled(true);

    d_CaseDuree->setDisabled(true);

    d_duree = d_CaseDuree->value();
    d_duree *= 1000;
    d_temps->start(33);
}

void Simulationtram::onInitialiser() {
    d_texte->setText("Initialisation en cours...");


    for (unsigned i = 0; i < d_lignes.size(); i++) {
        Arretstrams *crtArret = d_lignes[i].getD_teteArret(); // Utilisation du getter
        Tramways *crtTram = d_lignes[i].getD_teteTram(); // Utilisation du getter

        while (crtArret) {
            crtArret->d_arret->setVisible(true);
            crtArret->d_coordonnees->setVisible(true);
            crtArret = crtArret->d_suivant;
        }

        while (crtTram) {
            crtTram->d_tram->setVisible(true);
            crtTram = crtTram->d_suivant;
        }
    }

    d_texte->setText("La simulation est prête");
    d_btnInit->setDisabled(true);
    d_btnSimul->setDisabled(false);
    if (!d_btnInit->isEnabled()) {
        d_btnSimul->setStyleSheet("background-color: #dfb505; color: white;");
        d_btnInit->setStyleSheet("background-color: none;color: none;");
    }
}

void Simulationtram::onQuitter()
{
    if (!d_CaseDuree->isEnabled())
    {
        auto dialog = new QMessageBox{
                                      QMessageBox::Warning, "Warning","Confirmez la sortie !",
                                      QMessageBox::Yes|QMessageBox::No};

        if (dialog->exec() == QMessageBox::No)
            return;
    }

    close();
}

