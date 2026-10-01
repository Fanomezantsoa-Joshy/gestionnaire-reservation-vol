#include "connexion.h"

connexion::connexion() {}
QSqlDatabase connexion::connexionMysql()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("localhost");
    db.setDatabaseName("gestion_billets_avion");
    db.setUserName("root");
    db.setPassword("");

    if (!db.open()) {
        qDebug() << "Erreur de connexion à Mysql : " << db.lastError().text();
    } else {
        qDebug() << "Connexion à la base de donnée Mysql réussie.";
    }

    return db;
}
