#ifndef ACCEUIL_H
#define ACCEUIL_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class acceuil;
}
QT_END_NAMESPACE

class acceuil : public QMainWindow
{
    Q_OBJECT

public:
    acceuil(QWidget *parent = nullptr);
    ~acceuil();
    int pageStastistique = 0;
    int monCompte = 1;
    int modCompte = 2;
    int historique = 3;
    int aPropos = 4;
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
    void afficherHistorique();
    void afficherStatistiques();
    void infoCompte();

    QString immatriculationAvion;
    QString identifiantCompagnie;
    QString identifiantPassager;
    QString modPasseport;
    QString numeroReservation;
    QString numeroVol;

    static acceuil& instance() {
        static acceuil instance;
        return instance;
    }

    GlobalData(const acceuil&) = delete;
    acceuil& operator=(const acceuil&) = delete;

    QString compagnieAvion;
    int ligneAvion;
    int ligneCompagnie;
    int ligneVol;
    int modLigneVol;
    QString modCompagnie;
    QString modAvion;
    QString compagnieAerienne;

private slots:
    void on_menuAcceuil_clicked();

    void on_menuReservation_clicked();

    void on_menuPassager_clicked();

    void on_menuVol_clicked();

    void on_menuAvion_clicked();

    void on_menuCompagnieAerienne_clicked();

    void on_menuQuitter_clicked();

    void on_menuSeDeconnecter_clicked();

    void on_contenuAcceuil_currentChanged(int arg1);

    void on_rechercheHistorique_textChanged(const QString &arg1);

    void on_menuMonCompte_clicked();

    void on_btnEnregistrerMod_clicked();

    void on_btnSupprimer_clicked();

    void on_menuStatistique_clicked();

    void on_menuHistorique_clicked();

    void on_menuAPropos_clicked();

    void on_btnHistorique_clicked();

    void on_btnModifier_clicked();

    void on_btnAnnulerMod_clicked();

private:
    Ui::acceuil *ui;
};
#endif // ACCEUIL_H
