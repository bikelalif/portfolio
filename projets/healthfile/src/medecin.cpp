#include "medecin.h"
#include "patient.h"
#include "clinique.h"

Medecin::Medecin(const QString& id, const QString& nom, const QString& prenom,
                 const QDate& date_naissance, const QString& adresse,
                 const QString& sexe, const QString& email, const QString& telephone)
    : Personne(id, nom, prenom, date_naissance, adresse, sexe, email, telephone) {
}

Medecin::Medecin(const QString& id, const QString& nom, const QString& prenom,
                 const QDate& date_naissance, const QString& adresse,
                 const QString& sexe, const QString& email, const QString& telephone,
                 const QString& specialisation)
    : Personne(id, nom, prenom, date_naissance, adresse, sexe, email, telephone),
      specialisation(specialisation) {
}

QString Medecin::getSpecialisation() const {
    return specialisation;
}

QList<Patient*> Medecin::getPatients() const {
    return patients;
}

QList<Clinique*> Medecin::getCliniques() const {
    return cliniques;
}

int Medecin::getNombrePatients() const {
    return patients.size();
}

void Medecin::setSpecialisation(const QString& spec) {
    specialisation = spec;
}

// Gestion des patients

void Medecin::ajouterPatient(Patient* patient) {
    if (patient && !patients.contains(patient)) {
        patients.append(patient);
    }
}

void Medecin::retirerPatient(Patient* patient) {
    patients.removeAll(patient);
}

void Medecin::suivrePatient(Patient* patient) {
    if (patient) {
        ajouterPatient(patient);
        patient->setMedecin(this);  // Synchronisation bidirectionnelle
    }
}

// Gestion des cliniques

void Medecin::ajouterClinique(Clinique* clinique) {
    if (clinique && !cliniques.contains(clinique)) {
        cliniques.append(clinique);
    }
}

void Medecin::retirerClinique(Clinique* clinique) {
    cliniques.removeAll(clinique);
}

bool Medecin::travailleDans(Clinique* clinique) const {
    return cliniques.contains(clinique);
}

QString Medecin::toString() const {
    return QString("Dr. %1 %2 - %3 (ID: %4)").arg(prenom).arg(nom).arg(specialisation).arg(id);
}
