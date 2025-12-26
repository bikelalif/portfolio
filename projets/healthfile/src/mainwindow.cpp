#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QListWidgetItem>
#include <QDialog>
#include <QDateEdit>
#include <QComboBox>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QUuid>
#include <QFormLayout>
#include <QMessageBox>
#include <QFrame>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QRegularExpressionValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connexions Patient
    connect(ui->pushButton_ajouter, SIGNAL(clicked()), this, SLOT(formulaireAjoutPatient()));
    connect(ui->listWidgetPatient, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onPatientClicked(QListWidgetItem*)));
    connect(ui->lineEdit_recherchePatient, SIGNAL(textChanged(QString)), this, SLOT(rechercherPatient(QString)));

    // Connexions Medecin
    connect(ui->pushButton_ajouterMedecin, SIGNAL(clicked()), this, SLOT(formulaireAjoutMedecin()));
    connect(ui->listWidgetMedecin, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onMedecinClicked(QListWidgetItem*)));
    connect(ui->lineEdit_rechercheMedecin, SIGNAL(textChanged(QString)), this, SLOT(rechercherMedecin(QString)));

    // Connexions Clinique
    connect(ui->pushButton_ajouterClinique, SIGNAL(clicked()), this, SLOT(formulaireAjoutClinique()));
    connect(ui->listWidgetClinique, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onCliniqueClicked(QListWidgetItem*)));
    connect(ui->lineEdit_rechercheClinique, SIGNAL(textChanged(QString)), this, SLOT(rechercherClinique(QString)));

    // Connexions Allergie
    connect(ui->pushButton_ajouterAllergie, SIGNAL(clicked()), this, SLOT(formulaireAjoutAllergie()));
    connect(ui->listWidgetAllergie, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onAllergieClicked(QListWidgetItem*)));
    connect(ui->lineEdit_rechercheAllergie, SIGNAL(textChanged(QString)), this, SLOT(rechercherAllergie(QString)));

    // Connexions Import/Export
    connect(ui->actionExporter, SIGNAL(triggered()), this, SLOT(exporterDonnees()));
    connect(ui->actionImporter, SIGNAL(triggered()), this, SLOT(importerDonnees()));
    
    // Connexion À propos
    connect(ui->actionAPropos, SIGNAL(triggered()), this, SLOT(afficherAPropos()));
    
    // Connexions Langue
    connect(ui->actionFrancais, SIGNAL(triggered()), this, SLOT(changerLangueFrancais()));
    connect(ui->actionEnglish, SIGNAL(triggered()), this, SLOT(changerLangueAnglais()));


    // Créer quelques patients de test
    MainWindow::ajouterPatient(new Patient("P001", "Dupont", "Alice", QDate(1990, 5, 12), "Paris", "F", "alice@mail.com", "0612345678"));
    patients.append(new Patient("P002", "Martin", "Bob", QDate(1985, 3, 20), "Lyon", "M", "bob@mail.com", "0698765432"));
    patients.append(new Patient("P003", "Petit", "Claire", QDate(2000, 11, 8), "Marseille", "F", "claire@mail.com", "0654321098"));

    // Créer quelques medecins de test
    medecins.append(new Medecin("M001", "Durand", "Jean", QDate(1975, 2, 15), "Paris", "M", "jean.durand@mail.com", "0611111111", "Cardiologie"));
    medecins.append(new Medecin("M002", "Bernard", "Marie", QDate(1980, 8, 22), "Lyon", "F", "marie.bernard@mail.com", "0622222222", "Pédiatrie"));

    // Créer quelques cliniques de test
    cliniques.append(new Clinique("C001", "Clinique du Parc", "10 rue du Parc, Paris", "0144444444"));
    cliniques.append(new Clinique("C002", "Clinique Saint-Louis", "25 avenue Saint-Louis, Lyon", "0455555555"));

    // Créer quelques allergies de test
    allergies.append(Allergie("Pénicilline", "Allergie aux antibiotiques de la famille des pénicillines"));
    allergies.append(Allergie("Arachides", "Allergie aux cacahuètes et produits dérivés"));

    // Afficher les données
    afficherPatients();
    afficherMedecins();
    afficherCliniques();
    afficherAllergies();
}

MainWindow::~MainWindow()
{
    // Libération de la mémoire pour les objets alloués dynamiquement
    qDeleteAll(patients);
    patients.clear();
    qDeleteAll(medecins);
    medecins.clear();
    qDeleteAll(cliniques);
    cliniques.clear();
    allergies.clear();  // Pas de delete nécessaire (objets par valeur)
    delete ui;
}

QWidget* MainWindow::creerBullePatient(Patient* p)
{
    QWidget* bulle = new QWidget();
    bulle->setObjectName("bulle");
    bulle->setProperty("patientId", p->getId());  // Stockage de l'ID pour identification ultérieure

    QVBoxLayout* layout = new QVBoxLayout(bulle);

    QLabel* lblNom = new QLabel(QString("%1 %2").arg(p->getPrenom(), p->getNom()), bulle);

    QLabel* lblInfo = new QLabel(QString("ID: %1  |  Sexe: %2  |  Né(e): %3")
                                 .arg(p->getId(), p->getSexe(), p->getDate_naissance().toString("dd/MM/yyyy")), bulle);

    QLabel* lblContact = new QLabel(QString("%1  |  %2").arg(p->getEmail(), p->getTelephone()), bulle);

    layout->addWidget(lblNom);
    layout->addWidget(lblInfo);
    layout->addWidget(lblContact);

    // Ligne de séparation visuelle
    QFrame* ligne = new QFrame(bulle);
    ligne->setFrameShape(QFrame::HLine);
    ligne->setStyleSheet("color: #ccc;");

    layout->addWidget(ligne);

    return bulle;
}

void MainWindow::afficherPatients()
{
    ui->listWidgetPatient->clear();

    for (Patient* p : patients) {
        QListWidgetItem* item = new QListWidgetItem(ui->listWidgetPatient);
        item->setSizeHint(QSize(350, 75));

        QWidget* bulle = creerBullePatient(p);
        ui->listWidgetPatient->setItemWidget(item, bulle);
    }
}

void MainWindow::ajouterPatient(Patient* p){
        patients.append(p);
}

