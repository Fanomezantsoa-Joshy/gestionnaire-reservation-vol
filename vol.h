#ifndef VOL_H
#define VOL_H

#include <QMainWindow>

namespace Ui {
class vol;
}

class vol : public QMainWindow
{
    Q_OBJECT

public:
    explicit vol(QWidget *parent = nullptr);
    ~vol();
    void afficherListe();
    void infoListe();
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

    int creerVol = 0;
    int modVolForm = 4;
    int listeVol = 8;
    int modVol = 9;
    int supVol = 10;

private slots:
    void on_menuAcceuil_clicked();

    void on_menuReservation_clicked();

    void on_menuPassager_clicked();

    void on_menuVol_clicked();

    void on_menuAvion_clicked();

    void on_menuCompagnieAerienne_clicked();

    void on_menuQuitter_clicked();

    void on_btnAnnuler0_clicked();

    void on_btnSuivant0_clicked();

    void on_btnretour1_clicked();

    void on_btnAnnuler1_clicked();

    void on_btnSuivant1_clicked();

    void on_btnretour2_clicked();

    void on_btnAnnuler2_clicked();

    void on_btnSuivant2_clicked();

    void on_btnretour3_clicked();

    void on_btnAnnuler3_clicked();

    void on_btnEnregistrerVol_clicked();

    void on_btnAnnulerMod4_clicked();

    void on_btnSuivant4_clicked();

    void on_btnretour5_clicked();

    void on_btnAnnulerMod5_clicked();

    void on_btnSuivant5_clicked();

    void on_btnretour6_clicked();

    void on_btnAnnulerMod6_clicked();

    void on_btnSuivant6_clicked();

    void on_btnretour7_clicked();

    void on_btnAnnulerMod7_clicked();

    void on_btnEnregistrerMod_clicked();

    void on_btnSupprimer_clicked();

    void on_btnModifier_clicked();

    void on_btnInserer_clicked();

    void on_btnMod_clicked();

    void on_btnSup_clicked();

    void on_contenuVol_currentChanged(int arg1);

    void on_numeroVol_editingFinished();

    void on_aeroportArriver_editingFinished();

    void on_dateDepart_editingFinished();

    void on_heureDepart_editingFinished();

    void on_duree_editingFinished();

    void on_modNumeroVol_editingFinished();

    void on_modAeroportArriver_editingFinished();

    void on_modDateDepart_editingFinished();

    void on_modHeureDepart_editingFinished();

    void on_modDuree_editingFinished();

    void on_menuCreer_clicked();

    void on_menuModifier_clicked();

    void on_menuSupprimer_clicked();

    void on_menuListe_clicked();

    void on_rechercheCompagnie_textChanged(const QString &arg1);

    void on_modRechercheCompagnie_textChanged(const QString &arg1);

    void on_rechercheAvion_textChanged(const QString &arg1);

    void on_modRechercheAvion_textChanged(const QString &arg1);

    void on_rechercheVol_textChanged(const QString &arg1);

    void on_modRechercheVol_textChanged(const QString &arg1);

    void on_supRechercheVol_textChanged(const QString &arg1);

    void on_listeVol_clicked(const QModelIndex &index);

    void on_modListeVol_clicked(const QModelIndex &index);

    void on_supListeVol_clicked(const QModelIndex &index);

    void on_listeCompagnie_clicked(const QModelIndex &index);

    void on_listeAvion_clicked(const QModelIndex &index);

    void on_modListeCompagnie_clicked(const QModelIndex &index);

    void on_modListeAvion_clicked(const QModelIndex &index);

    void on_modDateDepart_userDateChanged(const QDate &date);


    void on_modAeroportArriver_textEdited(const QString &arg1);

    void on_numeroVol_textChanged(const QString &arg1);

    void on_modNumeroVol_textEdited(const QString &arg1);

    void on_aeroportArriver_textChanged(const QString &arg1);

    void on_menuSeDeconnecter_clicked();

private:
    Ui::vol *ui;
};

#endif // VOL_H
