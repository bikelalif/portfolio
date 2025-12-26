#include "clinique.h"
#include "patient.h"
#include "medecin.h"

Clinique::Clinique(const QString& id, const QString& nom, const QString& adresse, const QString& telephone)
    : id(id), nom(nom), adresse(adresse), telephone(telephone) {
}

QString Clinique::getId() const {
    return id;
}

QString Clinique::getNom() const {
    return nom;
}

QString Clinique::getAdresse() const {
    return adresse;
}

QString Clinique::getTelephone() const {
    return telephone;
}

QList<Patient*> Clinique::getPatients() const {
    return patients;
}

QList<Medecin*> Clinique::getMedecins() const {
    return medecins;
}

int Clinique::getNombreMedecins() const {
    return medecins.size();
}

int Clinique::getNombrePatientsHospitalises() const {
    return patients.size();
}

void Clinique::setNom(const QString& t_nom) {
    nom = t_nom;
}

void Clinique::setAdresse(const QString& t_adresse) {
    adresse = t_adresse;
}

void Clinique::setTelephone(const QString& t_telephone) {
    telephone = t_telephone;
}

// Gestion patients

void Clinique::hospitaliserPatient(Patient* patient) {
    if (patient && !patients.contains(patient)) {
        patients.append(patient);
    }
}

void Clinique::sortirPatient(Patient* patient) {
    patients.removeAll(patient);
}

bool Clinique::patientEstHospitalise(Patient* patient) const {
    return patients.contains(patient);
}

// Gestion médecins

void Clinique::ajouterMedecin(Medecin* medecin) {
    if (medecin && !medecins.contains(medecin)) {
        medecins.append(medecin);
    }
}

void Clinique::retirerMedecin(Medecin* medecin) {
    medecins.removeAll(medecin);
}

bool Clinique::medecinTravailleIci(Medecin* medecin) const {
    return medecins.contains(medecin);
}

QString Clinique::toString() const {
    return QString("Clinique: %1 - %2 (ID: %3)").arg(nom).arg(adresse).arg(id);
}
