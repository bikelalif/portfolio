#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QListWidget>
#include <QList>
#include <QTranslator>
#include "patient.h"
#include "medecin.h"
#include "clinique.h"
#include "allergie.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/**
 * @class MainWindow
 * @brief Fenêtre principale de l'application de gestion médicale
 * @details Cette classe hérite de QMainWindow et implémente l'interface utilisateur principale
 *          du système de gestion de fiches patients (SGM). Elle gère les opérations CRUD
 *          (Create, Read, Update, Delete) pour les patients, médecins, cliniques et allergies,
 *          ainsi que l'import/export de données au format JSON.
 * 
 * @author Bilal Kefif et Soni Diedhiou
 * @version 1.0
 * @date 2024
 * 
 * Fonctionnalités principales:
 * - Gestion complète des patients avec leurs allergies et hospitalisations
 * - Gestion des médecins et de leurs spécialisations
 * - Gestion des cliniques et des relations médecin-clinique
 * - Gestion des allergies
 * - Recherche et filtrage en temps réel
 * - Import/Export JSON avec préservation des relations bidirectionnelles
 * - Interface graphique avec bulles personnalisées pour chaque entité
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructeur de la fenêtre principale
     * @param parent Widget parent (nullptr par défaut)
     */
    MainWindow(QWidget *parent = nullptr);
    
    /**
     * @brief Destructeur de la fenêtre principale
     * @details Libère la mémoire allouée pour l'interface et les entités
     */
    ~MainWindow();

private slots:
    // ========== SLOTS GESTION PATIENTS ==========
    
    /**
     * @brief Affiche le formulaire d'ajout d'un nouveau patient
     * @details Ouvre une boîte de dialogue avec les champs nécessaires pour créer un patient
     */
    void formulaireAjoutPatient();
    
    /**
     * @brief Gère le clic sur un patient dans la liste
     * @param item L'élément de liste cliqué
     * @details Affiche la fiche détaillée du patient avec options de modification/suppression
     */
    void onPatientClicked(QListWidgetItem* item);
    
    /**
     * @brief Affiche le formulaire de modification d'un patient
     * @param p Pointeur vers le patient à modifier
     */
    void ModifierPatient(Patient *p);
    
    /**
     * @brief Supprime un patient de la liste
     * @param p Pointeur vers le patient à supprimer
     * @param index Index du patient dans la liste
     * @details Libère la mémoire et met à jour l'affichage
     */
    void SupprimerPatient(Patient *p, int index);
    
    /**
     * @brief Recherche des patients selon un texte
     * @param texte Texte de recherche (nom, prénom, email, etc.)
     * @details Filtre la liste en temps réel
     */
    void rechercherPatient(const QString& texte);

    // ========== SLOTS GESTION MEDECINS ==========
    
    /**
     * @brief Affiche le formulaire d'ajout d'un nouveau médecin
     */
    void formulaireAjoutMedecin();
    
    /**
     * @brief Gère le clic sur un médecin dans la liste
     * @param item L'élément de liste cliqué
     */
    void onMedecinClicked(QListWidgetItem* item);
    
    /**
     * @brief Affiche le formulaire de modification d'un médecin
     * @param m Pointeur vers le médecin à modifier
     */
    void ModifierMedecin(Medecin *m);
    
    /**
     * @brief Supprime un médecin de la liste
     * @param m Pointeur vers le médecin à supprimer
     * @param index Index du médecin dans la liste
     */
    void SupprimerMedecin(Medecin *m, int index);
    
    /**
     * @brief Recherche des médecins selon un texte
     * @param texte Texte de recherche
     */
    void rechercherMedecin(const QString& texte);

    // ========== SLOTS GESTION CLINIQUES ==========
    
    /**
     * @brief Affiche le formulaire d'ajout d'une nouvelle clinique
     */
    void formulaireAjoutClinique();
    
    /**
     * @brief Gère le clic sur une clinique dans la liste
     * @param item L'élément de liste cliqué
     */
    void onCliniqueClicked(QListWidgetItem* item);
    
    /**
     * @brief Affiche le formulaire de modification d'une clinique
     * @param c Pointeur vers la clinique à modifier
     */
    void ModifierClinique(Clinique *c);
    
    /**
     * @brief Supprime une clinique de la liste
     * @param c Pointeur vers la clinique à supprimer
     * @param index Index de la clinique dans la liste
     */
    void SupprimerClinique(Clinique *c, int index);
    
    /**
     * @brief Recherche des cliniques selon un texte
     * @param texte Texte de recherche
     */
    void rechercherClinique(const QString& texte);

    // ========== SLOTS GESTION ALLERGIES ==========
    
    /**
     * @brief Affiche le formulaire d'ajout d'une nouvelle allergie
     */
    void formulaireAjoutAllergie();
    
    /**
     * @brief Gère le clic sur une allergie dans la liste
     * @param item L'élément de liste cliqué
     */
    void onAllergieClicked(QListWidgetItem* item);
    
    /**
     * @brief Affiche le formulaire de modification d'une allergie
     * @param index Index de l'allergie dans la liste
     */
    void ModifierAllergie(int index);
    
    /**
     * @brief Supprime une allergie de la liste
     * @param index Index de l'allergie dans la liste
     */
    void SupprimerAllergie(int index);
    
    /**
     * @brief Recherche des allergies selon un texte
     * @param texte Texte de recherche
     */
    void rechercherAllergie(const QString& texte);
    
    // ========== SLOTS IMPORT/EXPORT ==========
    
    /**
     * @brief Exporte toutes les données au format JSON
     * @details Sauvegarde patients, médecins, cliniques, allergies et leurs relations
     */
    void exporterDonnees();
    
    /**
     * @brief Importe des données depuis un fichier JSON
     * @details Restaure toutes les entités et leurs relations bidirectionnelles
     */
    void importerDonnees();
    
    // ========== SLOT À PROPOS ==========
    
    /**
     * @brief Affiche la boîte de dialogue "À propos"
     * @details Présente l'application, la version et les auteurs
     */
    void afficherAPropos();
    
    // ========== SLOTS LANGUE ==========
    
    /**
     * @brief Change la langue de l'application en français
     */
    void changerLangueFrancais();
    
    /**
     * @brief Change la langue de l'application en anglais
     */
    void changerLangueAnglais();

