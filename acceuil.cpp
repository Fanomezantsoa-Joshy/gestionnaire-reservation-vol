#include "acceuil.h"
#include "avion.h"
#include "compagnie.h"
#include "passager.h"
#include "reservation.h"
#include "vol.h"
#include "connexion.h"
#include "admin.h"

#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QMessageBox>
#include "ui_acceuil.h"

acceuil::acceuil(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::acceuil)
{
    ui->setupUi(this);
    QString nomAdministrateur = admin::instance().nomAdministrateur;
    ui->contenuAcceuil->setCurrentIndex(pageStastistique);
    ui->nomAdministrateur->setText(nomAdministrateur);
    ui->menuStatistique->setStyleSheet(styleFocus);
    infoCompte();
    QDate date = QDate::currentDate();
    int jour = date.day();
    int mois = date.month();
    int annee = date.year() - 18;
    date.setDate(annee,mois,jour);
    afficherStatistiques();
}

acceuil::~acceuil()
{
    delete ui;
}

void acceuil::afficherHistorique()
{
    QSqlDatabase db = connexion::connexionMysql();
    if(db.isOpen())
    {
        QString administrateur = admin::instance().nomAdministrateur;
        QString recherche = QString(R"(select date,nom_utilisateur,operation from historique where nom_utilisateur = "%1")").arg(administrateur);
        QSqlQueryModel *model = new QSqlQueryModel(this);
        model->setQuery(recherche, db);
        model->setHeaderData(0, Qt::Horizontal, "Date");
        model->setHeaderData(1, Qt::Horizontal, "Nom de l'administrateur");
        model->setHeaderData(2, Qt::Horizontal, "Opération effectuer");

        ui->listeHistorique->setModel(model);
    }
    else
    {
        QMessageBox::critical(this,"Erreur","Impossible de se connecter à Mysql !");
        return;
    }
}

void acceuil::infoCompte()
{
    QString administratuer = admin::instance().nomAdministrateur;
    QSqlQuery query;
    QString nom;
    QString prenoms;
    QDate naissance;
    QString cin;
    query.prepare("select nom from compte where nom_utilisateur = ?");
    query.addBindValue(administratuer);
    if(query.exec())
    {
        if(query.next())
        {
            nom = query.value(0).toString();
        }
    }
    else
    {
        QMessageBox::critical(this,"Erreur","Impossible de se connecter à Mysql !");
        return;
    }
    query.prepare("select prenoms from compte where nom_utilisateur = ?");
    query.addBindValue(administratuer);
    if(query.exec())
    {
        if(query.next())
        {
            prenoms = query.value(0).toString();
        }
    }
    else
    {
        QMessageBox::critical(this,"Erreur","Impossible de se connecter à Mysql !");
        return;
    }
    query.prepare("select date_naissance from compte where nom_utilisateur = ?");
    query.addBindValue(administratuer);
    if(query.exec())
    {
        if(query.next())
        {
            naissance = query.value(0).toDate();
        }
    }
    else
    {
        QMessageBox::critical(this,"Erreur","Impossible de se connecter à Mysql !");
        return;
    }
    query.prepare("select numero_cin from compte where nom_utilisateur = ?");
    query.addBindValue(administratuer);
    if(query.exec())
    {
        if(query.next())
        {
            cin = query.value(0).toString();
        }
    }
    else
    {
        QMessageBox::critical(this,"Erreur","Impossible de se connecter à Mysql !");
        return;
    }
    ui->nom->setText(nom);
    ui->prenoms->setText(prenoms);
    ui->administrateur->setText(administratuer);
    ui->naissance->setDate(naissance);
    ui->cin->setText(cin);
}

