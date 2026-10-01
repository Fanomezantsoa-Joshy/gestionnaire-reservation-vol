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

#include "ui_vol.h"

vol::vol(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::vol)
{
    ui->setupUi(this);
    ui->rechercheVol->clearFocus();
    ui->contenuVol->setCurrentIndex(listeVol);
    ui->menuListe->setStyleSheet(styleFocus);
    ui->aeroportDepart->setText("Ivato");
    ui->modAeroportDepart->setText("Ivato");
    ui->dateDepart->setMinimumDate(QDate::currentDate());
    ui->modDateDepart->setMinimumDate(QDate::currentDate());
    acceuil::instance().ligneCompagnie = -1;
    acceuil::instance().ligneAvion = -1;
    QString nomAdministrateur = admin::instance().nomAdministrateur;
    ui->nomAdministrateur->setText(nomAdministrateur);
    afficherListe();
    infoListe();
}

vol::~vol()
{
    delete ui;
}

void vol::infoListe() {
    connect(ui->listeVol->selectionModel(),
            &QItemSelectionModel::currentRowChanged,
            this,
            [this](const QModelIndex &current, const QModelIndex &previous) {
                if (current.isValid()) {
                    QString numeroVol = ui->listeVol->model()->index(current.row(),2).data().toString();
                    QString immatriculation = ui->listeVol->model()->index(current.row(),6).data().toString();
                    QString passagerActuel;
                    QString passagerMax;
                    QSqlQuery query;
                    query.prepare("select count(passager_id) from reservation where numero_vol = ?");
                    query.addBindValue(numeroVol);
                    if(query.exec())
                    {
                        if(query.next())
                        {
                            passagerActuel = query.value(0).toString();
                            ui->passagerActuel->setText(passagerActuel);
                            query.prepare("select nombre_places from avion where immatriculation = ?");
                            query.addBindValue(immatriculation);
                            if(query.exec())
                            {
                                if(query.next())
                                {
                                    passagerMax = query.value(0).toString();
                                    ui->passagerMaximum->setText(passagerMax);
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

                    ui->btnSupprimer->setEnabled(true);
                    ui->btnModifier->setEnabled(true);
                }
            });
}

void vol::afficherListe()
{
    QString identifiantCompagnie =  acceuil::instance().compagnieAvion;
    QSqlDatabase db = connexion::connexionMysql();
    if(db.isOpen())
    {
        QSqlQueryModel *model1 = new QSqlQueryModel(this);
        model1->setQuery("select date_depart,heure_depart,numero_vol,aeroport_depart,aeroport_arrive,duree,avion_id,compagnie_id from vol", db);
        model1->setHeaderData(0, Qt::Horizontal, "Date de départ");
        model1->setHeaderData(1, Qt::Horizontal, "Heure de départ");
        model1->setHeaderData(2, Qt::Horizontal, "Numéro du vol");
        model1->setHeaderData(3, Qt::Horizontal, "Aéroport de départ");
        model1->setHeaderData(4, Qt::Horizontal, "Aéroport d'arriver");
        model1->setHeaderData(5, Qt::Horizontal, "Durer du vol");
        model1->setHeaderData(6, Qt::Horizontal, "Avion");
        model1->setHeaderData(7, Qt::Horizontal, "Compagnie");
        ui->listeVol->setModel(model1);
        ui->modListeVol->setModel(model1);
        ui->supListeVol->setModel(model1);

        QSqlQueryModel *model2 = new QSqlQueryModel(this);
        QString identifiantCompagnie = acceuil::instance().compagnieAvion;
        QString recherche = QString(R"(select identifiant,modele,nombre_places,compagnie_id from avion where compagnie_id = "%1")").arg(identifiantCompagnie);
        model2->setQuery(recherche, db);
        model2->setHeaderData(0, Qt::Horizontal, "Identifiant");
        model2->setHeaderData(1, Qt::Horizontal, "Modele");
        model2->setHeaderData(2, Qt::Horizontal, "Nombre de places");
        model2->setHeaderData(3, Qt::Horizontal, "Compagnie aérienne");
        ui->listeAvion->setModel(model2);
        ui->modListeAvion->setModel(model2);

        QSqlQueryModel *model3 = new QSqlQueryModel(this);
        model3->setQuery("select identifiant,nom,pays from compagnie_aerienne", db);
        model3->setHeaderData(0, Qt::Horizontal, "Identifiant");
        model3->setHeaderData(1, Qt::Horizontal, "Nom");
        model3->setHeaderData(2, Qt::Horizontal, "Pays");
        ui->listeCompagnie->setModel(model3);
        ui->modListeCompagnie->setModel(model3);
    }
    else
    {
        QMessageBox::critical(this,"Erreur","Impossible de se connecter à Mysql !");
        return;
    }
}


void vol::on_menuAcceuil_clicked()
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


void vol::on_menuReservation_clicked()
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


void vol::on_menuPassager_clicked()
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


void vol::on_menuVol_clicked()
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


void vol::on_menuAvion_clicked()
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


void vol::on_menuCompagnieAerienne_clicked()
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


void vol::on_menuQuitter_clicked()
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

void vol::on_menuCreer_clicked()
{
    ui->contenuVol->setCurrentIndex(creerVol);
    ui->numeroVol->setFocus();
}


void vol::on_menuModifier_clicked()
{
    ui->contenuVol->setCurrentIndex(modVol);
}


void vol::on_menuSupprimer_clicked()
{
    ui->contenuVol->setCurrentIndex(supVol);
}

void vol::on_menuListe_clicked()
{
    ui->contenuVol->setCurrentIndex(listeVol);
}

void vol::on_btnAnnuler0_clicked()
{
    QMessageBox message;
    message.setIcon(QMessageBox::Warning);
    message.setWindowTitle("Annuler la création d'un vol");
    message.setText("Voulez-vous vraiment annuler la création du vol ?");
    QPushButton *btnOui = message.addButton("Oui",QMessageBox::AcceptRole);
    QPushButton *btnNon = message.addButton("Non",QMessageBox::RejectRole);
    message.exec();
    if(message.clickedButton() == btnOui)
    {
        vol::on_menuVol_clicked();
    }
    else
    {
        return;
    }
}

void vol::on_btnSuivant0_clicked()
{
    if(ui->numeroVol->text().isEmpty())
    {
        QMessageBox::critical(this,"Champ vide","Veuillez saisir le numéro du vol !");
        ui->numeroVol->setFocus();
        return;
    }
    if(ui->numeroVol->text().length() != 6)
    {
        QMessageBox::critical(this,"Erreur","Le numero de vol doit contenir 03 chiffres !");
        ui->numeroVol->setCursorPosition(3);
        ui->numeroVol->setFocus();
        return;
    }

    QSqlQuery query;
    QString numeroVol = ui->numeroVol->text();
    query.prepare("select * from vol where numero_vol = ?");
    query.addBindValue(numeroVol);
    if(query.exec())
    {
        if(query.next())
        {
            QMessageBox::critical(this,"Erreur","Le numero de vol que vous avez saisi est déjà utiliser !");
            ui->numeroVol->setFocus();
            return;
        }
    }
    else
    {
        QMessageBox::critical(this,"Erreur","Impossible de se connecter à Mysql !");
        return;
    }

    if(ui->aeroportArriver->text().isEmpty())
    {
        QMessageBox::critical(this,"Champ vide","Veuillez saisir l'aéroport d'arriver !");
        ui->aeroportArriver->setFocus();
        return;
    }
    if(ui->aeroportArriver->text().isEmpty())
    {
        QMessageBox::critical(this,"Champ vide","Veuillez saisir l'aéroport d'arriver !");
        ui->aeroportArriver->setFocus();
        return;
    }

    ui->contenuVol->setCurrentIndex(1);
}


void vol::on_btnretour1_clicked()
{
    ui->contenuVol->setCurrentIndex(0);
}


void vol::on_btnAnnuler1_clicked()
{
    QMessageBox message;
    message.setIcon(QMessageBox::Warning);
    message.setWindowTitle("Annuler la création d'un vol");
    message.setText("Voulez-vous vraiment annuler la création du vol ?");
    QPushButton *btnOui = message.addButton("Oui",QMessageBox::AcceptRole);
    QPushButton *btnNon = message.addButton("Non",QMessageBox::RejectRole);
    message.exec();
    if(message.clickedButton() == btnOui)
    {
       vol::on_menuVol_clicked();
    }
    else
    {
        return;
    }
}


void vol::on_btnSuivant1_clicked()
{
    if(!(ui->listeCompagnie->currentIndex().isValid()))
    {
        QMessageBox::critical(this,"Erreur","Veuillez sélectionnez une compagnie aérienne !");
        return;
    }
    ui->contenuVol->setCurrentIndex(2);
}


void vol::on_btnretour2_clicked()
{
    ui->contenuVol->setCurrentIndex(1);
}


void vol::on_btnAnnuler2_clicked()
{
    QMessageBox message;
    message.setIcon(QMessageBox::Warning);
    message.setWindowTitle("Annuler la création d'un vol");
    message.setText("Voulez-vous vraiment annuler la création du vol ?");
    QPushButton *btnOui = message.addButton("Oui",QMessageBox::AcceptRole);
    QPushButton *btnNon = message.addButton("Non",QMessageBox::RejectRole);
    message.exec();
    if(message.clickedButton() == btnOui)
    {
        vol::on_menuVol_clicked();
    }
    else
    {
        return;
    }
}


void vol::on_btnSuivant2_clicked()
{
    if(!(ui->listeAvion->currentIndex().isValid()))
    {
        QMessageBox::critical(this,"Erreur","Veuillez sélectionnez un avion !");
        return;
    }

    int ligneCompagnie = ui->listeCompagnie->currentIndex().row();
    int ligneAvion = ui->listeAvion->currentIndex().row();
    QString aeroportDepart = ui->aeroportDepart->text();
    QString numeroVol = ui->numeroVol->text();
    QString aeroportArriver = ui->aeroportArriver->text();
    QString dateDepart = ui->dateDepart->text();
    QString heureDepart = ui->heureDepart->text();
    QString dureeVol = ui->duree->text();

    QString immatriculation = ui->listeAvion->model()->index(ligneAvion,0).data().toString();
    QString modele = ui->listeAvion->model()->index(ligneAvion,1).data().toString();
    QString place = ui->listeAvion->model()->index(ligneAvion,2).data().toString();
    ui->apImmatriculation->setText(immatriculation);
    ui->apModele->setText(modele);
    ui->apPlace->setText(place);

    QSqlDatabase db = connexion::connexionMysql();
    QString txtRechercheCompagnie = ui->rechercheCompagnie->text();
    QString rechercheCompagnie = QString(R"(select * from compagnie_aerienne where nom like "%%1%")").arg(txtRechercheCompagnie);
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery(rechercheCompagnie,db);
    model->setHeaderData(0, Qt::Horizontal, "Identifiant");
    model->setHeaderData(1, Qt::Horizontal, "Nom");
    model->setHeaderData(2, Qt::Horizontal, "Pays");
    ui->listeCompagnie->setModel(model);

    QString identifiant = ui->listeCompagnie->model()->index(ligneCompagnie,0).data().toString();
    QString nom = ui->listeCompagnie->model()->index(ligneCompagnie,1).data().toString();
    QString pays = ui->listeCompagnie->model()->index(ligneCompagnie,2).data().toString();

    ui->apAeroportDepart->setText(aeroportDepart);
    ui->apNumeroVol->setText(numeroVol);
    ui->apAeroportArriver->setText(aeroportArriver);
    ui->apDateDepart->setText(dateDepart);
    ui->apHeureDepart->setText(heureDepart);
    ui->apDuree->setText(dureeVol);
    ui->apIdentifiantCompagnie->setText(identifiant);
    ui->apNomCompagnie->setText(nom);
    ui->apPays->setText(pays);

    ui->contenuVol->setCurrentIndex(3);
}


void vol::on_btnretour3_clicked()
{
    ui->contenuVol->setCurrentIndex(2);
}


void vol::on_btnAnnuler3_clicked()
{
    QMessageBox message;
    message.setIcon(QMessageBox::Warning);
    message.setWindowTitle("Annuler la création d'un vol");
    message.setText("Voulez-vous vraiment annuler la création du vol ?");
    QPushButton *btnOui = message.addButton("Oui",QMessageBox::AcceptRole);
    QPushButton *btnNon = message.addButton("Non",QMessageBox::RejectRole);
    message.exec();
    if(message.clickedButton() == btnOui)
    {
        vol::on_menuVol_clicked();
    }
    else
    {
        return;
    }
}


void vol::on_btnEnregistrerVol_clicked()
{
    QString numeroVol = ui->numeroVol->text();
    QString aeroportArriver = ui->aeroportArriver->text();
    QDate dateDepart = ui->dateDepart->date();
    QTime heureDepart = ui->heureDepart->time();
    QString dureeVol = ui->duree->text();
    QString avion = ui->apImmatriculation->text();
    QString compagnie = ui->apIdentifiantCompagnie->text();

    QSqlQuery query;
    query.prepare("insert into vol (numero_vol,aeroport_arrive,date_depart,heure_depart,duree,avion_id,compagnie_id) values (?,?,?,?,?,?,?)");
    query.addBindValue(numeroVol);
    query.addBindValue(aeroportArriver);
    query.addBindValue(dateDepart);
    query.addBindValue(heureDepart);
    query.addBindValue(dureeVol);
    query.addBindValue(avion);
    query.addBindValue(compagnie);
    if(query.exec())
    {
        QString operation = "Création du vol numéro " + numeroVol;
        QString administrateur = ui->nomAdministrateur->text();
        query.prepare("insert into historique (operation,nom_utilisateur) values (?,?)");
        query.addBindValue(operation);
        query.addBindValue(administrateur);
        if(query.exec())
        {
            QMessageBox::information(this,"Création réussie","Le vol a été créer avec succès !");
            vol::on_menuVol_clicked();
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

void vol::on_btnAnnulerMod4_clicked()
{
    QMessageBox message;
    message.setIcon(QMessageBox::Warning);
    message.setWindowTitle("Annuler la modification du vol");
    message.setText("Les modifications que vous avez apporté à cette vol seront perdues.\nVoulez-vous continuer ?");
    QPushButton *btnOui = message.addButton("Oui",QMessageBox::AcceptRole);
    QPushButton *btnNon = message.addButton("Non",QMessageBox::RejectRole);
    message.exec();
    if(message.clickedButton() == btnOui)
    {
        vol::on_menuVol_clicked();
    }
    else
    {
        return;
    }
}

void vol::on_btnSuivant4_clicked()
{
    if(ui->modNumeroVol->text().isEmpty())
    {
        QMessageBox::critical(this,"Champ vide","Veuillez saisir le numéro du vol !");
        ui->modNumeroVol->setFocus();
        return;
    }
    if(ui->modAeroportArriver->text().isEmpty())
    {
        QMessageBox::critical(this,"Champ vide","Veuillez saisir l'aéroport d'arriver !");
        ui->modAeroportArriver->setFocus();
        return;
    }
    if(ui->modAeroportArriver->text().isEmpty())
    {
        QMessageBox::critical(this,"Champ vide","Veuillez saisir l'aéroport d'arriver !");
        ui->modAeroportArriver->setFocus();
        return;
    }

    QString numeroVol = acceuil::instance().numeroVol;

    if(ui->modNumeroVol->text() != numeroVol)
    {
        QSqlQuery query;
        query.prepare("select * from vol where numero_vol = ?");
        query.addBindValue(numeroVol);
        if(query.exec())
        {
            if(query.next())
            {
                QMessageBox::critical(this,"Erreur","Le numero de vol que vous avez saisi est déjà utiliser !");
                ui->modNumeroVol->setFocus();
                return;
            }
        }
    }

    ui->contenuVol->setCurrentIndex(5);
}


void vol::on_btnretour5_clicked()
{
    int ligne = ui->modListeCompagnie->currentIndex().row();
    QString modCompagnie = ui->modListeCompagnie->model()->index(ligne,0).data().toString();
    acceuil::instance().modCompagnie = modCompagnie;
    ui->contenuVol->setCurrentIndex(4);
}


void vol::on_btnAnnulerMod5_clicked()
{
    QMessageBox message;
    message.setIcon(QMessageBox::Warning);
    message.setWindowTitle("Annuler la modification du réservation");
    message.setText("Les modifications que vous avez apporté à cette réservation seront perdues.\nVoulez-vous continuer ?");
    QPushButton *btnOui = message.addButton("Oui",QMessageBox::AcceptRole);
    QPushButton *btnNon = message.addButton("Non",QMessageBox::RejectRole);
    message.exec();
    if(message.clickedButton() == btnOui)
    {
        vol::on_menuVol_clicked();
    }
    else
    {
        return;
    }
}


void vol::on_btnSuivant5_clicked()
{
    int ligne = ui->modListeCompagnie->currentIndex().row();
    QString modCompagnie = ui->modListeCompagnie->model()->index(ligne,0).data().toString();
    acceuil::instance().modCompagnie = modCompagnie;
    if(!(ui->modListeCompagnie->currentIndex().isValid()))
    {
        QMessageBox::critical(this,"Erreur","Veuillez sélectionnez une compagnie aérienne !");
        return;
    }

    ui->contenuVol->setCurrentIndex(6);
}


void vol::on_btnretour6_clicked()
{
    int ligne = ui->modListeAvion->currentIndex().row();
    QString modAvion = ui->modListeAvion->model()->index(ligne,0).data().toString();
    acceuil::instance().modAvion = modAvion;
    ui->contenuVol->setCurrentIndex(5);
}


void vol::on_btnAnnulerMod6_clicked()
{
    QMessageBox message;
    message.setIcon(QMessageBox::Warning);
    message.setWindowTitle("Annuler la modification du réservation");
    message.setText("Les modifications que vous avez apporté à cette réservation seront perdues.\nVoulez-vous continuer ?");
    QPushButton *btnOui = message.addButton("Oui",QMessageBox::AcceptRole);
    QPushButton *btnNon = message.addButton("Non",QMessageBox::RejectRole);
    message.exec();
    if(message.clickedButton() == btnOui)
    {
        vol::on_menuVol_clicked();
    }
    else
    {
        return;
    }
}


void vol::on_btnSuivant6_clicked()
{
    if(!(ui->modListeAvion->currentIndex().isValid()))
    {
        QMessageBox::critical(this,"Erreur","Veuillez sélectionnez un avion !");
        return;
    }

    int ligneAvion = ui->modListeAvion->currentIndex().row();
    QString aeroportDepart = ui->modAeroportDepart->text();
    QString numeroVol = ui->modNumeroVol->text();
    QString aeroportArriver = ui->modAeroportArriver->text();
    QString dateDepart = ui->modDateDepart->text();
    QString heureDepart = ui->modHeureDepart->text();
    QString dureeVol = ui->modDuree->text();

    QString immatriculation = ui->modListeAvion->model()->index(ligneAvion,0).data().toString();
    QString modele = ui->modListeAvion->model()->index(ligneAvion,1).data().toString();
    QString place = ui->modListeAvion->model()->index(ligneAvion,2).data().toString();
    ui->apModImmatriculation->setText(immatriculation);
    ui->apModModele->setText(modele);
    ui->apModPlace->setText(place);

    QSqlDatabase db = connexion::connexionMysql();
    QString modRechercheCompagnie = ui->modRechercheCompagnie->text();
    QString rechercheCompagnie = QString(R"(select * from compagnie_aerienne where nom like "%%1%")").arg(modRechercheCompagnie);
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery(rechercheCompagnie,db);
    model->setHeaderData(0, Qt::Horizontal, "Identifiant");
    model->setHeaderData(1, Qt::Horizontal, "Nom");
    model->setHeaderData(2, Qt::Horizontal, "Pays");
    ui->modListeCompagnie->setModel(model);

    int i;
    int ligneCompagnie;
    QString identifiant = acceuil::instance().modCompagnie;
    for(i=0; i<ui->modListeCompagnie->model()->rowCount(); i++)
    {
        if(ui->modListeCompagnie->model()->index(i,0).data().toString() == identifiant)
        {
            ligneCompagnie = i;
        }
    }
    QString nom = ui->modListeCompagnie->model()->index(ligneCompagnie,1).data().toString();
    QString pays = ui->modListeCompagnie->model()->index(ligneCompagnie,2).data().toString();

    ui->apModAeroportDepart->setText(aeroportDepart);
    ui->apModNumeroVol->setText(numeroVol);
    ui->apModAeroportArriver->setText(aeroportArriver);
    ui->apModDateDepart->setText(dateDepart);
    ui->apModHeureDepart->setText(heureDepart);
    ui->apModDureeVol->setText(dureeVol);
    ui->apModIdentifiantCompagnie->setText(identifiant);
    ui->apModNomCompagnie->setText(nom);
    ui->apModPays->setText(pays);

    acceuil::instance().modAvion = immatriculation;
    ui->contenuVol->setCurrentIndex(7);
}


void vol::on_btnretour7_clicked()
{
    ui->contenuVol->setCurrentIndex(6);
}


void vol::on_btnAnnulerMod7_clicked()
{
    QMessageBox message;
    message.setIcon(QMessageBox::Warning);
    message.setWindowTitle("Annuler la modification du réservation");
    message.setText("Les modifications que vous avez apporté à cette réservation seront perdues.\nVoulez-vous continuer ?");
    QPushButton *btnOui = message.addButton("Oui",QMessageBox::AcceptRole);
    QPushButton *btnNon = message.addButton("Non",QMessageBox::RejectRole);
    message.exec();
    if(message.clickedButton() == btnOui)
    {
        vol::on_menuVol_clicked();
    }
    else
    {
        return;
    }
}


void vol::on_btnEnregistrerMod_clicked()
{
    QString numeroVol = acceuil::instance().numeroVol;
    QString modNumeroVol = ui->modNumeroVol->text();
    QString modAeroportArriver = ui->modAeroportArriver->text();
    QDate modDateDepart = ui->modDateDepart->date();
    QTime modHeureDepart = ui->modHeureDepart->time();
    QString modDuree = ui->modDuree->text();
    QString modAvion = ui->apModImmatriculation->text();
    QString modCompagnie = ui->apModIdentifiantCompagnie->text();

    QSqlQuery query;
    query.prepare("update vol set numero_vol = ?, aeroport_arrive = ?, date_depart = ?, heure_depart = ?, duree = ?, avion_id = ?, compagnie_id = ? where numero_vol = ?");
    query.addBindValue(modNumeroVol);
    query.addBindValue(modAeroportArriver);
    query.addBindValue(modDateDepart);
    query.addBindValue(modHeureDepart);
    query.addBindValue(modDuree);
    query.addBindValue(modAvion);
    query.addBindValue(modCompagnie);
    query.addBindValue(numeroVol);

    if(query.exec())
    {
        QString operation = "Modification des informations du vol numéro " + numeroVol;
        QString administrateur = ui->nomAdministrateur->text();
        query.prepare("insert into historique (operation,nom_utilisateur) values (?,?)");
        query.addBindValue(operation);
        query.addBindValue(administrateur);
        if(query.exec())
        {
            QMessageBox::information(this,"Modification réussie","Les informations du vol ont été modifier avec succés !");
            vol::on_menuVol_clicked();
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

void vol::on_btnSupprimer_clicked()
{
    if(!(ui->listeVol->currentIndex().isValid()))
    {
        QMessageBox::critical(this,"Erreur","Veuillez sélectionnez le vol que vous voulez supprimer !");
        return;
    }

    QMessageBox message;
    message.setIcon(QMessageBox::Warning);
    message.setWindowTitle("Supprimer un vol");
    message.setText("Voulez-vous vraiment supprimer ce vol ?");
    QPushButton *btnOui = message.addButton("Oui",QMessageBox::AcceptRole);
    QPushButton *btnNon = message.addButton("Non",QMessageBox::RejectRole);
    message.exec();
    if(message.clickedButton() == btnOui)
    {
        int ligne = ui->listeVol->currentIndex().row();
        QString numeroVol = ui->listeVol->model()->index(ligne,2).data().toString();

        QSqlQuery query;
        query.prepare("delete from vol where numero_vol = ?");
        query.addBindValue(numeroVol);
        if(query.exec())
        {
            QString operation = "Suppression du vol numéro " + numeroVol;
            QString administrateur = ui->nomAdministrateur->text();
            query.prepare("insert into historique (operation,nom_utilisateur) values (?,?)");
            query.addBindValue(operation);
            query.addBindValue(administrateur);
            if(query.exec())
            {
                afficherListe();
                QMessageBox::information(this,"Suppression réussie","Le vol a été supprimer avec succès !");
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


void vol::on_btnModifier_clicked()
{
    if(!(ui->listeVol->currentIndex().isValid()))
    {
        QMessageBox::critical(this,"Erreur","Veuillez sélectionnez le vol que vous voulez modifier !");
        return;
    }

    int ligne = ui->listeVol->currentIndex().row();

    QDate dateDepart = ui->listeVol->model()->index(ligne,0).data().toDate();
    QTime heureDepart = ui->listeVol->model()->index(ligne,1).data().toTime();
    QString numeroVol = ui->listeVol->model()->index(ligne,2).data().toString();
    acceuil::instance().numeroVol = numeroVol;

    QString aeroportDepart = ui->listeVol->model()->index(ligne,3).data().toString();
    QString aeroportArriver = ui->listeVol->model()->index(ligne,4).data().toString();
    QString dureeVol = ui->listeVol->model()->index(ligne,5).data().toString();
    QString immatriculationAvion = ui->listeVol->model()->index(ligne,6).data().toString();
    QString identifiantCompagnie = ui->listeVol->model()->index(ligne,7).data().toString();
    acceuil::instance().compagnieAvion = identifiantCompagnie;

    acceuil::instance().modCompagnie = identifiantCompagnie;
    acceuil::instance().modAvion = immatriculationAvion;
    QTime duree;
    int heure = dureeVol.left(2).toInt();
    int min = dureeVol.mid(3,2).toInt();
    duree.setHMS(0,min,heure,0);

    ui->modAeroportDepart->setText(aeroportDepart);
    ui->modNumeroVol->setText(numeroVol);
    ui->modAeroportArriver->setText(aeroportArriver);
    ui->modDateDepart->setDate(dateDepart);
    ui->modHeureDepart->setTime(heureDepart);
    ui->modDuree->setTime(duree);

    ui->contenuVol->setCurrentIndex(modVolForm);
}


void vol::on_btnInserer_clicked()
{
    ui->contenuVol->setCurrentIndex(creerVol);
}


void vol::on_btnMod_clicked()
{
    if(!(ui->modListeVol->currentIndex().isValid()))
    {
        QMessageBox::critical(this,"Erreur","Veuillez sélectionnez le vol que vous voulez modifier !");
        return;
    }

    int ligne = ui->modListeVol->currentIndex().row();

    QDate dateDepart = ui->modListeVol->model()->index(ligne,0).data().toDate();
    QTime heureDepart = ui->modListeVol->model()->index(ligne,1).data().toTime();
    QString numeroVol = ui->modListeVol->model()->index(ligne,2).data().toString();
    acceuil::instance().numeroVol = numeroVol;
    QString aeroportDepart = ui->modListeVol->model()->index(ligne,3).data().toString();
    QString aeroportArriver = ui->modListeVol->model()->index(ligne,4).data().toString();
    QString dureeVol = ui->modListeVol->model()->index(ligne,5).data().toString();
    QString immatriculationAvion = ui->modListeVol->model()->index(ligne,6).data().toString();
    QString identifiantCompagnie = ui->modListeVol->model()->index(ligne,7).data().toString();
    acceuil::instance().compagnieAvion = identifiantCompagnie;

    acceuil::instance().modCompagnie = identifiantCompagnie;
    acceuil::instance().modAvion = immatriculationAvion;
    QTime duree;
    int heure = dureeVol.left(2).toInt();
    int min = dureeVol.mid(3,2).toInt();
    duree.setHMS(0,min,heure,0);

    ui->modAeroportDepart->setText(aeroportDepart);
    ui->modNumeroVol->setText(numeroVol);
    ui->modAeroportArriver->setText(aeroportArriver);
    ui->modDateDepart->setDate(dateDepart);
    ui->modHeureDepart->setTime(heureDepart);
    ui->modDuree->setTime(duree);

    ui->contenuVol->setCurrentIndex(modVolForm);
}

void vol::on_btnSup_clicked()
{
    if(!(ui->supListeVol->currentIndex().isValid()))
    {
        QMessageBox::critical(this,"Erreur","Veuillez sélectionnez le vol que vous voulez supprimer !");
        return;
    }

    QMessageBox message;
    message.setIcon(QMessageBox::Warning);
    message.setWindowTitle("Supprimer un vol");
    message.setText("Voulez-vous vraiment supprimer ce vol ?");
    QPushButton *btnOui = message.addButton("Oui",QMessageBox::AcceptRole);
    QPushButton *btnNon = message.addButton("Non",QMessageBox::RejectRole);
    message.exec();
    if(message.clickedButton() == btnOui)
    {
        int ligne = ui->supListeVol->currentIndex().row();
        QString numeroVol = ui->supListeVol->model()->index(ligne,2).data().toString();

        QSqlQuery query;
        query.prepare("delete from vol where numero_vol = ?");
        query.addBindValue(numeroVol);
        if(query.exec())
        {
            QString operation = "Insértion de l'avion " + numeroVol;
            QString administrateur = ui->nomAdministrateur->text();
            query.prepare("insert into historique (operation,nom_utilisateur) values (?,?)");
            query.addBindValue(operation);
            query.addBindValue(administrateur);
            if(query.exec())
            {
                afficherListe();
                QMessageBox::information(this,"Suppression réussie","Le vol a été supprimer avec succès !");
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

void vol::on_contenuVol_currentChanged(int arg1)
{
    ui->rechercheVol->clear();
    ui->modRechercheVol->clear();
    ui->supRechercheVol->clear();
    ui->passagerActuel->clear();
    ui->passagerMaximum->clear();
    ui->btnModifier->setEnabled(false);
    ui->btnSupprimer->setEnabled(false);
    ui->btnMod->setEnabled(false);
    ui->btnSup->setEnabled(false);

    ui->menuCreer->setStyleSheet(style);
    ui->menuModifier->setStyleSheet(style);
    ui->menuSupprimer->setStyleSheet(style);
    ui->menuListe->setStyleSheet(style);

    if(arg1 == 0 || arg1 == 1 || arg1 == 2 || arg1 == 3)
    {
        ui->rechercheCompagnie->clearFocus();
        ui->rechercheAvion->clearFocus();

        QSqlDatabase db = connexion::connexionMysql();
        QString txtRechercheCompagnie = ui->rechercheCompagnie->text();
        QString rechercheCompagnie = QString(R"(select * from compagnie_aerienne where nom like "%%1%")").arg(txtRechercheCompagnie);
        QSqlQueryModel *model = new QSqlQueryModel(this);
        model->setQuery(rechercheCompagnie,db);
        model->setHeaderData(0, Qt::Horizontal, "Identifiant");
        model->setHeaderData(1, Qt::Horizontal, "Nom");
        model->setHeaderData(2, Qt::Horizontal, "Pays");
        ui->listeCompagnie->setModel(model);

        QString identifiantCompagnie = acceuil::instance().compagnieAvion;
        QString txtRechercheAvion = ui->rechercheAvion->text();
        QString rechercheAvion = QString(R"(select * from avion where immatriculation like "%%1%" and compagnie_id = "%2")").arg(txtRechercheAvion,identifiantCompagnie);
        QSqlQueryModel *model1 = new QSqlQueryModel(this);
        model1->setQuery(rechercheAvion,db);
        model1->setHeaderData(0, Qt::Horizontal, "Immatriculation");
        model1->setHeaderData(1, Qt::Horizontal, "Modèle");
        model1->setHeaderData(2, Qt::Horizontal, "Nombre de places");
        model1->setHeaderData(3, Qt::Horizontal, "Compagnie aérienne");

        ui->listeAvion->setModel(model1);

        int ligneAvion = acceuil::instance().ligneAvion;
        ui->listeAvion->selectRow(ligneAvion);
        int ligneCompagnie = acceuil::instance().ligneCompagnie;
        ui->listeCompagnie->selectRow(ligneCompagnie);
        ui->menuCreer->setStyleSheet(styleFocus);
        ui->numeroVol->setFocus();
    }

    if(arg1 == 4 || arg1 == 5 || arg1 == 6 || arg1 == 7)
    {
        ui->modRechercheAvion->clearFocus();
        ui->modRechercheCompagnie->clearFocus();
        QSqlDatabase db = connexion::connexionMysql();
        QString modRechercheCompagnie = ui->modRechercheCompagnie->text();
        QString rechercheCompagnie = QString(R"(select * from compagnie_aerienne where nom like "%%1%")").arg(modRechercheCompagnie);
        QSqlQueryModel *model = new QSqlQueryModel(this);
        model->setQuery(rechercheCompagnie,db);
        model->setHeaderData(0, Qt::Horizontal, "Identifiant");
        model->setHeaderData(1, Qt::Horizontal, "Nom");
        model->setHeaderData(2, Qt::Horizontal, "Pays");
        ui->modListeCompagnie->setModel(model);

        QString modRechercheAvion = ui->modRechercheAvion->text();
        QString identifiantCompagnie = acceuil::instance().compagnieAvion;
        QString rechercheAvion = QString(R"(select * from avion where immatriculation like "%%1%" and compagnie_id = "%2")").arg(modRechercheAvion,identifiantCompagnie);
        QSqlQueryModel *model1 = new QSqlQueryModel(this);
        model1->setQuery(rechercheAvion,db);
        model1->setHeaderData(0, Qt::Horizontal, "Immatriculation");
        model1->setHeaderData(1, Qt::Horizontal, "Modèle");
        model1->setHeaderData(2, Qt::Horizontal, "Nombre de places");
        model1->setHeaderData(3, Qt::Horizontal, "Compagnie aérienne");
        ui->modListeAvion->setModel(model1);

        ui->menuModifier->setStyleSheet(styleFocus);
        ui->modNumeroVol->setFocus();
    }

    if(arg1 == modVol)
    {
        afficherListe();
        ui->menuModifier->setStyleSheet(styleFocus);
        ui->modRechercheVol->clearFocus();
    }

    if(arg1 == supVol)
    {
        afficherListe();
        ui->menuSupprimer->setStyleSheet(styleFocus);
        ui->supRechercheVol->clearFocus();
    }

    if(arg1 == listeVol)
    {
        afficherListe();
        ui->menuListe->setStyleSheet(styleFocus);
        ui->rechercheVol->clearFocus();
    }
    if(arg1 == modVol || arg1 == supVol || arg1 == listeVol)
    {
        ui->numeroVol->clear();
        ui->aeroportArriver->clear();
        ui->dateDepart->setDate(ui->dateDepart->minimumDate());
        ui->heureDepart->setTime(ui->heureDepart->minimumTime());
        ui->duree->setTime(ui->duree->minimumTime());
    }

    int i;
    int ligneAvion;
    QString immatriculation = acceuil::instance().modAvion;

    for(i=0; i<ui->modListeAvion->model()->rowCount(); i++)
    {
        if(ui->modListeAvion->model()->index(i,0).data().toString() == immatriculation)
        {
            ligneAvion = i;
        }
    }

    int ligneCompagnie;
    QString identifiant = acceuil::instance().modCompagnie;
    for(i=0; i<ui->modListeCompagnie->model()->rowCount(); i++)
    {
        if(ui->modListeCompagnie->model()->index(i,0).data().toString() == identifiant)
        {
            ligneCompagnie = i;
        }
    }

    if(arg1 == 5)
    {
        ui->modListeCompagnie->selectRow(ligneCompagnie);
    }

    if(arg1 == 6)
    {
        ui->modListeAvion->selectRow(ligneAvion);
    }
}

void vol::on_numeroVol_editingFinished()
{
    ui->aeroportArriver->setFocus();
}

void vol::on_aeroportArriver_editingFinished()
{
    ui->dateDepart->setFocus();
}

void vol::on_dateDepart_editingFinished()
{
    ui->heureDepart->setFocus();
}


void vol::on_heureDepart_editingFinished()
{
    ui->duree->setFocus();
}


void vol::on_duree_editingFinished()
{
    ui->duree->clearFocus();
}

void vol::on_modNumeroVol_editingFinished()
{
    ui->modAeroportArriver->setFocus();
    ui->btnSuivant4->setEnabled(true);
}

void vol::on_modAeroportArriver_editingFinished()
{
    ui->modDateDepart->setFocus();
    ui->btnSuivant4->setEnabled(true);
}

void vol::on_modDateDepart_editingFinished()
{
    ui->modHeureDepart->setFocus();
    ui->btnSuivant4->setEnabled(true);
}

void vol::on_modHeureDepart_editingFinished()
{
    ui->modDuree->setFocus();
    ui->btnSuivant4->setEnabled(true);
}

void vol::on_modDuree_editingFinished()
{
    ui->btnSuivant4->setEnabled(true);
}

void vol::on_rechercheCompagnie_textChanged(const QString &arg1)
{
    QSqlDatabase db = connexion::connexionMysql();
    QString recherche = QString(R"(select * from compagnie_aerienne where nom like "%%1%")").arg(arg1);
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery(recherche,db);
    model->setHeaderData(0, Qt::Horizontal, "Identifiant");
    model->setHeaderData(1, Qt::Horizontal, "Nom");
    model->setHeaderData(2, Qt::Horizontal, "Pays");
    ui->listeCompagnie->setModel(model);
    ui->btnSuivant1->setEnabled(false);
}

void vol::on_modRechercheCompagnie_textChanged(const QString &arg1)
{
    QSqlDatabase db = connexion::connexionMysql();
    QString recherche = QString(R"(select * from compagnie_aerienne where nom like "%%1%")").arg(arg1);
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery(recherche,db);
    model->setHeaderData(0, Qt::Horizontal, "Identifiant");
    model->setHeaderData(1, Qt::Horizontal, "Nom");
    model->setHeaderData(2, Qt::Horizontal, "Pays");
    ui->modListeCompagnie->setModel(model);
    ui->btnSuivant5->setEnabled(false);
}

void vol::on_rechercheAvion_textChanged(const QString &arg1)
{
    QSqlDatabase db = connexion::connexionMysql();
    QString identifiantCompagnie = acceuil::instance().compagnieAvion;
    QString recherche = QString(R"(select * from avion where immatriculation like "%%1%" and compagnie_id = "%2")").arg(arg1,identifiantCompagnie);
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery(recherche,db);
    model->setHeaderData(0, Qt::Horizontal, "Immatriculation");
    model->setHeaderData(1, Qt::Horizontal, "Modèle");
    model->setHeaderData(2, Qt::Horizontal, "Nombre de places");
    ui->listeAvion->setModel(model);
    ui->btnSuivant2->setEnabled(false);
}

void vol::on_modRechercheAvion_textChanged(const QString &arg1)
{
    QSqlDatabase db = connexion::connexionMysql();
    QString identifiantCompagnie = acceuil::instance().compagnieAvion;
    QString recherche = QString(R"(select * from avion where immatriculation like "%%1%" and compagnie_id = "%2")").arg(arg1,identifiantCompagnie);
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery(recherche,db);
    model->setHeaderData(0, Qt::Horizontal, "Immatriculation");
    model->setHeaderData(1, Qt::Horizontal, "Modèle");
    model->setHeaderData(2, Qt::Horizontal, "Nombre de places");
    ui->modListeAvion->setModel(model);
    ui->btnSuivant6->setEnabled(false);
}

void vol::on_rechercheVol_textChanged(const QString &arg1)
{
    QSqlDatabase db = connexion::connexionMysql();
    QString recherche = QString(R"(select date_depart,heure_depart,numero_vol,aeroport_depart,aeroport_arrive,duree,avion_id,compagnie_id from vol where aeroport_arrive like "%%1%")").arg(arg1);
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery(recherche,db);
    model->setHeaderData(0, Qt::Horizontal, "Date de départ");
    model->setHeaderData(1, Qt::Horizontal, "Heure de départ");
    model->setHeaderData(2, Qt::Horizontal, "Numéro du vol");
    model->setHeaderData(3, Qt::Horizontal, "Aéroport de départ");
    model->setHeaderData(4, Qt::Horizontal, "Aéroport d'arriver");
    model->setHeaderData(5, Qt::Horizontal, "Durer du vol");
    model->setHeaderData(6, Qt::Horizontal, "Avion");
    model->setHeaderData(7, Qt::Horizontal, "Compagnie");
    ui->listeVol->setModel(model);
    ui->btnModifier->setEnabled(false);
    ui->btnSupprimer->setEnabled(false);
    ui->passagerActuel->clear();
    ui->passagerMaximum->clear();
}

void vol::on_modRechercheVol_textChanged(const QString &arg1)
{
    QSqlDatabase db = connexion::connexionMysql();
    QString recherche = QString(R"(select date_depart,heure_depart,numero_vol,aeroport_depart,aeroport_arrive,duree,avion_id,compagnie_id from vol where aeroport_arrive like "%%1%")").arg(arg1);
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery(recherche,db);
    model->setHeaderData(0, Qt::Horizontal, "Date de départ");
    model->setHeaderData(1, Qt::Horizontal, "Heure de départ");
    model->setHeaderData(2, Qt::Horizontal, "Numéro du vol");
    model->setHeaderData(3, Qt::Horizontal, "Aéroport de départ");
    model->setHeaderData(4, Qt::Horizontal, "Aéroport d'arriver");
    model->setHeaderData(5, Qt::Horizontal, "Durer du vol");
    model->setHeaderData(6, Qt::Horizontal, "Avion");
    model->setHeaderData(7, Qt::Horizontal, "Compagnie");
    ui->modListeVol->setModel(model);
    ui->btnMod->setEnabled(false);
}

void vol::on_supRechercheVol_textChanged(const QString &arg1)
{
    QSqlDatabase db = connexion::connexionMysql();
    QString recherche = QString(R"(select date_depart,heure_depart,numero_vol,aeroport_depart,aeroport_arrive,duree,avion_id,compagnie_id from vol where aeroport_arrive like "%%1%")").arg(arg1);
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery(recherche,db);
    model->setHeaderData(0, Qt::Horizontal, "Date de départ");
    model->setHeaderData(1, Qt::Horizontal, "Heure de départ");
    model->setHeaderData(2, Qt::Horizontal, "Numéro du vol");
    model->setHeaderData(3, Qt::Horizontal, "Aéroport de départ");
    model->setHeaderData(4, Qt::Horizontal, "Aéroport d'arriver");
    model->setHeaderData(5, Qt::Horizontal, "Durer du vol");
    model->setHeaderData(6, Qt::Horizontal, "Avion");
    model->setHeaderData(7, Qt::Horizontal, "Compagnie");
    ui->supListeVol->setModel(model);
    ui->btnSup->setEnabled(false);
}

void vol::on_listeVol_clicked(const QModelIndex &index)
{
}

void vol::on_modListeVol_clicked(const QModelIndex &index)
{
        ui->btnMod->setEnabled(true);
}

void vol::on_supListeVol_clicked(const QModelIndex &index)
{
        ui->btnSup->setEnabled(true);
}

void vol::on_listeCompagnie_clicked(const QModelIndex &index)
{
    int ligne = ui->listeCompagnie->currentIndex().row();
    QString identifiantCompagnie = ui->listeCompagnie->model()->index(ligne,0).data().toString();
    acceuil::instance().compagnieAvion = identifiantCompagnie;
    acceuil::instance().ligneCompagnie = index.row();
    ui->btnSuivant1->setEnabled(true);
}

void vol::on_listeAvion_clicked(const QModelIndex &index)
{
    acceuil::instance().ligneAvion = index.row();
    ui->btnSuivant2->setEnabled(true);
}

void vol::on_modListeCompagnie_clicked(const QModelIndex &index)
{
    int ligne = ui->modListeCompagnie->currentIndex().row();
    QString identifiantCompagnie = ui->modListeCompagnie->model()->index(ligne,0).data().toString();
    acceuil::instance().compagnieAvion = identifiantCompagnie;
    ui->btnSuivant5->setEnabled(true);
}

void vol::on_modListeAvion_clicked(const QModelIndex &index)
{
    ui->btnSuivant6->setEnabled(true);
}

void vol::on_modDateDepart_userDateChanged(const QDate &date)
{
}

void vol::on_modAeroportArriver_textEdited(const QString &arg1)
{
    if(ui->modNumeroVol->text().length() == 6 && !ui->modAeroportArriver->text().isEmpty())
    {
        ui->btnSuivant4->setEnabled(true);
    }
}


void vol::on_numeroVol_textChanged(const QString &arg1)
{
    if(ui->numeroVol->text().length() == 6 && !ui->aeroportArriver->text().isEmpty())
    {
        ui->btnSuivant0->setEnabled(true);
    }
}


void vol::on_modNumeroVol_textEdited(const QString &arg1)
{
    if(ui->modNumeroVol->text().length() == 6 && !ui->modAeroportArriver->text().isEmpty())
    {
        ui->btnSuivant4->setEnabled(true);
    }
}


void vol::on_aeroportArriver_textChanged(const QString &arg1)
{
    if(ui->numeroVol->text().length() == 6 && !ui->aeroportArriver->text().isEmpty())
    {
        ui->btnSuivant0->setEnabled(true);
    }
}


void vol::on_menuSeDeconnecter_clicked()
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