private:
    Ui::MainWindow *ui;  ///< Interface utilisateur générée par Qt Designer
    QTranslator translator;  ///< Traducteur pour le support multilingue
    
    // ========== COLLECTIONS DE DONNÉES ==========
    
    QList<Patient*> patients;      ///< Liste des patients (allocation dynamique)
    QList<Medecin*> medecins;      ///< Liste des médecins (allocation dynamique)
    QList<Clinique*> cliniques;    ///< Liste des cliniques (allocation dynamique)
    QList<Allergie> allergies;     ///< Liste des allergies (objets valeur)

    // ========== MÉTHODES PRIVÉES - PATIENTS ==========
    
    /**
     * @brief Rafraîchit l'affichage de la liste des patients
     */
    void afficherPatients();
    
    /**
     * @brief Crée un widget personnalisé (bulle) pour afficher un patient
     * @param p Pointeur vers le patient
     * @return Widget personnalisé contenant les infos du patient
     */
    QWidget* creerBullePatient(Patient* p);
    
    /**
     * @brief Ajoute un patient à la collection
     * @param p Pointeur vers le patient à ajouter
     */
    void ajouterPatient(Patient* p);

    // ========== MÉTHODES PRIVÉES - MEDECINS ==========
    
    /**
     * @brief Rafraîchit l'affichage de la liste des médecins
     */
    void afficherMedecins();
    
    /**
     * @brief Crée un widget personnalisé pour afficher un médecin
     * @param m Pointeur vers le médecin
     * @return Widget personnalisé
     */
    QWidget* creerBulleMedecin(Medecin* m);
    
    /**
     * @brief Ajoute un médecin à la collection
     * @param m Pointeur vers le médecin à ajouter
     */
    void ajouterMedecin(Medecin* m);

    // ========== MÉTHODES PRIVÉES - CLINIQUES ==========
    
    /**
     * @brief Rafraîchit l'affichage de la liste des cliniques
     */
    void afficherCliniques();
    
    /**
     * @brief Crée un widget personnalisé pour afficher une clinique
     * @param c Pointeur vers la clinique
     * @return Widget personnalisé
     */
    QWidget* creerBulleClinique(Clinique* c);
    
    /**
     * @brief Ajoute une clinique à la collection
     * @param c Pointeur vers la clinique à ajouter
     */
    void ajouterClinique(Clinique* c);

    // ========== MÉTHODES PRIVÉES - ALLERGIES ==========
    
    /**
     * @brief Rafraîchit l'affichage de la liste des allergies
     */
    void afficherAllergies();
    
    /**
     * @brief Crée un widget personnalisé pour afficher une allergie
     * @param a Pointeur vers l'allergie
     * @return Widget personnalisé
     */
    QWidget* creerBulleAllergie(Allergie* a);
    
    /**
     * @brief Ajoute une allergie à la collection
     * @param a Référence vers l'allergie à ajouter
     */
    void ajouterAllergie(const Allergie& a);
    
    // ========== MÉTHODES DE FILTRAGE ==========
    
    /**
     * @brief Filtre une liste de médecins selon un texte
     * @param liste Widget de liste à filtrer
     * @param texte Texte de recherche
     */
    void filtrerListeMedecins(QListWidget* liste, const QString& texte);
    
    /**
     * @brief Filtre une liste de cliniques selon un texte
     * @param liste Widget de liste à filtrer
     * @param texte Texte de recherche
     */
    void filtrerListeCliniques(QListWidget* liste, const QString& texte);
    
    /**
     * @brief Filtre une liste d'allergies selon un texte
     * @param liste Widget de liste à filtrer
     * @param texte Texte de recherche
     */
    void filtrerListeAllergies(QListWidget* liste, const QString& texte);
};
#endif // MAINWINDOW_H
