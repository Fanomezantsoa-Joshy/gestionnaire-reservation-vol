#include "admin.h"
#include "acceuil.h"
#include "connexion.h"

#include <QMessageBox>
#include <QSqlQuery>

#include "ui_admin.h"

admin::admin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::admin)
{
    ui->setupUi(this);
    ui->contenuAdmin->setCurrentIndex(seConnecter);
    ui->nomUtilisateur->setFocus();
    connexion::connexionMysql();
    QDate date = QDate::currentDate();
    int jour = date.day();
    int mois = date.month();
    int annee = date.year() - 18;
    date.setDate(annee,mois,jour);
    ui->creerNaissance->setMaximumDate(date);
    ui->recNaissance->setMaximumDate(date);
}

admin::~admin()
{
    delete ui;
}

void admin::on_btnSeConnecter_clicked()
{
    QString nomUtilisateur = ui->nomUtilisateur->text();
    QString mdp = ui->mdp->text();
    if(nomUtilisateur.isEmpty())
    {
        QMessageBox::critical(this,"Champ vide","Veuillez saisir le nom d'utilisateur !");
        ui->nomUtilisateur->setFocus();
        return;
    }
    if(mdp.isEmpty())
    {
        QMessageBox::critical(this,"Champ vide","Veuillez saisir votre mot de passe !");
        ui->nomUtilisateur->setFocus();
        return;
    }
    QSqlQuery query;
    query.prepare("select * from compte where nom_utilisateur = ?");
    query.addBindValue(nomUtilisateur);
    if(query.exec())
    {
        if(query.next())
        {
            query.prepare("select * from compte where nom_utilisateur = ? and mdp = ?");
            query.addBindValue(nomUtilisateur);
            query.addBindValue(mdp);
            if(query.exec())
            {
                if(query.next())
                {
                    admin::instance().nomAdministrateur = nomUtilisateur;
                    ui->nomUtilisateur->clear();
                    ui->mdp->clear();
                    acceuil * fenetre = new acceuil();
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
                    QMessageBox::critical(this,"Erreur","Le mot de passe que vous avez saisie est incorrecte !");
                    ui->mdp->setFocus();
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
            QMessageBox::critical(this,"Erreur","Le nom d'utilisateur que vous avez saisie est incorrecte !");
            ui->nomUtilisateur->setFocus();
            return;
        }
    }
    else
    {
        QMessageBox::critical(this,"Erreur","Impossible de se connecter à Mysql !");
        return;
    }

}


void admin::on_nomUtilisateur_editingFinished()
{
    ui->mdp->setFocus();
}


void admin::on_mdp_editingFinished()
{
    ui->mdp->clearFocus();
}


void admin::on_nomUtilisateur_textChanged(const QString &arg1)
{
    if(!ui->mdp->text().isEmpty() && !arg1.isEmpty() && ui->mdp->text().length() >= 6)
    {
        ui->btnSeConnecter->setEnabled(true);
    }
    else
    {
        ui->btnSeConnecter->setEnabled(false);
    }
}


void admin::on_mdp_textChanged(const QString &arg1)
{
    if(!ui->nomUtilisateur->text().isEmpty() && !arg1.isEmpty() && ui->mdp->text().length() >= 6)
    {
        ui->btnSeConnecter->setEnabled(true);
    }
    else
    {
        ui->btnSeConnecter->setEnabled(false);
    }
}

void admin::on_btnMdpOublier_clicked()
{
    ui->nomUtilisateur->clear();
    ui->mdp->clear();
    ui->contenuAdmin->setCurrentIndex(mdpOublier);
}


void admin::on_btnQuitter_clicked()
{
    QMessageBox message;
    message.setIcon(QMessageBox::Warning);
    message.setWindowTitle("Quitter");
    message.setText("Voulez-vous vraiment quitter ?");
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


void admin::on_btnSuivant1_clicked()
{
    QString nom = ui->creerNom->text();
    QString prenoms = ui->creerPrenoms->text();
    QString nomUtilisateur = ui->creerUtilisateur->text();
    QString cin = ui->creerCin->text();
    if(nom.isEmpty())
    {
        QMessageBox::critical(this,"Champ vide","Veuillez saisir votre nom !");
        ui->creerNom->setFocus();
        return;
    }
    if(prenoms.isEmpty())
    {
        QMessageBox::critical(this,"Champ vide","Veuillez saisir votre prénoms !");
        ui->creerPrenoms->setFocus();
        return;
    }
    if(nomUtilisateur.isEmpty())
    {
        QMessageBox::critical(this,"Champ vide","Veuillez saisir le nom d'utilisateur que vous allez utiliser !");
        ui->creerUtilisateur->setFocus();
        return;
    }

    QSqlQuery query;
    query.prepare("select * from compte where nom_utilisateur = ?");
    query.addBindValue(nomUtilisateur);
    if(query.exec())
    {
        if(query.next())
        {
            QMessageBox::critical(this,"Erreur","Le nom d'utilisateur que vous avez saisi est déjà utiliser !");
            ui->creerUtilisateur->setFocus();
            return;
        }
        else
        {
            if(cin.isEmpty())
            {
                QMessageBox::critical(this,"Champ vide","Veuillez saisir votre numero CIN !");
                ui->creerCin->setFocus();
                return;
            }
            if(cin.length() != 12)
            {
                QMessageBox::critical(this,"CIN invalide","Le numéro CIN doit être composer de 12 chiffres !");
                ui->creerCin->setFocus();
                return;
            }
        }
    }
    else
    {
        QMessageBox::critical(this,"Erreur","Impossible de se connecter à Mysql !");
        return;
    }
    query.prepare("select * from compte where numero_cin = ?");
    query.addBindValue(cin);
    if(query.exec())
    {
        if(query.next())
        {
            QMessageBox::critical(this,"CIN invalide","Le numero CIN que vous avez saisi est déjà utiliser !");
            ui->creerCin->setFocus();
            return;
        }
        else
        {
            ui->contenuAdmin->setCurrentIndex(2);
        }
    }
    else
    {
        QMessageBox::critical(this,"Erreur","Impossible de se connecter à Mysql !");
        return;
    }
}


void admin::on_creerNom_editingFinished()
{
    ui->creerPrenoms->setFocus();
}


void admin::on_creerPrenoms_editingFinished()
{
    ui->creerUtilisateur->setFocus();
}


void admin::on_creerUtilisateur_editingFinished()
{
    ui->creerNaissance->setFocus();
}


void admin::on_creerNaissance_editingFinished()
{
    ui->creerCin->setFocus();
}


void admin::on_creerCin_editingFinished()
{
    ui->creerCin->clearFocus();
}


void admin::on_creerNom_textChanged(const QString &arg1)
{
    ui->creerNom->setText(arg1.toUpper());
    QString nom = ui->creerNom->text();
    QString prenoms = ui->creerPrenoms->text();
    QString nomUtilisateur = ui->creerUtilisateur->text();
    QString cin = ui->creerCin->text();
    if(!nom.isEmpty() && ! prenoms.isEmpty() && !nomUtilisateur.isEmpty() && !cin.isEmpty() && cin.length() == 12)
    {
        ui->btnEnregistrer->setEnabled(true);
    }
    else
    {
        ui->btnEnregistrer->setEnabled(false);
    }
}


void admin::on_creerPrenoms_textChanged(const QString &arg1)
{
    QString nom = ui->creerNom->text();
    QString prenoms = ui->creerPrenoms->text();
    QString nomUtilisateur = ui->creerUtilisateur->text();
    QString cin = ui->creerCin->text();
    if(!nom.isEmpty() && ! prenoms.isEmpty() && !nomUtilisateur.isEmpty() && !cin.isEmpty() && cin.length() == 12)
    {
        ui->btnEnregistrer->setEnabled(true);
    }
    else
    {
        ui->btnEnregistrer->setEnabled(false);
    }
}


void admin::on_creerUtilisateur_textChanged(const QString &arg1)
{
    QString nom = ui->creerNom->text();
    QString prenoms = ui->creerPrenoms->text();
    QString nomUtilisateur = ui->creerUtilisateur->text();
    QString cin = ui->creerCin->text();
    if(!nom.isEmpty() && ! prenoms.isEmpty() && !nomUtilisateur.isEmpty() && !cin.isEmpty() && cin.length() == 12)
    {
        ui->btnEnregistrer->setEnabled(true);
    }
    else
    {
        ui->btnEnregistrer->setEnabled(false);
    }
}


void admin::on_creerNaissance_userDateChanged(const QDate &date)
{
    QString nom = ui->creerNom->text();
    QString prenoms = ui->creerPrenoms->text();
    QString nomUtilisateur = ui->creerUtilisateur->text();
    QString cin = ui->creerCin->text();
    if(!nom.isEmpty() && ! prenoms.isEmpty() && !nomUtilisateur.isEmpty() && !cin.isEmpty() && cin.length() == 12)
    {
        ui->btnEnregistrer->setEnabled(true);
    }
    else
    {
        ui->btnEnregistrer->setEnabled(false);
    }
}


void admin::on_creerCin_textChanged(const QString &arg1)
{
    QString nom = ui->creerNom->text();
    QString prenoms = ui->creerPrenoms->text();
    QString nomUtilisateur = ui->creerUtilisateur->text();
    QString cin = ui->creerCin->text();
    if(!nom.isEmpty() && ! prenoms.isEmpty() && !nomUtilisateur.isEmpty() && !cin.isEmpty() && cin.length() == 12)
    {
        ui->btnEnregistrer->setEnabled(true);
    }
    else
    {
        ui->btnEnregistrer->setEnabled(false);
    }
}


void admin::on_btnAnnuler1_clicked()
{
    QMessageBox message;
    message.setIcon(QMessageBox::Warning);
    message.setWindowTitle("Confirmation");
    message.setText("Voulez-vous vraiment annuler la création de votre compte ?");
    QPushButton *btnOui = message.addButton("Oui",QMessageBox::AcceptRole);
    QPushButton *btnNon = message.addButton("Non",QMessageBox::RejectRole);
    message.exec();
    if(message.clickedButton() == btnOui)
    {
        ui->creerNom->clear();
        ui->creerPrenoms->clear();
        ui->creerUtilisateur->clear();
        ui->creerCin->clear();
        ui->creerNouveauMdp->clear();
        ui->creerConfirmerMdp->clear();
        ui->contenuAdmin->setCurrentIndex(seConnecter);
    }
    else
    {
        return;
    }
}


void admin::on_btnEnregistrer_clicked()
{
    QString nom = ui->creerNom->text();
    QString prenoms = ui->creerPrenoms->text();
    QString nomUtilisateur = ui->creerUtilisateur->text();
    QString cin = ui->creerCin->text();
    QDate naissance = ui->creerNaissance->date();
    QString nouveauMdp = ui->creerNouveauMdp->text();
    QString confirmerMdp = ui->creerConfirmerMdp->text();

    if(nouveauMdp.isEmpty())
    {
        QMessageBox::critical(this,"Champ vide","Veuillez saisir votre nouveau mot de passe !");
        ui->creerNouveauMdp->setFocus();
        return;
    }
    if(confirmerMdp.isEmpty())
    {
        QMessageBox::critical(this,"Champ vide","Veuillez confirmer le nouveau mot de passe !");
        ui->creerConfirmerMdp->setFocus();
        return;
    }
    if(confirmerMdp.length() < 6)
    {
        QMessageBox::critical(this,"Mot de passe invalide","Le mot de passe doit contenir au moin 06 caractères !");
        ui->creerConfirmerMdp->setFocus();
        return;
    }
    if(nouveauMdp != confirmerMdp)
    {
        QMessageBox::critical(this,"Champ vide","Les mots de passe que vous avez saisie sont différents !");
        ui->creerConfirmerMdp->setFocus();
        return;
    }

    QSqlQuery query;
    query.prepare("insert into compte (nom,prenoms,nom_utilisateur,date_naissance,numero_cin,mdp) values (?,?,?,?,?,?)");
    query.addBindValue(nom);
    query.addBindValue(prenoms);
    query.addBindValue(nomUtilisateur);
    query.addBindValue(naissance);
    query.addBindValue(cin);
    query.addBindValue(nouveauMdp);
    if(query.exec())
    {
        ui->creerNom->clear();
        ui->creerPrenoms->clear();
        ui->creerUtilisateur->clear();
        ui->creerCin->clear();
        ui->creerNouveauMdp->clear();
        ui->creerConfirmerMdp->clear();
        QMessageBox::information(this,"Création du compte réussie","Votre compte a été creer avec succès !");
        ui->contenuAdmin->setCurrentIndex(seConnecter);
    }
    else
    {
        QMessageBox::critical(this,"Erreur","Impossible de se connecter à Mysql !");
        return;
    }
}


void admin::on_creerNouveauMdp_editingFinished()
{
    ui->creerConfirmerMdp->setFocus();
}


void admin::on_creerConfirmerMdp_editingFinished()
{
    ui->creerConfirmerMdp->clearFocus();
}


void admin::on_creerNouveauMdp_textChanged(const QString &arg1)
{
    if(!arg1.isEmpty() && !ui->creerConfirmerMdp->text().isEmpty() && arg1 == ui->creerConfirmerMdp->text() && ui->creerNouveauMdp->text().length() >= 6)
    {
        ui->btnEnregistrer->setEnabled(true);
    }
    else
    {
        ui->btnEnregistrer->setEnabled(false);
    }
}


void admin::on_creerConfirmerMdp_textChanged(const QString &arg1)
{
    if(!arg1.isEmpty() && !ui->creerConfirmerMdp->text().isEmpty() && arg1 == ui->creerConfirmerMdp->text() && ui->creerNouveauMdp->text().length() >= 6)
    {
        ui->btnEnregistrer->setEnabled(true);
    }
    else
    {
        ui->btnEnregistrer->setEnabled(false);
    }
}


void admin::on_btnAnnuler2_clicked()
{
    QMessageBox message;
    message.setIcon(QMessageBox::Warning);
    message.setWindowTitle("Confirmation");
    message.setText("Voulez-vous vraiment annuler la création de votre compte ?");
    QPushButton *btnOui = message.addButton("Oui",QMessageBox::AcceptRole);
    QPushButton *btnNon = message.addButton("Non",QMessageBox::RejectRole);
    message.exec();
    if(message.clickedButton() == btnOui)
    {
        ui->creerNom->clear();
        ui->creerPrenoms->clear();
        ui->creerUtilisateur->clear();
        ui->creerCin->clear();
        ui->creerNouveauMdp->clear();
        ui->creerConfirmerMdp->clear();
        ui->contenuAdmin->setCurrentIndex(seConnecter);
    }
    else
    {
        return;
    }
}


void admin::on_btnRetour2_clicked()
{
    ui->contenuAdmin->setCurrentIndex(1);
}

void admin::on_btnCreerCompte_clicked()
{
    ui->contenuAdmin->setCurrentIndex(creeCompte);
}


void admin::on_contenuAdmin_currentChanged(int arg1)
{
    if(arg1 == seConnecter)
    {
        ui->nomUtilisateur->setFocus();
    }
    if(arg1 == creeCompte)
    {
        ui->creerNom->setFocus();
    }
    if(arg1 == 2)
    {
        ui->creerNouveauMdp->setFocus();
    }
    if(arg1 == mdpOublier)
    {
        ui->recNomUtilisateur->setFocus();
    }
    if(arg1 == 4)
    {
        ui->recNouveauMdp->setFocus();
    }
    if(arg1 != seConnecter)
    {
        ui->nomUtilisateur->clear();
        ui->mdp->clear();
    }
    if(arg1 != creeCompte && arg1 != 2)
    {
        ui->creerNom->clear();
        ui->creerPrenoms->clear();
        ui->creerUtilisateur->clear();
        ui->creerCin->clear();
        ui->creerNouveauMdp->clear();
        ui->creerConfirmerMdp->clear();
    }
    if(arg1 != mdpOublier && arg1 != 4)
    {
        ui->recNomUtilisateur->clear();
        ui->recCin->clear();
        ui->recNouveauMdp->clear();
        ui->recConfirmerMdp->clear();
    }
}

void admin::on_btnSuivant3_clicked()
{
    QString utilisateur = ui->recNomUtilisateur->text();
    QDate naissance = ui->recNaissance->date();
    QString cin = ui->recCin->text();
    QSqlQuery query;
    query.prepare("select * from compte where nom_utilisateur = ? and date_naissance = ? and numero_cin = ?");
    query.addBindValue(utilisateur);
    query.addBindValue(naissance);
    query.addBindValue(cin);
    if(query.exec())
    {
        if(query.next())
        {
            ui->contenuAdmin->setCurrentIndex(4);
        }
        else
        {
            QMessageBox::warning(this,"Erreur","Certains informations du compte sont incorrecte, impossible de faire la récupération !");
            return;
        }
    }
    else
    {
        QMessageBox::critical(this,"Erreur","Impossible de se connecter à Mysql !");
        return;
    }
}


void admin::on_recNomUtilisateur_editingFinished()
{
    ui->recNaissance->setFocus();
}


void admin::on_recNaissance_editingFinished()
{
    ui->recCin->setFocus();
}


void admin::on_recCin_editingFinished()
{
    ui->recCin->clearFocus();
}


void admin::on_recNomUtilisateur_textChanged(const QString &arg1)
{
    if(!ui->recNomUtilisateur->text().isEmpty() && !ui->recCin->text().isEmpty() && ui->recCin->text().length() == 12)
    {
        ui->btnSuivant3->setEnabled(true);
    }
    else
    {
        ui->btnSuivant3->setEnabled(false);
    }
}


void admin::on_recNaissance_userDateChanged(const QDate &date)
{
    if(!ui->recNomUtilisateur->text().isEmpty() && !ui->recCin->text().isEmpty() && ui->recCin->text().length() == 12)
    {
        ui->btnSuivant3->setEnabled(true);
    }
    else
    {
        ui->btnSuivant3->setEnabled(false);
    }
}


void admin::on_recCin_textChanged(const QString &arg1)
{
    if(!ui->recNomUtilisateur->text().isEmpty() && !ui->recCin->text().isEmpty() && ui->recCin->text().length() == 12)
    {
        ui->btnSuivant3->setEnabled(true);
    }
    else
    {
        ui->btnSuivant3->setEnabled(false);
    }
}


void admin::on_btnAnnuler3_clicked()
{
    QMessageBox message;
    message.setIcon(QMessageBox::Warning);
    message.setWindowTitle("Confirmation");
    message.setText("Voulez-vous vraiment annuler la récupération de votre compte ?");
    QPushButton *btnOui = message.addButton("Oui",QMessageBox::AcceptRole);
    QPushButton *btnNon = message.addButton("Non",QMessageBox::RejectRole);
    message.exec();
    if(message.clickedButton() == btnOui)
    {
        ui->contenuAdmin->setCurrentIndex(seConnecter);
    }
    else
    {
        return;
    }
}


void admin::on_recNouveauMdp_editingFinished()
{
    ui->recConfirmerMdp->setFocus();
}


void admin::on_recConfirmerMdp_editingFinished()
{
    ui->recConfirmerMdp->clearFocus();
}


void admin::on_recNouveauMdp_textChanged(const QString &arg1)
{
    if(!arg1.isEmpty() && !ui->recConfirmerMdp->text().isEmpty())
    {
        ui->btnEnregistrerRec->setEnabled(true);
    }
    else
    {
        ui->btnEnregistrerRec->setEnabled(false);
    }
}


void admin::on_recConfirmerMdp_textChanged(const QString &arg1)
{
    if(!arg1.isEmpty() && !ui->recConfirmerMdp->text().isEmpty())
    {
        ui->btnEnregistrerRec->setEnabled(true);
    }
    else
    {
        ui->btnEnregistrerRec->setEnabled(false);
    }
}


void admin::on_btnEnregistrerRec_clicked()
{
    QString utilisateur = ui->recNomUtilisateur->text();
    QString mdp = ui->recNouveauMdp->text();
    if(mdp.length() < 6)
    {
        QMessageBox::critical(this,"Erreur","Le mot de passe doit contenir au moin 06 caractères !");
        ui->recNouveauMdp->setFocus();
        return;
    }
    if(mdp != ui->recConfirmerMdp->text())
    {
        QMessageBox::critical(this,"Erreur","Les mots de passe que vous avez saisi sont différents !");
        ui->creerConfirmerMdp->setFocus();
        return;
    }
    QSqlQuery query;
    query.prepare("update compte set mdp = ? where nom_utilisateur = ?");
    query.addBindValue(mdp);
    query.addBindValue(utilisateur);
    if(query.exec())
    {
        QMessageBox::information(this,"Récupération réussie","Votre compte a été récupérer avec succès !");
        ui->contenuAdmin->setCurrentIndex(seConnecter);
    }
    else
    {
        QMessageBox::critical(this,"Erreur","Impossible de se connécter à Mysql !");
        return;
    }
}


void admin::on_btnSeConnecter2_clicked()
{
    ui->contenuAdmin->setCurrentIndex(seConnecter);
}


void admin::on_btnSeConnecter3_clicked()
{
    ui->contenuAdmin->setCurrentIndex(seConnecter);
}


void admin::on_btnCreerCompte2_clicked()
{
    ui->contenuAdmin->setCurrentIndex(creeCompte);
}


void admin::on_btnCreerCompte3_clicked()
{
    ui->contenuAdmin->setCurrentIndex(creeCompte);
}


void admin::on_btnRetour4_clicked()
{
    ui->contenuAdmin->setCurrentIndex(3);
}


void admin::on_btnAnnuler4_clicked()
{
    QMessageBox message;
    message.setIcon(QMessageBox::Warning);
    message.setWindowTitle("Confirmation");
    message.setText("Voulez-vous vraiment annuler la récupération de votre compte ?");
    QPushButton *btnOui = message.addButton("Oui",QMessageBox::AcceptRole);
    QPushButton *btnNon = message.addButton("Non",QMessageBox::RejectRole);
    message.exec();
    if(message.clickedButton() == btnOui)
    {
        ui->contenuAdmin->setCurrentIndex(seConnecter);
    }
    else
    {
        return;
    }
}



void admin::on_btnVoirMdp_clicked()
{
    if (ui->mdp->echoMode() == QLineEdit::Password) {
        ui->mdp->setEchoMode(QLineEdit::Normal);
        ui->btnVoirMdp->setIcon(QIcon(":/icons/cacher.svg"));
    } else {
        ui->mdp->setEchoMode(QLineEdit::Password);
        ui->btnVoirMdp->setIcon(QIcon(":/icons/voir.svg"));
    }
}


void admin::on_btnNouveauMdp_clicked()
{
    if (ui->creerNouveauMdp->echoMode() == QLineEdit::Password) {
        ui->creerNouveauMdp->setEchoMode(QLineEdit::Normal);
        ui->btnNouveauMdp->setIcon(QIcon(":/icons/cacher.svg"));
    } else {
        ui->creerNouveauMdp->setEchoMode(QLineEdit::Password);
        ui->btnNouveauMdp->setIcon(QIcon(":/icons/voir.svg"));
    }
}


void admin::on_btnConfirmerMdp_clicked()
{
    if (ui->creerConfirmerMdp->echoMode() == QLineEdit::Password) {
        ui->creerConfirmerMdp->setEchoMode(QLineEdit::Normal);
        ui->btnConfirmerMdp->setIcon(QIcon(":/icons/cacher.svg"));
    } else {
        ui->creerConfirmerMdp->setEchoMode(QLineEdit::Password);
        ui->btnConfirmerMdp->setIcon(QIcon(":/icons/voir.svg"));
    }
}


void admin::on_btnRecNouveauMdp_clicked()
{
    if (ui->recNouveauMdp->echoMode() == QLineEdit::Password) {
        ui->recNouveauMdp->setEchoMode(QLineEdit::Normal);
        ui->btnRecNouveauMdp->setIcon(QIcon(":/icons/cacher.svg"));
    } else {
        ui->recNouveauMdp->setEchoMode(QLineEdit::Password);
        ui->btnRecNouveauMdp->setIcon(QIcon(":/icons/voir.svg"));
    }
}


void admin::on_btnRecConfirmerMdp_clicked()
{
    if (ui->recConfirmerMdp->echoMode() == QLineEdit::Password) {
        ui->recConfirmerMdp->setEchoMode(QLineEdit::Normal);
        ui->btnRecConfirmerMdp->setIcon(QIcon(":/icons/cacher.svg"));
    } else {
        ui->recConfirmerMdp->setEchoMode(QLineEdit::Password);
        ui->btnRecConfirmerMdp->setIcon(QIcon(":/icons/voir.svg"));
    }
}

