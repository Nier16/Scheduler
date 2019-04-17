#ifndef GROUP_H
#define GROUP_H


#include "proc.h"

class Group : public Utilisateur
{
public:
    Group(std::string const& nom);
    void ajouterProc(Proc* proc);
    void supprimerProc(Proc* proc);
    Proc* procPrioritere();
    bool vide();
    QList<Proc*> procAttenteEs(int cpu);
    virtual void trier(QObject* obj);
    QList<Proc*> filleCpu();
    void clear();

protected:
    QList<Proc*> m_procs;
};

#endif // GROUP_H
