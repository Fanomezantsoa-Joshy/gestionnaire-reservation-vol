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

#include "ui_reservation.h"

reservation::reservation(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::reservation)
{
    ui->setupUi(this);
    ui->rechercheDate->clearFocus();
    ui->contenuReservation->setCurrentIndex(listeParDate);
    acceuil::instance().ligneVol = -1;
    ui->dateReservation->setDate(QDate::currentDate());
    ui->modDateReservation->setDate(QDate::currentDate());
    QString nomAdministrateur = admin::instance().nomAdministrateur;
    ui->nomAdministrateur->setText(nomAdministrateur);
    ui->naissance->setMaximumDate(QDate::currentDate());
    ui->modNaissance->setMaximumDate(QDate::currentDate());
    afficherListe();
}

reservation::~reservation()
{
    delete ui;
}

void reservation::afficherListe()
{
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

        QSqlQueryModel *model2 = new QSqlQueryModel(this);
        model2->setQuery("select immatriculation,modele,nombre_places from avion", db);
        model2->setHeaderData(0, Qt::Horizontal, "Immatriculation");
        model2->setHeaderData(1, Qt::Horizontal, "Modèle");
        model2->setHeaderData(2, Qt::Horizontal, "Nombre de places");
        ui->listeAvion->setModel(model2);

        QSqlQueryModel *model3 = new QSqlQueryModel(this);
        model3->setQuery("select identifiant,nom,pays from compagnie_aerienne", db);
        model3->setHeaderData(0, Qt::Horizontal, "Identifiant");
        model3->setHeaderData(1, Qt::Horizontal, "Nom");
        model3->setHeaderData(2, Qt::Horizontal, "Pays");
        ui->listeCompagnie->setModel(model3);

        QSqlQueryModel *model4 = new QSqlQueryModel(this);
        model4->setQuery("select identifiant,nom,prenoms,date_naissance,numero_passeport from passager", db);
        model4->setHeaderData(0, Qt::Horizontal, "Identifiant");
        model4->setHeaderData(1, Qt::Horizontal, "Nom");
        model4->setHeaderData(2, Qt::Horizontal, "Prenoms");
        model4->setHeaderData(3, Qt::Horizontal, "Date de naissance");
        model4->setHeaderData(4, Qt::Horizontal, "Numero de passeport");
        ui->listePassager->setModel(model4);


        QSqlQueryModel *model5 = new QSqlQueryModel(this);
        model5->setQuery("select vol.avion_id,reservation.passager_id,reservation.numero_vol,reservation.classe,reservation.numero_reservation from reservation inner join vol on reservation.numero_vol = vol.numero_vol", db);
        model5->setHeaderData(0, Qt::Horizontal, "Immatriculation de l'avion");
        model5->setHeaderData(1, Qt::Horizontal, "Passager");
        model5->setHeaderData(2, Qt::Horizontal, "Vol");
        model5->setHeaderData(3, Qt::Horizontal, "Classe");
        model5->setHeaderData(4, Qt::Horizontal, "Numero de réservation");
        ui->listeReservationParAvion->setModel(model5);

        QSqlQueryModel *model6 = new QSqlQueryModel(this);
        model6->setQuery("select date_reservation,passager_id,numero_vol,classe,numero_reservation from reservation", db);
        model6->setHeaderData(0, Qt::Horizontal, "Date de réservation");
        model6->setHeaderData(1, Qt::Horizontal, "Passager");
        model6->setHeaderData(2, Qt::Horizontal, "Vol");
        model6->setHeaderData(3, Qt::Horizontal, "Classe");
        model6->setHeaderData(4, Qt::Horizontal, "Numero de réservation");
        ui->listeReservationParDate->setModel(model6);
        ui->modListeDate->setModel(model6);
        ui->supListeDate->setModel(model6);
    }
    else
    {
        QMessageBox::critical(this,"Erreur","Impossible de se connecter à Mysql !");
        return;
    }
}


void reservation::on_menuAcceuil_clicked()
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


void reservation::on_menuReservation_clicked()
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


void reservation::on_menuPassager_clicked()
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


void reservation::on_menuVol_clicked()
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


void reservation::on_menuAvion_clicked()
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


void reservation::on_menuCompagnieAerienne_clicked()
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


void reservation::on_menuQuitter_clicked()
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

void reservation::on_menuCreer_clicked()
{
    afficherListe();
    ui->contenuReservation->setCurrentIndex(creerReservation);
    ui->nomPassager->setFocus();
}


void reservation::on_menuModifier_clicked()
{
    afficherListe();
    ui->contenuReservation->setCurrentIndex(modReservation);
}


void reservation::on_menuSupprimer_clicked()
{
    afficherListe();
    ui->contenuReservation->setCurrentIndex(supReservation);
}


void reservation::on_menuListeAvion_clicked()
{
    afficherListe();
    ui->contenuReservation->setCurrentIndex(listeParAvion);
}


void reservation::on_menuParDate_clicked()
{
    afficherListe();
    ui->contenuReservation->setCurrentIndex(listeParDate);
}

void reservation::on_btnAnnulerReservation0_clicked()
{
    QMessageBox message;
    message.setIcon(QMessageBox::Warning);
    message.setWindowTitle("Annuler la création d'une réservation");
    message.setText("Voulez-vous vraiment annuler la création du réservation ?");
    QPushButton *btnOui = message.addButton("Oui",QMessageBox::AcceptRole);
    QPushButton *btnNon = message.addButton("Non",QMessageBox::RejectRole);
    message.exec();
    if(message.clickedButton() == btnOui)
    {
        reservation::on_menuReservation_clicked();
    }
    else
    {
        return;
    }
}


void reservation::on_btnSuivant0_clicked()
{
    if(ui->nomPassager->text().isEmpty())
    {
        QMessageBox::critical(this,"Champ vide","Veuillez saisir le nom du passager !");
        ui->nomPassager->setFocus();
        return;
    }
    if(ui->prenoms->text().isEmpty())
    {
        QMessageBox::critical(this,"Champ vide","Veuillez saisir le prénoms du passager !");
        ui->prenoms->setFocus();
        return;
    }
    if(ui->passeport->text().isEmpty())
    {
        QMessageBox::critical(this,"Champ vide","Veuillez saisir le numéro de passeport du passager !");
        ui->passeport->setFocus();
        return;
    }

    QSqlQuery query;
    QString passeport = ui->passeport->text();
    query.prepare("select numero_passeport from passager where numero_passeport = ?");
    query.addBindValue(passeport);
    if(query.exec())
    {
        if(query.next())
        {
            QMessageBox::critical(this,"Erreur","Le numéro de passeport que vous avez saisie est déjà utiliser !");
            ui->passeport->setFocus();
            return;
        }
    }
    ui->contenuReservation->setCurrentIndex(1);
}


void reservation::on_btnretour1_clicked()
{
    ui->contenuReservation->setCurrentIndex(0);
}


void reservation::on_btnAnnulerReservation1_clicked()
{
    QMessageBox message;
    message.setIcon(QMessageBox::Warning);
    message.setWindowTitle("Annuler la création d'une réservation");
    message.setText("Voulez-vous vraiment annuler la création du réservation ?");
    QPushButton *btnOui = message.addButton("Oui",QMessageBox::AcceptRole);
    QPushButton *btnNon = message.addButton("Non",QMessageBox::RejectRole);
    message.exec();
    if(message.clickedButton() == btnOui)
    {
        reservation::on_menuReservation_clicked();
    }
    else
    {
        return;
    }
}


