#ifndef CREATIONPROC_H
#define CREATIONPROC_H

#include <QPushButton>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QLineEdit>
#include <QComboBox>
#include "proc.h"

class CreationProc : public QGroupBox
{
    Q_OBJECT
public:
    CreationProc(int mainWindow=true,int minDebut=0);
    void init(int minDebut);
    void connectAll();

public slots:
    void ajouterPlaning();
    void creerProc();
    void clear();

signals:
    void procCreer(Proc* res);

protected:
    void afficherPlaning();

    Proc* m_proc;
    QLineEdit* m_nom;
    QLineEdit* m_group;
    QSpinBox* m_pid;
    QSpinBox* m_ppid;
    QSpinBox* m_debut;
    QSpinBox* m_valeurPlaning;
    QComboBox* m_typePlaning;
    QPushButton* m_creer;
    QPushButton* m_ajouterPlaning;
    QTextEdit* m_planingPainter;
};

#endif // CREATIONPROC_H
