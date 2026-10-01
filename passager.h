#ifndef PASSAGER_H
#define PASSAGER_H

#include <QMainWindow>

namespace Ui {
class passager;
}

class passager : public QMainWindow
{
    Q_OBJECT

public:
    explicit passager(QWidget *parent = nullptr);
    ~passager();
    void afficherListePassager();
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

    int modPassagerForm = 0;
    int listePassager = 1;
    int modPassager = 2;
    int supPassager = 3;

private slots:
    void on_menuAcceuil_clicked();

    void on_menuReservation_clicked();

    void on_menuPassager_clicked();

    void on_menuVol_clicked();

    void on_menuAvion_clicked();

    void on_menuCompagnieAerienne_clicked();

    void on_menuQuitter_clicked();

    void on_btnListeMod_clicked();

    void on_btnSupprimer_clicked();

    void on_btnAnnulerMod_clicked();

    void on_btnEnregistrerMod_clicked();

    void on_btnModifier_clicked();

    void on_btnMod_clicked();

    void on_btnInserer_clicked();

    void on_btnSup_clicked();

    void on_contenuPassager_currentChanged(int arg1);

    void on_modNom_editingFinished();

    void on_modPrenoms_editingFinished();

    void on_modNaissance_editingFinished();

    void on_modPasseport_editingFinished();

    void on_menuCreer_clicked();

    void on_menuModifier_clicked();

    void on_menuSupprimer_clicked();

    void on_menuListe_clicked();

    void on_recherchePassager_textChanged(const QString &arg1);

    void on_modRecherchePassager_textChanged(const QString &arg1);

    void on_supRecherchePassager_textChanged(const QString &arg1);

    void on_listePassager_clicked(const QModelIndex &index);

    void on_modListePassager_clicked(const QModelIndex &index);

    void on_supListePassager_clicked(const QModelIndex &index);

    void on_modNom_textChanged(const QString &arg1);

    void on_modNom_textEdited(const QString &arg1);

    void on_modPrenoms_textEdited(const QString &arg1);

    void on_modNaissance_userDateChanged(const QDate &date);

    void on_modPasseport_textEdited(const QString &arg1);

    void on_menuSeDeconnecter_clicked();

private:
    Ui::passager *ui;
};

#endif // PASSAGER_H