void MainWindow::formulaireAjoutPatient(){
    QDialog dialog(this);
    dialog.setWindowTitle(tr("Nouveau Patient"));

    QFormLayout* form = new QFormLayout(&dialog);

    // Champs de saisie
    QLineEdit* editNom = new QLineEdit(&dialog);
    QLineEdit* editPrenom = new QLineEdit(&dialog);
    QDateEdit* editDate = new QDateEdit(QDate::currentDate(), &dialog);
    QComboBox* comboSexe = new QComboBox(&dialog);
    comboSexe->addItems({"M", "F"});
    QLineEdit* editEmail = new QLineEdit(&dialog);
    QLineEdit* editTel = new QLineEdit(&dialog);
    QLineEdit* editAdresse = new QLineEdit(&dialog);
    
    // Validators pour email et téléphone
    QRegularExpressionValidator* emailValidator = new QRegularExpressionValidator(
        QRegularExpression("[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}"), &dialog);
    QRegularExpressionValidator* telValidator = new QRegularExpressionValidator(
        QRegularExpression("^[0-9]{10}$"), &dialog);
    editEmail->setValidator(emailValidator);
    editTel->setValidator(telValidator);
    editTel->setPlaceholderText("0612345678");
    editEmail->setPlaceholderText("exemple@mail.com");

    // === Sélecteur de médecin ===
    Medecin* medecinChoisi = nullptr;
    QWidget* widgetMedecin = new QWidget(&dialog);
    QHBoxLayout* layoutMedecin = new QHBoxLayout(widgetMedecin);
    layoutMedecin->setContentsMargins(0, 0, 0, 0);
    QLabel* lblMedecinChoisi = new QLabel("Aucun", widgetMedecin);
    QPushButton* btnChoisirMedecin = new QPushButton("Choisir...", widgetMedecin);
    layoutMedecin->addWidget(lblMedecinChoisi);
    layoutMedecin->addWidget(btnChoisirMedecin);
    layoutMedecin->addStretch();
    
    connect(btnChoisirMedecin, &QPushButton::clicked, [this, &medecinChoisi, lblMedecinChoisi](){
        QDialog dlg(this);
        dlg.setWindowTitle("Choisir un médecin");
        dlg.setMinimumWidth(300);
        QVBoxLayout* lay = new QVBoxLayout(&dlg);
        
        QLineEdit* recherche = new QLineEdit(&dlg);
        recherche->setPlaceholderText("Rechercher...");
        
        QListWidget* liste = new QListWidget(&dlg);
        for (int i = 0; i < medecins.size(); i++) {
            Medecin* m = medecins.at(i);
            QListWidgetItem* item = new QListWidgetItem(QString("%1 %2 - %3").arg(m->getPrenom(), m->getNom(), m->getSpecialisation()));
            item->setData(Qt::UserRole, i);
            liste->addItem(item);
        }
        
        connect(recherche, &QLineEdit::textChanged, [liste, this](const QString& texte){
            filtrerListeMedecins(liste, texte);
        });
        
        QDialogButtonBox* btns = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dlg);
        connect(btns, SIGNAL(accepted()), &dlg, SLOT(accept()));
        connect(btns, SIGNAL(rejected()), &dlg, SLOT(reject()));
        
        lay->addWidget(recherche);
        lay->addWidget(liste);
        lay->addWidget(btns);
        
        if (dlg.exec() == QDialog::Accepted) {
            if (liste->currentItem()) {
                int idx = liste->currentItem()->data(Qt::UserRole).toInt();
                medecinChoisi = medecins.at(idx);
                lblMedecinChoisi->setText(QString("%1 %2").arg(medecinChoisi->getPrenom(), medecinChoisi->getNom()));
            }
        }
    });

    // === Sélecteur de clinique ===
    Clinique* cliniqueChoisie = nullptr;
    QWidget* widgetClinique = new QWidget(&dialog);
    QHBoxLayout* layoutClinique = new QHBoxLayout(widgetClinique);
    layoutClinique->setContentsMargins(0, 0, 0, 0);
    QLabel* lblCliniqueChoisie = new QLabel("Aucune", widgetClinique);
    QPushButton* btnChoisirClinique = new QPushButton("Choisir...", widgetClinique);
    layoutClinique->addWidget(lblCliniqueChoisie);
    layoutClinique->addWidget(btnChoisirClinique);
    layoutClinique->addStretch();
    
    connect(btnChoisirClinique, &QPushButton::clicked, [this, &cliniqueChoisie, lblCliniqueChoisie](){
        QDialog dlg(this);
        dlg.setWindowTitle("Choisir une clinique");
        dlg.setMinimumWidth(300);
        QVBoxLayout* lay = new QVBoxLayout(&dlg);
        
        QLineEdit* recherche = new QLineEdit(&dlg);
        recherche->setPlaceholderText("Rechercher...");
        
        QListWidget* liste = new QListWidget(&dlg);
        for (int i = 0; i < cliniques.size(); i++) {
            Clinique* c = cliniques.at(i);
            QListWidgetItem* item = new QListWidgetItem(QString("%1 - %2").arg(c->getNom(), c->getAdresse()));
            item->setData(Qt::UserRole, i);
            liste->addItem(item);
        }
        
        connect(recherche, &QLineEdit::textChanged, [liste, this](const QString& texte){
            filtrerListeCliniques(liste, texte);
        });
        
        QDialogButtonBox* btns = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dlg);
        connect(btns, SIGNAL(accepted()), &dlg, SLOT(accept()));
        connect(btns, SIGNAL(rejected()), &dlg, SLOT(reject()));
        
        lay->addWidget(recherche);
        lay->addWidget(liste);
        lay->addWidget(btns);
        
        if (dlg.exec() == QDialog::Accepted) {
            if (liste->currentItem()) {
                int idx = liste->currentItem()->data(Qt::UserRole).toInt();
                cliniqueChoisie = cliniques.at(idx);
                lblCliniqueChoisie->setText(cliniqueChoisie->getNom());
            }
        }
    });

    // === Sélecteur d'allergies ===
    QList<Allergie> allergiesChoisies;
    QWidget* widgetAllergies = new QWidget(&dialog);
    QVBoxLayout* layoutAllergies = new QVBoxLayout(widgetAllergies);
    layoutAllergies->setContentsMargins(0, 0, 0, 0);
    QLabel* lblAllergiesChoisies = new QLabel("Aucune", widgetAllergies);
    QPushButton* btnChoisirAllergies = new QPushButton("Choisir...", widgetAllergies);
    layoutAllergies->addWidget(lblAllergiesChoisies);
    layoutAllergies->addWidget(btnChoisirAllergies);
    
    connect(btnChoisirAllergies, &QPushButton::clicked, [this, &allergiesChoisies, lblAllergiesChoisies](){
        QDialog dlg(this);
        dlg.setWindowTitle("Choisir des allergies");
        dlg.setMinimumWidth(300);
        QVBoxLayout* lay = new QVBoxLayout(&dlg);
        
        QLineEdit* recherche = new QLineEdit(&dlg);
        recherche->setPlaceholderText("Rechercher...");
        
        QListWidget* liste = new QListWidget(&dlg);
        liste->setSelectionMode(QAbstractItemView::MultiSelection);
        for (int i = 0; i < allergies.size(); i++) {
            QListWidgetItem* item = new QListWidgetItem(allergies[i].getNom());
            item->setData(Qt::UserRole, i);
            liste->addItem(item);
            // Pré-sélectionner si déjà choisie
            for (int j = 0; j < allergiesChoisies.size(); j++) {
                if (allergiesChoisies[j].getNom() == allergies[i].getNom()) {
                    item->setSelected(true);
                }
            }
        }
        
        connect(recherche, &QLineEdit::textChanged, [liste, this](const QString& texte){
            filtrerListeAllergies(liste, texte);
        });
        
        QDialogButtonBox* btns = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dlg);
        connect(btns, SIGNAL(accepted()), &dlg, SLOT(accept()));
        connect(btns, SIGNAL(rejected()), &dlg, SLOT(reject()));
        
        lay->addWidget(recherche);
        lay->addWidget(liste);
        lay->addWidget(btns);
        
        if (dlg.exec() == QDialog::Accepted) {
            allergiesChoisies.clear();
            QStringList noms;
            for (int i = 0; i < liste->selectedItems().size(); i++) {
                QListWidgetItem* item = liste->selectedItems().at(i);
                int idx = item->data(Qt::UserRole).toInt();
                allergiesChoisies.append(allergies[idx]);
                noms.append(allergies[idx].getNom());
            }
            if (noms.isEmpty()) {
                lblAllergiesChoisies->setText("Aucune");
            } else {
                lblAllergiesChoisies->setText(noms.join(", "));
            }
        }
    });

    // Ajouter au formulaire
    form->addRow(tr("Nom:"), editNom);
    form->addRow(tr("Prénom:"), editPrenom);
    form->addRow(tr("Date de naissance:"), editDate);
    form->addRow(tr("Sexe:"), comboSexe);
    form->addRow(tr("Email:"), editEmail);
    form->addRow(tr("Téléphone:"), editTel);
    form->addRow(tr("Adresse:"), editAdresse);
    form->addRow(tr("Médecin:"), widgetMedecin);
    form->addRow(tr("Clinique:"), widgetClinique);
    form->addRow(tr("Allergies:"), widgetAllergies);

    // Boutons OK / Annuler
    QDialogButtonBox* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    form->addRow(buttons);

    // Afficher et récupérer le résultat
    if (dialog.exec() == QDialog::Accepted) {
        // Créer le patient avec les valeurs saisies
        QString id = QUuid::createUuid().toString(QUuid::WithoutBraces);
        // si un des champs essentiels à la création de la personne est null on renvoie un message d'erreur
        if (editNom->text().trimmed().isEmpty() || editPrenom->text().trimmed().isEmpty() || !editDate->date().isValid() || comboSexe->currentText().isEmpty() || editDate->date().isNull() ){
            QMessageBox::critical(this, tr("Erreur"), tr("Le nom est obligatoire !"));
            return;
        }
        else{
            Patient* p = new Patient(
                id,
                editNom->text(),
                editPrenom->text(),
                editDate->date(),
                editAdresse->text(),
                comboSexe->currentText(),
                editEmail->text(),
                editTel->text()
                );
            
            // Associer le médecin sélectionné
            p->setMedecin(medecinChoisi);
            if (medecinChoisi) {
                medecinChoisi->ajouterPatient(p);
            }
            
            // Associer la clinique sélectionnée
            if (cliniqueChoisie) {
                p->setHospitalisation(cliniqueChoisie);
                cliniqueChoisie->hospitaliserPatient(p);
            }
            
            // Associer les allergies sélectionnées
            for (const Allergie& a : allergiesChoisies) {
                p->ajouterAllergie(a);
            }
            
            ajouterPatient(p);
            afficherPatients();
            return;
        }

    }
}

void MainWindow::onPatientClicked(QListWidgetItem* item)
{
    //on récupère le numero de la ligne sur laquelle on a cliquer
    int index = ui->listWidgetPatient->row(item);
    //on récupère le patient à la position index de la ligne
    Patient* p = patients.at(index);

    //On ouvre une fiche avec tous les détails du patient
    QDialog dialog(this);
    dialog.setWindowTitle("Fiche Patient");
    dialog.setMinimumWidth(400);
    QVBoxLayout* layout = new QVBoxLayout(&dialog);
    QLabel* titre = new QLabel(QString("<h2>%1 %2</h2>").arg(p->getPrenom(), p->getNom()));
    titre->setAlignment(Qt::AlignCenter);

    // Infos de base
    QLabel* infos = new QLabel(QString(
                                   "<b>ID:</b> %1<br>"
                                   "<b>Sexe:</b> %2<br>"
                                   "<b>Date de naissance:</b> %3<br>"
                                   "<b>Adresse:</b> %4<br>"
                                   "<b>Email:</b> %5<br>"
                                   "<b>Téléphone:</b> %6"
                                   ).arg(
                                       p->getId(),
                                       p->getSexe(),
                                       p->getDate_naissance().toString("dd/MM/yyyy"),
                                       p->getAdresse(),
                                       p->getEmail(),
                                       p->getTelephone()
                                       ));

    // === Section Médecin ===
    QLabel* lblMedecin = new QLabel("<b>Médecin:</b>");
    QString nomMedecin = "Aucun";
    Medecin* m = p->getMedecin();
    if (m) {
        nomMedecin = QString("%1 %2").arg(m->getPrenom(), m->getNom());
    }
    QLabel* lblNomMedecin = new QLabel(nomMedecin);

    // === Section Clinique ===
    QLabel* lblClinique = new QLabel("<b>Clinique:</b>");
    QString nomClinique = "Aucune";
    Clinique* c = p->getClinique();
    if (c) {
        nomClinique = c->getNom();
    }
    QLabel* lblNomClinique = new QLabel(nomClinique);

    // === Section Allergies ===
    QLabel* lblAllergies = new QLabel("<b>Allergies:</b>");
    QWidget* widgetAllergies = new QWidget(&dialog);
    QVBoxLayout* layoutAllergies = new QVBoxLayout(widgetAllergies);
    layoutAllergies->setContentsMargins(0, 0, 0, 0);
    
    if (p->getAllergies().isEmpty()) {
        layoutAllergies->addWidget(new QLabel("Aucune"));
    } else {
        for (const Allergie& a : p->getAllergies()) {
            QWidget* ligneAllergie = new QWidget(widgetAllergies);
            QHBoxLayout* layoutLigne = new QHBoxLayout(ligneAllergie);
            layoutLigne->setContentsMargins(0, 0, 0, 0);
            
            QLabel* lblNomAllergie = new QLabel(a.getNom(), ligneAllergie);
            QPushButton* btnInfo = new QPushButton("?", ligneAllergie);
            btnInfo->setFixedSize(25, 25);
            
            // Capturer la description pour le dialog
            QString description = a.getDescription();
            QString nom = a.getNom();
            connect(btnInfo, &QPushButton::clicked, [this, nom, description](){
                QMessageBox::information(this, QString("Allergie: %1").arg(nom), description);
            });
            
            layoutLigne->addWidget(lblNomAllergie);
            layoutLigne->addWidget(btnInfo);
            layoutLigne->addStretch();
            layoutAllergies->addWidget(ligneAllergie);
        }
    }

    QPushButton* btnFermer = new QPushButton("Fermer");
    connect(btnFermer, SIGNAL(clicked()), &dialog, SLOT(close()));
    QPushButton* btnModifier = new QPushButton("Modifier");
    connect(btnModifier, SIGNAL(clicked()), &dialog, SLOT(accept()));
    QPushButton* btnSupprimer = new QPushButton("Supprimer");
    connect(btnSupprimer, &QPushButton::clicked, [&dialog]() { dialog.done(2); });

    layout->addWidget(titre);
    layout->addWidget(infos);
    layout->addSpacing(10);
    layout->addWidget(lblMedecin);
    layout->addWidget(lblNomMedecin);
    layout->addSpacing(5);
    layout->addWidget(lblClinique);
    layout->addWidget(lblNomClinique);
    layout->addSpacing(5);
    layout->addWidget(lblAllergies);
    layout->addWidget(widgetAllergies);
    layout->addSpacing(10);
    layout->addWidget(btnModifier);
    layout->addWidget(btnSupprimer);
    layout->addWidget(btnFermer);

    int resultat = dialog.exec();

    if (resultat == QDialog::Accepted) {
        ModifierPatient(p);
    }
    else if (resultat == 2) {
        SupprimerPatient(p, index);
    }
}


