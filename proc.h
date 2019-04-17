#ifndef PROC_H
#define PROC_H

#include <string>
#include <ctime>
#include <cstdlib>
#include <QColor>
#include "utilisateur.h"
#include <planing.h>

#define INITIAL_PRIORITE 1000
#define MIN_COLOR 50
#define MAX_COLOR 220

enum Etat
{
    COUR_ES=3,COUR_CPU=2,ATTENTE_CPU=0,ATTENTE_ES=1,ATTENTE_DEBUT=5,FIN_EXEC=4
};

enum TypeRetour
{
    DEMANDE_ES, NONE, DEMANDE_CPU, FIN_PROC
};

class Proc : public QObject
{
    Q_OBJECT
public:
    Proc();

    //GETTER SETTER
    double priorite() const;
    void setPriorite(double priorite);
    int pid() const;
    void setPid(int pid);
    int ppid() const;
    void setPpid(int ppid);
    QString nom() const;
    void setNom(const std::string &nom);
    void setDebut(int debut);
    int debut() const;
    Etat etat() const;
    void setEtat(const Etat &etat);
    Utilisateur *utilisateur() const;
    void setUtilisateur(Utilisateur *utilisateur);
    QColor color() const;
    void setColor(const QColor &color);
    int debutAttente() const;
    void setDebutAttente(int debutAttente);

    //UTILE
    TypeRetour e_s();
    TypeRetour cpu();
    Etat verifierEtat(int cpu);
    void actualiserPriorite(int nbGroup);
    void genererCouleur();
    QString toString();

    //STATIC
    static QString etatToString(Etat etat);

    Planing *planing();

protected:
    double m_priorite;
    double m_cpu;
    int m_pid;
    int m_ppid;
    std::string m_nom;
    int m_debut;
    Utilisateur* m_utilisateur;
    Etat m_etat;
    QColor m_color;
    int m_debutAttente;
    Planing m_planing;
};

#endif // PROC_H
