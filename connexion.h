#ifndef CONNEXION_H
#define CONNEXION_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class connexion
{
public:
    connexion();
    static QSqlDatabase connexionMysql();
};

#endif // CONNEXION_H
