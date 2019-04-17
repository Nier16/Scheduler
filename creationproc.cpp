#include "creationproc.h"

CreationProc::CreationProc(int mainWindow, int minDebut) : QGroupBox()
{
    if(!mainWindow)
        setTitle("Creation Proc");
    else
        setWindowTitle("Creation Proc");
    init(minDebut);
    this->show();
}

void CreationProc::init(int minDebut)
{
    QFormLayout* layout=new QFormLayout();
    QHBoxLayout* subLayout=new QHBoxLayout();

    m_proc=new Proc();
    m_nom=new QLineEdit();
    m_group=new QLineEdit();
    m_pid=new QSpinBox();
    m_ppid=new QSpinBox();
    m_debut=new QSpinBox();
    m_valeurPlaning=new QSpinBox();
    m_planingPainter=new QTextEdit();
    m_ajouterPlaning=new QPushButton("Ajouter au Planing");
    m_creer=new QPushButton("Créer");
    m_typePlaning=new QComboBox();

    m_debut->setMinimum(minDebut);
    m_debut->setValue(minDebut);
    m_debut->setMaximum(1000000);
    m_pid->setMinimum(0);
    m_pid->setMaximum(1000);
    m_ppid->setMinimum(0);
    m_ppid->setMaximum(1000);
    m_valeurPlaning->setMinimum(1);
    m_valeurPlaning->setMaximum(10000);

    m_typePlaning->addItem("CPU");
    m_typePlaning->addItem("E/S");

    subLayout->addWidget(m_typePlaning);
    subLayout->addWidget(m_valeurPlaning);
    layout->addRow("Nom",m_nom);
    layout->addRow("Utilisateur",m_group);
    layout->addRow("Pid",m_pid);
    layout->addRow("Ppid",m_ppid);
    layout->addRow("Debut",m_debut);
    layout->addRow(subLayout);
    layout->addRow(m_ajouterPlaning);
    layout->addRow(m_planingPainter);
    layout->addRow(m_creer);

    connectAll();

    this->setLayout(layout);
}

void CreationProc::connectAll()
{
    connect(m_creer,SIGNAL(clicked()),this,SLOT(creerProc()));
    connect(m_ajouterPlaning,SIGNAL(clicked()),this,SLOT(ajouterPlaning()));
}

void CreationProc::ajouterPlaning()
{
    if(m_typePlaning->currentIndex()==0)
        m_proc->planing()->ajouter(Planing::CPU,m_valeurPlaning->value());
    else
        m_proc->planing()->ajouter(Planing::E_S,m_valeurPlaning->value());
    afficherPlaning();
}

void CreationProc::creerProc()
{
    if(m_nom->text().isEmpty() || m_group->text().isEmpty() || m_proc->planing()->vide())
        return;
    m_proc->setNom(m_nom->text().toStdString());
    m_proc->setUtilisateur(new Utilisateur(m_group->text().toStdString()));
    m_proc->setPid(m_pid->value());
    m_proc->setPpid(m_ppid->value());
    m_proc->setDebut(m_debut->value());
    emit procCreer(m_proc);
}

void CreationProc::clear()
{
    m_proc=new Proc();
    m_pid->setValue(m_pid->minimum());
    m_ppid->setValue(m_ppid->minimum());
    m_debut->setMinimum(m_debut->minimum());
    m_nom->clear();
    m_group->clear();
    m_valeurPlaning->setValue(m_valeurPlaning->minimum());
    m_planingPainter->clear();
}

void CreationProc::afficherPlaning()
{
    m_planingPainter->clear();
    m_planingPainter->setText(m_proc->planing()->toString());
}
