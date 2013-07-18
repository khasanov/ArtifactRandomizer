#if QT_VERSION < 0x050000
#include <QTextCodec>
#endif

//#include <QTranslator>
//#include <QLibraryInfo>

#include <QApplication>

#include "MainWidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

#if QT_VERSION < 0x050000
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
#endif

    //QTranslator qtTranslator;
    //qtTranslator.load("qt_ru", QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    //app.installTranslator(&qtTranslator);

    MainWidget w;
    w.setMinimumSize(w.sizeHint());
    w.show();

    return app.exec();
}