void reservation::on_btnSuivant1_clicked()
{
    if(!(ui->listeVol->currentIndex().isValid()))
    {
        QMessageBox::critical(this,"Erreur","Veuillez sélectionnez un vol !");
        return;
    }
    ui->contenuReservation->setCurrentIndex(2);
}


void reservation::on_btnretour2_clicked()
{
    ui->contenuReservation->setCurrentIndex(1);
}


void reservation::on_btnAnnulerReservation2_clicked()
{
    QMessageBox message;
    message.setIcon(QMessageBox::Warning);
    message.setWindowTitle("Annuler la création d'une réservation");
    message.setText("Voulez-vous vraiment annuler la création du réservation ?");
    QPushButton *btnOui = message.addButton("Oui",QMessageBox::AcceptRole);
    QPushButton *btnNon = message.addButton("Non",QMessageBox::RejectRole);
    message.exec();
    if(message.clickedButton() == btnOui)
    {
        reservation::on_menuReservation_clicked();
    }
    else
    {
        return;
    }
}


void reservation::on_btnSuivant2_clicked()
{
    QString identifiant = ui->identifiantPassager->text();
    QString nom = ui->nomPassager->text();
    QString prenoms = ui->prenoms->text();
    QString naissance = ui->naissance->text();
    QString passeport = ui->passeport->text();
    QString numero = ui->numeroReservation->text();
    QString classe = ui->classe->currentText();
    QString date = ui->dateReservation->text();

    ui->apIdentifiant->setText(identifiant);
    ui->apNomPassager->setText(nom);
    ui->apPrenoms->setText(prenoms);
    ui->apNaissance->setText(naissance);
    ui->apPasseport->setText(passeport);
    ui->apNumeroReservation->setText(numero);
    ui->apClasse->setText(classe);
    ui->apDateReservation->setText(date);

    ui->contenuReservation->setCurrentIndex(3);
}


void reservation::on_btnretour3_clicked()
{
    ui->contenuReservation->setCurrentIndex(2);
}


void reservation::on_btnAnnulerReservation3_clicked()
{
    QMessageBox message;
    message.setIcon(QMessageBox::Warning);
    message.setWindowTitle("Annuler la création d'une réservation");
    message.setText("Voulez-vous vraiment annuler la création du réservation ?");
    QPushButton *btnOui = message.addButton("Oui",QMessageBox::AcceptRole);
    QPushButton *btnNon = message.addButton("Non",QMessageBox::RejectRole);
    message.exec();
    if(message.clickedButton() == btnOui)
    {
        reservation::on_menuReservation_clicked();
    }
    else
    {
        return;
    }
}


void reservation::on_btnSuivant3_clicked()
{
    int ligne = acceuil::instance().ligneVol;

    QString dateDepart = ui->listeVol->model()->index(ligne,0).data().toString();
    QString heureDepart = ui->listeVol->model()->index(ligne,1).data().toString();
    QString numeroVol = ui->listeVol->model()->index(ligne,2).data().toString();
    QString aeroportDepart = ui->listeVol->model()->index(ligne,3).data().toString();
    QString aeroportArriver = ui->listeVol->model()->index(ligne,4).data().toString();
    QString dureeVol = ui->listeVol->model()->index(ligne,5).data().toString();
    QString immatriculationAvion = ui->listeVol->model()->index(ligne,6).data().toString();
    QString identifiantCompagnie = ui->listeVol->model()->index(ligne,7).data().toString();

    ui->apDateDepart->setText(dateDepart);
    ui->apAeroportDepart->setText(aeroportDepart);
    ui->apAeroportArriver->setText(aeroportArriver);
    ui->apHeureDepart->setText(heureDepart);
    ui->apDureeVol->setText(dureeVol);
    ui->apNumeroVol->setText(numeroVol);
    ui->apImmatriculation->setText(immatriculationAvion);
    ui->apIdentifiantCompagnie->setText(identifiantCompagnie);

    int i;
    int ligneCompagnie;
    int ligneAvion;

    QSqlDatabase db = connexion::connexionMysql();
    QSqlQueryModel *model3 = new QSqlQueryModel(this);
    model3->setQuery("select identifiant,nom,pays from compagnie_aerienne", db);
    model3->setHeaderData(0, Qt::Horizontal, "Identifiant");
    model3->setHeaderData(1, Qt::Horizontal, "Nom");
    model3->setHeaderData(2, Qt::Horizontal, "Pays");
    ui->listeCompagnie->setModel(model3);
    for(i=0; i<ui->listeCompagnie->model()->rowCount(); i++)
    {
        if(ui->listeCompagnie->model()->index(i,0).data().toString() == identifiantCompagnie)
        {
            ligneCompagnie = i;
        }
    }
    QString nomCompagnie = ui->listeCompagnie->model()->index(ligneCompagnie,1).data().toString();
    QString paysCompagnie = ui->listeCompagnie->model()->index(ligneCompagnie,2).data().toString();
    ui->apNomCompagnie->setText(nomCompagnie);
    ui->apPays->setText(paysCompagnie);

    QSqlQueryModel *model2 = new QSqlQueryModel(this);
    model2->setQuery("select immatriculation,modele,nombre_places from avion", db);
    model2->setHeaderData(0, Qt::Horizontal, "Immatriculation");
    model2->setHeaderData(1, Qt::Horizontal, "Modèle");
    model2->setHeaderData(2, Qt::Horizontal, "Nombre de places");
    ui->listeAvion->setModel(model2);
    for(i=0; i<ui->listeAvion->model()->rowCount(); i++)
    {
        if(ui->listeAvion->model()->index(i,0).data().toString() == immatriculationAvion)
        {
            ligneAvion = i;
        }
    }
    QString modeleAvion = ui->listeAvion->model()->index(ligneAvion,1).data().toString();
    QString placeAvion = ui->listeAvion->model()->index(ligneAvion,2).data().toString();
    ui->apModele->setText(modeleAvion);
    ui->apPlace->setText(placeAvion);

    ui->contenuReservation->setCurrentIndex(4);
}


void reservation::on_btnretour4_clicked()
{
    ui->contenuReservation->setCurrentIndex(3);
}


void reservation::on_btnAnnulerReservation4_clicked()
{
    QMessageBox message;
    message.setIcon(QMessageBox::Warning);
    message.setWindowTitle("Annuler la création d'une réservation");
    message.setText("Voulez-vous vraiment annuler la création du réservation ?");
    QPushButton *btnOui = message.addButton("Oui",QMessageBox::AcceptRole);
    QPushButton *btnNon = message.addButton("Non",QMessageBox::RejectRole);
    message.exec();
    if(message.clickedButton() == btnOui)
    {
        reservation::on_menuReservation_clicked();
    }
    else
    {
        return;
    }
}

