#ifndef MEDECIN_H
#define MEDECIN_H

#include <QMainWindow>
#include <QString>
#include <QDate>
#include <QList>
#include "personne.h"

class Patient;
class Clinique;

/**
 * @class Medecin
 * @brief Classe représentant un médecin du système de gestion médical
 * @details Hérite de Personne et gère une liste de patients suivis et de cliniques où il travaille.
 *          Un médecin a une spécialisation et peut être associé à plusieurs cliniques.
 */
class Medecin : public Personne {
public:
    /**
     * @brief Constructeur de Medecin sans spécialisation
     * @param id Identifiant unique du médecin
     * @param nom Nom de famille
     * @param prenom Prénom
     * @param date_naissance Date de naissance
     * @param adresse Adresse postale
     * @param sexe Sexe (M/F)
     * @param email Adresse email
     * @param telephone Numéro de téléphone
     */
    Medecin(const QString& id, const QString& nom, const QString& prenom,
            const QDate& date_naissance, const QString& adresse,
            const QString& sexe, const QString& email, const QString& telephone);

    /**
     * @brief Constructeur de Medecin avec spécialisation
     * @param id Identifiant unique du médecin
     * @param nom Nom de famille
     * @param prenom Prénom
     * @param date_naissance Date de naissance
     * @param adresse Adresse postale
     * @param sexe Sexe (M/F)
     * @param email Adresse email
     * @param telephone Numéro de téléphone
     * @param specialisation Spécialité médicale
     */
    Medecin(const QString& id, const QString& nom, const QString& prenom,
            const QDate& date_naissance, const QString& adresse,
            const QString& sexe, const QString& email, const QString& telephone,
            const QString& specialisation);

    /**
     * @brief Récupère la spécialisation du médecin
     * @return Nom de la spécialité
     */
    QString getSpecialisation() const;
    
    /**
     * @brief Récupère la liste des patients suivis
     * @return Liste de pointeurs vers les patients
     */
    QList<Patient*> getPatients() const;
    
    /**
     * @brief Récupère la liste des cliniques
     * @return Liste de pointeurs vers les cliniques
     */
    QList<Clinique*> getCliniques() const;
    
    /**
     * @brief Compte le nombre de patients suivis
     * @return Nombre de patients
     */
    int getNombrePatients() const;

    /**
     * @brief Définit la spécialisation du médecin
     * @param specialisation Nom de la spécialité
     */
    void setSpecialisation(const QString& specialisation);

    /**
     * @brief Ajoute un patient à la liste du médecin
     * @param patient Pointeur vers le patient
     */
    void ajouterPatient(Patient* patient);
    
    /**
     * @brief Retire un patient de la liste du médecin
     * @param patient Pointeur vers le patient
     */
    void retirerPatient(Patient* patient);
    
    /**
     * @brief Établit la relation bidirectionnelle médecin-patient
     * @param patient Pointeur vers le patient à suivre
     */
    void suivrePatient(Patient* patient);

    /**
     * @brief Ajoute une clinique à la liste des lieux de travail
     * @param clinique Pointeur vers la clinique
     */
    void ajouterClinique(Clinique* clinique);
    
    /**
     * @brief Retire une clinique de la liste des lieux de travail
     * @param clinique Pointeur vers la clinique
     */
    void retirerClinique(Clinique* clinique);
    
    /**
     * @brief Vérifie si le médecin travaille dans une clinique
     * @param clinique Pointeur vers la clinique
     * @return true si le médecin y travaille, false sinon
     */
    bool travailleDans(Clinique* clinique) const;

    /**
     * @brief Génère une représentation textuelle du médecin
     * @return Chaîne de caractères formatée
     */
    QString toString() const;

protected:
    QString specialisation;
    QList<Patient*> patients;
    QList<Clinique*> cliniques;
};

#endif // MEDECIN_H
