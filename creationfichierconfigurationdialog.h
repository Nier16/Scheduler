#ifndef CREATIONFICHIERCONFIGURATIONDIALOG_H
#define CREATIONFICHIERCONFIGURATIONDIALOG_H

#include "creationproc.h"
#include <QDialog>
#include <QFileDialog>
#include <QTextStream>

class CreationFichierConfigurationDialog : public QDialog
{
    Q_OBJECT
public:
    CreationFichierConfigurationDialog();
    void init();
    void connectAll();

public slots:
    void procCreer(Proc* proc);
    void sauvgarder();
    void close();

signals:
    void closed();

protected:
    CreationProc* m_creationProc;
    QTextEdit* m_resultat;
    QPushButton* m_sauvgarder;
    QPushButton* m_quitter;


};

#endif // CREATIONFICHIERCONFIGURATIONDIALOG_H
