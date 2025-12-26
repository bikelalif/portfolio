#ifndef PERSONNE_H
#define PERSONNE_H

#include <QMainWindow>
#include <QString>
#include <QDate>

/**
 * Classe de base représentant une personne
 * Les attributs id, nom, prenom et date_naissance sont constants (non modifiables)
 */
class Personne {
public:
    Personne(const QString& id, const QString& nom, const QString& prenom, const QDate& date_naissance, const QString& adresse, const QString& sexe, const QString& email, const QString& telephone);

    // Accesseurs en lecture
    QString getId() const;
    QString getNom() const;
    QString getPrenom() const;
    QDate getDate_naissance() const;
    QString getAdresse() const;
    QString getSexe() const;
    QString getEmail() const;
    QString getTelephone() const;

    // Mutateurs pour les données modifiables
    void setTelephone(const QString& m_telephone);
    void setAdresse(const QString& m_adresse);
    void setSexe(const QString& m_sexe);
    void setEmail(const QString& m_email);

protected:
    const QString id;
    const QString nom;
    const QString prenom;
    const QDate date_naissance;
    QString adresse;
    QString sexe;
    QString email;
    QString telephone;
};

#endif // PERSONNE_H
