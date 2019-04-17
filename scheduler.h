#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <QObject>
#include "group.h"
#include <ctime>
#include <fstream>
#include "graphpainter.h"
#include <QTimer>

#define UNITE 10
#define QUANTUM 80
#define CFG_FILE_NAME "config.cfg"

class Scheduler : public QObject
{
    Q_OBJECT
public:
    Scheduler(std::string const& fileName=CFG_FILE_NAME);
    void start();
    void init(std::string const& fileName); // chargement des proc depuis le fichier d'origine
    void horloge(); // simule l'horloge
    Group *groupExist(std::string const& nom);
    void choisProc(); // choisi le proc les plus prioritere selon la politique de l énoncé
    void choisProc2();
    void procAttentEs(); // pour tous les proc non debuté vérifie si le moment est venue de les mettre en attente du cpu
    void es(); // vérifie si L E/S est vide et si la file d'attente E/S ne l est pas, si c le cas le premier de la file passe en E/S
    QList<Group *> groups() const;
    QList<Proc *> filleEs() const;
    int quantumMax() const;
    void setQuantumMax(int quantumMax);
    int unite() const;
    void setUnite(int unite);
    Proc *procES() const;
    void setProcES(Proc *procES);
    Proc *procCPU() const;
    void setProcCPU(Proc *procCPU);

    bool paused() const;
    void setPaused(bool paused);

public slots:
    void appelHorloge(); // function d'interuption de l horlogue
    void continu();
    void pause();
    void changerQuantum(int valeur);
    void changerUnit(int valeur);
    void incrCpu();
    void ajouterProc(Proc* res);
    void clear();
    void reinit(QString const& fileName=CFG_FILE_NAME);

signals:
    void addItem(int debut,int fin,GraphPainter::TypeItem type,QString const& nom, QColor const& color);
    void changementEtat(QString const& nom, int pid,Etat prec,Etat act,int cpu);
    void finProc(QString const& nom,int pid, int debut,int fin);
    void actualiser();
    void changerCpu(int valeur);
    void fin();

protected:
    void changerEtatProc(Proc* proc,Etat etat);
    void choisType1();
    void choisType2();

    QList<Group *> m_groups; // la list des groupes qui contienent la liste des proc;
    QList<Proc *> m_es; // la file d'attente E/S
    Proc* m_procES; // le proc actif en E/S
    Proc* m_procCPU; // le proc actif dans le CPU
    int m_cpu;
    int m_quantum;
    int m_debutCpu;
    int m_debutEs;
    std::string m_nomFichier;
    bool m_paused;
    int m_quantumMax;
    int m_unite;
};

#endif // SCHEDULER_H