void MainWindow::ModifierPatient(Patient *p){
    QDialog dialog(this);
    dialog.setWindowTitle("Modifier Patient");

    QFormLayout* form = new QFormLayout(&dialog);

    // Champs de saisie
    QComboBox* comboSexe = new QComboBox(&dialog);
    comboSexe->addItems({"M", "F"});
    QLineEdit* editEmail = new QLineEdit(&dialog);
    QLineEdit* editTel = new QLineEdit(&dialog);
    QLineEdit* editAdresse = new QLineEdit(&dialog);
    
    // Validators pour email et téléphone
    QRegularExpressionValidator* emailValidator = new QRegularExpressionValidator(
        QRegularExpression("[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}"), &dialog);
    QRegularExpressionValidator* telValidator = new QRegularExpressionValidator(
        QRegularExpression("^[0-9]{10}$"), &dialog);
    editEmail->setValidator(emailValidator);
    editTel->setValidator(telValidator);

    editAdresse->setText(p->getAdresse());
    comboSexe->setEditText(p->getSexe());
    editEmail->setText(p->getEmail());
    editTel->setText(p->getTelephone());

    // === Sélecteur de médecin ===
    Medecin* medecinChoisi = p->getMedecin();
    QWidget* widgetMedecin = new QWidget(&dialog);
    QHBoxLayout* layoutMedecin = new QHBoxLayout(widgetMedecin);
    layoutMedecin->setContentsMargins(0, 0, 0, 0);
    QString nomMedecinActuel = "Aucun";
    if (medecinChoisi) {
        nomMedecinActuel = QString("%1 %2").arg(medecinChoisi->getPrenom(), medecinChoisi->getNom());
    }
    QLabel* lblMedecinChoisi = new QLabel(nomMedecinActuel, widgetMedecin);
    QPushButton* btnChoisirMedecin = new QPushButton("Choisir...", widgetMedecin);
    layoutMedecin->addWidget(lblMedecinChoisi);
    layoutMedecin->addWidget(btnChoisirMedecin);
    layoutMedecin->addStretch();
    
    connect(btnChoisirMedecin, &QPushButton::clicked, [this, &medecinChoisi, lblMedecinChoisi](){
        QDialog dlg(this);
        dlg.setWindowTitle("Choisir un médecin");
        dlg.setMinimumWidth(300);
        QVBoxLayout* lay = new QVBoxLayout(&dlg);
        
        QLineEdit* recherche = new QLineEdit(&dlg);
        recherche->setPlaceholderText("Rechercher...");
        
        QListWidget* liste = new QListWidget(&dlg);
        for (int i = 0; i < medecins.size(); i++) {
            Medecin* m = medecins.at(i);
            QListWidgetItem* item = new QListWidgetItem(QString("%1 %2 - %3").arg(m->getPrenom(), m->getNom(), m->getSpecialisation()));
            item->setData(Qt::UserRole, i);
            liste->addItem(item);
            if (m == medecinChoisi) {
                liste->setCurrentItem(item);
            }
        }
        
        connect(recherche, &QLineEdit::textChanged, [liste, this](const QString& texte){
            filtrerListeMedecins(liste, texte);
        });
        
        QDialogButtonBox* btns = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dlg);
        connect(btns, SIGNAL(accepted()), &dlg, SLOT(accept()));
        connect(btns, SIGNAL(rejected()), &dlg, SLOT(reject()));
        
        lay->addWidget(recherche);
        lay->addWidget(liste);
        lay->addWidget(btns);
        
        if (dlg.exec() == QDialog::Accepted) {
            if (liste->currentItem()) {
                int idx = liste->currentItem()->data(Qt::UserRole).toInt();
                medecinChoisi = medecins.at(idx);
                lblMedecinChoisi->setText(QString("%1 %2").arg(medecinChoisi->getPrenom(), medecinChoisi->getNom()));
            }
        }
    });

    // === Sélecteur de clinique ===
    Clinique* cliniqueChoisie = p->getClinique();
    QWidget* widgetClinique = new QWidget(&dialog);
    QHBoxLayout* layoutClinique = new QHBoxLayout(widgetClinique);
    layoutClinique->setContentsMargins(0, 0, 0, 0);
    QString nomCliniqueActuelle = "Aucune";
    if (cliniqueChoisie) {
        nomCliniqueActuelle = cliniqueChoisie->getNom();
    }
    QLabel* lblCliniqueChoisie = new QLabel(nomCliniqueActuelle, widgetClinique);
    QPushButton* btnChoisirClinique = new QPushButton("Choisir...", widgetClinique);
    layoutClinique->addWidget(lblCliniqueChoisie);
    layoutClinique->addWidget(btnChoisirClinique);
    layoutClinique->addStretch();
    
    connect(btnChoisirClinique, &QPushButton::clicked, [this, &cliniqueChoisie, lblCliniqueChoisie](){
        QDialog dlg(this);
        dlg.setWindowTitle("Choisir une clinique");
        dlg.setMinimumWidth(300);
        QVBoxLayout* lay = new QVBoxLayout(&dlg);
        
        QLineEdit* recherche = new QLineEdit(&dlg);
        recherche->setPlaceholderText("Rechercher...");
        
        QListWidget* liste = new QListWidget(&dlg);
        for (int i = 0; i < cliniques.size(); i++) {
            Clinique* c = cliniques.at(i);
            QListWidgetItem* item = new QListWidgetItem(QString("%1 - %2").arg(c->getNom(), c->getAdresse()));
            item->setData(Qt::UserRole, i);
            liste->addItem(item);
            if (c == cliniqueChoisie) {
                liste->setCurrentItem(item);
            }
        }
        
        connect(recherche, &QLineEdit::textChanged, [liste, this](const QString& texte){
            filtrerListeCliniques(liste, texte);
        });
        
        QDialogButtonBox* btns = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dlg);
        connect(btns, SIGNAL(accepted()), &dlg, SLOT(accept()));
        connect(btns, SIGNAL(rejected()), &dlg, SLOT(reject()));
        
        lay->addWidget(recherche);
        lay->addWidget(liste);
        lay->addWidget(btns);
        
        if (dlg.exec() == QDialog::Accepted) {
            if (liste->currentItem()) {
                int idx = liste->currentItem()->data(Qt::UserRole).toInt();
                cliniqueChoisie = cliniques.at(idx);
                lblCliniqueChoisie->setText(cliniqueChoisie->getNom());
            }
        }
    });

    // === Sélecteur d'allergies ===
    QList<Allergie> allergiesChoisies = p->getAllergies();
    QWidget* widgetAllergies = new QWidget(&dialog);
    QVBoxLayout* layoutAllergies = new QVBoxLayout(widgetAllergies);
    layoutAllergies->setContentsMargins(0, 0, 0, 0);
    QStringList nomsAllergiesActuelles;
    for (int i = 0; i < allergiesChoisies.size(); i++) {
        nomsAllergiesActuelles.append(allergiesChoisies[i].getNom());
    }
    QString txtAllergies = "Aucune";
    if (!nomsAllergiesActuelles.isEmpty()) {
        txtAllergies = nomsAllergiesActuelles.join(", ");
    }
    QLabel* lblAllergiesChoisies = new QLabel(txtAllergies, widgetAllergies);
    QPushButton* btnChoisirAllergies = new QPushButton("Choisir...", widgetAllergies);
    layoutAllergies->addWidget(lblAllergiesChoisies);
    layoutAllergies->addWidget(btnChoisirAllergies);
    
    connect(btnChoisirAllergies, &QPushButton::clicked, [this, &allergiesChoisies, lblAllergiesChoisies](){
        QDialog dlg(this);
        dlg.setWindowTitle("Choisir des allergies");
        dlg.setMinimumWidth(300);
        QVBoxLayout* lay = new QVBoxLayout(&dlg);
        
        QLineEdit* recherche = new QLineEdit(&dlg);
        recherche->setPlaceholderText("Rechercher...");
        
        QListWidget* liste = new QListWidget(&dlg);
        liste->setSelectionMode(QAbstractItemView::MultiSelection);
        for (int i = 0; i < allergies.size(); i++) {
            QListWidgetItem* item = new QListWidgetItem(allergies[i].getNom());
            item->setData(Qt::UserRole, i);
            liste->addItem(item);
            // Pré-sélectionner si déjà choisie
            for (int j = 0; j < allergiesChoisies.size(); j++) {
                if (allergiesChoisies[j].getNom() == allergies[i].getNom()) {
                    item->setSelected(true);
                }
            }
        }
        
        connect(recherche, &QLineEdit::textChanged, [liste, this](const QString& texte){
            filtrerListeAllergies(liste, texte);
        });
        
        QDialogButtonBox* btns = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dlg);
        connect(btns, SIGNAL(accepted()), &dlg, SLOT(accept()));
        connect(btns, SIGNAL(rejected()), &dlg, SLOT(reject()));
        
        lay->addWidget(recherche);
        lay->addWidget(liste);
        lay->addWidget(btns);
        
        if (dlg.exec() == QDialog::Accepted) {
            allergiesChoisies.clear();
            QStringList noms;
            for (int i = 0; i < liste->selectedItems().size(); i++) {
                QListWidgetItem* item = liste->selectedItems().at(i);
                int idx = item->data(Qt::UserRole).toInt();
                allergiesChoisies.append(allergies[idx]);
                noms.append(allergies[idx].getNom());
            }
            if (noms.isEmpty()) {
                lblAllergiesChoisies->setText("Aucune");
            } else {
                lblAllergiesChoisies->setText(noms.join(", "));
            }
        }
    });

    // Ajouter au formulaire
    form->addRow(tr("Nom:"), new QLabel(p->getNom()));
    form->addRow(tr("Prénom:"), new QLabel(p->getPrenom()));
    form->addRow(tr("Date de naissance:"), new QLabel(p->getDate_naissance().toString("dd/MM/yyyy")));
    form->addRow(tr("Sexe:"), comboSexe);
    form->addRow(tr("Email:"), editEmail);
    form->addRow(tr("Téléphone:"), editTel);
    form->addRow(tr("Adresse:"), editAdresse);
    form->addRow(tr("Médecin:"), widgetMedecin);
    form->addRow(tr("Clinique:"), widgetClinique);
    form->addRow(tr("Allergies:"), widgetAllergies);

    // Boutons OK / Annuler
    QDialogButtonBox* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    form->addRow(buttons);

    // Afficher et récupérer le résultat
    if (dialog.exec() == QDialog::Accepted) {
        // si un des champs essentiels à la création de la personne est null on renvoie un message d'erreur
        if ( comboSexe->currentText().isEmpty() ){
            QMessageBox::critical(this, tr("Erreur"), tr("Le sexe est obligatoire !"));
            return;
        }
        else{
            p->setTelephone(editTel->text());
            p->setAdresse(editAdresse->text());
            p->setSexe(comboSexe->currentText());
            p->setEmail(editEmail->text());
            
            // Mettre à jour le médecin
            Medecin* ancienMedecin = p->getMedecin();
            if (ancienMedecin) {
                ancienMedecin->retirerPatient(p);
            }
            p->setMedecin(medecinChoisi);
            if (medecinChoisi) {
                medecinChoisi->ajouterPatient(p);
            }
            
            // Mettre à jour la clinique
            Clinique* ancienneClinique = p->getClinique();
            if (ancienneClinique) {
                ancienneClinique->sortirPatient(p);
                p->retirerHospitalisation();
            }
            if (cliniqueChoisie) {
                p->setHospitalisation(cliniqueChoisie);
                cliniqueChoisie->hospitaliserPatient(p);
            }
            
            // Mettre à jour les allergies
            p->clearAllergies();
            for (const Allergie& a : allergiesChoisies) {
                p->ajouterAllergie(a);
            }
            
            afficherPatients();
            return;
        }

    }
}

