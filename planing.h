#ifndef PLANING_H
#define PLANING_H

#include <QList>
#include <QString>

#define ATTRIBUT_NOM "nom"
#define ATTRIBUT_PID "pid"
#define ATTRIBUT_PPID "ppid"
#define ATTRIBUT_UTILISATEUR "utilisateur"
#define ATTRIBUT_DEBUT "debut"
#define ATTRIBUT_ES "e/s"
#define ATTRIBUT_CPU "cpu"
#define ATTRIBUT_FIN "fin"


class Planing
{
public:
    enum TypePlaning
    {
        E_S, CPU
    };

    struct ItemPlaning
    {
        int nombre;
        TypePlaning type;
    };

    Planing();
    void ajouter(TypePlaning type,int nombre);
    void dec();
    bool fini();
    bool vide();
    void removeLast();
    TypePlaning type();
    QList<ItemPlaning> planing() const;
    QString toString();

    static QString typePlaningToString(TypePlaning type);
    static QString planingItemToString(ItemPlaning const& item);

protected:
    QList<ItemPlaning> m_planing;

};

#endif // PLANING_H
