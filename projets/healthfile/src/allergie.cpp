#include "allergie.h"

Allergie::Allergie(const QString& nom, const QString& description)
    : nom(nom), description(description){
}

QString Allergie::getNom() const {
    return nom;
}

QString Allergie::getDescription() const {
    return description;
}

void Allergie::setNom(const QString& t_nom) {
    nom = t_nom;
}

void Allergie::setDescription(const QString& t_description) {
    description = t_description;
}

QString Allergie::to_String() const {
    return QString("Allergie: %1 - %2").arg(nom).arg(description);
}