void reservation::on_btnEnregistrerReservation_clicked()
{
    QString nom = ui->nomPassager->text();
    QString prenoms = ui->prenoms->text();
    QDate naissance = ui->naissance->date();
    QString passeport = ui->passeport->text();

    QSqlQuery query;
    query.prepare("insert into passager (nom,prenoms,date_naissance,numero_passeport) values (?,?,?,?)");
    query.addBindValue(nom);
    query.addBindValue(prenoms);
    query.addBindValue(naissance);
    query.addBindValue(passeport);
    if(query.exec())
    {
        QString numeroVol = ui->apNumeroVol->text();
        QString classe = ui->classe->currentText();
        query.prepare("select identifiant from passager order by identifiant desc");
        if(query.exec())
        {
            if(query.next())
            {
                QString identifiant = query.value(0).toString();
                query.prepare("insert into reservation (passager_id,numero_vol,classe) values (?,?,?)");
                query.addBindValue(identifiant);
                query.addBindValue(numeroVol);
                query.addBindValue(classe);

                if(query.exec())
                {
                    QString numeroReservation = ui->numeroReservation->text();
                    QString operation = "Création de la réservation numéro " + numeroReservation;
                    QString administrateur = ui->nomAdministrateur->text();

                    query.prepare("insert into historique (operation,nom_utilisateur) values (?,?)");
                    query.addBindValue(operation);
                    query.addBindValue(administrateur);
                    if(query.exec())
                    {
                        QMessageBox::information(this,"Création réussie","La réservation a été creer avec succès !");
                        reservation::on_menuReservation_clicked();
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
            QMessageBox::critical(this,"Erreur","Impossible de se connecter à Mysql");
            return;
        }

    }
    else
    {
        QMessageBox::critical(this,"Erreur","Impossible de se connecter à Mysql !");
        return;
    }
}


void reservation::on_btnAnnulerMod5_clicked()
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
        reservation::on_menuReservation_clicked();
    }
    else
    {
        return;
    }
}


void reservation::on_btnSuivant5_clicked()
{
    if(ui->modNomPassager->text().isEmpty())
    {
        QMessageBox::critical(this,"Champ vide","Veuillez saisir le nom du passager !");
        ui->modNomPassager->setFocus();
        return;
    }
    if(ui->modPrenoms->text().isEmpty())
    {
        QMessageBox::critical(this,"Champ vide","Veuillez saisir le prénoms du passager !");
        ui->modPrenoms->setFocus();
        return;
    }
    if(ui->modPasseport->text().isEmpty())
    {
        QMessageBox::critical(this,"Champ vide","Veuillez saisir le numéro de passeport du passager !");
        ui->modPasseport->setFocus();
        return;
    }
    QSqlQuery query;
    QString passeport = acceuil::instance().modPasseport;
    if(ui->modPasseport->text() != passeport)
    {
        query.prepare("select numero_passeport from passager where numero_passeport = ?");
        query.addBindValue(ui->modPasseport->text());
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

    ui->contenuReservation->setCurrentIndex(6);
}


void reservation::on_btnretour6_clicked()
{
    ui->contenuReservation->setCurrentIndex(5);
}


void reservation::on_btnAnnulerMod6_clicked()
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
        reservation::on_menuReservation_clicked();
    }
    else
    {
        return;
    }
}


void reservation::on_btnSuivant6_clicked()
{
    if(!(ui->modListeVol->currentIndex().isValid()))
    {
        QMessageBox::critical(this,"Erreur","Veuillez sélectionnez un vol !");
        return;
    }
    ui->contenuReservation->setCurrentIndex(7);
}


void reservation::on_btnRetour7_clicked()
{
    ui->contenuReservation->setCurrentIndex(6);
}


void reservation::on_btnAnnulerMod7_clicked()
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
        reservation::on_menuReservation_clicked();
    }
    else
    {
        return;
    }
}


void reservation::on_btnSuivant7_clicked()
{
    QString identifiant = ui->modIdentifiantPassager->text();
    QString nom = ui->modNomPassager->text();
    QString prenoms = ui->modPrenoms->text();
    QString naissance = ui->modNaissance->text();
    QString passeport = ui->modPasseport->text();
    QString numero = ui->modNumeroReservation->text();
    QString classe = ui->modClasse->currentText();
    QString date = ui->modDateReservation->text();

    ui->apModIdentifiant->setText(identifiant);
    ui->apModNomPassager->setText(nom);
    ui->apModPrenoms->setText(prenoms);
    ui->apModNaissance->setText(naissance);
    ui->apModPasseport->setText(passeport);
    ui->apModNumeroReservation->setText(numero);
    ui->apModClasse->setText(classe);
    ui->apModDateReservation->setText(date);

    ui->contenuReservation->setCurrentIndex(8);
}


void reservation::on_btnretour8_clicked()
{
    ui->contenuReservation->setCurrentIndex(7);
}


void reservation::on_btnAnnulerMod8_clicked()
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
        reservation::on_menuReservation_clicked();
    }
    else
    {
        return;
    }
}


void reservation::on_btnSuivant8_clicked()
{
    int ligne = acceuil::instance().modLigneVol;

    QString dateDepart = ui->modListeVol->model()->index(ligne,0).data().toString();
    QString heureDepart = ui->modListeVol->model()->index(ligne,1).data().toString();
    QString numeroVol = ui->modListeVol->model()->index(ligne,2).data().toString();
    QString aeroportDepart = ui->modListeVol->model()->index(ligne,3).data().toString();
    QString aeroportArriver = ui->modListeVol->model()->index(ligne,4).data().toString();
    QString dureeVol = ui->modListeVol->model()->index(ligne,5).data().toString();
    QString immatriculationAvion = ui->modListeVol->model()->index(ligne,6).data().toString();
    QString identifiantCompagnie = ui->modListeVol->model()->index(ligne,7).data().toString();

    ui->apModDateDepart->setText(dateDepart);
    ui->apModAeroportDepart->setText(aeroportDepart);
    ui->apModAeroportArriver->setText(aeroportArriver);
    ui->apModHeureDepart->setText(heureDepart);
    ui->apModDuree->setText(dureeVol);
    ui->apModNumeroVol->setText(numeroVol);
    ui->apModImmatriculation->setText(immatriculationAvion);
    ui->apModIdentifiantCompagnie->setText(identifiantCompagnie);

    int i;
    int ligneCompagnie;
    int ligneAvion;

    QSqlDatabase db = connexion::connexionMysql();
    QSqlQueryModel *model3 = new QSqlQueryModel(this);
    model3->setQuery("select identifiant,nom,pays from compagnie_aerienne", db);
    model3->setHeaderData(0, Qt::Horizontal, "Identifiant");
    model3->setHeaderData(1, Qt::Horizontal, "Nom");
    model3->setHeaderData(2, Qt::Horizontal, "Pays");
    ui->listeCompagnie->setModel(model3);

    for(i=0; i<ui->listeCompagnie->model()->rowCount(); i++)
    {
        if(ui->listeCompagnie->model()->index(i,0).data().toString() == identifiantCompagnie)
        {
            ligneCompagnie = i;
        }
    }

    QString nomCompagnie = ui->listeCompagnie->model()->index(ligneCompagnie,1).data().toString();
    QString paysCompagnie = ui->listeCompagnie->model()->index(ligneCompagnie,2).data().toString();
    ui->apModPays->setText(paysCompagnie);
    ui->apModNomCompagnie->setText(nomCompagnie);

    QSqlQueryModel *model2 = new QSqlQueryModel(this);
    model2->setQuery("select immatriculation,modele,nombre_places from avion", db);
    model2->setHeaderData(0, Qt::Horizontal, "Immatriculation");
    model2->setHeaderData(1, Qt::Horizontal, "Modèle");
    model2->setHeaderData(2, Qt::Horizontal, "Nombre de places");
    ui->listeAvion->setModel(model2);

    for(i=0; i<ui->listeAvion->model()->rowCount(); i++)
    {
        if(ui->listeAvion->model()->index(i,0).data().toString() == immatriculationAvion)
        {
            ligneAvion = i;
        }
    }
    QString modeleAvion = ui->listeAvion->model()->index(ligneAvion,1).data().toString();
    QString placeAvion = ui->listeAvion->model()->index(ligneAvion,2).data().toString();
    ui->apModModele->setText(modeleAvion);
    ui->apModPlace->setText(placeAvion);

    ui->contenuReservation->setCurrentIndex(9);
}

