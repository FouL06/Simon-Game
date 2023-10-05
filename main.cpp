#include "simongame.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "model.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "A5-SimonGame_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    Model model;
    SimonGame w(model);
    w.show();
    return a.exec();
}