void MainWindow::SupprimerPatient(Patient *p, int index){
    patients.removeAt(index);
    delete p;
    afficherPatients();
    return;
}

// ============================================
// ============== MEDECIN ====================
// ============================================

QWidget* MainWindow::creerBulleMedecin(Medecin* m)
{
    QWidget* bulle = new QWidget();
    bulle->setObjectName("bulle");
    bulle->setProperty("medecinId", m->getId());

    QVBoxLayout* layout = new QVBoxLayout(bulle);

    QLabel* lblNom = new QLabel(QString("%1 %2").arg(m->getPrenom(), m->getNom()), bulle);

    QLabel* lblInfo = new QLabel(QString("ID: %1  |  Spécialisation: %2")
                                 .arg(m->getId(), m->getSpecialisation()), bulle);

    QLabel* lblContact = new QLabel(QString("%1  |  %2").arg(m->getEmail(), m->getTelephone()), bulle);

    layout->addWidget(lblNom);
    layout->addWidget(lblInfo);
    layout->addWidget(lblContact);

    QFrame* ligne = new QFrame(bulle);
    ligne->setFrameShape(QFrame::HLine);
    ligne->setStyleSheet("color: #ccc;");
    layout->addWidget(ligne);

    return bulle;
}

void MainWindow::afficherMedecins()
{
    ui->listWidgetMedecin->clear();

    for (Medecin* m : medecins) {
        QListWidgetItem* item = new QListWidgetItem(ui->listWidgetMedecin);
        item->setSizeHint(QSize(350, 75));

        QWidget* bulle = creerBulleMedecin(m);
        ui->listWidgetMedecin->setItemWidget(item, bulle);
    }
}

void MainWindow::ajouterMedecin(Medecin* m){
    medecins.append(m);
}

void MainWindow::formulaireAjoutMedecin(){
    QDialog dialog(this);
    dialog.setWindowTitle("Nouveau Médecin");

    QFormLayout* form = new QFormLayout(&dialog);

    QLineEdit* editNom = new QLineEdit(&dialog);
    QLineEdit* editPrenom = new QLineEdit(&dialog);
    QDateEdit* editDate = new QDateEdit(QDate::currentDate(), &dialog);
    QComboBox* comboSexe = new QComboBox(&dialog);
    comboSexe->addItems({"M", "F"});
    QLineEdit* editEmail = new QLineEdit(&dialog);
    QLineEdit* editTel = new QLineEdit(&dialog);
    QLineEdit* editAdresse = new QLineEdit(&dialog);
    QLineEdit* editSpecialisation = new QLineEdit(&dialog);
    
    // === Sélecteur de cliniques ===
    QList<Clinique*> cliniquesChoisies;
    QWidget* widgetCliniques = new QWidget(&dialog);
    QVBoxLayout* layoutCliniques = new QVBoxLayout(widgetCliniques);
    layoutCliniques->setContentsMargins(0, 0, 0, 0);
    QLabel* lblCliniquesChoisies = new QLabel("Aucune", widgetCliniques);
    QPushButton* btnChoisirCliniques = new QPushButton("Choisir...", widgetCliniques);
    layoutCliniques->addWidget(lblCliniquesChoisies);
    layoutCliniques->addWidget(btnChoisirCliniques);
    
    connect(btnChoisirCliniques, &QPushButton::clicked, [this, &cliniquesChoisies, lblCliniquesChoisies](){
        QDialog dlg(this);
        dlg.setWindowTitle("Choisir des cliniques");
        dlg.setMinimumWidth(300);
        QVBoxLayout* lay = new QVBoxLayout(&dlg);
        
        QLineEdit* recherche = new QLineEdit(&dlg);
        recherche->setPlaceholderText("Rechercher...");
        
        QListWidget* liste = new QListWidget(&dlg);
        liste->setSelectionMode(QAbstractItemView::MultiSelection);
        for (int i = 0; i < cliniques.size(); i++) {
            Clinique* c = cliniques.at(i);
            QListWidgetItem* item = new QListWidgetItem(QString("%1 - %2").arg(c->getNom(), c->getAdresse()));
            item->setData(Qt::UserRole, i);
            liste->addItem(item);
            // Pré-sélectionner si déjà choisie
            for (Clinique* choisie : cliniquesChoisies) {
                if (choisie == c) {
                    item->setSelected(true);
                }
            }
        }
        
        connect(recherche, &QLineEdit::textChanged, [liste, this](const QString& texte){
            filtrerListeCliniques(liste, texte);
        });
        
        QDialogButtonBox* btns = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dlg);
        connect(btns, SIGNAL(accepted()), &dlg, SLOT(accept()));
        connect(btns, SIGNAL(rejected()), &dlg, SLOT(reject()));
        
        lay->addWidget(recherche);
        lay->addWidget(liste);
        lay->addWidget(btns);
        
        if (dlg.exec() == QDialog::Accepted) {
            cliniquesChoisies.clear();
            QStringList noms;
            for (int i = 0; i < liste->selectedItems().size(); i++) {
                QListWidgetItem* item = liste->selectedItems().at(i);
                int idx = item->data(Qt::UserRole).toInt();
                cliniquesChoisies.append(cliniques.at(idx));
                noms.append(cliniques.at(idx)->getNom());
            }
            if (noms.isEmpty()) {
                lblCliniquesChoisies->setText("Aucune");
            } else {
                lblCliniquesChoisies->setText(noms.join(", "));
            }
        }
    });

    form->addRow(tr("Nom:"), editNom);
    form->addRow(tr("Prénom:"), editPrenom);
    form->addRow(tr("Date de naissance:"), editDate);
    form->addRow(tr("Sexe:"), comboSexe);
    form->addRow(tr("Email:"), editEmail);
    form->addRow(tr("Téléphone:"), editTel);
    form->addRow(tr("Adresse:"), editAdresse);
    form->addRow(tr("Spécialisation:"), editSpecialisation);
    form->addRow(tr("Cliniques:"), widgetCliniques);

    QDialogButtonBox* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    form->addRow(buttons);

    if (dialog.exec() == QDialog::Accepted) {
        QString id = QUuid::createUuid().toString(QUuid::WithoutBraces);
        if (editNom->text().trimmed().isEmpty() || editPrenom->text().trimmed().isEmpty() || !editDate->date().isValid() || comboSexe->currentText().isEmpty() || editDate->date().isNull() ){
            QMessageBox::critical(this, tr("Erreur"), tr("Le nom est obligatoire !"));
            return;
        }
        else{
            Medecin* m = new Medecin(
                id,
                editNom->text(),
                editPrenom->text(),
                editDate->date(),
                editAdresse->text(),
                comboSexe->currentText(),
                editEmail->text(),
                editTel->text(),
                editSpecialisation->text()
                );
            
            // Ajouter les cliniques sélectionnées
            for(Clinique* c : cliniquesChoisies) {
                m->ajouterClinique(c);
                c->ajouterMedecin(m);
            }
            
            ajouterMedecin(m);
            afficherMedecins();
            return;
        }
    }
}