void reservation::on_btnretour9_clicked()
{
    ui->contenuReservation->setCurrentIndex(8);
}


void reservation::on_btnAnnulerMod9_clicked()
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
        reservation::on_menuReservation_clicked();
    }
    else
    {
        return;
    }
}


void reservation::on_btnEnregistrerMod_clicked()
{
    QString numeroReservation = acceuil::instance().numeroReservation;
    QString modIdentifiantPassager = ui->modIdentifiantPassager->text();
    QString modNumeroVol = ui->apModNumeroVol->text();
    QString modClasse = ui->modClasse->currentText();
    QSqlQuery query;
    query.prepare("update reservation set passager_id = ?, numero_vol = ?, classe = ? where numero_reservation = ?");
    query.addBindValue(modIdentifiantPassager);
    query.addBindValue(modNumeroVol);
    query.addBindValue(modClasse);
    query.addBindValue(numeroReservation);

    if(query.exec())
    {
        QString modNom = ui->modNomPassager->text();
        QString modPrenoms = ui->modPrenoms->text();
        QDate modNaissance = ui->modNaissance->date();
        QString modPasseport = ui->modPasseport->text();
        QString identifiant = ui->modIdentifiantPassager->text();
        query.prepare("update passager set nom = ?, prenoms = ?, date_naissance = ?, numero_passeport = ? where identifiant = ?");
        query.addBindValue(modNom);
        query.addBindValue(modPrenoms);
        query.addBindValue(modNaissance);
        query.addBindValue(modPasseport);
        query.addBindValue(identifiant);
        if(query.exec())
        {
            QString operation = "Modification de la réservation numéro " + numeroReservation;
            QString administrateur = ui->nomAdministrateur->text();
            query.prepare("insert into historique (operation,nom_utilisateur) values (?,?)");
            query.addBindValue(operation);
            query.addBindValue(administrateur);
            if(query.exec())
            {
                QMessageBox::information(this,"Modification réussie","Les informations du réservation et du passager ont été modifier avec succés !");
                reservation::on_menuReservation_clicked();
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

void reservation::on_btnDetail1_clicked()
{
    if(!(ui->listeReservationParAvion->currentIndex().isValid()))
    {
        QMessageBox::critical(this,"Erreur","Veuillez sélectionnez une réservation !");
        return;
    }

    int ligne = ui->listeReservationParAvion->currentIndex().row();
    QString immatriculation = ui->listeReservationParAvion->model()->index(ligne,0).data().toString();
    QString identifiantPassager = ui->listeReservationParAvion->model()->index(ligne,1).data().toString();
    QString numeroVol = ui->listeReservationParAvion->model()->index(ligne,2).data().toString();
    QString classe = ui->listeReservationParAvion->model()->index(ligne,3).data().toString();
    QString numeroReservation = ui->listeReservationParAvion->model()->index(ligne,4).data().toString();

    afficherListe();
    int i;
    int ligneAvion;
    for(i=0;i<ui->listeAvion->model()->rowCount();i++)
    {
        if(ui->listeAvion->model()->index(i,0).data().toString() == immatriculation)
        {
            ligneAvion = i;
        }
    }

    QString modele = ui->listeAvion->model()->index(ligneAvion,1).data().toString();
    QString nbrPlace = ui->listeAvion->model()->index(ligneAvion,2).data().toString();

    int ligneReservation;

    for(i=0;i<ui->listeReservationParDate->model()->rowCount();i++)
    {
        if(ui->listeReservationParDate->model()->index(i,4).data().toString() == numeroReservation)
        {
            ligneReservation = i;
        }
    }

    QString dateReservation = ui->listeReservationParDate->model()->index(ligneReservation,0).data().toString();

    int ligneVol;

    for(i=0;i<ui->listeVol->model()->rowCount();i++)
    {
        if(ui->listeVol->model()->index(i,2).data().toString() == numeroVol)
        {
            ligneVol = i;
        }
    }

    QString dateDepart = ui->listeVol->model()->index(ligneVol,0).data().toString();
    QString heureDepart = ui->listeVol->model()->index(ligneVol,1).data().toString();
    QString aeroportDepart = ui->listeVol->model()->index(ligneVol,3).data().toString();
    QString aeroportArriver = ui->listeVol->model()->index(ligneVol,4).data().toString();
    QString dureeVol = ui->listeVol->model()->index(ligneVol,5).data().toString();
    QString identifiantCompagnie = ui->listeVol->model()->index(ligneVol,7).data().toString();

    int ligneCompagnie;
    for(i=0;i<ui->listeCompagnie->model()->rowCount();i++)
    {
        if(ui->listeCompagnie->model()->index(i,0).data().toString() == identifiantCompagnie)
        {
            ligneCompagnie = i;
        }
    }

    QString nomCompagnie = ui->listeCompagnie->model()->index(ligneCompagnie,1).data().toString();
    QString pays = ui->listeCompagnie->model()->index(ligneCompagnie,2).data().toString();

    int lignePassager;

    for(i=0;i<ui->listePassager->model()->rowCount();i++)
    {
        if(ui->listePassager->model()->index(i,0).data().toString() == identifiantPassager)
        {
            lignePassager = i;
        }
    }

    QString nomPassager = ui->listePassager->model()->index(lignePassager,1).data().toString();
    QString prenoms = ui->listePassager->model()->index(lignePassager,2).data().toString();
    QString naissance = ui->listePassager->model()->index(lignePassager,3).data().toString();
    QString passeport = ui->listePassager->model()->index(lignePassager,4).data().toString();

    ui->detNumeroVol->setText(numeroVol);
    ui->detAeroportDepart->setText(aeroportDepart);
    ui->detAeroportArriver->setText(aeroportArriver);
    ui->detDateDepart->setText(dateDepart);
    ui->detHeureDepart->setText(heureDepart);
    ui->detDureeVol->setText(dureeVol);
    ui->detImmatriculation->setText(immatriculation);
    ui->detModele->setText(modele);
    ui->detPlace->setText(nbrPlace);
    ui->detIdentifiantCompagnie->setText(identifiantCompagnie);
    ui->detNomCompagnie->setText(nomCompagnie);
    ui->detPays->setText(pays);
    ui->detNumerorReservation->setText(numeroReservation);
    ui->detDateReservation->setText(dateReservation.left(10));
    ui->detClasseReservation->setText(classe);
    ui->detNomPassager->setText(nomPassager);
    ui->detPrenoms->setText(prenoms);
    ui->detIdentifiantPassager->setText(identifiantPassager);
    ui->detNaissance->setText(naissance);
    ui->detPasseport->setText(passeport);

    ui->contenuReservation->setCurrentIndex(14);
}

void reservation::on_btnSupprimer1_clicked()
{
    if(!(ui->listeReservationParAvion->currentIndex().isValid()))
    {
        QMessageBox::critical(this,"Erreur","Veuillez sélectionnez la réservation que vous voulez supprimer !");
        return;
    }
    QMessageBox message;
    message.setIcon(QMessageBox::Warning);
    message.setWindowTitle("Supprimer une réservation");
    message.setText("Le passager qui a effectuer cette réservation aussi sera supprimer.\nVoulez-vous continuer ?");
    QPushButton *btnOui = message.addButton("Oui",QMessageBox::AcceptRole);
    QPushButton *btnNon = message.addButton("Non",QMessageBox::RejectRole);
    message.exec();
    if(message.clickedButton() == btnOui)
    {
        int ligne = ui->listeReservationParAvion->currentIndex().row();
        QString numeroReservation = ui->listeReservationParAvion->model()->index(ligne,4).data().toString();
        QString identifiant = ui->listeReservationParAvion->model()->index(ligne,1).data().toString();
        QString prenoms;
        QSqlQuery query;
        query.prepare("select prenoms from passager where identifiant = ?");
        query.addBindValue(identifiant);
        if(query.exec())
        {
            if(query.next())
            {
                prenoms = query.value(0).toString();

                query.prepare("delete from reservation where numero_reservation = ?");
                query.addBindValue(numeroReservation);
                if(query.exec())
                {
                    query.prepare("delete from passager where identifiant = ?");
                    query.addBindValue(identifiant);
                    if(query.exec())
                    {
                        QString operation = "Suppression de la reservation numéro " + numeroReservation + " et du passager " + prenoms;
                        QString administrateur = ui->nomAdministrateur->text();
                        query.prepare("insert into historique (operation,nom_utilisateur) values (?,?)");
                        query.addBindValue(operation);
                        query.addBindValue(administrateur);
                        if(query.exec())
                        {
                            afficherListe();
                            QMessageBox::information(this,"Suppression réussie","La réservation et le passager ont été supprimer avec succès !");
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
            QMessageBox::critical(this,"Erreur","Impossible de se connecter à Mysql !");
            return;
        }
    }
    else
    {
        return;
    }
}

void reservation::on_btnModifier1_clicked()
{
    if(!(ui->listeReservationParAvion->currentIndex().isValid()))
    {
        QMessageBox::critical(this,"Erreur","Veuillez sélectionnez une réservation !");
        return;
    }

    int ligne = ui->listeReservationParAvion->currentIndex().row();
    QString identifiantPassager = ui->listeReservationParAvion->model()->index(ligne,1).data().toString();
    QString numeroVol = ui->listeReservationParAvion->model()->index(ligne,2).data().toString();
    QString classe = ui->listeReservationParAvion->model()->index(ligne,3).data().toString();
    QString numeroReservation = ui->listeReservationParAvion->model()->index(ligne,4).data().toString();

    afficherListe();
    int i;
    int ligneReservation;

    for(i=0;i<ui->listeReservationParDate->model()->rowCount();i++)
    {
        if(ui->listeReservationParDate->model()->index(i,4).data().toString() == numeroReservation)
        {
            ligneReservation = i;
        }
    }

    QDate dateReservation = ui->listeReservationParDate->model()->index(ligneReservation,0).data().toDate();

    int ligneVol;

    for(i=0;i<ui->modListeVol->model()->rowCount();i++)
    {
        if(ui->modListeVol->model()->index(i,2).data().toString() == numeroVol)
        {
            ligneVol = i;
        }
    }
    acceuil::instance().modLigneVol = ligneVol;
    int lignePassager;

    for(i=0;i<ui->listePassager->model()->rowCount();i++)
    {
        if(ui->listePassager->model()->index(i,0).data().toString() == identifiantPassager)
        {
            lignePassager = i;
        }
    }

    QString nomPassager = ui->listePassager->model()->index(lignePassager,1).data().toString();
    QString prenoms = ui->listePassager->model()->index(lignePassager,2).data().toString();

    QDate dateNaissance = ui->listePassager->model()->index(lignePassager,3).data().toDate();
    QString passeport = ui->listePassager->model()->index(lignePassager,4).data().toString();

    ui->modNomPassager->setText(nomPassager);
    ui->modPrenoms->setText(prenoms);
    ui->modIdentifiantPassager->setText(identifiantPassager);
    ui->modNaissance->setDate(dateNaissance);
    ui->modPasseport->setText(passeport);
    ui->modNumeroReservation->setText(numeroReservation);
    ui->modDateReservation->setDate(dateReservation);
    ui->modClasse->setCurrentText(classe);

    acceuil::instance().modPasseport = passeport;
    ui->contenuReservation->setCurrentIndex(modReservationForm);
}


void reservation::on_btnInserer1_clicked()
{
    ui->contenuReservation->setCurrentIndex(creerReservation);
}


void reservation::on_btnDetail2_clicked()
{
    if(!(ui->listeReservationParDate->currentIndex().isValid()))
    {
        QMessageBox::critical(this,"Erreur","Veuillez sélectionnez une réservation !");
        return;
    }

    int ligne = ui->listeReservationParDate->currentIndex().row();
    QString dateReservation = ui->listeReservationParDate->model()->index(ligne,0).data().toString();
    QString identifiantPassager = ui->listeReservationParDate->model()->index(ligne,1).data().toString();
    QString numeroVol = ui->listeReservationParDate->model()->index(ligne,2).data().toString();
    QString classe = ui->listeReservationParDate->model()->index(ligne,3).data().toString();
    QString numeroReservation = ui->listeReservationParDate->model()->index(ligne,4).data().toString();

    afficherListe();
    int i;
    int ligneVol;

    for(i=0;i<ui->listeVol->model()->rowCount();i++)
    {
        if(ui->listeVol->model()->index(i,2).data().toString() == numeroVol)
        {
            ligneVol = i;
        }
    }

    QString dateDepart = ui->listeVol->model()->index(ligneVol,0).data().toString();
    QString heureDepart = ui->listeVol->model()->index(ligneVol,1).data().toString();
    QString aeroportDepart = ui->listeVol->model()->index(ligneVol,3).data().toString();
    QString aeroportArriver = ui->listeVol->model()->index(ligneVol,4).data().toString();
    QString dureeVol = ui->listeVol->model()->index(ligneVol,5).data().toString();
    QString immatriculation = ui->listeVol->model()->index(ligneVol,6).data().toString();
    QString identifiantCompagnie = ui->listeVol->model()->index(ligneVol,7).data().toString();

    int ligneAvion;

    for(i=0;i<ui->listeAvion->model()->rowCount();i++)
    {
        if(ui->listeAvion->model()->index(i,0).data().toString() == immatriculation)
        {
            ligneAvion = i;
        }
    }

    QString modele = ui->listeAvion->model()->index(ligneAvion,1).data().toString();
    QString nbrPlace = ui->listeAvion->model()->index(ligneAvion,2).data().toString();

    int ligneCompagnie;
    for(i=0;i<ui->listeCompagnie->model()->rowCount();i++)
    {
        if(ui->listeCompagnie->model()->index(i,0).data().toString() == identifiantCompagnie)
        {
            ligneCompagnie = i;
        }
    }
    QString nomCompagnie = ui->listeCompagnie->model()->index(ligneCompagnie,1).data().toString();
    QString pays = ui->listeCompagnie->model()->index(ligneCompagnie,2).data().toString();

    int lignePassager;

    for(i=0;i<ui->listePassager->model()->rowCount();i++)
    {
        if(ui->listePassager->model()->index(i,0).data().toString() == identifiantPassager)
        {
            lignePassager = i;
        }
    }

    QString nomPassager = ui->listePassager->model()->index(lignePassager,1).data().toString();
    QString prenoms = ui->listePassager->model()->index(lignePassager,2).data().toString();
    QString naissance = ui->listePassager->model()->index(lignePassager,3).data().toString();
    QString passeport = ui->listePassager->model()->index(lignePassager,4).data().toString();

    ui->detNumeroVol->setText(numeroVol);
    ui->detAeroportDepart->setText(aeroportDepart);
    ui->detAeroportArriver->setText(aeroportArriver);
    ui->detDateDepart->setText(dateDepart);
    ui->detHeureDepart->setText(heureDepart);
    ui->detDureeVol->setText(dureeVol);
    ui->detImmatriculation->setText(immatriculation);
    ui->detModele->setText(modele);
    ui->detPlace->setText(nbrPlace);
    ui->detIdentifiantCompagnie->setText(identifiantCompagnie);
    ui->detNomCompagnie->setText(nomCompagnie);
    ui->detPays->setText(pays);
    ui->detNumerorReservation->setText(numeroReservation);
    ui->detDateReservation->setText(dateReservation.left(10));
    ui->detClasseReservation->setText(classe);
    ui->detNomPassager->setText(nomPassager);
    ui->detPrenoms->setText(prenoms);
    ui->detIdentifiantPassager->setText(identifiantPassager);
    ui->detNaissance->setText(naissance);
    ui->detPasseport->setText(passeport);

    ui->contenuReservation->setCurrentIndex(14);
}


void reservation::on_btnSupprimer2_clicked()
{
    if(!(ui->listeReservationParDate->currentIndex().isValid()))
    {
        QMessageBox::critical(this,"Erreur","Veuillez sélectionnez la réservation que vous voulez supprimer !");
        return;
    }

    QMessageBox message;
    message.setIcon(QMessageBox::Warning);
    message.setWindowTitle("Supprimer une réservation");
    message.setText("Le passager qui a effectuer cette réservation aussi sera supprimer.\nVoulez-vous continuer ?");
    QPushButton *btnOui = message.addButton("Oui",QMessageBox::AcceptRole);
    QPushButton *btnNon = message.addButton("Non",QMessageBox::RejectRole);
    message.exec();
    if(message.clickedButton() == btnOui)
    {
        int ligne = ui->listeReservationParDate->currentIndex().row();
        QString numeroReservation = ui->listeReservationParDate->model()->index(ligne,4).data().toString();
        QString identifiant = ui->listeReservationParDate->model()->index(ligne,1).data().toString();
        QString prenoms;
        QSqlQuery query;
        query.prepare("select prenoms from passager where identifiant = ?");
        query.addBindValue(identifiant);
        if(query.exec())
        {
            if(query.next())
            {
                prenoms = query.value(0).toString();

                query.prepare("delete from reservation where numero_reservation = ?");
                query.addBindValue(numeroReservation);
                if(query.exec())
                {
                    query.prepare("delete from passager where identifiant = ?");
                    query.addBindValue(identifiant);
                    if(query.exec())
                    {
                        QString operation = "Suppression de la reservation numéro " + numeroReservation + " et du passager " + prenoms;
                        QString administrateur = ui->nomAdministrateur->text();
                        query.prepare("insert into historique (operation,nom_utilisateur) values (?,?)");
                        query.addBindValue(operation);
                        query.addBindValue(administrateur);
                        if(query.exec())
                        {
                            afficherListe();
                            QMessageBox::information(this,"Suppression réussie","La réservation et le passager ont été supprimer avec succès !");
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
            QMessageBox::critical(this,"Erreur","Impossible de se connecter à Mysql !");
            return;
        }
    }
    else
    {
        return;
    }
}


void reservation::on_btnModifier2_clicked()
{
    if(!(ui->listeReservationParDate->currentIndex().isValid()))
    {
        QMessageBox::critical(this,"Erreur","Veuillez sélectionnez la réservation que vous voulez modifier !");
        return;
    }

    int ligne = ui->listeReservationParDate->currentIndex().row();

    QDate dateReservation = ui->listeReservationParDate->model()->index(ligne,0).data().toDate();
    QString identifiantPassager = ui->listeReservationParDate->model()->index(ligne,1).data().toString();
    QString numeroVol = ui->listeReservationParDate->model()->index(ligne,2).data().toString();
    QString classe = ui->listeReservationParDate->model()->index(ligne,3).data().toString();
    QString numeroReservation = ui->listeReservationParDate->model()->index(ligne,4).data().toString();
    acceuil::instance().numeroReservation = numeroReservation;

    afficherListe();
    int i;
    int ligneVol;

    for(i=0;i<ui->modListeVol->model()->rowCount();i++)
    {
        if(ui->modListeVol->model()->index(i,2).data().toString() == numeroVol)
        {
            ligneVol = i;
        }
    }
    acceuil::instance().modLigneVol = ligneVol;

    int lignePassager;

    for(i=0;i<ui->listePassager->model()->rowCount();i++)
    {
        if(ui->listePassager->model()->index(i,0).data().toString() == identifiantPassager)
        {
            lignePassager = i;
        }
    }

    QString nomPassager = ui->listePassager->model()->index(lignePassager,1).data().toString();
    QString prenoms = ui->listePassager->model()->index(lignePassager,2).data().toString();
    QDate dateNaissance = ui->listePassager->model()->index(lignePassager,3).data().toDate();
    QString passeport = ui->listePassager->model()->index(lignePassager,4).data().toString();

    ui->modNomPassager->setText(nomPassager);
    ui->modPrenoms->setText(prenoms);
    ui->modIdentifiantPassager->setText(identifiantPassager);
    ui->modNaissance->setDate(dateNaissance);
    ui->modPasseport->setText(passeport);
    ui->modNumeroReservation->setText(numeroReservation);
    ui->modDateReservation->setDate(dateReservation);
    ui->modClasse->setCurrentText(classe);

    acceuil::instance().modPasseport = passeport;
    ui->contenuReservation->setCurrentIndex(modReservationForm);
}


void reservation::on_btnInserer2_clicked()
{
    ui->contenuReservation->setCurrentIndex(creerReservation);
}


void reservation::on_btnMod_clicked()
{
    if(!(ui->modListeDate->currentIndex().isValid()))
    {
        QMessageBox::critical(this,"Erreur","Veuillez sélectionnez la réservation que vous voulez modifier !");
        return;
    }

    int ligne = ui->modListeDate->currentIndex().row();

    QDate dateReservation = ui->modListeDate->model()->index(ligne,0).data().toDate();
    QString identifiantPassager = ui->modListeDate->model()->index(ligne,1).data().toString();
    QString numeroVol = ui->modListeDate->model()->index(ligne,2).data().toString();
    QString classe = ui->modListeDate->model()->index(ligne,3).data().toString();
    QString numeroReservation = ui->modListeDate->model()->index(ligne,4).data().toString();
    acceuil::instance().numeroReservation = numeroReservation;

    afficherListe();
    int i;
    int ligneVol;

    for(i=0;i<ui->modListeVol->model()->rowCount();i++)
    {
        if(ui->modListeVol->model()->index(i,2).data().toString() == numeroVol)
        {
            ligneVol = i;
        }
    }
    acceuil::instance().modLigneVol = ligneVol;

    int lignePassager;

    for(i=0;i<ui->listePassager->model()->rowCount();i++)
    {
        if(ui->listePassager->model()->index(i,0).data().toString() == identifiantPassager)
        {
            lignePassager = i;
        }
    }

    QString nomPassager = ui->listePassager->model()->index(lignePassager,1).data().toString();
    QString prenoms = ui->listePassager->model()->index(lignePassager,2).data().toString();
    QDate dateNaissance = ui->listePassager->model()->index(lignePassager,3).data().toDate();
    QString passeport = ui->listePassager->model()->index(lignePassager,4).data().toString();

    ui->modNomPassager->setText(nomPassager);
    ui->modPrenoms->setText(prenoms);
    ui->modIdentifiantPassager->setText(identifiantPassager);
    ui->modNaissance->setDate(dateNaissance);
    ui->modPasseport->setText(passeport);
    ui->modNumeroReservation->setText(numeroReservation);
    ui->modDateReservation->setDate(dateReservation);
    ui->modClasse->setCurrentText(classe);

    acceuil::instance().modPasseport = passeport;
    ui->contenuReservation->setCurrentIndex(modReservationForm);
}


void reservation::on_btnSup_clicked()
{
    if(!(ui->supListeDate->currentIndex().isValid()))
    {
        QMessageBox::critical(this,"Erreur","Veuillez sélectionnez la réservation que vous voulez supprimer !");
        return;
    }

    QMessageBox message;
    message.setIcon(QMessageBox::Warning);
    message.setWindowTitle("Supprimer une réservation");
    message.setText("Le passager qui a effectuer cette réservation aussi sera supprimer.\nVoulez-vous continuer ?");
    QPushButton *btnOui = message.addButton("Oui",QMessageBox::AcceptRole);
    QPushButton *btnNon = message.addButton("Non",QMessageBox::RejectRole);
    message.exec();
    if(message.clickedButton() == btnOui)
    {
        int ligne = ui->supListeDate->currentIndex().row();
        QString numeroReservation = ui->supListeDate->model()->index(ligne,4).data().toString();
        QString identifiant = ui->supListeDate->model()->index(ligne,1).data().toString();
        QString prenoms;
        QSqlQuery query;
        query.prepare("select prenoms from passager where identifiant = ?");
        query.addBindValue(identifiant);
        if(query.exec())
        {
            if(query.next())
            {
                prenoms = query.value(0).toString();

                query.prepare("delete from reservation where numero_reservation = ?");
                query.addBindValue(numeroReservation);
                if(query.exec())
                {
                    query.prepare("delete from passager where identifiant = ?");
                    query.addBindValue(identifiant);
                    if(query.exec())
                    {
                        QString operation = "Suppression de la reservation numéro " + numeroReservation + " et du passager " + prenoms;
                        QString administrateur = ui->nomAdministrateur->text();
                        query.prepare("insert into historique (operation,nom_utilisateur) values (?,?)");
                        query.addBindValue(operation);
                        query.addBindValue(administrateur);
                        if(query.exec())
                        {
                            afficherListe();
                            QMessageBox::information(this,"Suppression réussie","La réservation et le passager ont été supprimer avec succès !");
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
            QMessageBox::critical(this,"Erreur","Impossible de se connecter à Mysql !");
            return;
        }
    }
    else
    {
        return;
    }
}

void reservation::on_contenuReservation_currentChanged(int arg1)
{
    ui->rechercheAvion->clear();
    ui->rechercheDate->clear();
    ui->modRechercheDate->clear();
    ui->supRechercheDate->clear();
    ui->btnModifier1->setEnabled(false);
    ui->btnSupprimer1->setEnabled(false);
    ui->btnDetail1->setEnabled(false);
    ui->btnModifier2->setEnabled(false);
    ui->btnSupprimer2->setEnabled(false);
    ui->btnDetail2->setEnabled(false);
    ui->btnMod->setEnabled(false);
    ui->btnSup->setEnabled(false);

    if(arg1 == creerReservation)
    {
        ui->nomPassager->setFocus();
        ui->rechercheVol->clearFocus();

        QSqlQuery query;
        query.prepare("select * from passager order by identifiant desc;");
        if(query.exec())
        {
            QString identifiant;
            if(query.next())
            {
                QString id = query.value(0).toString();
                int numero = id.right(4).toInt() + 1;

                if(numero > 9)
                {
                    identifiant = "PASS00" + QString::number(numero);
                }
                else
                {
                    identifiant = "PASS000" + QString::number(numero);
                }
                ui->identifiantPassager->setText(identifiant);
            }
            else
            {
                ui->identifiantPassager->setText("PASS0001");
            }
        }
        else
        {
            QMessageBox::critical(this,"Erreur","Impossible de se connecter à Mysql !");
            return;
        }

        query.prepare("select * from reservation order by numero_reservation desc;");
        if(query.exec())
        {
            if(query.next())
            {
                QString id = query.value(0).toString();
                int numero = id.right(3).toInt() + 1;
                QString date = ui->dateReservation->text().right(2);
                QString numeroReservation;
                if(numero > 9)
                {
                    numeroReservation = "RES" + date + "0" +QString::number(numero);
                }
                else
                {
                    numeroReservation = "RES" + date + "00" +QString::number(numero);

                }
                ui->numeroReservation->setText(numeroReservation);
            }
            else
            {
                QString date = ui->dateReservation->text().right(2);
                ui->numeroReservation->setText("RES" + date + "001" );
            }
        }
        else
        {
            QMessageBox::critical(this,"Erreur","Impossible de se connecter à Mysql !");
            return;
        }
    }
    ui->menuCreer->setStyleSheet(style);
    ui->menuModifier->setStyleSheet(style);
    ui->menuSupprimer->setStyleSheet(style);
    ui->menuListeAvion->setStyleSheet(style);
    ui->menuParDate->setStyleSheet(style);

    if(arg1 == 0 || arg1 == 1 || arg1 == 2 || arg1 == 3 || arg1 == 4)
    {
        QSqlDatabase db = connexion::connexionMysql();
        QString rechercheVol = ui->rechercheVol->text();
        QString recherche = QString(R"(select date_depart,heure_depart,numero_vol,aeroport_depart,aeroport_arrive,duree,avion_id,compagnie_id from vol where aeroport_arrive like "%%1%")").arg(rechercheVol);
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

        int ligneVol = acceuil::instance().ligneVol;
        ui->listeVol->selectRow(ligneVol);
        ui->menuCreer->setStyleSheet(styleFocus);
        ui->nomPassager->setFocus();
    }
    if(arg1 == 5 || arg1 == 6 || arg1 == 7 || arg1 == 8 || arg1 == 9 )
    {
        ui->modRechercheVol->clearFocus();
        QSqlDatabase db = connexion::connexionMysql();
        QString modRechercheVol = ui->modRechercheVol->text();
        QString recherche = QString(R"(select date_depart,heure_depart,numero_vol,aeroport_depart,aeroport_arrive,duree,avion_id,compagnie_id from vol where aeroport_arrive like "%%1%")").arg(modRechercheVol);
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

        ui->menuModifier->setStyleSheet(styleFocus);
        ui->modNomPassager->setFocus();
        int ligneVol = acceuil::instance().modLigneVol;
        ui->modListeVol->selectRow(ligneVol);
    }

    if(arg1 == modReservation)
    {
        afficherListe();
        ui->menuModifier->setStyleSheet(styleFocus);
        ui->modRechercheDate->clearFocus();
    }
    if(arg1 == supReservation)
    {
        afficherListe();
        ui->menuSupprimer->setStyleSheet(styleFocus);
        ui->supRechercheDate->clearFocus();
    }
    if(arg1 == listeParAvion)
    {
        afficherListe();
        ui->menuListeAvion->setStyleSheet(styleFocus);
        ui->rechercheAvion->clearFocus();
    }
    if(arg1 == listeParDate)
    {
        afficherListe();
        ui->menuParDate->setStyleSheet(styleFocus);
        ui->rechercheDate->clearFocus();
    }
    if(arg1 == supReservation || arg1 == modReservation || arg1 == listeParDate || arg1 == listeParAvion)
    {
        ui->nomPassager->clear();
        ui->prenoms->clear();
        ui->passeport->clear();
    }
}


void reservation::on_nomPassager_editingFinished()
{
    ui->prenoms->setFocus();
}


void reservation::on_prenoms_editingFinished()
{
    ui->naissance->setFocus();
}


void reservation::on_naissance_editingFinished()
{
    ui->passeport->setFocus();
}


void reservation::on_passeport_editingFinished()
{
    ui->passeport->clearFocus();
}

void reservation::on_modNomPassager_editingFinished()
{
    ui->modPrenoms->setFocus();
    ui->btnSuivant5->setEnabled(true);
}

void reservation::on_modPrenoms_editingFinished()
{
    ui->modNaissance->setFocus();
    ui->btnSuivant5->setEnabled(true);
}

void reservation::on_modNaissance_editingFinished()
{
    ui->modPasseport->setFocus();
    ui->btnSuivant5->setEnabled(true);
}


void reservation::on_modPasseport_editingFinished()
{
    ui->modPasseport->clearFocus();
}

void reservation::on_rechercheVol_textChanged(const QString &arg1)
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
    ui->btnSuivant1->setEnabled(false);
}


void reservation::on_modRechercheVol_textChanged(const QString &arg1)
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
    ui->btnSuivant6->setEnabled(false);
}


void reservation::on_rechercheAvion_textChanged(const QString &arg1)
{
    QSqlDatabase db = connexion::connexionMysql();
    QString recherche = QString(R"(select vol.avion_id,reservation.passager_id,reservation.numero_vol,reservation.classe,reservation.numero_reservation from reservation inner join vol on reservation.numero_vol = vol.numero_vol where avion_id like "%%1%")").arg(arg1);
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery(recherche,db);
    model->setHeaderData(0, Qt::Horizontal, "Immatriculation de l'avion");
    model->setHeaderData(1, Qt::Horizontal, "Passager");
    model->setHeaderData(2, Qt::Horizontal, "Vol");
    model->setHeaderData(3, Qt::Horizontal, "Classe");
    model->setHeaderData(4, Qt::Horizontal, "Numero de réservation");
    ui->listeReservationParAvion->setModel(model);
    ui->btnModifier1->setEnabled(false);
    ui->btnSupprimer1->setEnabled(false);
    ui->btnDetail1->setEnabled(false);
}


void reservation::on_rechercheDate_textChanged(const QString &arg1)
{
    QSqlDatabase db = connexion::connexionMysql();
    QString recherche = QString(R"(select date_reservation,passager_id,numero_vol,classe,numero_reservation from reservation where date_reservation like "%%1%")").arg(arg1);
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery(recherche,db);
    model->setHeaderData(0, Qt::Horizontal, "Date de réservation");
    model->setHeaderData(1, Qt::Horizontal, "Passager");
    model->setHeaderData(2, Qt::Horizontal, "Vol");
    model->setHeaderData(3, Qt::Horizontal, "Classe");
    model->setHeaderData(4, Qt::Horizontal, "Numero de réservation");
    ui->listeReservationParDate->setModel(model);
    ui->btnModifier2->setEnabled(false);
    ui->btnSupprimer2->setEnabled(false);
    ui->btnDetail2->setEnabled(false);
}


void reservation::on_modRechercheDate_textChanged(const QString &arg1)
{
    QSqlDatabase db = connexion::connexionMysql();
    QString recherche = QString(R"(select date_reservation,passager_id,numero_vol,classe,numero_reservation from reservation where date_reservation like "%%1%")").arg(arg1);
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery(recherche,db);
    model->setHeaderData(0, Qt::Horizontal, "Date de réservation");
    model->setHeaderData(1, Qt::Horizontal, "Passager");
    model->setHeaderData(2, Qt::Horizontal, "Vol");
    model->setHeaderData(3, Qt::Horizontal, "Classe");
    model->setHeaderData(4, Qt::Horizontal, "Numero de réservation");
    ui->modListeDate->setModel(model);
    ui->btnMod->setEnabled(false);
}


void reservation::on_supRechercheDate_textChanged(const QString &arg1)
{
    QSqlDatabase db = connexion::connexionMysql();
    QString recherche = QString(R"(select date_reservation,passager_id,numero_vol,classe,numero_reservation from reservation where date_reservation like "%%1%")").arg(arg1);
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery(recherche,db);
    model->setHeaderData(0, Qt::Horizontal, "Date de réservation");
    model->setHeaderData(1, Qt::Horizontal, "Passager");
    model->setHeaderData(2, Qt::Horizontal, "Vol");
    model->setHeaderData(3, Qt::Horizontal, "Classe");
    model->setHeaderData(4, Qt::Horizontal, "Numero de réservation");
    ui->supListeDate->setModel(model);
    ui->btnSup->setEnabled(false);
}


void reservation::on_listeReservationParDate_clicked(const QModelIndex &index)
{
        ui->btnDetail2->setEnabled(true);
        ui->btnSupprimer2->setEnabled(true);
        ui->btnModifier2->setEnabled(true);
}


void reservation::on_modListeDate_clicked(const QModelIndex &index)
{
        ui->btnMod->setEnabled(true);
}


void reservation::on_supListeDate_clicked(const QModelIndex &index)
{
        ui->btnSup->setEnabled(true);
}


void reservation::on_modListeVol_clicked(const QModelIndex &index)
{
    acceuil::instance().modLigneVol = index.row();
        ui->btnSuivant6->setEnabled(true);
}


void reservation::on_listeVol_clicked(const QModelIndex &index)
{
    acceuil::instance().ligneVol = index.row();
    ui->btnSuivant1->setEnabled(true);
}

void reservation::on_listeReservationParAvion_clicked(const QModelIndex &index)
{
    ui->btnDetail1->setEnabled(true);
    ui->btnSupprimer1->setEnabled(true);
    ui->btnModifier1->setEnabled(true);
}

void reservation::on_nomPassager_textChanged(const QString &arg1)
{
    if(!ui->nomPassager->text().isEmpty() && !ui->prenoms->text().isEmpty() && !ui->passeport->text().isEmpty())
    {
        ui->btnSuivant0->setEnabled(true);
    }
    QString nom = ui->nomPassager->text().toUpper();
    ui->nomPassager->setText(nom);
}



void reservation::on_passeport_textChanged(const QString &arg1)
{
    QString passeport = ui->passeport->text().toUpper();
    ui->passeport->setText(passeport);
    if(!ui->nomPassager->text().isEmpty() && !ui->prenoms->text().isEmpty() && !ui->passeport->text().isEmpty())
    {
        ui->btnSuivant0->setEnabled(true);
    }
}


void reservation::on_modNomPassager_textEdited(const QString &arg1)
{
    QString nom = ui->modNomPassager->text().toUpper();
    ui->modNomPassager->setText(nom);
    if(!ui->modNomPassager->text().isEmpty() && !ui->modPrenoms->text().isEmpty() && !ui->modPasseport->text().isEmpty())
    {
        ui->btnSuivant5->setEnabled(true);
    }
}


void reservation::on_modPasseport_textEdited(const QString &arg1)
{
    QString passeport = ui->modPasseport->text().toUpper();
    ui->modPasseport->setText(passeport);
    if(!ui->modNomPassager->text().isEmpty() && !ui->modPrenoms->text().isEmpty() && !ui->modPasseport->text().isEmpty())
    {
        ui->btnSuivant5->setEnabled(true);
    }
}


void reservation::on_prenoms_textChanged(const QString &arg1)
{
    if(!ui->nomPassager->text().isEmpty() && !ui->prenoms->text().isEmpty() && !ui->passeport->text().isEmpty())
    {
        ui->btnSuivant0->setEnabled(true);
    }
}

void reservation::on_modPrenoms_textEdited(const QString &arg1)
{
    if(!ui->modNomPassager->text().isEmpty() && !ui->modPrenoms->text().isEmpty() && !ui->modPasseport->text().isEmpty())
    {
        ui->btnSuivant5->setEnabled(true);
    }
}


void reservation::on_menuSeDeconnecter_clicked()
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

