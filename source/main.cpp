#include <QGuiApplication>
#include <QtQuick/QQuickView>
#include <QQmlEngine>
#include <QQmlContext>
#include <QDir>

#include "squircle.h"
#include "ComboBoxModel.h"
#include "keyboard.h"


static bool exists(QString path)
{
    QDir d(path);
    return d.exists();
}


//  main
//-----------------------------------------------------------------------------------------------------------
int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);

    //  find data path
    QString adp = QCoreApplication::applicationDirPath(), data;
    data = adp + "/data/";
    if (!exists(data)) {
        data = adp + "/../data/";
        if (!exists(data)) {
            data = adp + "/../../data/";
            if (!exists(data)) {
                //QMessageBox(QMessageBox::Critical, "CKeys", "Can't find data path!", QMessageBox::Ok);
                return -1;
    }   }   }

    //  main.qml  gui create, load
    qmlRegisterType<Squircle>("QSquircle", 1, 0, "Squircle");


    QQuickView view;
    view.setSource(QUrl::fromLocalFile(data + "main.qml"));
    QQmlEngine& engine = *view.engine();
    view.create();


    //  list files in dir, layout json
    //====================================
    QDir path(data);
    QStringList files = path.entryList(QStringList("*.json"), QDir::Files);


    //  fill combobox  ----
    ComboBoxModel combo;
    combo.setComboList(files);
    view.rootContext()->setContextProperty("comboModel", &combo);



    //Squircle* sq = view.findChild<Squircle*>("base");  //-
    //const QVariant &parent = QVariant::fromValue<QObject*>(/*root/*engine.rootObjects().first()*/);
    QQmlComponent cBtn(&engine, QUrl::fromLocalFile(data + "Button.qml"));

    Keyboard kbd;
    ev.kbd = &kbd;
    kbd.LoadFromJson(cBtn, view.rootContext(), data.toStdString() + "default.json");


    //  info
    //-----------------------------------------------------------
    #if 0
    QObject *o = co.create();
    o->setProperty("xx", 20);  o->setProperty("yy", 20);
    o->setProperty("w", 100);  o->setProperty("h", 30);
    o->setProperty("sc", 16);
    o->setProperty("txt", "Info");
    o->setProperty("parent", parent);
    #endif


    //  run
    QObject::connect(view.engine(), SIGNAL(quit()), qApp, SLOT(quit()));
    view.show();

    return app.exec();
}
