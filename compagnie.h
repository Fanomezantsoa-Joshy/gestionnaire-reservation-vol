#ifndef COMPAGNIE_H
#define COMPAGNIE_H

#include <QMainWindow>

namespace Ui {
class compagnie;
}

class compagnie : public QMainWindow
{
    Q_OBJECT

public:
    explicit compagnie(QWidget *parent = nullptr);
    ~compagnie();
    void afficherListeCompagnie();
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

    int ajoutCompagnie = 0;
    int modCompagnieForm = 1;
    int listeCompagnie = 2;
    int modCompagnie = 3;
    int supCompagnie = 4;

private slots:
    void on_menuAcceuil_clicked();

    void on_menuReservation_clicked();

    void on_menuPassager_clicked();

    void on_menuVol_clicked();

    void on_menuAvion_clicked();

    void on_menuCompagnieAerienne_clicked();

    void on_menuQuitter_clicked();

    void on_btnSupprimer_clicked();

    void on_btnListe_clicked();

    void on_btnAnnuler_clicked();

    void on_btnEnregistrer_clicked();

    void on_btnListeMod_clicked();

    void on_btnAnnulerMod_clicked();

    void on_btnEnregistrerMod_clicked();

    void on_btnModifier_clicked();

    void on_btnInserer_clicked();

    void on_btnMod_clicked();

    void on_btnSup_clicked();

    void on_identifiant_editingFinished();

    void on_nom_editingFinished();

    void on_pays_editingFinished();

    void on_modIdentifiant_editingFinished();

    void on_modNom_editingFinished();

    void on_modPays_editingFinished();

    void on_contenuCompagnie_currentChanged(int arg1);

    void on_menuAjouter_clicked();

    void on_menuModifier_clicked();

    void on_menuSupprimer_clicked();

    void on_menuListe_clicked();

    void on_rechercheCompagnie_textChanged(const QString &arg1);

    void on_modRechercheCompagnie_textChanged(const QString &arg1);

    void on_supRechercheCompagnie_textChanged(const QString &arg1);

    void on_listeCompagnie_clicked(const QModelIndex &index);

    void on_supListeCompagnie_clicked(const QModelIndex &index);

    void on_modListeCompagnie_clicked(const QModelIndex &index);

    void on_identifiant_textChanged(const QString &arg1);

    void on_modIdentifiant_textChanged(const QString &arg1);

    void on_modPays_textChanged(const QString &arg1);

    void on_pays_textChanged(const QString &arg1);

    void on_nom_textChanged(const QString &arg1);

    void on_modIdentifiant_textEdited(const QString &arg1);

    void on_modNom_textEdited(const QString &arg1);

    void on_modPays_textEdited(const QString &arg1);

    void on_menuSeDeconnecter_clicked();

private:
    Ui::compagnie *ui;
};

#endif // COMPAGNIE_H
