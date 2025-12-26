#ifndef ALLERGIE_H
#define ALLERGIE_H

#include <QMainWindow>
#include <QString>

/**
 * Classe représentant une allergie avec son nom et sa description
 */
class Allergie{
public:
    Allergie(const QString& nom, const QString& description);
    QString getNom() const;
    QString getDescription() const;
    void setNom(const QString& t_nom);
    void setDescription(const QString& t_description);
    QString to_String() const;
protected:
    QString nom;
    QString description;
};

#endif // ALLERGIE_H
