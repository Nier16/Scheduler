#ifndef UTILISATEUR_H
#define UTILISATEUR_H

#include <string>
#include <QObject>

class Utilisateur
{
public:
    Utilisateur(std::string const& nom);
    double grp() const;
    void setGrp(double grp);

    std::string nom() const;
    void setNom(const std::string &nom);

    void incGrp(int value=1);
    double actualiserGrp(int nbGroup);

    virtual void trier(QObject*) const {}
protected:
    double m_grp;
    std::string m_nom;
};

#endif // UTILISATEUR_H
