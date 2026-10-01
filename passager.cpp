#include "acceuil.h"
#include "avion.h"
#include "compagnie.h"
#include "passager.h"
#include "reservation.h"
#include "vol.h"
#include "connexion.h"
#include "admin.h"

#include <QSqlQueryModel>
#include <QMessageBox>
#include <QSqlQuery>

#include "ui_passager.h"

passager::passager(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::passager)
{
    ui->setupUi(this);
    ui->contenuPassager->setCurrentIndex(listePassager);
    ui->recherchePassager->clearFocus();
    ui->menuListe->setStyleSheet(styleFocus);
    ui->modNom->setFocus();
    QString nomAdministrateur = admin::instance().nomAdministrateur;
    ui->nomAdministrateur->setText(nomAdministrateur);
    ui->modNaissance->setMaximumDate(QDate::currentDate());
    afficherListePassager();
    infoListe();
}

passager::~passager()
{
    delete ui;
}

void passager::infoListe() {
    connect(ui->listePassager->selectionModel(),
            &QItemSelectionModel::currentRowChanged,
            this,
            [this](const QModelIndex &current, const QModelIndex &previous) {
                if (current.isValid()) {
                    QString identifiant = ui->listePassager->model()->index(current.row(),0).data().toString();
                    QString reservationEffetuer;
                    QString volReserver;
                    QSqlQuery query;
                    query.prepare("select numero_reservation from reservation where passager_id = ?");
                    query.addBindValue(identifiant);
                    if(query.exec())
                    {
                        if(query.next())
                        {
                            reservationEffetuer = query.value(0).toString();
                            ui->reservationEffectuer->setText(reservationEffetuer);
                            query.prepare("select numero_vol from reservation where passager_id = ?");
                            query.addBindValue(identifiant);
                            if(query.exec())
                            {
                                if(query.next())
                                {
                                    volReserver = query.value(0).toString();
                                    ui->volReserver->setText(volReserver);
                                }
                            }
                            else
                            {
                                QMessageBox::critical(this,"Erreur","Impossible de se connecter à Mysql !");
                                return;
                            }
                        }
                    }
                    else
                    {
                        QMessageBox::critical(this,"Erreur","Impossible de se connecter à Mysql !");
                        return;
                    }
                    ui->btnModifier->setEnabled(true);
                }
            });
}

void passager::afficherListePassager()
{
    QSqlDatabase db = connexion::connexionMysql();
    if(db.isOpen())
    {
        QSqlQueryModel *model = new QSqlQueryModel(this);
        model->setQuery("select identifiant,nom,prenoms,date_naissance,numero_passeport from passager", db);
        model->setHeaderData(0, Qt::Horizontal, "Identifiant");
        model->setHeaderData(1, Qt::Horizontal, "Nom");
        model->setHeaderData(2, Qt::Horizontal, "Prénoms");
        model->setHeaderData(3, Qt::Horizontal, "Date de naissance");
        model->setHeaderData(4, Qt::Horizontal, "Numero de passeport");
        ui->listePassager->setModel(model);
        ui->modListePassager->setModel(model);
        ui->supListePassager->setModel(model);
    }
    else
    {
        QMessageBox::critical(this,"Erreur","Impossible de se connecter à Mysql !");
        return;
    }
}


void passager::on_menuAcceuil_clicked()
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


void passager::on_menuReservation_clicked()
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


void passager::on_menuPassager_clicked()
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


void passager::on_menuVol_clicked()
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


void passager::on_menuAvion_clicked()
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


void passager::on_menuCompagnieAerienne_clicked()
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


void passager::on_menuQuitter_clicked()
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
    }}

void passager::on_menuCreer_clicked()
{
    QMessageBox message;
    message.setIcon(QMessageBox::Warning);
    message.setWindowTitle("Ajouter un passager");
    message.setText("Vouz devez créer une réservation pour effectuer cette action !");
    QPushButton *btnCreer = message.addButton("Créer une réservation",QMessageBox::AcceptRole);
    QPushButton *btnAnnuler = message.addButton("Annuler",QMessageBox::RejectRole);
    message.exec();
    if(message.clickedButton() == btnCreer)
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
    else
    {
        return;
    }
}


