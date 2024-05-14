#include "mainwindow.h"
#include "endwindow.h"
#include "loginwindow.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Mario_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    //w.show();  //gamewiget
    loginwindow l;
    endwindow e;
    e.show();
    QObject::connect(&l,&loginwindow::startGame,&w,&MainWindow::show);
    QObject::connect(&e,&endwindow::reset,&l,&loginwindow::show);
    //l.show();

    return a.exec();
}
