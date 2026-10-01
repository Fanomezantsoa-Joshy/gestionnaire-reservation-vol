#ifndef AVION_H
#define AVION_H

#include <QMainWindow>

namespace Ui {
class avion;
}

class avion : public QMainWindow
{
    Q_OBJECT

public:
    explicit avion(QWidget *parent = nullptr);
    ~avion();
    void afficherListeAvion();
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
    int ajoutAvion = 0;
    int modAvionForm = 2;
    int listeAvion = 4;
    int modAvion = 5;
    int supAvion = 6;

private slots:
    void on_menuAcceuil_clicked();

    void on_menuReservation_clicked();

    void on_menuPassager_clicked();

    void on_menuVol_clicked();

    void on_menuAvion_clicked();

    void on_menuCompagnieAerienne_clicked();

    void on_menuQuitter_clicked();

    void on_btnEnregistrer_clicked();

    void on_btnEnregistrerMod_clicked();

    void on_btnSupprimer_clicked();

    void on_btnModifier_clicked();

    void on_btnInserer_clicked();

    void on_btnMod_clicked();

    void on_btnSup_clicked();

    void on_immatriculation_editingFinished();

    void on_modele_editingFinished();

    void on_place_editingFinished();

    void on_modImmatriculation_editingFinished();

    void on_modModele_editingFinished();

    void on_modPlace_editingFinished();

    void on_contenuAvion_currentChanged(int arg1);

    void on_menuCreer_clicked();

    void on_menuModifier_clicked();

    void on_menuSupprimer_clicked();

    void on_menuListe_clicked();

    void on_rechercheAvion_textChanged(const QString &arg1);

    void on_listeAvion_clicked(const QModelIndex &index);

    void on_modListeAvion_clicked(const QModelIndex &index);

    void on_supListeAvion_clicked(const QModelIndex &index);

    void on_modRechercheAvion_textChanged(const QString &arg1);

    void on_supRechercheAvion_textChanged(const QString &arg1);

    void on_immatriculation_textChanged(const QString &arg1);

    void on_modele_textChanged(const QString &arg1);

    void on_place_textChanged(const QString &arg1);

    void on_modImmatriculation_textEdited(const QString &arg1);

    void on_modModele_textEdited(const QString &arg1);

    void on_modPlace_textEdited(const QString &arg1);

    void on_modImmatriculation_textChanged(const QString &arg1);

    void on_rechercheCompagnie_textChanged(const QString &arg1);

    void on_modRechercheCompagnie_textChanged(const QString &arg1);

    void on_btnSuivant0_clicked();

    void on_btnRetour1_clicked();

    void on_listeCompagnie_clicked(const QModelIndex &index);

    void on_btnSuivant2_clicked();

    void on_btnretour3_clicked();

    void on_modListeCompagnie_clicked(const QModelIndex &index);

    void on_btnAnnuler0_clicked();

    void on_btnAnnuler1_clicked();

    void on_btnAnnulerMod2_clicked();

    void on_btnAnnulerMod3_clicked();

    void on_menuSeDeconnecter_clicked();

private:
    Ui::avion *ui;
};

#endif // AVION_H
