#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QMainWindow>
#include <QTableWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QScrollBar>
#include <QFormLayout>
#include <QSpinBox>
#include <QLineEdit>

#include "graphpainter.h"
#include "scheduler.h"
#include "creationfichierconfigurationdialog.h"
#include "utile.h"
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QToolBar>
#include <QGuiApplication>
#include <QLabel>

#define CONTINUER "Continuer"
#define DEBUTER "Debuter"
#define PAUSE "Pause"

class MainWidget : public QMainWindow
{
    Q_OBJECT
public:
    MainWidget();
    void init();
    QHBoxLayout* initButton();
    QGridLayout* initGrid();
    void initAfficheur();
    void initMenu();
    void connectAll();

    static QStringList stringListFromStringArray(QString* stringArray,int taille);
    static QTableWidgetItem* creationTableItem(QString const& text, bool bold=false);
    static QGroupBox* creationWidgetPrincipale(QWidget* widget,QString const& nom);
public slots:
    void creationDialogFC();
    void creationDialogAP();
    void chargerFichier();
    void actualiser();
    void actualiserFilleCpu();
    void actualiserFilleEs();
    void actualiserProcFin(QString const& nom,int pid,int arrive,int sortie);
    void actualiserAction(QString const& nom,int pid,Etat etatPrec,Etat etatAct,int cpu);
    void pauseContinue();
    void quitter();
    void ajusterTaille(int, int max);
    void changerCpu(int valeur);
    void changerUnite(int valeur);
    void changerQuantum(int valeur);
    void clear();

protected :
    void ecrireLigneEs(Proc* proc,int ligne);
    void ecrireLigneCpu(Proc* proc, int ligne, bool bold=false);
    void connectBar(QScrollBar* bar);
    QFormLayout* inlineForm(QWidget* widget,QString const& test);
    void setColor(QPalette::ColorRole role,QColor const& color);
    static QTableWidget* createTableWidget(int row,int column,QStringList const& list);

    QTableWidget* m_filleCpu;
    QTableWidget* m_filleEs;
    QTableWidget* m_procFini;
    QTableWidget* m_tacheActif;
    QTableWidget* m_action;
    QGridLayout* m_layout;
    Scheduler* m_scheduler;
    GraphPainter* m_graphPainter;
    QScrollArea* m_graphPainterContainer;
    QPushButton* m_pauseContinue;
    QPushButton* m_quitter;
    QSpinBox* m_unite;
    QSpinBox* m_quantum;
    QLineEdit* m_cpu;
};

#endif // MAINWIDGET_H