void acceuil::afficherStatistiques()
{
    QString nbrAvion;
    QString nbrCompagnie;
    QString nbrReservation;
    QString nbrVol;
    QString reservationAu;
    QString volAu;
    int avionDisponnible;
    QDate date = QDate::currentDate();
    QSqlQuery query;

    query.prepare("select count(immatriculation) from avion");
    if(query.exec())
    {
        if(query.next())
        {
            nbrAvion = query.value(0).toString();
        }
    }
    else
    {
        QMessageBox::critical(this,"Erreur","Impossible de se connecter à Mysql !");
        return;
    }

    query.prepare("select count(identifiant) from compagnie_aerienne");
    if(query.exec())
    {
        if(query.next())
        {
            nbrCompagnie = query.value(0).toString();
        }
        else
        {
            QMessageBox::critical(this,"Erreur","Impossible de se connecter à Mysql !");
            return;
        }
    }
    else
    {
        QMessageBox::critical(this,"Erreur","Impossible de se connecter à Mysql !");
        return;
    }

    query.prepare("select count(numero_reservation) from reservation");
    if(query.exec())
    {
        if(query.next())
        {
            nbrReservation = query.value(0).toString();
        }
        else
        {
            QMessageBox::critical(this,"Erreur","Impossible de se connecter à Mysql !");
            return;
        }
    }
    else
    {
        QMessageBox::critical(this,"Erreur","Impossible de se connecter à Mysql !");
        return;
    }

    query.prepare("select count(numero_vol) from vol");
    if(query.exec())
    {
        if(query.next())
        {
            nbrVol = query.value(0).toString();
        }
        else
        {
            QMessageBox::critical(this,"Erreur","Impossible de se connecter à Mysql !");
            return;
        }
    }
    else
    {
        QMessageBox::critical(this,"Erreur","Impossible de se connecter à Mysql !");
        return;
    }

    query.prepare("select count(numero_reservation) from reservation where date_reservation = ?");
    query.addBindValue(date);
    if(query.exec())
    {
        if(query.next())
        {
            reservationAu = query.value(0).toString();
        }
        else
        {
            QMessageBox::critical(this,"Erreur","Impossible de se connecter à Mysql !");
            return;
        }
    }
    else
    {
        QMessageBox::critical(this,"Erreur","Impossible de se connecter à Mysql !");
        return;
    }

    query.prepare("select count(numero_vol) from vol where date_depart = ?");
    query.addBindValue(date);
    if(query.exec())
    {
        if(query.next())
        {
            volAu = query.value(0).toString();
        }
        else
        {
            QMessageBox::critical(this,"Erreur","Impossible de se connecter à Mysql !");
            return;
        }
    }
    else
    {
        QMessageBox::critical(this,"Erreur","Impossible de se connecter à Mysql !");
        return;
    }

    query.prepare("select count(avion_id) from vol");
    if(query.exec())
    {
        if(query.next())
        {
            int nombreAvion = nbrAvion.toInt();
            avionDisponnible = nombreAvion - query.value(0).toInt();
        }
        else
        {
            QMessageBox::critical(this,"Erreur","Impossible de se connecter à Mysql !");
            return;
        }
    }
    else
    {
        QMessageBox::critical(this,"Erreur","Impossible de se connecter à Mysql !");
        return;
    }

    ui->nbrAvion->setText(nbrAvion);
    ui->nbrCompagnie->setText(nbrCompagnie);
    ui->nbrReservation->setText(nbrReservation);
    ui->nbrVol->setText(nbrVol);
    ui->reservationAu->setText(reservationAu);
    ui->departAu->setText(volAu);
    ui->avionDisponnible->setText(QString::number(avionDisponnible));
}

void acceuil::on_menuAcceuil_clicked()
{
    acceuil *fenetre = new acceuil();
    if(this->isMaximized())
    {
        fenetre->showMaximized();
    }
    else
    {
        fenetre->show();
    }
    this->close();
}


void acceuil::on_menuReservation_clicked()
{
    reservation *fenetre = new reservation();
    if(this->isMaximized())
    {
        fenetre->showMaximized();
    }
    else
    {
        fenetre->show();
    }
    this->close();
}


void acceuil::on_menuPassager_clicked()
{
    passager *fenetre = new passager();
    if(this->isMaximized())
    {
        fenetre->showMaximized();
    }
    else
    {
        fenetre->show();
    }
    this->close();
}


void acceuil::on_menuVol_clicked()
{
   vol *fenetre = new vol();
    if(this->isMaximized())
    {
        fenetre->showMaximized();
    }
    else
    {
        fenetre->show();
    }
    this->close();
}


void acceuil::on_menuAvion_clicked()
{
    avion *fenetre = new avion();
    if(this->isMaximized())
    {
        fenetre->showMaximized();
    }
    else
    {
        fenetre->show();
    }
    this->close();
}


