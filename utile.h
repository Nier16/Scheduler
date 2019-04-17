#ifndef UTILE_H
#define UTILE_H

#include <QWidget>
#include <QColor>
#include <QPalette>

class Utile
{
public:
    static void setWidgetColor(QWidget* widget,QPalette::ColorRole role,QColor const& color);
};

#endif // UTILE_H
