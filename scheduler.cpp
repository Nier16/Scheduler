#include "scheduler.h"

Scheduler::Scheduler(const std::string &fichierName)
{
    m_procCPU=NULL;
    m_procES=NULL;
    m_cpu=0;
    m_quantum=0;
    m_quantumMax=QUANTUM;
    m_unite=UNITE;
    m_nomFichier=fichierName;
    m_paused=true;
}

void Scheduler::start()
{
    m_paused=false;
    init(m_nomFichier);
    procAttentEs();
    choisProc();
    es();
    horloge();
}

void Scheduler::init(std::string const& fichierName) // version tres simplifier qui obligue le fichier de configuration a réspécter une sintaxe strict(pas de ctrl)
{
    std::ifstream fichier(fichierName.c_str());
    if(!fichier)
    {

        exit(0);
    }
    std::string attribut,sValeur;
    int iValeur;
    Proc* proc;
    while(true)
    {
        fichier >> attribut;
        if(attribut==ATTRIBUT_NOM)
        {
            fichier >> sValeur;
            proc=new Proc();
            proc->setNom(sValeur);
        }
        else if(attribut==ATTRIBUT_UTILISATEUR)
        {
            fichier >> sValeur;
            Group* group=groupExist(sValeur);
            if(group!=NULL)
                group->ajouterProc(proc);
            else
            {
                m_groups.push_back(new Group(sValeur));
                m_groups.back()->ajouterProc(proc);
            }
        }
        else if(attribut==ATTRIBUT_DEBUT)
        {
            fichier >> iValeur;
            proc->setDebut(iValeur);
        }
        else if(attribut==ATTRIBUT_PID)
        {
            fichier >> iValeur;
            proc->setPid(iValeur);
        }
        else if(attribut==ATTRIBUT_PPID)
        {
            fichier >> iValeur;
            proc->setPpid(iValeur);
        }
        else if(attribut==ATTRIBUT_CPU)
        {
            fichier >> iValeur;
            proc->planing()->ajouter(Planing::CPU,iValeur);
        }
        else if(attribut==ATTRIBUT_ES)
        {
            fichier >> iValeur;
            proc->planing()->ajouter(Planing::E_S,iValeur);
        }
        else if(attribut==ATTRIBUT_FIN)
            break;
    }
}

void Scheduler::horloge()
{
    if(!m_paused)
        QTimer::singleShot(m_unite,this,SLOT(appelHorloge()));
}

void Scheduler::continu()
{
    m_paused=false;
    horloge();
}

void Scheduler::pause()
{
    m_paused=true;
}

void Scheduler::changerQuantum(int valeur)
{
    m_quantumMax=valeur;
}

void Scheduler::changerUnit(int valeur)
{
    m_unite=valeur;
}

void Scheduler::incrCpu()
{
    m_cpu++;
    emit changerCpu(m_cpu);
}

void Scheduler::ajouterProc(Proc *res)
{
    Group* g;
    if((g=groupExist(res->utilisateur()->nom()))!=NULL)
        g->ajouterProc(res);
    else
        m_groups.push_back((Group*)res->utilisateur());
}

void Scheduler::clear()
{
    m_paused=true;
    m_procCPU=NULL;
    m_procES=NULL;
    m_es.clear();
    for(int i=0;i<m_groups.size();i++)
    {
        m_groups[i]->clear();
        delete m_groups[i];
    }
    m_groups.clear();
    m_cpu=0;
    m_debutCpu=0;
    m_debutEs=0;
}

void Scheduler::reinit(const QString &fileName)
{
    m_nomFichier=fileName.toStdString();
    clear();
    start();
}

void Scheduler::appelHorloge()
{
    procAttentEs();
    TypeRetour typeRetour;
    incrCpu();
    if(m_procCPU!=NULL)
    {
        m_quantum++;
        typeRetour=m_procCPU->cpu();  
        if(typeRetour==DEMANDE_ES)
        {
            m_es.push_back(m_procCPU);
            changerEtatProc(m_procCPU,ATTENTE_ES);
            choisProc();
        }
        else if(typeRetour==FIN_PROC)
        {
            changerEtatProc(m_procCPU,FIN_EXEC);
            m_procCPU=NULL;
            choisProc();
        }
        else if(m_quantum==m_quantumMax)
        {
            changerEtatProc(m_procCPU,ATTENTE_CPU);
            choisProc();
        }
    }
    else
        choisProc();
    if(m_procES!=NULL)
    {
        typeRetour=m_procES->e_s();
        if(typeRetour==FIN_PROC)
        {
            changerEtatProc(m_procES,FIN_EXEC);
            m_procES=NULL;
        }
        else if(typeRetour==DEMANDE_CPU)
        {
            changerEtatProc(m_procES,ATTENTE_CPU);
            m_procES=NULL;
        }
    }
    es();
    horloge();
}