void acceuil::on_menuCompagnieAerienne_clicked()
{
    compagnie *fenetre = new compagnie();
    if(this->isMaximized())
    {
        fenetre->showMaximized();
    }
    else
    {
        fenetre->show();
    }
    this->close();
}


void acceuil::on_menuQuitter_clicked()
{
    QMessageBox message;
    message.setIcon(QMessageBox::Warning);
    message.setWindowTitle("Quitter");
    message.setText("Voulez vous vraiment quitter ?");
    QPushButton *btnOui = message.addButton("Oui",QMessageBox::AcceptRole);
    QPushButton *btnNon = message.addButton("Non",QMessageBox::RejectRole);
    message.exec();
    if(message.clickedButton() == btnOui)
    {
        this->close();
    }
    else
    {
        return;
    }
}


void acceuil::on_menuSeDeconnecter_clicked()
{
    QMessageBox message;
    message.setIcon(QMessageBox::Warning);
    message.setWindowTitle("Se déconnecter");
    message.setText("Voulez vous vraiment déconnecter ?");
    QPushButton *btnOui = message.addButton("Oui",QMessageBox::AcceptRole);
    QPushButton *btnNon = message.addButton("Non",QMessageBox::RejectRole);
    message.exec();
    if(message.clickedButton() == btnOui)
    {
        admin *fenetre = new admin();
        if(this->isMaximized())
        {
            fenetre->showMaximized();
        }
        else
        {
            fenetre->show();
        }
        this->close();
    }
    else
    {
        return;
    }
}

void acceuil::on_contenuAcceuil_currentChanged(int arg1)
{
    ui->menuStatistique->setStyleSheet(style);
    ui->menuMonCompte->setStyleSheet(style);
    ui->menuHistorique->setStyleSheet(style);
    ui->menuAPropos->setStyleSheet(style);
    if(arg1 == pageStastistique)
    {
        afficherStatistiques();
        ui->menuStatistique->setStyleSheet(styleFocus);
    }
    if(arg1 == monCompte || arg1 == modCompte)
    {
        ui->menuMonCompte->setStyleSheet(styleFocus);
    }
    if(arg1 == historique)
    {
        afficherHistorique();
        ui->menuHistorique->setStyleSheet(styleFocus);
    }
    if(arg1 == aPropos)
    {
        ui->menuAPropos->setStyleSheet(styleFocus);
    }
    if(arg1 == modCompte)
    {
        QString nom = ui->nom->text();
        QString prenoms = ui->prenoms->text();
        QString admin = ui->administrateur->text();
        QDate naissance = ui->naissance->date();
        QString cin = ui->cin->text();
        ui->modNom->setText(nom);
        ui->modPrenoms->setText(prenoms);
        ui->modAdministrateur->setText(admin);
        ui->modNaissance->setDate(naissance);
        ui->modCin->setText(cin);

        ui->modNom->setFocus();
    }
}

void acceuil::on_rechercheHistorique_textChanged(const QString &arg1)
{
    QSqlDatabase db = connexion::connexionMysql();
    QString administrateur = admin::instance().nomAdministrateur;
    QString recherche = QString(R"(select date,nom_utilisateur,operation from historique where date like "%%1%" and nom_utilisateur = "%2")").arg(arg1,administrateur);
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery(recherche,db);
    model->setHeaderData(0, Qt::Horizontal, "Date");
    model->setHeaderData(1, Qt::Horizontal, "Nom de l'administrateur");
    model->setHeaderData(2, Qt::Horizontal, "Opération effectuer");

    ui->listeHistorique->setModel(model);
}


void acceuil::on_menuMonCompte_clicked()
{
    ui->contenuAcceuil->setCurrentIndex(monCompte);
}


