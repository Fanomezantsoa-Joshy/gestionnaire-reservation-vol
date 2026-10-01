#ifndef ADMIN_H
#define ADMIN_H

#include <QMainWindow>

namespace Ui {
class admin;
}

class admin : public QMainWindow
{
    Q_OBJECT

public:
    explicit admin(QWidget *parent = nullptr);
    ~admin();
    int seConnecter = 0;
    int creeCompte = 1;
    int mdpOublier = 3;

    static admin& instance() {
        static admin instance;
        return instance;
    }

    GlobalData(const admin&) = delete;
    admin& operator=(const admin&) = delete;
    QString nomAdministrateur;

private slots:
    void on_btnSeConnecter_clicked();

    void on_nomUtilisateur_editingFinished();

    void on_mdp_editingFinished();

    void on_nomUtilisateur_textChanged(const QString &arg1);

    void on_mdp_textChanged(const QString &arg1);

    void on_btnMdpOublier_clicked();

    void on_btnQuitter_clicked();

    void on_btnSuivant1_clicked();

    void on_creerNom_editingFinished();

    void on_creerPrenoms_editingFinished();

    void on_creerUtilisateur_editingFinished();

    void on_creerNaissance_editingFinished();

    void on_creerCin_editingFinished();

    void on_creerNom_textChanged(const QString &arg1);

    void on_creerPrenoms_textChanged(const QString &arg1);

    void on_creerUtilisateur_textChanged(const QString &arg1);

    void on_creerNaissance_userDateChanged(const QDate &date);

    void on_creerCin_textChanged(const QString &arg1);

    void on_btnAnnuler1_clicked();

    void on_btnEnregistrer_clicked();

    void on_creerNouveauMdp_editingFinished();

    void on_creerConfirmerMdp_editingFinished();

    void on_creerNouveauMdp_textChanged(const QString &arg1);

    void on_creerConfirmerMdp_textChanged(const QString &arg1);

    void on_btnAnnuler2_clicked();

    void on_btnRetour2_clicked();

    void on_btnCreerCompte_clicked();

    void on_contenuAdmin_currentChanged(int arg1);

    void on_btnSuivant3_clicked();

    void on_recNomUtilisateur_editingFinished();

    void on_recNaissance_editingFinished();

    void on_recCin_editingFinished();

    void on_recNomUtilisateur_textChanged(const QString &arg1);

    void on_recNaissance_userDateChanged(const QDate &date);

    void on_recCin_textChanged(const QString &arg1);

    void on_btnAnnuler3_clicked();

    void on_recNouveauMdp_editingFinished();

    void on_recConfirmerMdp_editingFinished();

    void on_recNouveauMdp_textChanged(const QString &arg1);

    void on_recConfirmerMdp_textChanged(const QString &arg1);

    void on_btnEnregistrerRec_clicked();

    void on_btnSeConnecter2_clicked();

    void on_btnSeConnecter3_clicked();

    void on_btnCreerCompte2_clicked();

    void on_btnCreerCompte3_clicked();

    void on_btnRetour4_clicked();

    void on_btnAnnuler4_clicked();

    void on_btnVoirMdp_clicked();

    void on_btnNouveauMdp_clicked();

    void on_btnConfirmerMdp_clicked();

    void on_btnRecNouveauMdp_clicked();

    void on_btnRecConfirmerMdp_clicked();

private:
    Ui::admin *ui;
};

#endif // ADMIN_H