void Scheduler::changerEtatProc(Proc *proc, Etat etat)
{
    if(proc->etat()==COUR_CPU)
        emit addItem(m_debutCpu,m_cpu,GraphPainter::CPU,proc->nom(),proc->color());
    else if(proc->etat()==COUR_ES)
        emit addItem(m_debutEs,m_cpu,GraphPainter::ES,proc->nom(),proc->color());
    if(etat==ATTENTE_CPU || etat==ATTENTE_ES)
        proc->setDebutAttente(m_cpu);
    else if(etat==COUR_CPU)
        m_debutCpu=m_cpu;
    else if(etat==COUR_ES)
        m_debutEs=m_cpu;
    else if(etat==FIN_EXEC)
    {
        Group* group=(Group*)proc->utilisateur();
        emit finProc(proc->nom(),proc->pid(),proc->debut(),m_cpu);
        group->supprimerProc(proc);
        if(group->vide())
        {
            m_groups.pop_back();
            delete group;
        }
        return;
    }
    emit changementEtat(proc->nom(),proc->pid(),proc->etat(),etat,m_cpu);
    proc->setEtat(etat);
    emit actualiser();
}
bool Scheduler::paused() const
{
    return m_paused;
}

void Scheduler::setPaused(bool paused)
{
    m_paused = paused;
}

Proc *Scheduler::procCPU() const
{
    return m_procCPU;
}

void Scheduler::setProcCPU(Proc *procCPU)
{
    m_procCPU = procCPU;
}

Proc *Scheduler::procES() const
{
    return m_procES;
}

void Scheduler::setProcES(Proc *procES)
{
    m_procES = procES;
}

int Scheduler::unite() const
{
    return m_unite;
}

void Scheduler::setUnite(int unite)
{
    m_unite = unite;
}

int Scheduler::quantumMax() const
{
    return m_quantumMax;
}

void Scheduler::setQuantumMax(int quantumMax)
{
    m_quantumMax = quantumMax;
}


QList<Group *> Scheduler::groups() const
{
    return m_groups;
}

QList<Proc *> Scheduler::filleEs() const
{
    return m_es;
}

Group* Scheduler::groupExist(const std::string &nom)
{
    for(QList<Group *>::iterator i=m_groups.begin();i!=m_groups.end();i++)
        if((*i)->nom()==nom)
            return *i;
    return NULL;
}

void Scheduler::procAttentEs()
{
    QList<Proc *> temp;
    for(QList<Group *>::iterator i=m_groups.begin();i!=m_groups.end();i++)
    {
        temp=(*i)->procAttenteEs(m_cpu);
        for(int j=0;j<temp.size();j++)
        {
            changerEtatProc(temp[j],ATTENTE_ES);
            m_es.push_back(temp[j]);
        }
    }
}

void Scheduler::es()
{
    if(m_procES==NULL && !m_es.empty())
    {
        m_procES=m_es.front();
        changerEtatProc(m_procES,COUR_ES);
        m_es.pop_front();
    }
}

void Scheduler::choisProc()
{
    quint32 i=0;
    if(m_procCPU!=NULL)
    {
        m_procCPU->actualiserPriorite(m_groups.size());
        m_procCPU=NULL;
    }
    choisType1();
    if(m_procCPU!=NULL)
    {
        changerEtatProc(m_procCPU,COUR_CPU);
        m_quantum=0;
    }
    else
        actualiser();
}


void Scheduler::choisType1()
{
    Proc* proc=NULL;
    for(int i=0;i<m_groups.size();i++)
    {
        proc=m_groups[i]->procPrioritere();
        if(proc!=NULL && (m_procCPU==NULL || proc->priorite()>m_procCPU->priorite()))
            m_procCPU=proc;
    }
}

void Scheduler::choisType2()
{
    Group* group;
    int i=0;
    while(i++!=m_groups.size())
    {
        group=m_groups.front();
        m_groups.pop_front();
        m_groups.push_back(group);
        m_procCPU=group->procPrioritere();
        if(m_procCPU!=NULL)
            return;
    }
}