void acceuil::on_btnEnregistrerMod_clicked()
{
    QString administrateur = admin::instance().nomAdministrateur;
    QString nom = ui->modNom->text();
    QString prenoms = ui->modPrenoms->text();
    QString modAdmin = ui->modAdministrateur->text();
    QDate naissance = ui->modNaissance->date();
    QString cin = ui->modCin->text();
    if(nom.isEmpty())
    {
        QMessageBox::critical(this,"Champ vide","Veuillez saisir votre nom !");
        ui->modNom->setFocus();
        return;
    }
    if(prenoms.isEmpty())
    {
        QMessageBox::critical(this,"Champ vide","Veuillez saisir votre prenoms !");
        ui->modPrenoms->setFocus();
        return;
    }
    if(modAdmin.isEmpty())
    {
        QMessageBox::critical(this,"Champ vide","Veuillez saisir le nom d'administrateur que vous allez utiliser !");
        ui->modAdministrateur->setFocus();
        return;
    }

    QSqlQuery query;
    query.prepare("select * from compte where nom_utilisteur = ?");
    query.addBindValue(modAdmin);
    if(query.exec())
    {
        if(query.next())
        {
            QMessageBox::critical(this,"Erreur","Le nom d'administrateur que vous avez utiliser est déjà utiliser !");
            ui->modAdministrateur->setFocus();
            return;
        }
    }
    else
    {
        QMessageBox::critical(this,"Erreur","Impossible de se connecter à Mysql !");
        return;
    }

    if(cin.isEmpty())
    {
        QMessageBox::critical(this,"Champ vide","Veuillez saisir votre numero CIN !");
        ui->modCin->setFocus();
        return;
    }

    query.prepare("update compte set nom = ?, prenoms = ?, nom_utilisateur = ?, date_naissance = ?, numero_cin = ? where nom_utilisateur = ?");
    query.addBindValue(nom);
    query.addBindValue(prenoms);
    query.addBindValue(modAdmin);
    query.addBindValue(naissance);
    query.addBindValue(cin);
    query.addBindValue(administrateur);
    if(query.exec())
    {
        ui->contenuAcceuil->setCurrentIndex(monCompte);
        admin::instance().nomAdministrateur = modAdmin;
        ui->nomAdministrateur->setText(admin::instance().nomAdministrateur);
        QMessageBox::information(this,"Modification réussie","Les informations de votre compte ont été modifier avec succès !");
    }
    else
    {
        QMessageBox::critical(this,"Erreur","Impossible de se connecter à Mysql !");
        return;
    }
}


void acceuil::on_btnSupprimer_clicked()
{
    QMessageBox message;
    message.setIcon(QMessageBox::Warning);
    message.setWindowTitle("Confirmation");
    message.setText("Voulez vous vraiment supprimer votre compte administrateur ?");
    QPushButton *btnOui = message.addButton("Oui",QMessageBox::AcceptRole);
    QPushButton *btnNon = message.addButton("Non",QMessageBox::RejectRole);
    message.exec();
    if(message.clickedButton() == btnOui)
    {
        QString nomAdmin = admin::instance().nomAdministrateur;
        QSqlQuery query;
        query.prepare("delete from compte where nom_utilisateur = ?");
        query.addBindValue(nomAdmin);
        if(query.exec())
        {
            admin *fenetre = new admin();
            if(this->isMaximized())
            {
                fenetre->showMaximized();
            }
            else
            {
                fenetre->show();
            }
            this->close();
            QMessageBox::information(this,"Suppression réussie","Votre compte a été supprimer avec succès !");
        }
        else
        {
            QMessageBox::critical(this,"Erreur","Impossible de se connecter à Mysql !");
            return;
        }
    }
    else
    {
        return;
    }
}


void acceuil::on_menuStatistique_clicked()
{
    ui->contenuAcceuil->setCurrentIndex(pageStastistique);
}


void acceuil::on_menuHistorique_clicked()
{
    ui->contenuAcceuil->setCurrentIndex(historique);
}


void acceuil::on_menuAPropos_clicked()
{
    ui->contenuAcceuil->setCurrentIndex(aPropos);
}


void acceuil::on_btnHistorique_clicked()
{
    ui->contenuAcceuil->setCurrentIndex(historique);
}


void acceuil::on_btnModifier_clicked()
{
    ui->contenuAcceuil->setCurrentIndex(modCompte);
}


void acceuil::on_btnAnnulerMod_clicked()
{
    QMessageBox message;
    message.setIcon(QMessageBox::Warning);
    message.setWindowTitle("Confirmation");
    message.setText("Les modifications que vous avez apporté à votre compte seront perdue.\nVoulez vous continuez ?");
    QPushButton *btnOui = message.addButton("Oui",QMessageBox::AcceptRole);
    QPushButton *btnNon = message.addButton("Non",QMessageBox::RejectRole);
    message.exec();
    if(message.clickedButton() == btnOui)
    {
        ui->contenuAcceuil->setCurrentIndex(monCompte);
    }
    else
    {
        return;
    }
}

