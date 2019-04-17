#include "utilisateur.h"

Utilisateur::Utilisateur(std::string const& nom)
{
    m_grp=0;
    m_nom=nom;
}

double Utilisateur::grp() const
{
    return m_grp;
}

void Utilisateur::setGrp(double grp)
{
    m_grp = grp;
}
std::string Utilisateur::nom() const
{
    return m_nom;
}

void Utilisateur::setNom(const std::string &nom)
{
    m_nom = nom;
}

void Utilisateur::incGrp(int value)
{
    m_grp+=value;
}

double Utilisateur::actualiserGrp(int nbGroup)
{
    m_grp/=nbGroup;
    return m_grp;
}
