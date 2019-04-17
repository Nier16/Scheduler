#include "utile.h"

void Utile::setWidgetColor(QWidget *widget, QPalette::ColorRole role, const QColor &color)
{
    QPalette p=widget->palette();
    p.setColor(role,color);
    widget->setPalette(p);
}
