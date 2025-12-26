#include "patient.h"
#include "medecin.h"
#include "clinique.h"

Patient::Patient(const QString& id, const QString& nom, const QString& prenom,
                 const QDate& date_naissance, const QString& adresse,
                 const QString& sexe, const QString& email, const QString& telephone)
    : Personne(id, nom, prenom, date_naissance, adresse, sexe, email, telephone),
      clinique(nullptr) {
}

// Gestion des allergies

void Patient::ajouterAllergie(const Allergie& allergie) {
    allergies.append(allergie);
}

void Patient::retirerAllergie(const Allergie& allergie) {
    for (int i = 0; i < allergies.size(); ++i) {
        if (allergies[i].getNom() == allergie.getNom()) {
            allergies.removeAt(i);
            break;
        }
    }
}

void Patient::clearAllergies() {
    allergies.clear();
}

QList<Allergie> Patient::getAllergies() const {
    return allergies;
}

// Gestion du médecin traitant

void Patient::setMedecin(Medecin* m) {
    medecin = m;
}

Medecin* Patient::getMedecin() const {
    return medecin;
}

// Gestion de l'hospitalisation

void Patient::setHospitalisation(Clinique* c) {
    clinique = c;
}

void Patient::retirerHospitalisation() {
    clinique = nullptr;
}

Clinique* Patient::getClinique() const {
    return clinique;
}

bool Patient::estHospitalise() const {
    return clinique != nullptr;
}

QString Patient::toString() const {
    return QString("Patient: %1 %2 (ID: %3)").arg(prenom).arg(nom).arg(id);
}
