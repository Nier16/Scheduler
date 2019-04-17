#include "planing.h"

Planing::Planing()
{
}

void Planing::ajouter(TypePlaning type, int nombre)
{
    if(!m_planing.isEmpty() && m_planing.first().type==type)
    {
        m_planing.first().nombre+=nombre;
        return;
    }
    ItemPlaning ip;
    ip.type=type;
    ip.nombre=nombre;
    m_planing.push_front(ip);
}

void Planing::dec()
{
    m_planing.last().nombre--;
}

bool Planing::fini()
{
    return m_planing.last().nombre==0;
}

bool Planing::vide()
{
    return m_planing.empty();
}

void Planing::removeLast()
{
    m_planing.pop_back();
}

Planing::TypePlaning Planing::type()
{
    return m_planing.last().type;
}

QList<Planing::ItemPlaning> Planing::planing() const
{
    return m_planing;
}

QString Planing::toString()
{
    QString res;
    for(int i=m_planing.size()-1;i>=0;i--)
    {
        res.append(planingItemToString(m_planing[i]));
        if(i!=0)
            res.append("\n");
    }
    return res;
}

QString Planing::typePlaningToString(Planing::TypePlaning type)
{
    if(type==Planing::E_S)
        return "E/S";
    else
        return "CPU";
}

QString Planing::planingItemToString(const Planing::ItemPlaning &item)
{
    return Planing::typePlaningToString(item.type) + " " + QString::number(item.nombre);
}