void MainWindow::onMedecinClicked(QListWidgetItem* item)
{
    int index = ui->listWidgetMedecin->row(item);
    Medecin* m = medecins.at(index);

    QDialog dialog(this);
    dialog.setWindowTitle("Fiche Médecin");
    dialog.setMinimumWidth(350);
    QVBoxLayout* layout = new QVBoxLayout(&dialog);
    QLabel* titre = new QLabel(QString("<h2>%1 %2</h2>").arg(m->getPrenom(), m->getNom()));
    titre->setAlignment(Qt::AlignCenter);

    QLabel* infos = new QLabel(QString(
                                   "<b>ID:</b> %1<br>"
                                   "<b>Sexe:</b> %2<br>"
                                   "<b>Date de naissance:</b> %3<br>"
                                   "<b>Adresse:</b> %4<br>"
                                   "<b>Email:</b> %5<br>"
                                   "<b>Téléphone:</b> %6<br>"
                                   "<b>Spécialisation:</b> %7"
                                   ).arg(
                                       m->getId(),
                                       m->getSexe(),
                                       m->getDate_naissance().toString("dd/MM/yyyy"),
                                       m->getAdresse(),
                                       m->getEmail(),
                                       m->getTelephone(),
                                       m->getSpecialisation()
                                       ));

    // === Section Patients ===
    QLabel* lblPatients = new QLabel("<b>Patients:</b>");
    QLabel* lblNombrePatients = new QLabel(QString("%1 patient(s)").arg(m->getNombrePatients()));
    QPushButton* btnDetailsPatients = new QPushButton("Voir détails");
    connect(btnDetailsPatients, &QPushButton::clicked, [this, m](){
        QDialog dlg(this);
        dlg.setWindowTitle("Liste des patients");
        dlg.setMinimumWidth(400);
        QVBoxLayout* lay = new QVBoxLayout(&dlg);
        
        QLabel* titre = new QLabel(QString("<h3>Patients de %1 %2</h3>").arg(m->getPrenom(), m->getNom()));
        lay->addWidget(titre);
        
        if (m->getPatients().isEmpty()) {
            lay->addWidget(new QLabel("Aucun patient"));
        } else {
            QListWidget* liste = new QListWidget(&dlg);
            for (Patient* p : m->getPatients()) {
                QString info = QString("%1 %2 - %3").arg(p->getPrenom(), p->getNom(), p->getTelephone());
                liste->addItem(info);
            }
            lay->addWidget(liste);
        }
        
        QPushButton* btnFermer = new QPushButton("Fermer", &dlg);
        connect(btnFermer, &QPushButton::clicked, &dlg, &QDialog::accept);
        lay->addWidget(btnFermer);
        
        dlg.exec();
    });
    
    // === Section Cliniques ===
    QLabel* lblCliniques = new QLabel("<b>Cliniques:</b>");
    QString txtCliniques = "Aucune";
    if (!m->getCliniques().isEmpty()) {
        QStringList noms;
        for (Clinique* c : m->getCliniques()) {
            noms.append(c->getNom());
        }
        txtCliniques = noms.join(", ");
    }
    QLabel* lblNomCliniques = new QLabel(txtCliniques);

    QPushButton* btnFermer = new QPushButton("Fermer");
    connect(btnFermer, SIGNAL(clicked()), &dialog, SLOT(close()));
    QPushButton* btnModifier = new QPushButton("Modifier");
    connect(btnModifier, SIGNAL(clicked()), &dialog, SLOT(accept()));
    QPushButton* btnSupprimer = new QPushButton("Supprimer");
    connect(btnSupprimer, &QPushButton::clicked, [&dialog]() { dialog.done(2); });

    layout->addWidget(titre);
    layout->addWidget(infos);
    layout->addSpacing(10);
    layout->addWidget(lblPatients);
    layout->addWidget(lblNombrePatients);
    layout->addWidget(btnDetailsPatients);
    layout->addSpacing(5);
    layout->addWidget(lblCliniques);
    layout->addWidget(lblNomCliniques);
    layout->addSpacing(10);
    layout->addWidget(btnModifier);
    layout->addWidget(btnSupprimer);
    layout->addWidget(btnFermer);

    int resultat = dialog.exec();

    if (resultat == QDialog::Accepted) {
        ModifierMedecin(m);
    }
    else if (resultat == 2) {
        SupprimerMedecin(m, index);
    }
}

void MainWindow::ModifierMedecin(Medecin *m){
    QDialog dialog(this);
    dialog.setWindowTitle("Modifier Médecin");

    QFormLayout* form = new QFormLayout(&dialog);

    QComboBox* comboSexe = new QComboBox(&dialog);
    comboSexe->addItems({"M", "F"});
    QLineEdit* editEmail = new QLineEdit(&dialog);
    QLineEdit* editTel = new QLineEdit(&dialog);
    QLineEdit* editAdresse = new QLineEdit(&dialog);
    QLineEdit* editSpecialisation = new QLineEdit(&dialog);

    editAdresse->setText(m->getAdresse());
    comboSexe->setEditText(m->getSexe());
    editEmail->setText(m->getEmail());
    editTel->setText(m->getTelephone());
    editSpecialisation->setText(m->getSpecialisation());

    // === Sélecteur de cliniques ===
    QList<Clinique*> cliniquesChoisies = m->getCliniques();
    QWidget* widgetCliniques = new QWidget(&dialog);
    QVBoxLayout* layoutCliniques = new QVBoxLayout(widgetCliniques);
    layoutCliniques->setContentsMargins(0, 0, 0, 0);
    QStringList nomsActuelles;
    for (Clinique* c : cliniquesChoisies) {
        nomsActuelles.append(c->getNom());
    }
    QString txtCliniques = "Aucune";
    if (!nomsActuelles.isEmpty()) {
        txtCliniques = nomsActuelles.join(", ");
    }
    QLabel* lblCliniquesChoisies = new QLabel(txtCliniques, widgetCliniques);
    QPushButton* btnChoisirCliniques = new QPushButton("Choisir...", widgetCliniques);
    layoutCliniques->addWidget(lblCliniquesChoisies);
    layoutCliniques->addWidget(btnChoisirCliniques);
    
    connect(btnChoisirCliniques, &QPushButton::clicked, [this, &cliniquesChoisies, lblCliniquesChoisies](){
        QDialog dlg(this);
        dlg.setWindowTitle("Choisir des cliniques");
        dlg.setMinimumWidth(300);
        QVBoxLayout* lay = new QVBoxLayout(&dlg);
        
        QLineEdit* recherche = new QLineEdit(&dlg);
        recherche->setPlaceholderText("Rechercher...");
        
        QListWidget* liste = new QListWidget(&dlg);
        liste->setSelectionMode(QAbstractItemView::MultiSelection);
        for (int i = 0; i < cliniques.size(); i++) {
            Clinique* c = cliniques.at(i);
            QListWidgetItem* item = new QListWidgetItem(QString("%1 - %2").arg(c->getNom(), c->getAdresse()));
            item->setData(Qt::UserRole, i);
            liste->addItem(item);
            // Pré-sélectionner si déjà choisie
            for (Clinique* choisie : cliniquesChoisies) {
                if (choisie == c) {
                    item->setSelected(true);
                }
            }
        }
        
        connect(recherche, &QLineEdit::textChanged, [liste, this](const QString& texte){
            filtrerListeCliniques(liste, texte);
        });
        
        QDialogButtonBox* btns = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dlg);
        connect(btns, SIGNAL(accepted()), &dlg, SLOT(accept()));
        connect(btns, SIGNAL(rejected()), &dlg, SLOT(reject()));
        
        lay->addWidget(recherche);
        lay->addWidget(liste);
        lay->addWidget(btns);
        
        if (dlg.exec() == QDialog::Accepted) {
            cliniquesChoisies.clear();
            QStringList noms;
            for (int i = 0; i < liste->selectedItems().size(); i++) {
                QListWidgetItem* item = liste->selectedItems().at(i);
                int idx = item->data(Qt::UserRole).toInt();
                cliniquesChoisies.append(cliniques.at(idx));
                noms.append(cliniques.at(idx)->getNom());
            }
            if (noms.isEmpty()) {
                lblCliniquesChoisies->setText("Aucune");
            } else {
                lblCliniquesChoisies->setText(noms.join(", "));
            }
        }
    });

    form->addRow(tr("Nom:"), new QLabel(m->getNom()));
    form->addRow(tr("Prénom:"), new QLabel(m->getPrenom()));
    form->addRow(tr("Date de naissance:"), new QLabel(m->getDate_naissance().toString("dd/MM/yyyy")));
    form->addRow(tr("Sexe:"), comboSexe);
    form->addRow(tr("Email:"), editEmail);
    form->addRow(tr("Téléphone:"), editTel);
    form->addRow(tr("Adresse:"), editAdresse);
    form->addRow(tr("Spécialisation:"), editSpecialisation);
    form->addRow(tr("Cliniques:"), widgetCliniques);

    QDialogButtonBox* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    form->addRow(buttons);

    if (dialog.exec() == QDialog::Accepted) {
        if ( comboSexe->currentText().isEmpty() ){
            QMessageBox::critical(this, tr("Erreur"), tr("Le sexe est obligatoire !"));
            return;
        }
        else{
            m->setTelephone(editTel->text());
            m->setAdresse(editAdresse->text());
            m->setSexe(comboSexe->currentText());
            m->setEmail(editEmail->text());
            m->setSpecialisation(editSpecialisation->text());
            
            // Mettre à jour les cliniques
            // Retirer des anciennes cliniques
            QList<Clinique*> anciennesCliniques = m->getCliniques();
            for (Clinique* c : anciennesCliniques) {
                c->retirerMedecin(m);
                m->retirerClinique(c);
            }
            
            // Ajouter aux nouvelles cliniques
            for (Clinique* c : cliniquesChoisies) {
                m->ajouterClinique(c);
                c->ajouterMedecin(m);
            }
            
            afficherMedecins();
            return;
        }
    }
}

