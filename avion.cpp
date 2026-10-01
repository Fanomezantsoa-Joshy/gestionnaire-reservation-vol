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

#include "ui_avion.h"

avion::avion(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::avion)
{
    ui->setupUi(this);
    ui->contenuAvion->setCurrentIndex(listeAvion);
    ui->menuListe->setStyleSheet(styleFocus);
    QString nomAdministrateur = admin::instance().nomAdministrateur;
    ui->nomAdministrateur->setText(nomAdministrateur);
    afficherListeAvion();
    infoListe();
}

avion::~avion()
{
    delete ui;
}

void avion::infoListe() {
    connect(ui->listeAvion->selectionModel(),
        &QItemSelectionModel::currentRowChanged,
    this,
        [this](const QModelIndex &current, const QModelIndex &previous) {
            if (current.isValid()) {
                    QString immatriculation = ui->listeAvion->model()->index(current.row(),0).data().toString();
                    QString statut;
                    QString volEffectuer;
                    QSqlQuery query;
                    query.prepare("select * from vol where avion_id = ?");
                    query.addBindValue(immatriculation);
                    if(query.exec())
                    {
                        if(query.next())
                        {
                            statut = "Occupé";

                            query.prepare("select numero_vol from vol where avion_id = ?");
                            query.addBindValue(immatriculation);
                            if(query.exec())
                            {
                                if(query.next())
                                {
                                    volEffectuer = query.value(0).toString();
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
                            statut = "Libre";
                            volEffectuer = "Auccun";
                        }
                        ui->volEffectuer->setText(volEffectuer);
                        ui->statutAvion->setText(statut);
                    }
                    else
                    {
                        QMessageBox::critical(this,"Erreur","Impossible de se connecter à Mysql !");
                        return;
                    }

                    ui->btnModifier->setEnabled(true);
                    ui->btnSupprimer->setEnabled(true);
            }
            });
}

void avion::afficherListeAvion()
{
    QSqlDatabase db = connexion::connexionMysql();
    if(db.isOpen())
    {
        QSqlQueryModel *model1 = new QSqlQueryModel(this);
        model1->setQuery("select immatriculation,modele,nombre_places,compagnie_id from avion", db);
        model1->setHeaderData(0, Qt::Horizontal, "Immatriculation");
        model1->setHeaderData(1, Qt::Horizontal, "Modèle");
        model1->setHeaderData(2, Qt::Horizontal, "Nombre de places");
        model1->setHeaderData(3, Qt::Horizontal, "Compagnie aérienne");

        ui->listeAvion->setModel(model1);
        ui->modListeAvion->setModel(model1);
        ui->supListeAvion->setModel(model1);

        QSqlQueryModel *model2 = new QSqlQueryModel(this);
        model2->setQuery("select identifiant,nom,pays from compagnie_aerienne", db);
        model2->setHeaderData(0, Qt::Horizontal, "Identifiant");
        model2->setHeaderData(1, Qt::Horizontal, "Nom");
        model2->setHeaderData(2, Qt::Horizontal, "Pays");
        ui->listeCompagnie->setModel(model2);
        ui->modListeCompagnie->setModel(model2);
    }
    else
    {
        QMessageBox::critical(this,"Erreur","Impossible de se connecter à Mysql !");
        return;
    }
}

void avion::on_menuAcceuil_clicked()
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


void avion::on_menuReservation_clicked()
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


void avion::on_menuPassager_clicked()
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


void avion::on_menuVol_clicked()
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


void avion::on_menuAvion_clicked()
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


void avion::on_menuCompagnieAerienne_clicked()
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


void avion::on_menuQuitter_clicked()
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

void avion::on_menuCreer_clicked()
{
    ui->contenuAvion->setCurrentIndex(ajoutAvion);
    ui->immatriculation->setFocus();
}


void avion::on_menuModifier_clicked()
{
    ui->contenuAvion->setCurrentIndex(modAvion);
}


void avion::on_menuSupprimer_clicked()
{
    ui->contenuAvion->setCurrentIndex(supAvion);
}


void avion::on_menuListe_clicked()
{
    ui->contenuAvion->setCurrentIndex(listeAvion);
}

void avion::on_btnEnregistrer_clicked()
{
    if(!ui->listeCompagnie->currentIndex().isValid())
    {
        QMessageBox::critical(this,"Erreur","Veuillez selectionnez une compagnie aérienne !");
        return;
    }

    QString immatriculation = ui->immatriculation->text();
    QString modele = ui->modele->text();
    QString place = ui->place->text();
    int ligne = ui->listeCompagnie->currentIndex().row();
    QString identifiantCompagnie = ui->listeCompagnie->model()->index(ligne,0).data().toString();

    QSqlQuery query;
    query.prepare("insert into avion (immatriculation,modele,nombre_places,compagnie_id) values (?,?,?,?)");
    query.addBindValue(immatriculation);
    query.addBindValue(modele);
    query.addBindValue(place);
    query.addBindValue(identifiantCompagnie);

    if(query.exec())
    {
        QString operation = "Insértion de l'avion " + immatriculation;
        QString administrateur = ui->nomAdministrateur->text();
        query.prepare("insert into historique (operation,nom_utilisateur) values (?,?)");
        query.addBindValue(operation);
        query.addBindValue(administrateur);
        if(query.exec())
        {
            ui->immatriculation->clear();
            ui->modele->clear();
            ui->place->clear();
            QMessageBox::information(this,"Ajout réussi","L'avion a été ajouter avec succès !");
            avion::on_menuAvion_clicked();
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

void avion::on_btnEnregistrerMod_clicked()
{
    if(!ui->modListeCompagnie->currentIndex().isValid())
    {
        QMessageBox::critical(this,"Erreur","Veuillez selectionnez une compagnie aérienne !");
        return;
    }

    QString immatriculation = acceuil::instance().immatriculationAvion;
    QString modImmatriculation = ui->modImmatriculation->text();
    QString modModele = ui->modModele->text();
    int modPlace = ui->modPlace->text().toInt();
    int ligne = ui->modListeCompagnie->currentIndex().row();
    QString modIdentifiantCompagnie = ui->modListeCompagnie->model()->index(ligne,0).data().toString();

    QSqlQuery query;
    query.prepare("update avion set immatriculation = ?, modele = ?, nombre_places = ?, compagnie_id = ? where immatriculation = ?");
    query.addBindValue(modImmatriculation);
    query.addBindValue(modModele);
    query.addBindValue(modPlace);
    query.addBindValue(modIdentifiantCompagnie);
    query.addBindValue(immatriculation);

    if(query.exec())
    {
        QString operation = "Modification des informations de l'avion " + immatriculation;
        QString administrateur = ui->nomAdministrateur->text();
        query.prepare("insert into historique (operation,nom_utilisateur) values (?,?)");
        query.addBindValue(operation);
        query.addBindValue(administrateur);
        if(query.exec())
        {
            ui->modImmatriculation->clear();
            ui->modModele->clear();
            ui->modPlace->clear();
            QMessageBox::information(this,"Modification réussie","Les informations de l'avion ont été modifier avec succès !");
            avion::on_menuAvion_clicked();
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


void avion::on_btnSupprimer_clicked()
{
    if(!(ui->listeAvion->currentIndex().isValid()))
    {
        QMessageBox::critical(this,"Erreur","Veuillez sélectionnez l'avion que vous voulez supprimer !");
        return;
    }
    QMessageBox message;
    message.setIcon(QMessageBox::Warning);
    message.setWindowTitle("Supprimer un avion");
    message.setText("Voulez-vous vraiment supprimer cette avion ?");
    QPushButton *btnOui = message.addButton("Oui",QMessageBox::AcceptRole);
    QPushButton *btnNon = message.addButton("Non",QMessageBox::RejectRole);
    message.exec();
    if(message.clickedButton() == btnOui)
    {
        int ligne = ui->listeAvion->currentIndex().row();
        QString immatriculation = ui->listeAvion->model()->index(ligne,0).data().toString();

        QSqlQuery query;
        query.prepare("delete from avion where immatriculation = ?");
        query.addBindValue(immatriculation);
        if(query.exec())
        {
            QString operation = "Suppression de l'avion " + immatriculation;
            QString administrateur = ui->nomAdministrateur->text();
            query.prepare("insert into historique (operation,nom_utilisateur) values (?,?)");
            query.addBindValue(operation);
            query.addBindValue(administrateur);
            if(query.exec())
            {
                afficherListeAvion();
                QMessageBox::information(this,"Suppression réussie","L'avion a été supprimer avec succès !");

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


void avion::on_btnModifier_clicked()
{
    if(!(ui->listeAvion->currentIndex().isValid()))
    {
        QMessageBox::critical(this,"Erreur","Veuillez sélectionnez l'avion que vous voulez modifier !");
        return;
    }

    int ligne = ui->listeAvion->currentIndex().row();

    QString immatriculation = ui->listeAvion->model()->index(ligne,0).data().toString();
    QString modele = ui->listeAvion->model()->index(ligne,1).data().toString();
    QString nbrPlace = ui->listeAvion->model()->index(ligne,2).data().toString();
    QString identifiant = ui->listeAvion->model()->index(ligne,3).data().toString();

    ui->modImmatriculation->setText(immatriculation);
    ui->modModele->setText(modele);
    ui->modPlace->setText(nbrPlace);

    acceuil::instance().compagnieAerienne = identifiant;
    acceuil::instance().immatriculationAvion = immatriculation;
    ui->contenuAvion->setCurrentIndex(modAvionForm);
}


void avion::on_btnInserer_clicked()
{
    ui->contenuAvion->setCurrentIndex(ajoutAvion);
}


void avion::on_btnMod_clicked()
{
    if(!(ui->modListeAvion->currentIndex().isValid()))
    {
        QMessageBox::critical(this,"Erreur","Veuillez sélectionnez l'avion que vous voulez modifier !");
        return;
    }

    int ligne = ui->modListeAvion->currentIndex().row();
    QString immatriculation = ui->modListeAvion->model()->index(ligne,0).data().toString();
    QString modele = ui->modListeAvion->model()->index(ligne,1).data().toString();
    QString nbrPlace = ui->modListeAvion->model()->index(ligne,2).data().toString();
    QString identifiant = ui->modListeAvion->model()->index(ligne,3).data().toString();

    ui->modImmatriculation->setText(immatriculation);
    ui->modModele->setText(modele);
    ui->modPlace->setText(nbrPlace);

    acceuil::instance().compagnieAerienne = identifiant;
    acceuil::instance().immatriculationAvion = immatriculation;
    ui->contenuAvion->setCurrentIndex(modAvionForm);
}


void avion::on_btnSup_clicked()
{
    if(!(ui->supListeAvion->currentIndex().isValid()))
    {
        QMessageBox::critical(this,"Erreur","Veuillez sélectionnez l'avion que vous voulez supprimer !");
        return;
    }

    QMessageBox message;
    message.setIcon(QMessageBox::Warning);
    message.setWindowTitle("Supprimer un avion");
    message.setText("Voulez-vous vraiment supprimer cette avion ?");
    QPushButton *btnOui = message.addButton("Oui",QMessageBox::AcceptRole);
    QPushButton *btnNon = message.addButton("Non",QMessageBox::RejectRole);
    message.exec();
    if(message.clickedButton() == btnOui)
    {
        int ligne = ui->supListeAvion->currentIndex().row();
        QString immatriculation = ui->supListeAvion->model()->index(ligne,0).data().toString();

        QSqlQuery query;
        query.prepare("delete from avion where immatriculation = ?");
        query.addBindValue(immatriculation);
        if(query.exec())
        {
            QString operation = "Suppression de l'avion " + immatriculation;
            QString administrateur = ui->nomAdministrateur->text();
            query.prepare("insert into historique (operation,nom_utilisateur) values (?,?)");
            query.addBindValue(operation);
            query.addBindValue(administrateur);
            if(query.exec())
            {
                afficherListeAvion();
                QMessageBox::information(this,"Suppression réussie","L'avion a été supprimer avec succès !");
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

void avion::on_immatriculation_editingFinished()
{
    ui->modele->setFocus();
}


void avion::on_modele_editingFinished()
{
    ui->place->setFocus();
    ui->place->setCursorPosition(0);
}

void avion::on_place_editingFinished()
{
    ui->place->clearFocus();
}


void avion::on_modImmatriculation_editingFinished()
{
    ui->modModele->setFocus();
}


void avion::on_modModele_editingFinished()
{
    ui->modPlace->setFocus();
    ui->modPlace->setCursorPosition(0);
}

void avion::on_modPlace_editingFinished()
{
    ui->modPlace->clearFocus();
}

void avion::on_contenuAvion_currentChanged(int arg1)
{
    ui->rechercheAvion->clear();
    ui->modRechercheAvion->clear();
    ui->supRechercheAvion->clear();
    ui->volEffectuer->clear();
    ui->statutAvion->clear();
    ui->rechercheAvion->clearFocus();

    ui->modRechercheAvion->clearFocus();
    ui->supRechercheAvion->clearFocus();
    ui->btnModifier->setEnabled(false);
    ui->btnSupprimer->setEnabled(false);
    ui->btnMod->setEnabled(false);
    ui->btnSup->setEnabled(false);

    afficherListeAvion();

    ui->menuCreer->setStyleSheet(style);
    ui->menuModifier->setStyleSheet(style);
    ui->menuSupprimer->setStyleSheet(style);
    ui->menuListe->setStyleSheet(style);

    if(arg1 == ajoutAvion || arg1 == 1)
    {
        ui->menuCreer->setStyleSheet(styleFocus);
        ui->immatriculation->setFocus();
    }
    if(arg1 == modAvionForm || arg1 == modAvion || arg1 == 3)
    {
        ui->menuModifier->setStyleSheet(styleFocus);
        ui->modImmatriculation->setFocus();
    }

    if(arg1 == supAvion)
    {
        ui->menuSupprimer->setStyleSheet(styleFocus);
    }
    if(arg1 == listeAvion)
    {
        ui->menuListe->setStyleSheet(styleFocus);
    }
    if(arg1 == modAvion || arg1 == listeAvion || arg1 == supAvion)
    {
        ui->immatriculation->clear();
        ui->modele->clear();
        ui->place->clear();
    }
}

void avion::on_rechercheAvion_textChanged(const QString &arg1)
{
    QSqlDatabase db = connexion::connexionMysql();
    QString recherche = QString(R"(select * from avion where immatriculation like "%%1%")").arg(arg1);
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery(recherche,db);
    model->setHeaderData(0, Qt::Horizontal, "Immatriculation");
    model->setHeaderData(1, Qt::Horizontal, "Modèle");
    model->setHeaderData(2, Qt::Horizontal, "Nombre de places");
    model->setHeaderData(3, Qt::Horizontal, "Compagnie aérienne");
    ui->listeAvion->setModel(model);
    ui->btnSupprimer->setEnabled(false);
    ui->btnModifier->setEnabled(false);
    ui->volEffectuer->clear();
    ui->statutAvion->clear();
}

void avion::on_modRechercheAvion_textChanged(const QString &arg1)
{
    QSqlDatabase db = connexion::connexionMysql();
    QString recherche = QString(R"(select * from avion where immatriculation like "%%1%")").arg(arg1);
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery(recherche,db);
    model->setHeaderData(0, Qt::Horizontal, "Immatriculation");
    model->setHeaderData(1, Qt::Horizontal, "Modèle");
    model->setHeaderData(2, Qt::Horizontal, "Nombre de places");
    model->setHeaderData(3, Qt::Horizontal, "Compagnie aérienne");
    ui->modListeAvion->setModel(model);
}

void avion::on_supRechercheAvion_textChanged(const QString &arg1)
{
    QSqlDatabase db = connexion::connexionMysql();
    QString recherche = QString(R"(select * from avion where immatriculation like "%%1%")").arg(arg1);
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery(recherche,db);
    model->setHeaderData(0, Qt::Horizontal, "Immatriculation");
    model->setHeaderData(1, Qt::Horizontal, "Modèle");
    model->setHeaderData(2, Qt::Horizontal, "Nombre de places");
    model->setHeaderData(3, Qt::Horizontal, "Compagnie aérienne");
    ui->supListeAvion->setModel(model);
}

void avion::on_listeAvion_clicked(const QModelIndex &index)
{

}


void avion::on_modListeAvion_clicked(const QModelIndex &index)
{
    ui->btnMod->setEnabled(true);
}


void avion::on_supListeAvion_clicked(const QModelIndex &index)
{
    ui->btnSup->setEnabled(true);
}

void avion::on_immatriculation_textChanged(const QString &arg1)
{
    QString immatriculation = arg1.toUpper();
    ui->immatriculation->setText(immatriculation);
    if(!ui->immatriculation->text().isEmpty() && !ui->modele->text().isEmpty() && !ui->place->text().isEmpty())
    {
        ui->btnEnregistrer->setEnabled(true);
    }
    else
    {
        ui->btnEnregistrer->setEnabled(false);
    }
}


void avion::on_modele_textChanged(const QString &arg1)
{
    if(!ui->immatriculation->text().isEmpty() && !ui->modele->text().isEmpty() && !ui->place->text().isEmpty())
    {
        ui->btnEnregistrer->setEnabled(true);
    }
    else
    {
        ui->btnEnregistrer->setEnabled(false);
    }
}


void avion::on_place_textChanged(const QString &arg1)
{
    if(!ui->immatriculation->text().isEmpty() && !ui->modele->text().isEmpty() && !ui->place->text().isEmpty())
    {
        ui->btnEnregistrer->setEnabled(true);
    }
    else
    {
        ui->btnEnregistrer->setEnabled(false);
    }
}

void avion::on_modImmatriculation_textEdited(const QString &arg1)
{
    if(!ui->modImmatriculation->text().isEmpty() && !ui->modModele->text().isEmpty() && !ui->modPlace->text().isEmpty())
    {
        ui->btnEnregistrerMod->setEnabled(true);
    }
    else
    {
        ui->btnEnregistrerMod->setEnabled(false);
    }
}


void avion::on_modModele_textEdited(const QString &arg1)
{
    if(!ui->modImmatriculation->text().isEmpty() && !ui->modModele->text().isEmpty() && !ui->modPlace->text().isEmpty())
    {
        ui->btnEnregistrerMod->setEnabled(true);
    }
    else
    {
        ui->btnEnregistrerMod->setEnabled(false);
    }
}


void avion::on_modPlace_textEdited(const QString &arg1)
{
    if(!ui->modImmatriculation->text().isEmpty() && !ui->modModele->text().isEmpty() && !ui->modPlace->text().isEmpty())
    {
        ui->btnEnregistrerMod->setEnabled(true);
    }
    else
    {
        ui->btnEnregistrerMod->setEnabled(false);
    }
}

void avion::on_modImmatriculation_textChanged(const QString &arg1)
{
    QString immatriculation = arg1.toUpper();
    ui->modImmatriculation->setText(immatriculation);
}


void avion::on_rechercheCompagnie_textChanged(const QString &arg1)
{
    QSqlDatabase db = connexion::connexionMysql();
    QString recherche = QString(R"(select * from compagnie_aerienne where nom like "%%1%")").arg(arg1);
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery(recherche,db);
    model->setHeaderData(0, Qt::Horizontal, "Identifiant");
    model->setHeaderData(1, Qt::Horizontal, "Nom");
    model->setHeaderData(2, Qt::Horizontal, "Pays");
    ui->listeCompagnie->setModel(model);
    ui->btnEnregistrer->setEnabled(true);
}


void avion::on_modRechercheCompagnie_textChanged(const QString &arg1)
{
    QSqlDatabase db = connexion::connexionMysql();
    QString recherche = QString(R"(select * from compagnie_aerienne where nom like "%%1%")").arg(arg1);
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery(recherche,db);
    model->setHeaderData(0, Qt::Horizontal, "Identifiant");
    model->setHeaderData(1, Qt::Horizontal, "Nom");
    model->setHeaderData(2, Qt::Horizontal, "Pays");
    ui->modListeCompagnie->setModel(model);
    ui->btnEnregistrerMod->setEnabled(false);
}


void avion::on_btnSuivant0_clicked()
{
    QString immatriculation = ui->immatriculation->text();
    QString modele = ui->modele->text();
    QString place = ui->place->text();
    if(immatriculation.isEmpty())
    {
        QMessageBox champVide;
        champVide.setIcon(QMessageBox::Critical);
        champVide.setWindowTitle("Champ vide");
        champVide.setText("Veuillez saisir l'immatriculation de l'avion");
        champVide.exec();
        ui->immatriculation->setFocus();
        return;
    }
    if(modele.isEmpty())
    {
        QMessageBox champVide;
        champVide.setIcon(QMessageBox::Critical);
        champVide.setWindowTitle("Champ vide");
        champVide.setText("Veuillez saisir le modèle de l'avion");
        champVide.exec();
        ui->modele->setFocus();
        return;
    }
    if(place.isEmpty())
    {
        QMessageBox champVide;
        champVide.setIcon(QMessageBox::Critical);
        champVide.setWindowTitle("Champ vide");
        champVide.setText("Veuillez saisir le nombre de places dans l'avion");
        champVide.exec();
        ui->place->setFocus();
        return;
    }

    QSqlQuery query;
    query.prepare("select immatriculation from avion where immatriculation = ?");
    query.addBindValue(immatriculation);
    if(query.exec())
    {
        if(query.next())
        {
            QMessageBox::critical(this,"Erreur","L'immatriculation que vous avez saisie est déjà utiliser !");
            ui->immatriculation->setFocus();
            return;
        }
    }
    ui->contenuAvion->setCurrentIndex(1);
}


void avion::on_btnRetour1_clicked()
{
    ui->contenuAvion->setCurrentIndex(0);
}


void avion::on_listeCompagnie_clicked(const QModelIndex &index)
{
    ui->btnEnregistrer->setEnabled(true);
}


void avion::on_btnSuivant2_clicked()
{
    QString immatriculation = acceuil::instance().immatriculationAvion;
    QString modImmatriculation = ui->modImmatriculation->text();
    QString modModele = ui->modModele->text();
    QString identifiant = acceuil::instance().compagnieAerienne;

    int modPlace = ui->modPlace->text().toInt();

    if(modImmatriculation.isEmpty())
    {
        QMessageBox champVide;
        champVide.setIcon(QMessageBox::Critical);
        champVide.setWindowTitle("Champ vide");
        champVide.setText("Veuillez saisir l'immatriculation de l'avion");
        champVide.exec();
        ui->modImmatriculation->setFocus();
        return;
    }
    if(modModele.isEmpty())
    {
        QMessageBox champVide;
        champVide.setIcon(QMessageBox::Critical);
        champVide.setWindowTitle("Champ vide");
        champVide.setText("Veuillez saisir le modèle de l'avion");
        champVide.exec();
        ui->modModele->setFocus();
        return;
    }
    if(ui->modPlace->text().isEmpty())
    {
        QMessageBox champVide;
        champVide.setIcon(QMessageBox::Critical);
        champVide.setWindowTitle("Champ vide");
        champVide.setText("Veuillez saisir le nombre de places dans l'avion");
        champVide.exec();
        ui->modPlace->setFocus();
        return;
    }

    if(modImmatriculation != immatriculation)
    {
        QSqlQuery query;
        query.prepare("select immatriculation from avion where immatriculation = ?");
        query.addBindValue(modImmatriculation);
        if(query.exec())
        {
            if(query.next())
            {
                QMessageBox::critical(this,"Erreur","L'immatriculation que vous avez saisie est déjà utiliser !");
                ui->modImmatriculation->setFocus();
                return;
            }
        }
    }

    int i;
    int ligne;
    for(i=0; i<ui->modListeCompagnie->model()->rowCount(); i++)
    {
        if(ui->modListeCompagnie->model()->index(i,0).data().toString() == identifiant)
        {
            ligne = i;
        }
    }

    ui->contenuAvion->setCurrentIndex(3);
    ui->modListeCompagnie->selectRow(ligne);
}


void avion::on_btnretour3_clicked()
{
    int ligne = ui->modListeCompagnie->currentIndex().row();
    acceuil::instance().compagnieAerienne = ui->modListeCompagnie->model()->index(ligne,0).data().toString();
    ui->contenuAvion->setCurrentIndex(2);
}


void avion::on_modListeCompagnie_clicked(const QModelIndex &index)
{
    ui->btnEnregistrer->setEnabled(true);
}


void avion::on_btnAnnuler0_clicked()
{
    QMessageBox message;
    message.setIcon(QMessageBox::Warning);
    message.setWindowTitle("Annuler l'ajout de l'avion");
    message.setText("Voulez-vous vraiment annuler l'ajout de l'avion ?");
    QPushButton *btnOui = message.addButton("Oui",QMessageBox::AcceptRole);
    QPushButton *btnNon = message.addButton("Non",QMessageBox::RejectRole);
    message.exec();
    if(message.clickedButton() == btnOui)
    {
        ui->immatriculation->clear();
        ui->modele->clear();
        ui->place->clear();
        avion::on_menuAvion_clicked();
    }
    else
    {
        return;
    }
}


void avion::on_btnAnnuler1_clicked()
{
    QMessageBox message;
    message.setIcon(QMessageBox::Warning);
    message.setWindowTitle("Annuler l'ajout de l'avion");
    message.setText("Voulez-vous vraiment annuler l'ajout de l'avion ?");
    QPushButton *btnOui = message.addButton("Oui",QMessageBox::AcceptRole);
    QPushButton *btnNon = message.addButton("Non",QMessageBox::RejectRole);
    message.exec();
    if(message.clickedButton() == btnOui)
    {
        ui->immatriculation->clear();
        ui->modele->clear();
        ui->place->clear();
        avion::on_menuAvion_clicked();
    }
    else
    {
        return;
    }
}


void avion::on_btnAnnulerMod2_clicked()
{
    QMessageBox message;
    message.setIcon(QMessageBox::Warning);
    message.setWindowTitle("Annuler la modification de l'avion");
    message.setText("Les modifications que vous avez apporté à cette avion seront perdues.\nVoulez-vous continuez  ?");
    QPushButton *btnOui = message.addButton("Oui",QMessageBox::AcceptRole);
    QPushButton *btnNon = message.addButton("Non",QMessageBox::RejectRole);
    message.exec();
    if(message.clickedButton() == btnOui)
    {
        avion::on_menuAvion_clicked();
    }
    else
    {
        return;
    }
}


void avion::on_btnAnnulerMod3_clicked()
{
    QMessageBox message;
    message.setIcon(QMessageBox::Warning);
    message.setWindowTitle("Annuler la modification de l'avion");
    message.setText("Les modifications que vous avez apporté à cette avion seront perdues.\nVoulez-vous continuez  ?");
    QPushButton *btnOui = message.addButton("Oui",QMessageBox::AcceptRole);
    QPushButton *btnNon = message.addButton("Non",QMessageBox::RejectRole);
    message.exec();
    if(message.clickedButton() == btnOui)
    {
        avion::on_menuAvion_clicked();
    }
    else
    {
        return;
    }
}


void avion::on_menuSeDeconnecter_clicked()
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
