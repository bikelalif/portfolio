#ifndef PATIENT_H
#define PATIENT_H

#include <QMainWindow>
#include <QString>
#include <QDate>
#include <QList>
#include "personne.h"
#include "allergie.h"

class Medecin;
class Clinique;

/**
 * @class Patient
 * @brief Classe représentant un patient du système de gestion médical
 * @details Hérite de Personne et gère les allergies, le médecin traitant et l'hospitalisation.
 *          Un patient peut avoir plusieurs allergies, un médecin traitant et être hospitalisé dans une clinique.
 */
class Patient : public Personne {
public:
    /**
     * @brief Constructeur de Patient
     * @param id Identifiant unique du patient
     * @param nom Nom de famille
     * @param prenom Prénom
     * @param date_naissance Date de naissance
     * @param adresse Adresse postale
     * @param sexe Sexe (M/F)
     * @param email Adresse email
     * @param telephone Numéro de téléphone
     */
    Patient(const QString& id, const QString& nom, const QString& prenom,
            const QDate& date_naissance, const QString& adresse,
            const QString& sexe, const QString& email, const QString& telephone);

    /**
     * @brief Ajoute une allergie à la fiche du patient
     * @param allergie L'allergie à ajouter
     */
    void ajouterAllergie(const Allergie& allergie);
    
    /**
     * @brief Retire une allergie de la fiche du patient
     * @param allergie L'allergie à retirer
     */
    void retirerAllergie(const Allergie& allergie);
    
    /**
     * @brief Efface toutes les allergies du patient
     */
    void clearAllergies();
    
    /**
     * @brief Récupère la liste des allergies du patient
     * @return Liste des allergies
     */
    QList<Allergie> getAllergies() const;

    /**
     * @brief Définit le médecin traitant du patient
     * @param medecin Pointeur vers le médecin traitant
     */
    void setMedecin(Medecin* medecin);
    
    /**
     * @brief Récupère le médecin traitant du patient
     * @return Pointeur vers le médecin traitant, nullptr si aucun
     */
    Medecin* getMedecin() const;

    /**
     * @brief Hospitalise le patient dans une clinique
     * @param clinique Pointeur vers la clinique d'hospitalisation
     */
    void setHospitalisation(Clinique* clinique);
    
    /**
     * @brief Termine l'hospitalisation du patient
     */
    void retirerHospitalisation();
    
    /**
     * @brief Récupère la clinique où le patient est hospitalisé
     * @return Pointeur vers la clinique, nullptr si pas hospitalisé
     */
    Clinique* getClinique() const;
    
    /**
     * @brief Vérifie si le patient est actuellement hospitalisé
     * @return true si hospitalisé, false sinon
     */
    bool estHospitalise() const;

    /**
     * @brief Génère une représentation textuelle du patient
     * @return Chaîne de caractères formatée
     */
    QString toString() const;

protected:
    QList<Allergie> allergies;
    Medecin* medecin = nullptr;
    Clinique* clinique = nullptr;
};

#endif // PATIENT_H