void passager::on_menuModifier_clicked()
{
    ui->contenuPassager->setCurrentIndex(modPassager);
}


void passager::on_menuSupprimer_clicked()
{
    ui->contenuPassager->setCurrentIndex(supPassager);
}


void passager::on_menuListe_clicked()
{
    ui->contenuPassager->setCurrentIndex(listePassager);
}

void passager::on_btnListeMod_clicked()
{
    afficherListePassager();
    ui->contenuPassager->setCurrentIndex(listePassager);
}

void passager::on_btnAnnulerMod_clicked()
{
    QMessageBox message;
    message.setIcon(QMessageBox::Warning);
    message.setWindowTitle("Annuler la modification du passager");
    message.setText("Les modifications que vous avez apporté à ce passager seront perdues.\nVoulez-vous continuer ?");
    QPushButton *btnOui = message.addButton("Oui",QMessageBox::AcceptRole);
    QPushButton *btnNon = message.addButton("Non",QMessageBox::RejectRole);
    message.exec();
    if(message.clickedButton() == btnOui)
    {
        passager::on_menuPassager_clicked();
    }
    else
    {
        return;
    }
}


void passager::on_btnEnregistrerMod_clicked()
{
    QString identifiant = acceuil::instance().identifiantPassager;
    QString modNom = ui->modNom->text();
    QString modPrenoms = ui->modPrenoms->text();
    QDate modNaissance = ui->modNaissance->date();
    QString modPasseport = ui->modPasseport->text();

    if(modNom.isEmpty())
    {
        QMessageBox::critical(this,"Champ vide","Veuillez saisir le nom du passager !");
        ui->modNom->setFocus();
        return;
    }
    if(modPrenoms.isEmpty())
    {
        QMessageBox::critical(this,"Champ vide","Veuillez saisir le prénoms du passager !");
        ui->modPrenoms->setFocus();
        return;
    }
    if(modPasseport.isEmpty())
    {
        QMessageBox::critical(this,"Champ vide","Veuillez saisir le numéro de passeport du passager !");
        ui->modPasseport->setFocus();
        return;
    }

    QSqlQuery query;
    QString passeport = acceuil::instance().modPasseport;
    if(modPasseport != passeport)
    {
        query.prepare("select numero_passeport from passager where numero_passeport = ?");
        query.addBindValue(modPasseport);
        if(query.exec())
        {
            if(query.next())
            {
                QMessageBox::critical(this,"Erreur","Le numéro de passeport que vous avez saisie est déjà utiliser !");
                ui->modPasseport->setFocus();
                return;
            }
        }
    }

    query.prepare("update passager set nom = ?, prenoms = ?, date_naissance = ?, numero_passeport = ? where identifiant = ?");
    query.addBindValue(modNom);
    query.addBindValue(modPrenoms);
    query.addBindValue(modNaissance);
    query.addBindValue(modPasseport);
    query.addBindValue(identifiant);

    if(query.exec())
    {
        QString operation = "Modification des informations du passager " + modPrenoms;
        QString administrateur = ui->nomAdministrateur->text();
        query.prepare("insert into historique (operation,nom_utilisateur) values (?,?)");
        query.addBindValue(operation);
        query.addBindValue(administrateur);
        if(query.exec())
        {
            ui->modNom->clear();
            ui->modPrenoms->clear();
            ui->modNaissance->clear();
            ui->modPasseport->clear();
            QMessageBox::information(this,"Modification réussie","Les informations du passager ont été modifier avec succès !");
            passager::on_menuPassager_clicked();
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
}

void passager::on_btnSupprimer_clicked()
{
    if(!(ui->listePassager->currentIndex().isValid()))
    {
        QMessageBox::critical(this,"Erreur","Veuillez sélectionnez le passager que vous voulez supprimer !");
        return;
    }


    QMessageBox message;
    message.setIcon(QMessageBox::Warning);
    message.setWindowTitle("Supprimer un passager");
    message.setText("La réservation au nom de ce passager aussi sera supprimer.\nVoulez-vous continuer ?");
    QPushButton *btnOui = message.addButton("Oui",QMessageBox::AcceptRole);
    QPushButton *btnNon = message.addButton("Non",QMessageBox::RejectRole);
    message.exec();

    if(message.clickedButton() == btnOui)
    {
        int ligne = ui->listePassager->currentIndex().row();
        QString identifiant = ui->listePassager->model()->index(ligne,0).data().toString();
        QString prenoms = ui->listePassager->model()->index(ligne,2).data().toString();
        QString numeroReservation;
        QSqlQuery query;
        query.prepare("select numero_reservation from reservation where passager_id = ?");
        if(query.exec())
        {
            if(query.next())
            {
                numeroReservation = query.value(0).toString();
                query.prepare("delete from passager where identifiant = ?");
                query.addBindValue(identifiant);
                if(query.exec())
                {
                    QString operation = "Suppression du passager " + prenoms + " et du reservation numéro " + numeroReservation;
                    QString administrateur = ui->nomAdministrateur->text();

                    query.prepare("insert into historique (operation,nom_utilisateur) values (?,?)");
                    query.addBindValue(operation);
                    query.addBindValue(administrateur);
                    if(query.exec())
                    {
                        afficherListePassager();
                        QMessageBox::information(this,"Suppression réussie","Le passager et la réservation ont été supprimer avec succès !");
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
    }
    else
    {
        return;
    }
}

void passager::on_btnModifier_clicked()
{
    if(!(ui->listePassager->currentIndex().isValid()))
    {
        QMessageBox::critical(this,"Erreur","Veuillez sélectionnez le passager que vous voulez modifier !");
        return;
    }

    int ligne = ui->listePassager->currentIndex().row();
    QString modIdentifiant = ui->listePassager->model()->index(ligne,0).data().toString();
    QString modNom = ui->listePassager->model()->index(ligne,1).data().toString();
    QString modPrenoms = ui->listePassager->model()->index(ligne,2).data().toString();
    QDate naissance = ui->listePassager->model()->index(ligne,3).data().toDate();
    QString modPasseport = ui->listePassager->model()->index(ligne,4).data().toString();

    ui->modIdentifiant->setText(modIdentifiant);
    ui->modNom->setText(modNom);
    ui->modPrenoms->setText(modPrenoms);
    ui->modNaissance->setDate(naissance);
    ui->modPasseport->setText(modPasseport);

    acceuil::instance().identifiantPassager = modIdentifiant;
    acceuil::instance().modPasseport = modPasseport;
    ui->contenuPassager->setCurrentIndex(modPassagerForm);
}

void passager::on_btnInserer_clicked()
{
    QMessageBox message;
    message.setIcon(QMessageBox::Warning);
    message.setWindowTitle("Ajouter un passager");
    message.setText("Vouz devez créer une réservation pour effectuer cette action !");
    QPushButton *btnCreer = message.addButton("Créer une réservation",QMessageBox::AcceptRole);
    QPushButton *btnAnnuler = message.addButton("Annuler",QMessageBox::RejectRole);
    message.exec();
    if(message.clickedButton() == btnCreer)
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
    else
    {
        return;
    }
}

void passager::on_btnMod_clicked()
{
    if(!(ui->modListePassager->currentIndex().isValid()))
    {
        QMessageBox::critical(this,"Erreur","Veuillez sélectionnez le passager que vous voulez modifier !");
        return;
    }

    int ligne = ui->modListePassager->currentIndex().row();
    QString modIdentifiant = ui->modListePassager->model()->index(ligne,0).data().toString();
    QString modNom = ui->modListePassager->model()->index(ligne,1).data().toString();
    QString modPrenoms = ui->modListePassager->model()->index(ligne,2).data().toString();
    QDate naissance = ui->modListePassager->model()->index(ligne,3).data().toDate();
    QString modPasseport = ui->modListePassager->model()->index(ligne,4).data().toString();

    ui->modIdentifiant->setText(modIdentifiant);
    ui->modNom->setText(modNom);
    ui->modPrenoms->setText(modPrenoms);
    ui->modNaissance->setDate(naissance);
    ui->modPasseport->setText(modPasseport);

    acceuil::instance().identifiantPassager = modIdentifiant;
    acceuil::instance().modPasseport = modPasseport;
    ui->contenuPassager->setCurrentIndex(modPassagerForm);
}

void passager::on_btnSup_clicked()
{
    if(!(ui->supListePassager->currentIndex().isValid()))
    {
        QMessageBox::critical(this,"Erreur","Veuillez sélectionnez le passager que vous voulez supprimer !");
        return;
    }

    QMessageBox message;
    message.setIcon(QMessageBox::Warning);
    message.setWindowTitle("Supprimer un passager");
    message.setText("La réservation au nom de ce passager aussi sera supprimer.\nVoulez-vous continuer ?");
    QPushButton *btnOui = message.addButton("Oui",QMessageBox::AcceptRole);
    QPushButton *btnNon = message.addButton("Non",QMessageBox::RejectRole);
    message.exec();

    if(message.clickedButton() == btnOui)
    {
        int ligne = ui->supListePassager->currentIndex().row();
        QString identifiant = ui->supListePassager->model()->index(ligne,0).data().toString();
        QString prenoms = ui->supListePassager->model()->index(ligne,2).data().toString();
        QString numeroReservation;
        QSqlQuery query;
        query.prepare("select numero_reservation from reservation where passager_id = ?");
        if(query.exec())
        {
            if(query.next())
            {
                numeroReservation = query.value(0).toString();
                query.prepare("delete from passager where identifiant = ?");
                query.addBindValue(identifiant);
                if(query.exec())
                {
                    QString operation = "Suppression du passager " + prenoms + " et du reservation numéro " + numeroReservation;
                    QString administrateur = ui->nomAdministrateur->text();

                    query.prepare("insert into historique (operation,nom_utilisateur) values (?,?)");
                    query.addBindValue(operation);
                    query.addBindValue(administrateur);
                    if(query.exec())
                    {
                        afficherListePassager();
                        QMessageBox::information(this,"Suppression réussie","Le passager et la réservation ont été supprimer avec succès !");
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
    }
    else
    {
        return;
    }
}


void passager::on_contenuPassager_currentChanged(int arg1)
{
    ui->recherchePassager->clear();
    ui->modRecherchePassager->clear();
    ui->supRecherchePassager->clear();
    ui->reservationEffectuer->clear();
    ui->volReserver->clear();
    ui->recherchePassager->clearFocus();
    ui->modRecherchePassager->clearFocus();
    ui->supRecherchePassager->clearFocus();
    ui->btnModifier->setEnabled(false);
    ui->btnSupprimer->setEnabled(false);
    ui->btnMod->setEnabled(false);
    ui->btnSup->setEnabled(false);

    afficherListePassager();

    ui->menuCreer->setStyleSheet(style);
    ui->menuModifier->setStyleSheet(style);
    ui->menuSupprimer->setStyleSheet(style);
    ui->menuListe->setStyleSheet(style);

    if(arg1 == listePassager)
    {
        ui->menuListe->setStyleSheet(styleFocus);
    }
    if(arg1 == modPassagerForm || arg1 == modPassager)
    {
        ui->menuModifier->setStyleSheet(styleFocus);
        ui->modNom->setFocus();
    }
    if(arg1 == supPassager)
    {
        ui->menuSupprimer->setStyleSheet(styleFocus);
    }
}


void passager::on_modNom_editingFinished()
{
    ui->modPrenoms->setFocus();
}


void passager::on_modPrenoms_editingFinished()
{
    ui->modNaissance->setFocus();
}


void passager::on_modNaissance_editingFinished()
{
    ui->modPasseport->setFocus();
}


void passager::on_modPasseport_editingFinished()
{
    ui->modPasseport->clearFocus();
}

void passager::on_recherchePassager_textChanged(const QString &arg1)
{
    QSqlDatabase db = connexion::connexionMysql();
    QString recherche = QString(R"(select * from passager where prenoms like "%%1%")").arg(arg1);
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery(recherche,db);
    model->setHeaderData(0, Qt::Horizontal, "Identifiant");
    model->setHeaderData(1, Qt::Horizontal, "Nom");
    model->setHeaderData(2, Qt::Horizontal, "Prenoms");
    model->setHeaderData(3, Qt::Horizontal, "Date de naissance");
    model->setHeaderData(4, Qt::Horizontal, "Numero de passeport");
    ui->listePassager->setModel(model);
    ui->btnModifier->setEnabled(false);
    ui->btnSupprimer->setEnabled(false);
    ui->reservationEffectuer->clear();
    ui->volReserver->clear();
}


void passager::on_modRecherchePassager_textChanged(const QString &arg1)
{
    QSqlDatabase db = connexion::connexionMysql();
    QString recherche = QString(R"(select * from passager where prenoms like "%%1%")").arg(arg1);
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery(recherche,db);
    model->setHeaderData(0, Qt::Horizontal, "Identifiant");
    model->setHeaderData(1, Qt::Horizontal, "Nom");
    model->setHeaderData(2, Qt::Horizontal, "Prenoms");
    model->setHeaderData(3, Qt::Horizontal, "Date de naissance");
    model->setHeaderData(4, Qt::Horizontal, "Numero de passeport");
    ui->modListePassager->setModel(model);
    ui->btnMod->setEnabled(false);
}

void passager::on_supRecherchePassager_textChanged(const QString &arg1)
{
    QSqlDatabase db = connexion::connexionMysql();
    QString recherche = QString(R"(select * from passager where prenoms like "%%1%")").arg(arg1);
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery(recherche,db);
    model->setHeaderData(0, Qt::Horizontal, "Identifiant");
    model->setHeaderData(1, Qt::Horizontal, "Nom");
    model->setHeaderData(2, Qt::Horizontal, "Prenoms");
    model->setHeaderData(3, Qt::Horizontal, "Date de naissance");
    model->setHeaderData(4, Qt::Horizontal, "Numero de passeport");
    ui->supListePassager->setModel(model);
    ui->btnSup->setEnabled(false);
}



void passager::on_listePassager_clicked(const QModelIndex &index)
{
}


void passager::on_modListePassager_clicked(const QModelIndex &index)
{
        ui->btnMod->setEnabled(true);
}


void passager::on_supListePassager_clicked(const QModelIndex &index)
{
        ui->btnSup->setEnabled(true);
}


void passager::on_modNom_textChanged(const QString &arg1)
{
    QString nom = ui->modNom->text().toUpper();
    ui->modNom->setText(nom);
}


void passager::on_modNom_textEdited(const QString &arg1)
{
    if(!ui->modNom->text().isEmpty() && !ui->modPrenoms->text().isEmpty() && !ui->modPasseport->text().isEmpty())
    {
        ui->btnEnregistrerMod->setEnabled(true);
    }
    else
    {
        ui->btnEnregistrerMod->setEnabled(false);
    }
}


void passager::on_modPrenoms_textEdited(const QString &arg1)
{
    if(!ui->modNom->text().isEmpty() && !ui->modPrenoms->text().isEmpty() && !ui->modPasseport->text().isEmpty())
    {
        ui->btnEnregistrerMod->setEnabled(true);
    }
    else
    {
        ui->btnEnregistrerMod->setEnabled(false);
    }
}


void passager::on_modNaissance_userDateChanged(const QDate &date)
{
    if(!ui->modNom->text().isEmpty() && !ui->modPrenoms->text().isEmpty() && !ui->modPasseport->text().isEmpty())
    {
        ui->btnEnregistrerMod->setEnabled(true);
    }
    else
    {
        ui->btnEnregistrerMod->setEnabled(false);
    }
}


void passager::on_modPasseport_textEdited(const QString &arg1)
{
    if(!ui->modNom->text().isEmpty() && !ui->modPrenoms->text().isEmpty() && !ui->modPasseport->text().isEmpty())
    {
        ui->btnEnregistrerMod->setEnabled(true);
    }
    else
    {
        ui->btnEnregistrerMod->setEnabled(false);
    }
}



void passager::on_menuSeDeconnecter_clicked()
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

