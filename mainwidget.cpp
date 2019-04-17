#include "mainwidget.h"

MainWidget::MainWidget()
{
    init();
}

void MainWidget::init()
{
    srand(time(NULL));
    resize(1200,650);
    QWidget* mainWidget=new QWidget();
    QVBoxLayout* layout=new QVBoxLayout();
    layout->addLayout(initGrid());
    layout->addLayout(initButton());
    initMenu();
    mainWidget->setLayout(layout);
    connectAll();
    setFont(QFont("algerien.ttf",10));
    setColor(QPalette::Background,QColor(225,233,240));
    setColor(QPalette::Text,QColor(110,130,250));
    setColor(QPalette::ButtonText,QColor(80,120,80));
    Utile::setWidgetColor(mainWidget,QPalette::ButtonText,QColor(200,80,80));
    this->setCentralWidget(mainWidget);
    this->show();
}

QHBoxLayout* MainWidget::initButton()
{
    QHBoxLayout* res=new QHBoxLayout();
    m_quitter=new QPushButton("Quitter");
    m_pauseContinue=new QPushButton(DEBUTER);
    res->addWidget(m_pauseContinue);
    res->addWidget(m_quitter);
    res->setAlignment(Qt::AlignRight);
    return res;
}

QGridLayout *MainWidget::initGrid()
{
    QList<QString> header;
    QList<QString> header2;
    QList<QString> header3;
    QList<QString> header4;
    QGridLayout* layout=new QGridLayout();
    m_graphPainter=new GraphPainter();
    m_graphPainterContainer=new QScrollArea();
    m_scheduler=new Scheduler();

    header << "Pid" << "Groupe" << "Nom" << "Priorité";
    header2 << "Pid" << "Groupe" << "Nom" << "debut Attente";
    header3 << "Pid" << "NOM" << "Arrivé" << "Sortie";
    header4 << "Cpu" << "Pid" << "NOM" << "Etat pre" << "Etat actual";

    m_filleCpu=createTableWidget(1,4,header2);
    m_filleEs=createTableWidget(1,4,header);
    m_procFini=createTableWidget(1,4,header3);
    m_action=createTableWidget(1,5,header4);

    layout->setSpacing(20);
    layout->addWidget(creationWidgetPrincipale(m_filleCpu,"File Cpu"),1,1);
    layout->addWidget(creationWidgetPrincipale(m_filleEs,"File E/S"),1,2);
    layout->addWidget(creationWidgetPrincipale(m_procFini,"Proc Fini"),1,3);
    layout->addWidget(creationWidgetPrincipale(m_graphPainterContainer,"Graphe execution"),2,1,1,2);
    layout->addWidget(creationWidgetPrincipale(m_action,"Actions"),2,3);

    m_graphPainterContainer->setWidget(m_graphPainter);
    m_graphPainterContainer->setBackgroundRole(QPalette::Light);

    return layout;
}

void MainWidget::initAfficheur()
{
    m_quantum=new QSpinBox();
    m_unite=new QSpinBox();
    m_cpu=new QLineEdit();

    m_quantum->setMinimum(1);
    m_quantum->setMaximum(100);
    m_unite->setMinimum(10);
    m_unite->setMaximum(1000);
    m_quantum->setValue(QUANTUM);
    m_unite->setValue(UNITE);
    m_cpu->setText("0");
    m_cpu->setReadOnly(true);
    m_cpu->setMaximumWidth(50);
}

void MainWidget::initMenu()
{
    initAfficheur();
    QMenu* fichiers=menuBar()->addMenu("Fichier");
    QMenu* actions=menuBar()->addMenu("Actions");

    QToolBar* toolBar=addToolBar("Fichier");
    QToolBar* toolBar2=addToolBar("Action");

    QAction* a1=fichiers->addAction("Nouveau Fichier de Configuration");
    QAction* a2=fichiers->addAction("Charger Fichier de configuration");
    QAction* a3=actions->addAction("Ajouter Processus");
    QAction* a4=actions->addAction("Pause / Start");
    QAction* a5=actions->addAction("Quitter");

    toolBar->addAction(a1);
    toolBar->addAction(a2);
    toolBar->addAction(a3);
    toolBar->addAction(a4);
    toolBar->addAction(a5);

    toolBar2->addWidget(new QLabel("Cpu : "));
    toolBar2->addWidget(m_cpu);
    toolBar2->addSeparator();
    toolBar2->addWidget(new QLabel("Quantum : "));
    toolBar2->addWidget(m_quantum);
    toolBar2->addSeparator();
    toolBar2->addWidget(new QLabel("Unitée : "));
    toolBar2->addWidget(m_unite);

    a1->setShortcut(QKeySequence("Ctrl+N"));
    a2->setShortcut(QKeySequence("Ctrl+C"));
    a3->setShortcut(QKeySequence("Ctrl+F"));
    a4->setShortcut(QKeySequence("Ctrl+P"));
    a5->setShortcut(QKeySequence("Ctrl+Q"));

    connect(a1,SIGNAL(triggered()),this,SLOT(creationDialogFC()));
    connect(a2,SIGNAL(triggered()),this,SLOT(chargerFichier()));
    connect(a3,SIGNAL(triggered()),this,SLOT(creationDialogAP()));
    connect(a4,SIGNAL(triggered()),this,SLOT(pauseContinue()));
    connect(a5,SIGNAL(triggered()),this,SLOT(quitter()));
}

