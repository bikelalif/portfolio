#include "personne.h"

Personne::Personne(const QString& id, const QString& nom, const QString& prenom, const QDate& date_naissance, const QString& adresse, const QString& sexe, const QString& email, const QString& telephone)
    : id(id), nom(nom), prenom(prenom),  date_naissance(date_naissance), adresse(adresse), sexe(sexe), email(email), telephone(telephone){
}

QString Personne::getId() const {
    return id;
}

QString Personne::getNom() const {
    return nom;
}

QString Personne::getPrenom() const {
    return prenom;
}

QDate Personne::getDate_naissance() const{
    return date_naissance;
}

QString Personne::getAdresse() const {
    return adresse;
}

QString Personne::getSexe() const {
    return sexe;
}

QString Personne::getEmail() const {
    return email;
}

QString Personne::getTelephone() const {
    return telephone;
}

void Personne::setTelephone(const QString& m_telephone){
    telephone = m_telephone;
}

void Personne::setAdresse(const QString& m_adresse){
    adresse = m_adresse;
}

void Personne::setSexe(const QString& m_sexe){
    sexe = m_sexe;
}

void Personne::setEmail(const QString& m_email){
    email = m_email;
}
