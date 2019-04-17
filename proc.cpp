#include "proc.h"
#include <iomanip>

Proc::Proc() : m_priorite(INITIAL_PRIORITE), m_cpu(0)
{
    m_etat=ATTENTE_DEBUT;
    m_priorite=INITIAL_PRIORITE;
    genererCouleur();
}

void Proc::actualiserPriorite(int nbGroup)
{
    m_priorite-=( m_utilisateur->actualiserGrp(nbGroup) + (m_cpu/=nbGroup) );
    //m_utilisateur->trier(this);
}

void Proc::genererCouleur()
{
    static int max=MAX_COLOR-MIN_COLOR;
    m_color.setRgb(rand()%max+MIN_COLOR,
                   rand()%max+MIN_COLOR,
                   rand()%max+MIN_COLOR);
}

QString Proc::toString()
{
    static const QString espace=QString(" ");
    static const QString saut=QString("\n");
    return (ATTRIBUT_NOM + espace + QString::fromStdString(m_nom) + saut +
            ATTRIBUT_UTILISATEUR + espace + QString::fromStdString(m_utilisateur->nom()) + saut +
            ATTRIBUT_PID + espace + QString::number(m_pid) + saut +
            ATTRIBUT_PPID + espace + QString::number(m_ppid) + saut +
            ATTRIBUT_DEBUT + espace + QString::number(m_debut) + saut +
            m_planing.toString());
}

double Proc::priorite() const
{
    return m_priorite;
}

void Proc::setPriorite(double priorite)
{
    m_priorite = priorite;
}

int Proc::pid() const
{
    return m_pid;
}

void Proc::setPid(int pid)
{
    m_pid = pid;
}

int Proc::ppid() const
{
    return m_ppid;
}

void Proc::setPpid(int ppid)
{
    m_ppid = ppid;
}
QString Proc::nom() const
{
    return QString::fromStdString(m_nom);
}

void Proc::setNom(const std::string &nom)
{
    m_nom = nom;
}

void Proc::setDebut(int debut)
{
    m_debut=debut;
}

int Proc::debut() const
{
    return m_debut;
}

TypeRetour Proc::e_s()
{
    m_planing.dec();
    if(!m_planing.fini())
        return NONE;
    else
    {
        m_planing.removeLast();
        if(m_planing.vide())
            return FIN_PROC;
        else
            return DEMANDE_CPU;
    }
}

TypeRetour Proc::cpu()
{
    m_cpu++;
    m_utilisateur->incGrp();
    m_planing.dec();
    if(!m_planing.fini())
        return NONE;
    else
    {
        m_planing.removeLast();
        if(m_planing.vide())
            return FIN_PROC;
        else
            return DEMANDE_ES;
    }

}

Etat Proc::verifierEtat(int cpu)
{
    if(cpu>=m_debut)
    {
        if(m_planing.type()==Planing::E_S)
            setEtat(ATTENTE_ES);
        else
            setEtat(ATTENTE_CPU);
    }
    return m_etat;
}

Utilisateur *Proc::utilisateur() const
{
    return m_utilisateur;
}

void Proc::setUtilisateur(Utilisateur *utilisateur)
{
    m_utilisateur = utilisateur;
}

QString Proc::etatToString(Etat etat)
{
    static QString list[]={"Attente CPU",
                         "Attente E/S",
                         "Cour CPU",
                         "Cour E/S",
                         "Fin_Exec",
                         "Attente Debut"};
    return list[etat];
}

Planing *Proc::planing()
{
    return &m_planing;
}

QColor Proc::color() const
{
    return m_color;
}

void Proc::setColor(const QColor &color)
{
    m_color = color;
}
int Proc::debutAttente() const
{
    return m_debutAttente;
}

void Proc::setDebutAttente(int debutAttente)
{
    m_debutAttente = debutAttente;
}


Etat Proc::etat() const
{
    return m_etat;
}

void Proc::setEtat(const Etat &etat)
{
    m_etat = etat;
}
