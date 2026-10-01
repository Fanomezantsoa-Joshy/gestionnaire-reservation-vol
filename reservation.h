#ifndef RESERVATION_H
#define RESERVATION_H

#include <QMainWindow>

namespace Ui {
class reservation;
}

class reservation : public QMainWindow
{
    Q_OBJECT

public:
    explicit reservation(QWidget *parent = nullptr);
    ~reservation();
    void afficherListe();
    QString style = "QPushButton {"
                    "border : none;"
                    "border-bottom : 2px solid #bef3f1;"
                    "border-top : 2px solid #bef3f1;"
                    "background-color : lightseagreen;"
                    "color : white;"
                    "font-size : 14px;}"
                    "QPushButton:hover {"
                    "background-color : #1fada6;}";

    QString styleFocus = "border : none;"
                         "border-bottom : 3px solid white;"
                         "border-top : 2px solid #bef3f1;"
                         "background-color : #1b9891;"
                         "color : white;"
                         "font-size : 14px;";

    int creerReservation = 0;
    int modReservationForm = 5;
    int listeParAvion = 10;
    int listeParDate = 11;
    int modReservation = 12;
    int supReservation = 13;

private slots:
    void on_menuAcceuil_clicked();

    void on_menuReservation_clicked();

    void on_menuPassager_clicked();

    void on_menuVol_clicked();

    void on_menuAvion_clicked();

    void on_menuCompagnieAerienne_clicked();

    void on_menuQuitter_clicked();

    void on_btnAnnulerReservation0_clicked();

    void on_btnSuivant0_clicked();

    void on_btnretour1_clicked();

    void on_btnAnnulerReservation1_clicked();

    void on_btnSuivant1_clicked();

    void on_btnretour2_clicked();

    void on_btnAnnulerReservation2_clicked();

    void on_btnSuivant2_clicked();

    void on_btnretour3_clicked();

    void on_btnAnnulerReservation3_clicked();

    void on_btnSuivant3_clicked();

    void on_btnretour4_clicked();

    void on_btnAnnulerReservation4_clicked();

    void on_btnEnregistrerReservation_clicked();

    void on_btnAnnulerMod5_clicked();

    void on_btnSuivant5_clicked();

    void on_btnretour6_clicked();

    void on_btnAnnulerMod6_clicked();

    void on_btnSuivant6_clicked();

    void on_btnRetour7_clicked();

    void on_btnAnnulerMod7_clicked();

    void on_btnSuivant7_clicked();

    void on_btnretour8_clicked();

    void on_btnAnnulerMod8_clicked();

    void on_btnSuivant8_clicked();

    void on_btnretour9_clicked();

    void on_btnAnnulerMod9_clicked();

    void on_btnEnregistrerMod_clicked();

    void on_btnDetail1_clicked();

    void on_btnSupprimer1_clicked();

    void on_btnModifier1_clicked();

    void on_btnInserer1_clicked();

    void on_btnDetail2_clicked();

    void on_btnSupprimer2_clicked();

    void on_btnModifier2_clicked();

    void on_btnInserer2_clicked();

    void on_btnMod_clicked();

    void on_btnSup_clicked();

    void on_contenuReservation_currentChanged(int arg1);

    void on_nomPassager_editingFinished();

    void on_prenoms_editingFinished();

    void on_naissance_editingFinished();

    void on_passeport_editingFinished();

    void on_modNomPassager_editingFinished();

    void on_modPrenoms_editingFinished();

    void on_modNaissance_editingFinished();

    void on_modPasseport_editingFinished();

    void on_menuCreer_clicked();

    void on_menuModifier_clicked();

    void on_menuSupprimer_clicked();

    void on_menuListeAvion_clicked();

    void on_menuParDate_clicked();

    void on_rechercheVol_textChanged(const QString &arg1);

    void on_modRechercheVol_textChanged(const QString &arg1);

    void on_rechercheDate_textChanged(const QString &arg1);

    void on_modRechercheDate_textChanged(const QString &arg1);

    void on_supRechercheDate_textChanged(const QString &arg1);

    void on_listeReservationParDate_clicked(const QModelIndex &index);

    void on_modListeDate_clicked(const QModelIndex &index);

    void on_supListeDate_clicked(const QModelIndex &index);

    void on_modListeVol_clicked(const QModelIndex &index);

    void on_listeVol_clicked(const QModelIndex &index);

    void on_listeReservationParAvion_clicked(const QModelIndex &index);

    void on_rechercheAvion_textChanged(const QString &arg1);

    void on_nomPassager_textChanged(const QString &arg1);

    void on_passeport_textChanged(const QString &arg1);

    void on_modNomPassager_textEdited(const QString &arg1);

    void on_modPasseport_textEdited(const QString &arg1);

    void on_prenoms_textChanged(const QString &arg1);

    void on_modPrenoms_textEdited(const QString &arg1);

    void on_menuSeDeconnecter_clicked();

private:
    Ui::reservation *ui;
};

#endif // RESERVATION_H
