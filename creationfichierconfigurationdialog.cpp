#include "creationfichierconfigurationdialog.h"

CreationFichierConfigurationDialog::CreationFichierConfigurationDialog()
{
    init();
    setWindowTitle("Creation Fichier de Configuration");
}

void CreationFichierConfigurationDialog::init()
{
    QVBoxLayout* layout=new QVBoxLayout();
    QHBoxLayout* subLayout=new QHBoxLayout();

    m_creationProc=new CreationProc(false);
    m_resultat=new QTextEdit();
    m_sauvgarder=new QPushButton("Sauvgarder");
    m_quitter=new QPushButton("Quitter");
    subLayout->addWidget(m_sauvgarder);
    subLayout->addWidget(m_quitter);
    layout->addWidget(m_creationProc);
    layout->addWidget(m_resultat);
    layout->addLayout(subLayout);

    connectAll();

    this->setLayout(layout);
    this->show();
}

void CreationFichierConfigurationDialog::connectAll()
{
    connect(m_quitter,SIGNAL(clicked()),this,SLOT(close()));
    connect(m_sauvgarder,SIGNAL(clicked()),this,SLOT(sauvgarder()));
    connect(m_creationProc,SIGNAL(procCreer(Proc*)),this,SLOT(procCreer(Proc*)));
}

void CreationFichierConfigurationDialog::procCreer(Proc *proc)
{
    m_resultat->append(proc->toString());
}

void CreationFichierConfigurationDialog::sauvgarder()
{
    if(m_resultat->toPlainText().isEmpty())
        return;
    QString chemin=QFileDialog::getSaveFileName(this,"Enregister le fichier de configuration",QString(),".cfg");
    QFile file(chemin);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream writer(&file);
    writer << m_resultat->toPlainText() << ATTRIBUT_FIN;
    file.close();
    this->close();
}

void CreationFichierConfigurationDialog::close()
{
    emit closed();
    QDialog::close();
}


