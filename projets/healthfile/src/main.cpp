#include "mainwindow.h"

#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    // Infos application (pour QSettings et À propos)
    a.setApplicationName("SGM");
    a.setApplicationVersion("1.0");
    a.setOrganizationName("Bilal");
    
    // Icône de l'application
    a.setWindowIcon(QIcon(":/icons/healthfile.png"));
    
    MainWindow w;
    w.show();
    return a.exec();
}
