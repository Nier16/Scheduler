#include "graphpainter.h"

GraphPainter::GraphPainter(int nombreUnite, int unitTemp, int separation, int epesseurAxe, int epesseurLigne,
                           const QSize &tailleBordure, const QColor &colorAxeX, const QColor &colorAxeY) : QWidget()
{
    m_nombreUnite=nombreUnite;
    m_tailleUnite=unitTemp;
    m_sepration=separation;
    m_epesseurAxe=epesseurAxe;
    m_epesseurLigne=epesseurLigne;
    m_tailleBordure=tailleBordure;
    m_colorAxeX=colorAxeX;
    m_colorAxeY=colorAxeY;
    setMinimumSize(800,200);
    Utile::setWidgetColor(this,QPalette::Background,BACKGROUND_COLOR);
    resize();
}

void GraphPainter::addItem(int debut, int fin, GraphPainter::TypeItem type, QString nom, QColor color)
{
    Item item;
    item.debut=debut;
    item.fin=fin;
    item.type=type;
    item.nom=nom;
    item.color=color;
    m_item.push_back(item);
    resize();
    repaint();
}

void GraphPainter::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(this->rect(),QBrush(BACKGROUND_COLOR));
    paintAxeX(&painter);
    paintAxeY(&painter);
    paintDonnees(&painter);
}

void GraphPainter::paintAxeX(QPainter *painter)
{
    QPoint debut(m_tailleBordure.width(),height()-m_tailleBordure.height());
    QPoint fin(width()-m_tailleBordure.width(),debut.y()+m_epesseurAxe);
    QPoint act;
    QPoint posText;
    act.setY(height()-m_tailleBordure.height());
    posText.setY(act.y()+15);
    painter->setPen(m_colorAxeX);
    painter->fillRect(QRect(debut,fin),QBrush(m_colorAxeX));
    if(m_item.isEmpty())
        return;
    for(int x=m_nombreUnite;x<=m_item.last().fin;x+=m_nombreUnite)
    {
        act.setX(x*m_tailleUnite+m_tailleBordure.width());
        posText.setX(act.x()-5);
        tracerTirer(painter,act,m_colorAxeX);
        painter->drawText(posText,QString::number(x));
    }
}

void GraphPainter::paintAxeY(QPainter *painter)
{
    QPoint debut(m_tailleBordure.width(),height()-m_tailleBordure.height());
    QPoint fin(debut.x()-m_epesseurAxe,m_tailleBordure.height());
    painter->setPen(m_colorAxeY);
    painter->fillRect(QRect(debut,fin),QBrush(m_colorAxeY));
    painter->drawText(QPoint(fin.x()-20,m_hauteurEs-6),QString("e/s"));
    painter->drawText(QPoint(fin.x()-20,m_hauteurCpu-6),QString("cpu"));
}

void GraphPainter::paintDonnees(QPainter *painter)
{
    QPoint debut;
    QPoint fin;
    QPoint textPos;
    for(int i=0;i<m_item.size();i++)
    {
        debut.setX(m_item[i].debut*m_tailleUnite+m_tailleBordure.width());
        fin.setX(m_item[i].fin*m_tailleUnite+m_tailleBordure.width());
        if(m_item[i].type==GraphPainter::ES)
        {
            debut.setY(m_hauteurEs);
            fin.setY(m_hauteurEs+m_epesseurLigne);
        }
        else
        {
            debut.setY(m_hauteurCpu);
            fin.setY(m_hauteurCpu+m_epesseurLigne);
        }
        textPos.setY(debut.y()-15);
        textPos.setX(debut.x()+((fin.x()-debut.x())/2)-15);
        painter->setPen(m_item[i].color);
        painter->fillRect(QRect(debut,fin),QBrush(m_item[i].color));
        painter->drawText(textPos,m_item[i].nom);
    }
}

void GraphPainter::tracerTirer(QPainter *painter, const QPoint &point, QColor const& couleur, int largeur,int hauteur)
{
    QPoint debut(point.x()-largeur/2,point.y()-hauteur/2);
    QPoint fin(debut.x()+largeur,debut.y()+hauteur);
    painter->fillRect(QRect(debut,fin),QBrush(couleur));
}

void GraphPainter::resize()
{
    int largeur;
    if(m_item.isEmpty() || (m_item.last().fin*m_tailleUnite+2*m_tailleBordure.width())<=MIN_WIDTH)
        largeur=MIN_WIDTH;
    else
        largeur=m_item.last().fin*m_tailleUnite+2*m_tailleBordure.width();
    QWidget::resize(largeur,3*m_sepration+2*m_tailleBordure.height());
    actualiserHauter();
}

void GraphPainter::clear()
{
    m_item.clear();
    repaint();
}

int GraphPainter::sepration() const
{
    return m_sepration;
}

void GraphPainter::setSepration(int sepration)
{
    m_sepration = sepration;
    resize();
}
int GraphPainter::epesseurAxe() const
{
    return m_epesseurAxe;
}

void GraphPainter::setEpesseurAxe(int epesseurAxe)
{
    m_epesseurAxe = epesseurAxe;
}
int GraphPainter::epesseurLigne() const
{
    return m_epesseurLigne;
}

void GraphPainter::setEpesseurLigne(int epesseurLigne)
{
    m_epesseurLigne = epesseurLigne;
}
QSize GraphPainter::tailleBordure() const
{
    return m_tailleBordure;
}

void GraphPainter::setTailleBordure(const QSize &tailleBordure)
{
    m_tailleBordure = tailleBordure;
    resize();
}
QColor GraphPainter::colorAxeX() const
{
    return m_colorAxeX;
}

void GraphPainter::setColorAxeX(const QColor &colorAxeX)
{
    m_colorAxeX = colorAxeX;
}
QColor GraphPainter::colorAxeY() const
{
    return m_colorAxeY;
}

void GraphPainter::setColorAxeY(const QColor &colorAxeY)
{
    m_colorAxeY = colorAxeY;
}

int GraphPainter::nombreUnite() const
{
    return m_nombreUnite;
}

void GraphPainter::setNombreUnite(int nombreUnite)
{
    m_nombreUnite = nombreUnite;
}
int GraphPainter::tailleUnite() const
{
    return m_tailleUnite;
}

void GraphPainter::setTailleUnite(int tailleUnite)
{
    m_tailleUnite = tailleUnite;
}


void GraphPainter::actualiserHauter()
{
    m_hauteurCpu=height()-m_tailleBordure.height()-m_sepration;
    m_hauteurEs=m_hauteurCpu-m_sepration;
}
