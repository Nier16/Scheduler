#ifndef GRAPHPAINTER_H
#define GRAPHPAINTER_H

#include <QPaintDevice>
#include <QPaintEvent>
#include <QPainter>
#include <QWidget>
#include "utile.h"

#define TAILLE_UNITE_TEMPS 3
#define NOMBRE_UNITE 15
#define SEPARATION 58
#define EPESSEUR_AXE 3
#define EPESSEUR_LIGNE 2
#define TAILLE_BORDURE QSize(50,40)
#define COLOR_AXE_X Qt::blue
#define COLOR_AXE_Y Qt::green
#define MIN_WIDTH 300
#define BACKGROUND_COLOR QColor(255,251,195)

class GraphPainter : public QWidget
{
    Q_OBJECT
public:
    enum TypeItem
    {
        ES,
        CPU
    };

    struct Item
    {
        int debut;
        int fin;
        TypeItem type;
        QString nom;
        QColor color;
    };
    GraphPainter(int nombreUnite=NOMBRE_UNITE,int unitTemp=TAILLE_UNITE_TEMPS,int separation=SEPARATION,int epesseurAxe=EPESSEUR_AXE,
                 int epesseurLigne=EPESSEUR_LIGNE,QSize const& tailleBordure=TAILLE_BORDURE,QColor const& colorAxeX=COLOR_AXE_X,
                 QColor const& colorAxeY=COLOR_AXE_Y);
    void paintEvent(QPaintEvent *);
    void paintAxeX(QPainter* painter);
    void paintAxeY(QPainter* painter);
    void paintDonnees(QPainter* painter);
    void tracerTirer(QPainter* painter, QPoint const& point, const QColor &couleur, int largeur=3, int hauteur=6);
    void resize();
    void clear();

    int sepration() const;
    void setSepration(int sepration);

    int epesseurAxe() const;
    void setEpesseurAxe(int epesseurAxe);

    int epesseurLigne() const;
    void setEpesseurLigne(int epesseurLigne);

    QSize tailleBordure() const;
    void setTailleBordure(const QSize &tailleBordure);

    QColor colorAxeX() const;
    void setColorAxeX(const QColor &colorAxeX);

    QColor colorAxeY() const;
    void setColorAxeY(const QColor &colorAxeY);

    int nombreUnite() const;
    void setNombreUnite(int nombreUnite);

    int tailleUnite() const;
    void setTailleUnite(int tailleUnite);

public slots:
    void addItem(int debut,int fin,GraphPainter::TypeItem type,QString nom,QColor color);

protected :
    QList<Item> m_item;
    int m_tailleUnite;
    int m_nombreUnite;
    int m_sepration;
    int m_epesseurAxe;
    int m_epesseurLigne;
    QSize m_tailleBordure;
    QColor m_colorAxeX;
    QColor m_colorAxeY;
private :
    void actualiserHauter();

    int m_hauteurEs;
    int m_hauteurCpu;

signals:

public slots:

};

#endif // GRAPHPAINTER_H
