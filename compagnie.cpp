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

#include "ui_compagnie.h"

compagnie::compagnie(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::compagnie)
{
    ui->setupUi(this);
    ui->rechercheCompagnie->clearFocus();
    ui->contenuCompagnie->setCurrentIndex(listeCompagnie);
    QString nomAdministrateur = admin::instance().nomAdministrateur;
    ui->menuListe->setStyleSheet(styleFocus);
    ui->nomAdministrateur->setText(nomAdministrateur);
    afficherListeCompagnie();
    infoListe();
}

compagnie::~compagnie()
{
    delete ui;
}

void compagnie::infoListe() {
    connect(ui->listeCompagnie->selectionModel(),
            &QItemSelectionModel::currentRowChanged,
            this,
            [this](const QModelIndex &current, const QModelIndex &previous) {
                if (current.isValid()) {
                    QString identifiant = ui->listeCompagnie->model()->index(current.row(),0).data().toString();
                    QString avionPosseder;
                    int avionDisponnible;
                    QSqlQuery query;
                    query.prepare("select count(immatriculation) from avion where compagnie_id = ?");
                    query.addBindValue(identifiant);
                    if(query.exec())
                    {
                        if(query.next())
                        {
                            avionPosseder = query.value(0).toString();
                            ui->nbrAvion->setText(avionPosseder);
                            query.prepare("select count(avion_id) from vol where compagnie_id = ?");
                            query.addBindValue(identifiant);
                            if(query.exec())
                            {
                                if(query.next())
                                {
                                    int avionOccuper = query.value(0).toInt();
                                    avionDisponnible = avionPosseder.toInt() - avionOccuper;
                                    ui->avionDisponnible->setText(QString::number(avionDisponnible));
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
                    ui->btnSupprimer->setEnabled(true);
                }
            });
}

void compagnie::afficherListeCompagnie()
{
    QSqlDatabase db = connexion::connexionMysql();
    if(db.isOpen())
    {
        QSqlQueryModel *model = new QSqlQueryModel(this);
        model->setQuery("select identifiant,nom,pays from compagnie_aerienne", db);
        model->setHeaderData(0, Qt::Horizontal, "Identifiant");
        model->setHeaderData(1, Qt::Horizontal, "Nom");
        model->setHeaderData(2, Qt::Horizontal, "Pays");
        ui->listeCompagnie->setModel(model);
        ui->modListeCompagnie->setModel(model);
        ui->supListeCompagnie->setModel(model);
    }
    else
    {
        QMessageBox::critical(this,"Erreur","Impossible de se connecter à Mysql !");
        return;
    }
}

void compagnie::on_menuAcceuil_clicked()
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


void compagnie::on_menuReservation_clicked()
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


void compagnie::on_menuPassager_clicked()
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


void compagnie::on_menuVol_clicked()
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


void compagnie::on_menuAvion_clicked()
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


void compagnie::on_menuCompagnieAerienne_clicked()
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


void compagnie::on_menuQuitter_clicked()
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

void compagnie::on_menuAjouter_clicked()
{
    ui->contenuCompagnie->setCurrentIndex(ajoutCompagnie);
    ui->identifiant->setFocus();
}


void compagnie::on_menuModifier_clicked()
{
    ui->contenuCompagnie->setCurrentIndex(modCompagnie);
}


void compagnie::on_menuSupprimer_clicked()
{
    ui->contenuCompagnie->setCurrentIndex(supCompagnie);
}


void compagnie::on_menuListe_clicked()
{
    ui->contenuCompagnie->setCurrentIndex(listeCompagnie);
}

void compagnie::on_btnListe_clicked()
{
    afficherListeCompagnie();
    ui->contenuCompagnie->setCurrentIndex(listeCompagnie);
}


void compagnie::on_btnAnnuler_clicked()
{
    QMessageBox message;
    message.setIcon(QMessageBox::Warning);
    message.setWindowTitle("Annuler l'ajout d'une compagnie aérienne");
    message.setText("Voulez-vous vraiment annuler l'ajout de cette compagnie aérienne ?");
    QPushButton *btnOui = message.addButton("Oui",QMessageBox::AcceptRole);
    QPushButton *btnNon = message.addButton("Non",QMessageBox::RejectRole);
    message.exec();
    if(message.clickedButton() == btnOui)
    {
        ui->identifiant->clear();
        ui->nom->clear();
        ui->pays->clear();
        compagnie::on_menuCompagnieAerienne_clicked();
    }
    else
    {
        return;
    }
}


void compagnie::on_btnEnregistrer_clicked()
{
    QString identifiant = ui->identifiant->text();
    QString nom = ui->nom->text();
    QString pays = ui->pays->text();
    if(identifiant.isEmpty())
    {
        QMessageBox champVide;
        champVide.setIcon(QMessageBox::Critical);
        champVide.setWindowTitle("Champ vide");
        champVide.setText("Veuillez saisir l'identifiant de la compagie aérienne !");
        champVide.exec();
        ui->identifiant->setFocus();
        return;
    }
    if(nom.isEmpty())
    {
        QMessageBox champVide;
        champVide.setIcon(QMessageBox::Critical);
        champVide.setWindowTitle("Champ vide");
        champVide.setText("Veuillez saisir le nom de la compagnie aérienne !");
        champVide.exec();
        ui->nom->setFocus();
        return;
    }
    if(pays.isEmpty())
    {
        QMessageBox champVide;
        champVide.setIcon(QMessageBox::Critical);
        champVide.setWindowTitle("Champ vide");
        champVide.setText("Veuillez saisir le nom du pays d'orignie de la compagnie aérienne !");
        champVide.exec();
        ui->pays->setFocus();
        return;
    }

    QSqlQuery query;
    query.prepare("select identifiant from compagnie_aerienne where identifiant = ?");
    query.addBindValue(identifiant);
    if(query.exec())
    {
        if(query.next())
        {
            QMessageBox::critical(this,"Erreur","L'identifiant que vous avez saisie est déjà utiliser !");
            ui->identifiant->setFocus();
            return;
        }
    }
    else
    {
        QMessageBox::critical(this,"Erreur","Impossible de se connecter à Mysql !");
        return;
    }

    query.prepare("insert into compagnie_aerienne (identifiant,nom,pays) values (?,?,?)");
    query.addBindValue(identifiant);
    query.addBindValue(nom);
    query.addBindValue(pays);

    if(query.exec())
    {
        QString operation = "Insértion de la compagnie aérienne " + nom;
        QString administrateur = ui->nomAdministrateur->text();
        query.prepare("insert into historique (operation,nom_utilisateur) values (?,?)");
        query.addBindValue(operation);
        query.addBindValue(administrateur);
        if(query.exec())
        {
            ui->identifiant->clear();
            ui->nom->clear();
            ui->pays->clear();
            QMessageBox::information(this,"Ajout réussie","La compagnie aérienne a été ajouter avec succès !");
            compagnie::on_menuCompagnieAerienne_clicked();
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


void compagnie::on_btnListeMod_clicked()
{
    afficherListeCompagnie();
    ui->contenuCompagnie->setCurrentIndex(listeCompagnie);
}


void compagnie::on_btnAnnulerMod_clicked()
{
    QMessageBox message;
    message.setIcon(QMessageBox::Warning);
    message.setWindowTitle("Annuler la modification d'une compagnie aérienne");
    message.setText("Les modifications que vous avez apporté à cette compagnie aérienne seront perdues.\nVoulez-vous continuer ?");
    QPushButton *btnOui = message.addButton("Oui",QMessageBox::AcceptRole);
    QPushButton *btnNon = message.addButton("Non",QMessageBox::RejectRole);
    message.exec();
    if(message.clickedButton() == btnOui)
    {
        ui->modIdentifiant->clear();
        ui->modNom->clear();
        ui->modPays->clear();
        compagnie::on_menuCompagnieAerienne_clicked();
    }
    else
    {
        return;
    }
}


void compagnie::on_btnEnregistrerMod_clicked()
{
    QString identifiant = acceuil::instance().identifiantCompagnie;
    QString modIdentifiant = ui->modIdentifiant->text();
    QString modNom = ui->modNom->text();
    QString modPays = ui->modPays->text();

    if(modIdentifiant.isEmpty())
    {
        QMessageBox champVide;
        champVide.setIcon(QMessageBox::Critical);
        champVide.setWindowTitle("Champ vide");
        champVide.setText("Veuillez saisir l'identifiant de la compagie aérienne !");
        champVide.exec();
        ui->modIdentifiant->setFocus();
        return;
    }
    if(modNom.isEmpty())
    {
        QMessageBox champVide;
        champVide.setIcon(QMessageBox::Critical);
        champVide.setWindowTitle("Champ vide");
        champVide.setText("Veuillez saisir le nom de la compagnie aérienne !");
        champVide.exec();
        ui->modNom->setFocus();
        return;
    }
    if(modPays.isEmpty())
    {
        QMessageBox champVide;
        champVide.setIcon(QMessageBox::Critical);
        champVide.setWindowTitle("Champ vide");
        champVide.setText("Veuillez saisir le nom du pays d'orignie de la compagnie aérienne !");
        champVide.exec();
        ui->modPays->setFocus();
        return;
    }

    QSqlQuery query;

    if(modIdentifiant != identifiant)
    {
        QSqlQuery query;
        query.prepare("select identifiant from compagnie_aerienne where identifiant = ?");
        query.addBindValue(modIdentifiant);
        if(query.exec())
        {
            if(query.next())
            {
                QMessageBox::critical(this,"Erreur","L'identifiant que vous avez saisie est déjà utiliser !");
                ui->modIdentifiant->setFocus();
                return;
            }
        }
        else
        {
            QMessageBox::critical(this,"Erreur","Impossible de se connecter à Mysql !");
            return;
        }
    }

    query.prepare("update compagnie_aerienne set identifiant = ?, nom = ?, pays = ? where identifiant = ?");
    query.addBindValue(modIdentifiant);
    query.addBindValue(modNom);
    query.addBindValue(modPays);
    query.addBindValue(identifiant);

    if(query.exec())
    {
        QString operation = "Modification de la compagnie aérienne " + modNom;
        QString administrateur = ui->nomAdministrateur->text();
        query.prepare("insert into historique (operation,nom_utilisateur) values (?,?)");
        query.addBindValue(operation);
        query.addBindValue(administrateur);
        if(query.exec())
        {
            ui->modIdentifiant->clear();
            ui->modNom->clear();
            ui->modPays->clear();
            QMessageBox::information(this,"Modification réussie","Les informations de la compagnie aérienne ont été modifier avec succès !");
            compagnie::on_menuCompagnieAerienne_clicked();
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

void compagnie::on_btnSupprimer_clicked()
{
    if(!(ui->listeCompagnie->currentIndex().isValid()))
    {
        QMessageBox::critical(this,"Erreur","Veuillez sélectionnez la compagnie aérienne que vous voulez supprimer !");
        return;
    }

    QMessageBox message;
    message.setIcon(QMessageBox::Warning);
    message.setWindowTitle("Supprimer une compagnie aérienne");
    message.setText("Voulez-vous vraiment supprimer cette compagnie aérienne ?");
    QPushButton *btnOui = message.addButton("Oui",QMessageBox::AcceptRole);
    QPushButton *btnNon = message.addButton("Non",QMessageBox::RejectRole);
    message.exec();
    if(message.clickedButton() == btnOui)
    {
        int ligne = ui->listeCompagnie->currentIndex().row();
        QString identifiant = ui->listeCompagnie->model()->index(ligne,0).data().toString();
        QString nom = ui->listeCompagnie->model()->index(ligne,1).data().toString();

        QSqlQuery query;
        query.prepare("delete from compagnie_aerienne where identifiant = ?");
        query.addBindValue(identifiant);
        if(query.exec())
        {
            QString operation = "Suppression de la compagnie aérienne " + nom;
            QString administrateur = ui->nomAdministrateur->text();
            query.prepare("insert into historique (operation,nom_utilisateur) values (?,?)");
            query.addBindValue(operation);
            query.addBindValue(administrateur);
            if(query.exec())
            {
                afficherListeCompagnie();
                QMessageBox::information(this,"Suppression réussie","La compagnie aérienne a été supprimer avec succès !");

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


void compagnie::on_btnModifier_clicked()
{
    if(!(ui->listeCompagnie->currentIndex().isValid()))
    {
        QMessageBox::critical(this,"Erreur","Veuillez sélectionnez la compagnie aérienne que vous voulez modifier !");
        return;
    }

    int ligne = ui->listeCompagnie->currentIndex().row();
    QString identifiant = ui->listeCompagnie->model()->index(ligne,0).data().toString();
    QString nom = ui->listeCompagnie->model()->index(ligne,1).data().toString();
    QString pays = ui->listeCompagnie->model()->index(ligne,2).data().toString();

    ui->modIdentifiant->setText(identifiant);
    ui->modNom->setText(nom);
    ui->modPays->setText(pays);

    acceuil::instance().identifiantCompagnie = identifiant;
    ui->contenuCompagnie->setCurrentIndex(modCompagnieForm);
}


void compagnie::on_btnInserer_clicked()
{
    ui->contenuCompagnie->setCurrentIndex(ajoutCompagnie);
}


void compagnie::on_btnMod_clicked()
{
    if(!(ui->modListeCompagnie->currentIndex().isValid()))
    {
        QMessageBox::critical(this,"Erreur","Veuillez sélectionnez la compagnie aérienne que vous voulez modifier !");
        return;
    }
    int ligne = ui->modListeCompagnie->currentIndex().row();
    QString modIdentifiant = ui->modListeCompagnie->model()->index(ligne,0).data().toString();
    QString modNom = ui->modListeCompagnie->model()->index(ligne,1).data().toString();
    QString modPays = ui->modListeCompagnie->model()->index(ligne,2).data().toString();

    ui->modIdentifiant->setText(modIdentifiant);
    ui->modNom->setText(modNom);
    ui->modPays->setText(modPays);

    acceuil::instance().identifiantCompagnie = modIdentifiant;
    ui->contenuCompagnie->setCurrentIndex(modCompagnieForm);
}


void compagnie::on_btnSup_clicked()
{
    if(!(ui->supListeCompagnie->currentIndex().isValid()))
    {
        QMessageBox::critical(this,"Erreur","Veuillez sélectionnez la compagnie aérienne que vous voulez supprimer !");
        return;
    }

    QMessageBox message;
    message.setIcon(QMessageBox::Warning);
    message.setWindowTitle("Supprimer une compagnie aérienne");
    message.setText("Voulez-vous vraiment supprimer cette compagnie aérienne ?");
    QPushButton *btnOui = message.addButton("Oui",QMessageBox::AcceptRole);
    QPushButton *btnNon = message.addButton("Non",QMessageBox::RejectRole);
    message.exec();
    if(message.clickedButton() == btnOui)
    {
        int ligne = ui->supListeCompagnie->currentIndex().row();
        QString identifiant = ui->supListeCompagnie->model()->index(ligne,0).data().toString();
        QString nom = ui->supListeCompagnie->model()->index(ligne,1).data().toString();
        QSqlQuery query;
        query.prepare("delete from compagnie_aerienne where identifiant = ?");
        query.addBindValue(identifiant);
        if(query.exec())
        {
            QString operation = "Suppression de la compagnie aérienne " + nom;
            QString administrateur = ui->nomAdministrateur->text();
            query.prepare("insert into historique (operation,nom_utilisateur) values (?,?)");
            query.addBindValue(operation);
            query.addBindValue(administrateur);
            if(query.exec())
            {
                afficherListeCompagnie();
                QMessageBox::information(this,"Suppression réussie","La compagnie aérienne a été supprimer avec succès !");

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


void compagnie::on_identifiant_editingFinished()
{
    ui->nom->setFocus();
}


void compagnie::on_nom_editingFinished()
{
    ui->pays->setFocus();
}

void compagnie::on_pays_editingFinished()
{
    ui->pays->clearFocus();
}


void compagnie::on_modIdentifiant_editingFinished()
{
    ui->modNom->setFocus();
}


void compagnie::on_modNom_editingFinished()
{
    ui->modPays->setFocus();
}

void compagnie::on_modPays_editingFinished()
{
    ui->modPays->clearFocus();
}

void compagnie::on_contenuCompagnie_currentChanged(int arg1)
{
    ui->rechercheCompagnie->clear();
    ui->modRechercheCompagnie->clear();
    ui->supRechercheCompagnie->clear();
    ui->identifiant->clear();
    ui->avionDisponnible->clear();
    ui->nbrAvion->clear();
    ui->nom->clear();
    ui->pays->clear();
    ui->rechercheCompagnie->clearFocus();
    ui->modRechercheCompagnie->clearFocus();
    ui->supRechercheCompagnie->clearFocus();
    ui->btnModifier->setEnabled(false);
    ui->btnSupprimer->setEnabled(false);
    ui->btnMod->setEnabled(false);
    ui->btnSup->setEnabled(false);

    afficherListeCompagnie();

    ui->menuAjouter->setStyleSheet(style);
    ui->menuModifier->setStyleSheet(style);
    ui->menuSupprimer->setStyleSheet(style);
    ui->menuListe->setStyleSheet(style);

    if(arg1 == ajoutCompagnie)
    {
        ui->menuAjouter->setStyleSheet(styleFocus);
        ui->identifiant->setFocus();
    }
    if(arg1 == modCompagnieForm || arg1 == modCompagnie)
    {
        ui->menuModifier->setStyleSheet(styleFocus);
        ui->modIdentifiant->setFocus();
    }
    if(arg1 == supCompagnie)
    {
        ui->menuSupprimer->setStyleSheet(styleFocus);
    }
    if(arg1 == listeCompagnie)
    {
        ui->menuListe->setStyleSheet(styleFocus);
    }
}


void compagnie::on_rechercheCompagnie_textChanged(const QString &arg1)
{
    QSqlDatabase db = connexion::connexionMysql();
    QString recherche = QString(R"(select * from compagnie_aerienne where nom like "%%1%")").arg(arg1);
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery(recherche,db);
    model->setHeaderData(0, Qt::Horizontal, "Identifiant");
    model->setHeaderData(1, Qt::Horizontal, "Nom");
    model->setHeaderData(2, Qt::Horizontal, "Pays");
    ui->listeCompagnie->setModel(model);
    ui->btnModifier->setEnabled(false);
    ui->btnSupprimer->setEnabled(false);
    ui->avionDisponnible->clear();
    ui->nbrAvion->clear();
}


void compagnie::on_modRechercheCompagnie_textChanged(const QString &arg1)
{
    QSqlDatabase db = connexion::connexionMysql();
    QString recherche = QString(R"(select * from compagnie_aerienne where nom like "%%1%")").arg(arg1);
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery(recherche,db);
    model->setHeaderData(0, Qt::Horizontal, "Identifiant");
    model->setHeaderData(1, Qt::Horizontal, "Nom");
    model->setHeaderData(2, Qt::Horizontal, "Pays");
    ui->modListeCompagnie->setModel(model);
    ui->btnMod->setEnabled(false);
}


void compagnie::on_supRechercheCompagnie_textChanged(const QString &arg1)
{
    QSqlDatabase db = connexion::connexionMysql();
    QString recherche = QString(R"(select * from compagnie_aerienne where nom like "%%1%")").arg(arg1);
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery(recherche,db);
    model->setHeaderData(0, Qt::Horizontal, "Identifiant");
    model->setHeaderData(1, Qt::Horizontal, "Nom");
    model->setHeaderData(2, Qt::Horizontal, "Pays");
    ui->supListeCompagnie->setModel(model);
    ui->btnSup->setEnabled(false);
}

void compagnie::on_listeCompagnie_clicked(const QModelIndex &index)
{
}


void compagnie::on_modListeCompagnie_clicked(const QModelIndex &index)
{
    ui->btnMod->setEnabled(true);
}

void compagnie::on_supListeCompagnie_clicked(const QModelIndex &index)
{
        ui->btnSup->setEnabled(true);
}



void compagnie::on_identifiant_textChanged(const QString &arg1)
{
    QString identifiant = arg1.toUpper();
    ui->identifiant->setText(identifiant);
    if(!ui->identifiant->text().isEmpty() && !ui->nom->text().isEmpty() && !ui->pays->text().isEmpty())
    {
        ui->btnEnregistrer->setEnabled(true);
    }
    else
    {
        ui->btnEnregistrer->setEnabled(false);
    }
}


void compagnie::on_modIdentifiant_textChanged(const QString &arg1)
{
    QString identifiant = arg1.toUpper();
    ui->modIdentifiant->setText(identifiant);
}


void compagnie::on_modPays_textChanged(const QString &arg1)
{
    QString pays = arg1.toUpper();
    ui->modPays->setText(pays);
}


void compagnie::on_pays_textChanged(const QString &arg1)
{
    QString pays = arg1.toUpper();
    ui->pays->setText(pays);
    if(!ui->identifiant->text().isEmpty() && !ui->nom->text().isEmpty() && !ui->pays->text().isEmpty())
    {
        ui->btnEnregistrer->setEnabled(true);
    }
    else
    {
        ui->btnEnregistrer->setEnabled(false);
    }
}


void compagnie::on_nom_textChanged(const QString &arg1)
{
    if(!ui->identifiant->text().isEmpty() && !ui->nom->text().isEmpty() && !ui->pays->text().isEmpty())
    {
        ui->btnEnregistrer->setEnabled(true);
    }
    else
    {
        ui->btnEnregistrer->setEnabled(false);
    }
}


void compagnie::on_modIdentifiant_textEdited(const QString &arg1)
{
    if(!ui->modIdentifiant->text().isEmpty() && !ui->modNom->text().isEmpty() && !ui->modPays->text().isEmpty())
    {
        ui->btnEnregistrerMod->setEnabled(true);
    }
    else
    {
        ui->btnEnregistrerMod->setEnabled(false);
    }
}


void compagnie::on_modNom_textEdited(const QString &arg1)
{
    if(!ui->modIdentifiant->text().isEmpty() && !ui->modNom->text().isEmpty() && !ui->modPays->text().isEmpty())
    {
        ui->btnEnregistrerMod->setEnabled(true);
    }
    else
    {
        ui->btnEnregistrerMod->setEnabled(false);
    }
}


void compagnie::on_modPays_textEdited(const QString &arg1)
{
    if(!ui->modIdentifiant->text().isEmpty() && !ui->modNom->text().isEmpty() && !ui->modPays->text().isEmpty())
    {
        ui->btnEnregistrerMod->setEnabled(true);
    }
    else
    {
        ui->btnEnregistrerMod->setEnabled(false);
    }
}


void compagnie::on_menuSeDeconnecter_clicked()
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