void MainWindow::SupprimerMedecin(Medecin *m, int index){
    medecins.removeAt(index);
    delete m;
    afficherMedecins();
    return;
}

// ============================================
// ============== CLINIQUE ====================
// ============================================

QWidget* MainWindow::creerBulleClinique(Clinique* c)
{
    QWidget* bulle = new QWidget();
    bulle->setObjectName("bulle");
    bulle->setProperty("cliniqueId", c->getId());

    QVBoxLayout* layout = new QVBoxLayout(bulle);

    QLabel* lblNom = new QLabel(QString("%1").arg(c->getNom()), bulle);

    QLabel* lblInfo = new QLabel(QString("ID: %1  |  Adresse: %2")
                                 .arg(c->getId(), c->getAdresse()), bulle);

    QLabel* lblContact = new QLabel(QString("Téléphone: %1").arg(c->getTelephone()), bulle);

    layout->addWidget(lblNom);
    layout->addWidget(lblInfo);
    layout->addWidget(lblContact);

    QFrame* ligne = new QFrame(bulle);
    ligne->setFrameShape(QFrame::HLine);
    ligne->setStyleSheet("color: #ccc;");
    layout->addWidget(ligne);

    return bulle;
}

void MainWindow::afficherCliniques()
{
    ui->listWidgetClinique->clear();

    for (Clinique* c : cliniques) {
        QListWidgetItem* item = new QListWidgetItem(ui->listWidgetClinique);
        item->setSizeHint(QSize(350, 75));

        QWidget* bulle = creerBulleClinique(c);
        ui->listWidgetClinique->setItemWidget(item, bulle);
    }
}

void MainWindow::ajouterClinique(Clinique* c){
    cliniques.append(c);
}

void MainWindow::formulaireAjoutClinique(){
    QDialog dialog(this);
    dialog.setWindowTitle("Nouvelle Clinique");

    QFormLayout* form = new QFormLayout(&dialog);

    QLineEdit* editNom = new QLineEdit(&dialog);
    QLineEdit* editAdresse = new QLineEdit(&dialog);
    QLineEdit* editTel = new QLineEdit(&dialog);

    form->addRow(tr("Nom:"), editNom);
    form->addRow(tr("Adresse:"), editAdresse);
    form->addRow(tr("Téléphone:"), editTel);

    QDialogButtonBox* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    form->addRow(buttons);

    if (dialog.exec() == QDialog::Accepted) {
        QString id = QUuid::createUuid().toString(QUuid::WithoutBraces);
        if (editNom->text().trimmed().isEmpty()){
            QMessageBox::critical(this, tr("Erreur"), tr("Le nom est obligatoire !"));
            return;
        }
        else{
            Clinique* c = new Clinique(
                id,
                editNom->text(),
                editAdresse->text(),
                editTel->text()
                );
            ajouterClinique(c);
            afficherCliniques();
            return;
        }
    }
}

void MainWindow::onCliniqueClicked(QListWidgetItem* item)
{
    int index = ui->listWidgetClinique->row(item);
    Clinique* c = cliniques.at(index);

    QDialog dialog(this);
    dialog.setWindowTitle("Fiche Clinique");
    dialog.setMinimumWidth(350);
    QVBoxLayout* layout = new QVBoxLayout(&dialog);
    QLabel* titre = new QLabel(QString("<h2>%1</h2>").arg(c->getNom()));
    titre->setAlignment(Qt::AlignCenter);

    QLabel* infos = new QLabel(QString(
                                   "<b>ID:</b> %1<br>"
                                   "<b>Adresse:</b> %2<br>"
                                   "<b>Téléphone:</b> %3"
                                   ).arg(
                                       c->getId(),
                                       c->getAdresse(),
                                       c->getTelephone()
                                       ));

    // === Section Patients ===
    QLabel* lblPatients = new QLabel("<b>Patients hospitalisés:</b>");
    QLabel* lblNombrePatients = new QLabel(QString("%1 patient(s)").arg(c->getNombrePatientsHospitalises()));
    QPushButton* btnDetailsPatients = new QPushButton("Voir détails");
    connect(btnDetailsPatients, &QPushButton::clicked, [this, c](){
        QDialog dlg(this);
        dlg.setWindowTitle("Patients hospitalisés");
        dlg.setMinimumWidth(400);
        QVBoxLayout* lay = new QVBoxLayout(&dlg);
        
        QLabel* titre = new QLabel(QString("<h3>Patients de %1</h3>").arg(c->getNom()));
        lay->addWidget(titre);
        
        if (c->getPatients().isEmpty()) {
            lay->addWidget(new QLabel("Aucun patient hospitalisé"));
        } else {
            QListWidget* liste = new QListWidget(&dlg);
            for (Patient* p : c->getPatients()) {
                QString info = QString("%1 %2 - %3").arg(p->getPrenom(), p->getNom(), p->getTelephone());
                liste->addItem(info);
            }
            lay->addWidget(liste);
        }
        
        QPushButton* btnFermer = new QPushButton("Fermer", &dlg);
        connect(btnFermer, &QPushButton::clicked, &dlg, &QDialog::accept);
        lay->addWidget(btnFermer);
        
        dlg.exec();
    });
    
    // === Section Médecins ===
    QLabel* lblMedecins = new QLabel("<b>Médecins:</b>");
    QLabel* lblNombreMedecins = new QLabel(QString("%1 médecin(s)").arg(c->getNombreMedecins()));
    QPushButton* btnDetailsMedecins = new QPushButton("Voir détails");
    connect(btnDetailsMedecins, &QPushButton::clicked, [this, c](){
        QDialog dlg(this);
        dlg.setWindowTitle("Médecins de la clinique");
        dlg.setMinimumWidth(400);
        QVBoxLayout* lay = new QVBoxLayout(&dlg);
        
        QLabel* titre = new QLabel(QString("<h3>Médecins de %1</h3>").arg(c->getNom()));
        lay->addWidget(titre);
        
        if (c->getMedecins().isEmpty()) {
            lay->addWidget(new QLabel("Aucun médecin"));
        } else {
            QListWidget* liste = new QListWidget(&dlg);
            for (Medecin* m : c->getMedecins()) {
                QString info = QString("%1 %2 - %3").arg(m->getPrenom(), m->getNom(), m->getSpecialisation());
                liste->addItem(info);
            }
            lay->addWidget(liste);
        }
        
        QPushButton* btnFermer = new QPushButton("Fermer", &dlg);
        connect(btnFermer, &QPushButton::clicked, &dlg, &QDialog::accept);
        lay->addWidget(btnFermer);
        
        dlg.exec();
    });

    QPushButton* btnFermer = new QPushButton("Fermer");
    connect(btnFermer, SIGNAL(clicked()), &dialog, SLOT(close()));
    QPushButton* btnModifier = new QPushButton("Modifier");
    connect(btnModifier, SIGNAL(clicked()), &dialog, SLOT(accept()));
    QPushButton* btnSupprimer = new QPushButton("Supprimer");
    connect(btnSupprimer, &QPushButton::clicked, [&dialog]() { dialog.done(2); });

    layout->addWidget(titre);
    layout->addWidget(infos);
    layout->addSpacing(10);
    layout->addWidget(lblPatients);
    layout->addWidget(lblNombrePatients);
    layout->addWidget(btnDetailsPatients);
    layout->addSpacing(5);
    layout->addWidget(lblMedecins);
    layout->addWidget(lblNombreMedecins);
    layout->addWidget(btnDetailsMedecins);
    layout->addSpacing(10);
    layout->addWidget(btnModifier);
    layout->addWidget(btnSupprimer);
    layout->addWidget(btnFermer);

    int resultat = dialog.exec();

    if (resultat == QDialog::Accepted) {
        ModifierClinique(c);
    }
    else if (resultat == 2) {
        SupprimerClinique(c, index);
    }
}

void MainWindow::ModifierClinique(Clinique *c){
    QDialog dialog(this);
    dialog.setWindowTitle("Modifier Clinique");

    QFormLayout* form = new QFormLayout(&dialog);

    QLineEdit* editNom = new QLineEdit(&dialog);
    QLineEdit* editAdresse = new QLineEdit(&dialog);
    QLineEdit* editTel = new QLineEdit(&dialog);

    editNom->setText(c->getNom());
    editAdresse->setText(c->getAdresse());
    editTel->setText(c->getTelephone());

    form->addRow(tr("ID:"), new QLabel(c->getId()));
    form->addRow(tr("Nom:"), editNom);
    form->addRow(tr("Adresse:"), editAdresse);
    form->addRow(tr("Téléphone:"), editTel);

    QDialogButtonBox* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    form->addRow(buttons);

    if (dialog.exec() == QDialog::Accepted) {
        if (editNom->text().trimmed().isEmpty()){
            QMessageBox::critical(this, tr("Erreur"), tr("Le nom est obligatoire !"));
            return;
        }
        else{
            c->setNom(editNom->text());
            c->setAdresse(editAdresse->text());
            c->setTelephone(editTel->text());
            afficherCliniques();
            return;
        }
    }
}

