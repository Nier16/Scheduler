#include "group.h"

Group::Group(std::string const& nom) : Utilisateur(nom)
{
}

void Group::ajouterProc(Proc *proc)
{
    m_procs.push_back(proc);
    proc->setUtilisateur(this);
}

Proc *Group::procPrioritere()
{
    Proc* res=NULL;
    for(QList<Proc*>::iterator i=m_procs.begin();i!=m_procs.end();i++)
        if((*i)->etat()==ATTENTE_CPU && (res==NULL || (*i)->priorite()>res->priorite()))
            res=*i;
    return res;
}

bool Group::vide()
{
    return m_procs.empty();
}

void Group::trier(QObject *obj)
{
    Proc* proc=(Proc*)obj;
    m_procs.removeOne(proc);
    for(int i=0;i<m_procs.size();i++)
        if(m_procs[i]->priorite()<proc->priorite())
        {
            m_procs.insert(i,proc);
            return;
        }
    m_procs.push_back(proc);
}

QList<Proc *> Group::filleCpu()
{
    QList<Proc *> res;
    for(int i=0;i<m_procs.size();i++)
    {
        if(m_procs[i]->etat()==ATTENTE_CPU)
            res.push_back(m_procs[i]);
    }
    return res;
}

void Group::clear()
{
    for(int i=0;i<m_procs.size();i++)
        delete m_procs[i];
    m_procs.clear();
}

QList<Proc *> Group::procAttenteEs(int cpu)
{
    QList<Proc *> res;
    for(QList<Proc*>::iterator i=m_procs.begin();i!=m_procs.end();i++)
        if((*i)->etat()==ATTENTE_DEBUT && (*i)->verifierEtat(cpu)==ATTENTE_ES)
            res.push_back(*i);
    return res;
}

void Group::supprimerProc(Proc *proc)
{
    m_procs.removeOne(proc);
    delete proc;
}
