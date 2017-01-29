#include <QGuiApplication>
#include <QtQuick/QQuickView>
#include <QQmlEngine>
#include <QQmlContext>
#include <QDir>

#include "Background.h"
#include "ComboBoxModel.h"
#include "keyboard.h"


//  main
//-----------------------------------------------------------------------------------------------------------
int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);

    Keyboard kbd;  // paths
    if (!kbd.Init(QCoreApplication::applicationDirPath()))
    {
                //QMessageBox(QMessageBox::Critical, "CKeys", "Can't find data path!", QMessageBox::Ok);
                return -1;
    }

    //  main.qml  gui create, load
    qmlRegisterType<Background>("QBackground", 1, 0, "Background");


    QQuickView view;
    view.setSource(QUrl::fromLocalFile(kbd.data + "main.qml"));
    QQmlEngine& engine = *view.engine();
    view.create();



    //  list files in dir, layout .json
    //----------------------------
    QDir path(kbd.data);
    kbd.files = path.entryList(QStringList("*.json"), QDir::Files);

    //  fill combobox
    ComboBoxModel combo;
    combo.setComboList(kbd.files);
    view.rootContext()->setContextProperty("comboModel", &combo);

    GuiEvent ev;
    view.rootContext()->setContextProperty("GuiEvent", &ev);

    QQmlComponent cBtn(&engine, QUrl::fromLocalFile(kbd.data + "Button.qml"));

    ev.kbd = &kbd;
    kbd.cBtn = &cBtn;
    kbd.root = view.rootObject();  //engine.rootObjects().first();
    Background *bck = kbd.root->findChild<Background*>("base");

    kbd.LoadIndex(2);  // last .set

    //  fps
    QObject* oFps = kbd.root->findChild<QObject*>("fps");
    if (bck)  bck->setFps(oFps);


    //  run
    QObject::connect(view.engine(), SIGNAL(quit()), qApp, SLOT(quit()));
    view.show();

    return app.exec();
}