void MainWindow::SupprimerClinique(Clinique *c, int index){
    cliniques.removeAt(index);
    delete c;
    afficherCliniques();
    return;
}

// ============================================
// ============== ALLERGIE ====================
// ============================================

QWidget* MainWindow::creerBulleAllergie(Allergie* a)
{
    QWidget* bulle = new QWidget();
    bulle->setObjectName("bulle");

    QVBoxLayout* layout = new QVBoxLayout(bulle);

    QLabel* lblNom = new QLabel(QString("%1").arg(a->getNom()), bulle);

    QLabel* lblDesc = new QLabel(QString("Description: %1").arg(a->getDescription()), bulle);

    layout->addWidget(lblNom);
    layout->addWidget(lblDesc);

    QFrame* ligne = new QFrame(bulle);
    ligne->setFrameShape(QFrame::HLine);
    ligne->setStyleSheet("color: #ccc;");
    layout->addWidget(ligne);

    return bulle;
}

void MainWindow::afficherAllergies()
{
    ui->listWidgetAllergie->clear();

    for (int i = 0; i < allergies.size(); i++) {
        QListWidgetItem* item = new QListWidgetItem(ui->listWidgetAllergie);
        item->setSizeHint(QSize(350, 60));

        QWidget* bulle = creerBulleAllergie(&allergies[i]);
        ui->listWidgetAllergie->setItemWidget(item, bulle);
    }
}

void MainWindow::ajouterAllergie(const Allergie& a){
    allergies.append(a);
}

void MainWindow::formulaireAjoutAllergie(){
    QDialog dialog(this);
    dialog.setWindowTitle("Nouvelle Allergie");

    QFormLayout* form = new QFormLayout(&dialog);

    QLineEdit* editNom = new QLineEdit(&dialog);
    QLineEdit* editDescription = new QLineEdit(&dialog);

    form->addRow("Nom:", editNom);
    form->addRow("Description:", editDescription);

    QDialogButtonBox* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    form->addRow(buttons);

    if (dialog.exec() == QDialog::Accepted) {
        if (editNom->text().trimmed().isEmpty()){
            QMessageBox::critical(this, tr("Erreur"), tr("Le nom est obligatoire !"));
            return;
        }
        else{
            Allergie a(editNom->text(), editDescription->text());
            ajouterAllergie(a);
            afficherAllergies();
            return;
        }
    }
}

void MainWindow::onAllergieClicked(QListWidgetItem* item)
{
    int index = ui->listWidgetAllergie->row(item);
    Allergie* a = &allergies[index];

    QDialog dialog(this);
    dialog.setWindowTitle("Fiche Allergie");
    dialog.setMinimumWidth(350);
    QVBoxLayout* layout = new QVBoxLayout(&dialog);
    QLabel* titre = new QLabel(QString("<h2>%1</h2>").arg(a->getNom()));
    titre->setAlignment(Qt::AlignCenter);

    QLabel* infos = new QLabel(QString(
                                   "<b>Nom:</b> %1<br>"
                                   "<b>Description:</b> %2"
                                   ).arg(
                                       a->getNom(),
                                       a->getDescription()
                                       ));
    QPushButton* btnFermer = new QPushButton("Fermer");
    connect(btnFermer, SIGNAL(clicked()), &dialog, SLOT(close()));
    QPushButton* btnModifier = new QPushButton("Modifier");
    connect(btnModifier, SIGNAL(clicked()), &dialog, SLOT(accept()));
    QPushButton* btnSupprimer = new QPushButton("Supprimer");
    connect(btnSupprimer, &QPushButton::clicked, [&dialog]() { dialog.done(2); });

    layout->addWidget(titre);
    layout->addWidget(infos);
    layout->addSpacing(10);
    layout->addWidget(btnModifier);
    layout->addWidget(btnSupprimer);
    layout->addWidget(btnFermer);

    int resultat = dialog.exec();

    if (resultat == QDialog::Accepted) {
        ModifierAllergie(index);
    }
    else if (resultat == 2) {
        SupprimerAllergie(index);
    }
}

void MainWindow::ModifierAllergie(int index){
    Allergie* a = &allergies[index];

    QDialog dialog(this);
    dialog.setWindowTitle("Modifier Allergie");

    QFormLayout* form = new QFormLayout(&dialog);

    QLineEdit* editNom = new QLineEdit(&dialog);
    QLineEdit* editDescription = new QLineEdit(&dialog);

    editNom->setText(a->getNom());
    editDescription->setText(a->getDescription());

    form->addRow(tr("Nom:"), editNom);
    form->addRow(tr("Description:"), editDescription);

    QDialogButtonBox* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    form->addRow(buttons);

    if (dialog.exec() == QDialog::Accepted) {
        if (editNom->text().trimmed().isEmpty()){
            QMessageBox::critical(this, tr("Erreur"), tr("Le nom est obligatoire !"));
            return;
        }
        else{
            a->setNom(editNom->text());
            a->setDescription(editDescription->text());
            afficherAllergies();
            return;
        }
    }
}

void MainWindow::SupprimerAllergie(int index){
    allergies.removeAt(index);
    afficherAllergies();
    return;
}

void MainWindow::rechercherPatient(const QString& texte)
{
    for (int i = 0; i < ui->listWidgetPatient->count(); i++) {
        QListWidgetItem* item = ui->listWidgetPatient->item(i);
        Patient* p = patients.at(i);

        bool correspond = texte.isEmpty() ||
                          p->getId().contains(texte, Qt::CaseInsensitive) ||
                          p->getNom().contains(texte, Qt::CaseInsensitive) ||
                          p->getPrenom().contains(texte, Qt::CaseInsensitive) ||
                          p->getAdresse().contains(texte, Qt::CaseInsensitive) ||
                          p->getSexe().contains(texte, Qt::CaseInsensitive) ||
                          p->getEmail().contains(texte, Qt::CaseInsensitive) ||
                          p->getTelephone().contains(texte, Qt::CaseInsensitive) ||
                          p->getDate_naissance().toString("dd/MM/yyyy").contains(texte, Qt::CaseInsensitive);

        item->setHidden(!correspond);
    }
}

void MainWindow::filtrerListeMedecins(QListWidget* liste, const QString& texte)
{
    for (int i = 0; i < liste->count(); i++) {
        QListWidgetItem* item = liste->item(i);
        int idx = item->data(Qt::UserRole).toInt();
        Medecin* m = medecins.at(idx);
        bool correspond = false;
        if (texte.isEmpty()) {
            correspond = true;
        } else if (m->getNom().contains(texte, Qt::CaseInsensitive)) {
            correspond = true;
        } else if (m->getPrenom().contains(texte, Qt::CaseInsensitive)) {
            correspond = true;
        }
        item->setHidden(!correspond);
    }
}

void MainWindow::filtrerListeCliniques(QListWidget* liste, const QString& texte)
{
    for (int i = 0; i < liste->count(); i++) {
        QListWidgetItem* item = liste->item(i);
        int idx = item->data(Qt::UserRole).toInt();
        Clinique* c = cliniques.at(idx);
        bool correspond = false;
        if (texte.isEmpty()) {
            correspond = true;
        } else if (c->getNom().contains(texte, Qt::CaseInsensitive)) {
            correspond = true;
        } else if (c->getAdresse().contains(texte, Qt::CaseInsensitive)) {
            correspond = true;
        }
        item->setHidden(!correspond);
    }
}

void MainWindow::filtrerListeAllergies(QListWidget* liste, const QString& texte)
{
    for (int i = 0; i < liste->count(); i++) {
        QListWidgetItem* item = liste->item(i);
        int idx = item->data(Qt::UserRole).toInt();
        bool correspond = false;
        if (texte.isEmpty()) {
            correspond = true;
        } else if (allergies[idx].getNom().contains(texte, Qt::CaseInsensitive)) {
            correspond = true;
        }
        item->setHidden(!correspond);
    }
}

void MainWindow::rechercherMedecin(const QString& texte)
{
    for (int i = 0; i < ui->listWidgetMedecin->count(); i++) {
        QListWidgetItem* item = ui->listWidgetMedecin->item(i);
        Medecin* m = medecins.at(i);

        bool correspond = texte.isEmpty() ||
                          m->getId().contains(texte, Qt::CaseInsensitive) ||
                          m->getNom().contains(texte, Qt::CaseInsensitive) ||
                          m->getPrenom().contains(texte, Qt::CaseInsensitive) ||
                          m->getSpecialisation().contains(texte, Qt::CaseInsensitive) ||
                          m->getEmail().contains(texte, Qt::CaseInsensitive) ||
                          m->getTelephone().contains(texte, Qt::CaseInsensitive);

        item->setHidden(!correspond);
    }
}

void MainWindow::rechercherClinique(const QString& texte)
{
    for (int i = 0; i < ui->listWidgetClinique->count(); i++) {
        QListWidgetItem* item = ui->listWidgetClinique->item(i);
        Clinique* c = cliniques.at(i);

        bool correspond = texte.isEmpty() ||
                          c->getId().contains(texte, Qt::CaseInsensitive) ||
                          c->getNom().contains(texte, Qt::CaseInsensitive) ||
                          c->getAdresse().contains(texte, Qt::CaseInsensitive) ||
                          c->getTelephone().contains(texte, Qt::CaseInsensitive);

        item->setHidden(!correspond);
    }
}