void MainWidget::connectAll()
{
    connect(m_scheduler,SIGNAL(addItem(int,int,GraphPainter::TypeItem,QString,QColor)),
            m_graphPainter,SLOT(addItem(int,int,GraphPainter::TypeItem,QString,QColor)));
    connect(m_scheduler,SIGNAL(actualiser()),this,SLOT(actualiser()));
    connect(m_scheduler,SIGNAL(finProc(QString,int,int,int)),
            this,SLOT(actualiserProcFin(QString,int,int,int)));
    connect(m_scheduler,SIGNAL(changementEtat(QString,int,Etat,Etat,int)),
            this,SLOT(actualiserAction(QString,int,Etat,Etat,int)));
    connect(m_pauseContinue,SIGNAL(clicked()),this,SLOT(pauseContinue()));
    connect(m_quitter,SIGNAL(clicked()),this,SLOT(quitter()));
    connect(m_quantum,SIGNAL(valueChanged(int)),this,SLOT(changerQuantum(int)));
    connect(m_unite,SIGNAL(valueChanged(int)),this,SLOT(changerUnite(int)));
    connect(m_scheduler,SIGNAL(changerCpu(int)),this,SLOT(changerCpu(int)));
    connectBar(m_action->verticalScrollBar());
    connectBar(m_procFini->verticalScrollBar());
    connectBar(m_graphPainterContainer->horizontalScrollBar());
}

QTableWidgetItem *MainWidget::creationTableItem(const QString &text,bool bold)
{
    QTableWidgetItem* res=new QTableWidgetItem(text);
    if(bold)
        res->setFont(QFont("Times", 10, QFont::Bold));
    return res;
}

QGroupBox *MainWidget::creationWidgetPrincipale(QWidget *widget, const QString &nom)
{
    QGroupBox* res=new QGroupBox();
    QVBoxLayout* layout=new QVBoxLayout();
    layout->addWidget(widget);
    res->setTitle(nom);
    res->setLayout(layout);
    return res;
}

void MainWidget::creationDialogFC()
{
    if(!m_scheduler->paused())
        pauseContinue();
    CreationFichierConfigurationDialog* w=new CreationFichierConfigurationDialog();
    connect(w,SIGNAL(closed()),this,SLOT(pauseContinue()));
}

void MainWidget::creationDialogAP()
{
    if(!m_scheduler->paused())
        pauseContinue();
    CreationProc* p=new CreationProc(m_cpu->text().toInt());
    connect(p,SIGNAL(procCreer(Proc*)),m_scheduler,SLOT(ajouterProc(Proc*)));
    connect(p,SIGNAL(procCreer(Proc*)),this,SLOT(pauseContinue()));
}

void MainWidget::chargerFichier()
{
    QString fileName=QFileDialog::getOpenFileName(this,"Chargement Fichier de Configuration",QString(),"*");
    if(fileName.size()==0)
        return;
    clear();
    m_scheduler->reinit(fileName);
}

void MainWidget::actualiser()
{
    actualiserFilleCpu();
    actualiserFilleEs();
}

void MainWidget::actualiserFilleCpu()
{
    QList<Proc *> filleCpu;
    int k=0;
    m_filleCpu->clearContents();
    if(m_scheduler->procCPU()!=NULL)
    {
        ecrireLigneCpu(m_scheduler->procCPU(),0,true);
        k++;
    }
    m_filleCpu->setRowCount(k+1);
    for(int i=0;i<m_scheduler->groups().size();i++)
    {
        filleCpu=m_scheduler->groups().at(i)->filleCpu();
        for(int j=0;j<filleCpu.size();j++)
        {
            m_filleCpu->setRowCount(k+1);
            ecrireLigneCpu(filleCpu[j],k);
            k++;
        }
    }
}

void MainWidget::ecrireLigneCpu(Proc *proc, int ligne,bool bold)
{
    m_filleCpu->setItem(ligne,0,creationTableItem(QString::number(proc->pid()),bold));
    m_filleCpu->setItem(ligne,1,creationTableItem(QString::fromStdString(proc->utilisateur()->nom()),bold));
    m_filleCpu->setItem(ligne,2,creationTableItem(proc->nom(),bold));
    m_filleCpu->setItem(ligne,3,creationTableItem(QString::number(proc->priorite()),bold));
}

