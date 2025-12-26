#ifndef CLINIQUE_H
#define CLINIQUE_H

#include <QString>
#include <QList>

class Patient;
class Medecin;

/**
 * @class Clinique
 * @brief Classe représentant une clinique médicale
 * @details Gère une liste de médecins travaillant dans l'établissement et de patients hospitalisés.
 *          Une clinique possède un identifiant, un nom, une adresse et un numéro de téléphone.
 */
class Clinique {
public:
    /**
     * @brief Constructeur de Clinique
     * @param id Identifiant unique de la clinique
     * @param nom Nom de la clinique
     * @param adresse Adresse complète
     * @param telephone Numéro de téléphone
     */
    Clinique(const QString& id, const QString& nom, const QString& adresse, const QString& telephone);
    
    /**
     * @brief Récupère l'identifiant de la clinique
     * @return Identifiant unique
     */
    QString getId() const;
    
    /**
     * @brief Récupère le nom de la clinique
     * @return Nom de l'établissement
     */
    QString getNom() const;
    
    /**
     * @brief Récupère l'adresse de la clinique
     * @return Adresse complète
     */
    QString getAdresse() const;
    
    /**
     * @brief Récupère le numéro de téléphone
     * @return Numéro de téléphone
     */
    QString getTelephone() const;
    
    /**
     * @brief Récupère la liste des patients hospitalisés
     * @return Liste de pointeurs vers les patients
     */
    QList<Patient*> getPatients() const;
    
    /**
     * @brief Récupère la liste des médecins travaillant dans la clinique
     * @return Liste de pointeurs vers les médecins
     */
    QList<Medecin*> getMedecins() const;
    
    /**
     * @brief Compte le nombre de médecins
     * @return Nombre de médecins
     */
    int getNombreMedecins() const;
    
    /**
     * @brief Compte le nombre de patients hospitalisés
     * @return Nombre de patients
     */
    int getNombrePatientsHospitalises() const;

    /**
     * @brief Modifie le nom de la clinique
     * @param nom Nouveau nom
     */
    void setNom(const QString& nom);
    
    /**
     * @brief Modifie l'adresse de la clinique
     * @param adresse Nouvelle adresse
     */
    void setAdresse(const QString& adresse);
    
    /**
     * @brief Modifie le numéro de téléphone
     * @param telephone Nouveau numéro
     */
    void setTelephone(const QString& telephone);

    /**
     * @brief Hospitalise un patient dans la clinique
     * @param patient Pointeur vers le patient
     */
    void hospitaliserPatient(Patient* patient);
    
    /**
     * @brief Fait sortir un patient de la clinique
     * @param patient Pointeur vers le patient
     */
    void sortirPatient(Patient* patient);
    
    /**
     * @brief Vérifie si un patient est hospitalisé
     * @param patient Pointeur vers le patient
     * @return true si hospitalisé, false sinon
     */
    bool patientEstHospitalise(Patient* patient) const;

    /**
     * @brief Ajoute un médecin à la clinique
     * @param medecin Pointeur vers le médecin
     */
    void ajouterMedecin(Medecin* medecin);
    
    /**
     * @brief Retire un médecin de la clinique
     * @param medecin Pointeur vers le médecin
     */
    void retirerMedecin(Medecin* medecin);
    
    /**
     * @brief Vérifie si un médecin travaille dans la clinique
     * @param medecin Pointeur vers le médecin
     * @return true si le médecin travaille ici, false sinon
     */
    bool medecinTravailleIci(Medecin* medecin) const;

    QString toString() const;

protected:
    QString id;
    QString nom;
    QString adresse;
    QString telephone;
    QList<Medecin*> medecins;
    QList<Patient*> patients;
};

#endif // CLINIQUE_H