void MainWindow::rechercherAllergie(const QString& texte)
{
    for (int i = 0; i < ui->listWidgetAllergie->count(); i++) {
        QListWidgetItem* item = ui->listWidgetAllergie->item(i);
        Allergie a = allergies.at(i);

        bool correspond = texte.isEmpty() ||
                          a.getNom().contains(texte, Qt::CaseInsensitive) ||
                          a.getDescription().contains(texte, Qt::CaseInsensitive);

        item->setHidden(!correspond);
    }
}

void MainWindow::exporterDonnees()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Exporter les données"), "", tr("Fichiers JSON (*.json)"));
    if (fileName.isEmpty())
        return;

    QJsonObject root;

    // Export Patients
    QJsonArray patientsArray;
    for (Patient* p : patients) {
        QJsonObject patientObj;
        patientObj["id"] = p->getId();
        patientObj["nom"] = p->getNom();
        patientObj["prenom"] = p->getPrenom();
        patientObj["dateNaissance"] = p->getDate_naissance().toString("yyyy-MM-dd");
        patientObj["adresse"] = p->getAdresse();
        patientObj["sexe"] = p->getSexe();
        patientObj["email"] = p->getEmail();
        patientObj["telephone"] = p->getTelephone();
        
        // Médecin associé
        if (p->getMedecin()) {
            patientObj["medecinId"] = p->getMedecin()->getId();
        }
        
        // Clinique associée
        if (p->getClinique()) {
            patientObj["cliniqueId"] = p->getClinique()->getId();
        }
        
        // Allergies
        QJsonArray allergiesArray;
        for (const Allergie& a : p->getAllergies()) {
            allergiesArray.append(a.getNom());
        }
        patientObj["allergies"] = allergiesArray;
        
        patientsArray.append(patientObj);
    }
    root["patients"] = patientsArray;

    // Export Medecins
    QJsonArray medecinsArray;
    for (Medecin* m : medecins) {
        QJsonObject medecinObj;
        medecinObj["id"] = m->getId();
        medecinObj["nom"] = m->getNom();
        medecinObj["prenom"] = m->getPrenom();
        medecinObj["dateNaissance"] = m->getDate_naissance().toString("yyyy-MM-dd");
        medecinObj["adresse"] = m->getAdresse();
        medecinObj["sexe"] = m->getSexe();
        medecinObj["email"] = m->getEmail();
        medecinObj["telephone"] = m->getTelephone();
        medecinObj["specialisation"] = m->getSpecialisation();
        
        // Cliniques associées
        QJsonArray cliniquesArray;
        for (Clinique* c : m->getCliniques()) {
            cliniquesArray.append(c->getId());
        }
        medecinObj["cliniques"] = cliniquesArray;
        
        medecinsArray.append(medecinObj);
    }
    root["medecins"] = medecinsArray;

    // Export Cliniques
    QJsonArray cliniquesArray;
    for (Clinique* c : cliniques) {
        QJsonObject cliniqueObj;
        cliniqueObj["id"] = c->getId();
        cliniqueObj["nom"] = c->getNom();
        cliniqueObj["adresse"] = c->getAdresse();
        cliniqueObj["telephone"] = c->getTelephone();
        cliniquesArray.append(cliniqueObj);
    }
    root["cliniques"] = cliniquesArray;

    // Export Allergies
    QJsonArray allergiesArray;
    for (Allergie a : allergies) {
        QJsonObject allergieObj;
        allergieObj["nom"] = a.getNom();
        allergieObj["description"] = a.getDescription();
        allergiesArray.append(allergieObj);
    }
    root["allergies"] = allergiesArray;

    QJsonDocument doc(root);
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson());
        file.close();
        QMessageBox::information(this, tr("Succès"), tr("Données exportées avec succès !"));
    } else {
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible d'écrire le fichier !"));
    }
}

void MainWindow::importerDonnees()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Importer les données"), "", tr("Fichiers JSON (*.json)"));
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible d'ouvrir le fichier !"));
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isObject()) {
        QMessageBox::critical(this, tr("Erreur"), tr("Format JSON invalide !"));
        return;
    }

    // Demander confirmation
    QMessageBox::StandardButton reply = QMessageBox::question(this, tr("Confirmation"),
        tr("L'importation effacera toutes les données actuelles. Continuer ?"),
        QMessageBox::Yes | QMessageBox::No);
    
    if (reply != QMessageBox::Yes)
        return;

    // Nettoyer les données actuelles
    qDeleteAll(patients);
    patients.clear();
    qDeleteAll(medecins);
    medecins.clear();
    qDeleteAll(cliniques);
    cliniques.clear();
    allergies.clear();

    QJsonObject root = doc.object();

    // Import Allergies (d'abord car référencées par patients)
    if (root.contains("allergies")) {
        QJsonArray allergiesArray = root["allergies"].toArray();
        for (const QJsonValue& val : allergiesArray) {
            QJsonObject obj = val.toObject();
            Allergie a(obj["nom"].toString(), obj["description"].toString());
            allergies.append(a);
        }
    }

    // Import Cliniques (avant médecins et patients)
    if (root.contains("cliniques")) {
        QJsonArray cliniquesArray = root["cliniques"].toArray();
        for (const QJsonValue& val : cliniquesArray) {
            QJsonObject obj = val.toObject();
            Clinique* c = new Clinique(
                obj["id"].toString(),
                obj["nom"].toString(),
                obj["adresse"].toString(),
                obj["telephone"].toString()
            );
            cliniques.append(c);
        }
    }

    // Import Medecins (avant patients car référencés)
    if (root.contains("medecins")) {
        QJsonArray medecinsArray = root["medecins"].toArray();
        for (const QJsonValue& val : medecinsArray) {
            QJsonObject obj = val.toObject();
            Medecin* m = new Medecin(
                obj["id"].toString(),
                obj["nom"].toString(),
                obj["prenom"].toString(),
                QDate::fromString(obj["dateNaissance"].toString(), "yyyy-MM-dd"),
                obj["adresse"].toString(),
                obj["sexe"].toString(),
                obj["email"].toString(),
                obj["telephone"].toString(),
                obj["specialisation"].toString()
            );
            medecins.append(m);
        }
    }

    // Import Patients
    if (root.contains("patients")) {
        QJsonArray patientsArray = root["patients"].toArray();
        for (const QJsonValue& val : patientsArray) {
            QJsonObject obj = val.toObject();
            Patient* p = new Patient(
                obj["id"].toString(),
                obj["nom"].toString(),
                obj["prenom"].toString(),
                QDate::fromString(obj["dateNaissance"].toString(), "yyyy-MM-dd"),
                obj["adresse"].toString(),
                obj["sexe"].toString(),
                obj["email"].toString(),
                obj["telephone"].toString()
            );
            patients.append(p);
        }
    }

    // Rétablir les relations Medecin-Clinique
    if (root.contains("medecins")) {
        QJsonArray medecinsArray = root["medecins"].toArray();
        for (int i = 0; i < medecinsArray.size(); i++) {
            QJsonObject obj = medecinsArray[i].toObject();
            Medecin* m = medecins[i];
            
            if (obj.contains("cliniques")) {
                QJsonArray cliniquesIds = obj["cliniques"].toArray();
                for (const QJsonValue& cId : cliniquesIds) {
                    QString cliniqueId = cId.toString();
                    for (Clinique* c : cliniques) {
                        if (c->getId() == cliniqueId) {
                            m->ajouterClinique(c);
                            c->ajouterMedecin(m);
                            break;
                        }
                    }
                }
            }
        }
    }

    // Rétablir les relations Patient-Medecin-Clinique-Allergie
    if (root.contains("patients")) {
        QJsonArray patientsArray = root["patients"].toArray();
        for (int i = 0; i < patientsArray.size(); i++) {
            QJsonObject obj = patientsArray[i].toObject();
            Patient* p = patients[i];
            
            // Médecin
            if (obj.contains("medecinId")) {
                QString medecinId = obj["medecinId"].toString();
                for (Medecin* m : medecins) {
                    if (m->getId() == medecinId) {
                        p->setMedecin(m);
                        m->ajouterPatient(p);
                        break;
                    }
                }
            }
            
            // Clinique
            if (obj.contains("cliniqueId")) {
                QString cliniqueId = obj["cliniqueId"].toString();
                for (Clinique* c : cliniques) {
                    if (c->getId() == cliniqueId) {
                        p->setHospitalisation(c);
                        c->hospitaliserPatient(p);
                        break;
                    }
                }
            }
            
            // Allergies
            if (obj.contains("allergies")) {
                QJsonArray allergiesNames = obj["allergies"].toArray();
                for (const QJsonValue& aName : allergiesNames) {
                    QString allergieName = aName.toString();
                    for (const Allergie& a : allergies) {
                        if (a.getNom() == allergieName) {
                            p->ajouterAllergie(a);
                            break;
                        }
                    }
                }
            }
        }
    }

    // Rafraîchir l'affichage
    afficherPatients();
    afficherMedecins();
    afficherCliniques();
    afficherAllergies();
}

/**
 * @brief Affiche la boîte de dialogue "À propos"
 */
void MainWindow::afficherAPropos()
{
    QMessageBox::about(this, 
        tr("À propos"),
        tr("<h2>SGM - Système de Gestion Médicale</h2>"
           "<p>Version 1.0</p>"
           "<p>Application de gestion de fiches patients, médecins et cliniques.</p>"
           "<p><b>Auteurs:</b> Bilal Kefif et Soni Diedhiou</p>"
           "<p>Projet scolaire Qt/C++</p>"));
}

/**
 * @brief Change la langue de l'application en français
 */
void MainWindow::changerLangueFrancais()
{
    qApp->removeTranslator(&translator);
    ui->retranslateUi(this);
}

/**
 * @brief Change la langue de l'application en anglais
 */
void MainWindow::changerLangueAnglais()
{
    // Chercher le fichier .qm dans le dossier build ou à côté de l'exécutable
    QString path = QCoreApplication::applicationDirPath() + "/sgm_en.qm";
    if (translator.load(path)) {
        qApp->installTranslator(&translator);
        ui->retranslateUi(this);
    }
}