void MainWidget::actualiserFilleEs()
{
    QList<Proc *> filleEs=m_scheduler->filleEs();
    if(m_scheduler->procES()!=NULL)
        filleEs.push_front(m_scheduler->procES());
    m_filleEs->clearContents();
    m_filleEs->setRowCount(filleEs.size() + 1);
    for(int i=0;i<filleEs.size();i++)
        ecrireLigneEs(filleEs[i],i);
}

void MainWidget::ecrireLigneEs(Proc *proc, int ligne)
{
    bool bold=false;
    if(ligne==0)
        bold=true;
    m_filleEs->setItem(ligne,0,creationTableItem(QString::number(proc->pid()),bold));
    m_filleEs->setItem(ligne,1,creationTableItem(QString::fromStdString(proc->utilisateur()->nom()),bold));
    m_filleEs->setItem(ligne,2,creationTableItem(proc->nom(),bold));
    m_filleEs->setItem(ligne,3,creationTableItem(QString::number(proc->debutAttente()),bold));
}


void MainWidget::actualiserProcFin(const QString &nom, int pid, int arrive, int sortie)
{
    int i=m_procFini->rowCount() - 1;
    m_procFini->setRowCount(i + 2);
    m_procFini->setItem(i,0,creationTableItem(QString::number(pid)));
    m_procFini->setItem(i,1,creationTableItem(nom));
    m_procFini->setItem(i,2,creationTableItem(QString::number(arrive)));
    m_procFini->setItem(i,3,creationTableItem(QString::number(sortie)));
}

void MainWidget::actualiserAction(const QString &nom, int pid, Etat etatPrec, Etat etatAct, int cpu)
{
    int i=m_action->rowCount() - 1;
    m_action->setRowCount(i + 2);
    m_action->setItem(i,0,creationTableItem(QString::number(cpu)));
    m_action->setItem(i,1,creationTableItem(QString::number(pid)));
    m_action->setItem(i,2,creationTableItem(nom));
    m_action->setItem(i,3,creationTableItem(Proc::etatToString(etatPrec)));
    m_action->setItem(i,4,creationTableItem(Proc::etatToString(etatAct)));
}

void MainWidget::pauseContinue()
{
    if(m_pauseContinue->text()==DEBUTER)
    {
        m_scheduler->start();
        m_pauseContinue->setText(PAUSE);
    }
    else if(m_pauseContinue->text()==CONTINUER)
    {
        m_scheduler->continu();
        m_pauseContinue->setText(PAUSE);
    }
    else
    {
        m_scheduler->pause();
        m_pauseContinue->setText(CONTINUER);
    }
}

void MainWidget::quitter()
{
    this->close();
}

void MainWidget::ajusterTaille(int,int max)
{
    QScrollBar* bar=dynamic_cast<QScrollBar*>(sender());
    bar->setValue(max);
}

void MainWidget::changerCpu(int valeur)
{
    m_cpu->setText(QString::number(valeur));
}

void MainWidget::changerUnite(int valeur)
{
    m_scheduler->setUnite(valeur);
}

void MainWidget::changerQuantum(int valeur)
{
    m_scheduler->setQuantumMax(valeur);
}

void MainWidget::clear()
{
    m_filleCpu->clearContents();
    m_filleEs->clearContents();
    m_action->clearContents();
    m_procFini->clearContents();
    m_filleCpu->setRowCount(1);
    m_filleEs->setRowCount(1);
    m_procFini->setRowCount(1);
    m_action->setRowCount(1);
    m_graphPainter->clear();

}

void MainWidget::connectBar(QScrollBar *bar)
{
    connect(bar,SIGNAL(rangeChanged(int,int)),this,SLOT(ajusterTaille(int,int)));
}

QFormLayout *MainWidget::inlineForm(QWidget *widget, const QString &text)
{
    QFormLayout* res=new QFormLayout();
    res->addRow(text,widget);
    return res;
}

void MainWidget::setColor(QPalette::ColorRole role, const QColor &color)
{
    Utile::setWidgetColor(this,role,color);
}

QTableWidget *MainWidget::createTableWidget(int row, int column, const QStringList &list)
{
    QTableWidget* res=new QTableWidget(row,column);
    res->setHorizontalHeaderLabels(list);
    res->horizontalScrollBar()->hide();
    Utile::setWidgetColor(res,QPalette::Base,BACKGROUND_COLOR);
    Utile::setWidgetColor(res,QPalette::Window,BACKGROUND_COLOR);
    return res;
}

