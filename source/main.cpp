#include <QGuiApplication>
#include <QtQuick/QQuickView>
#include <QQmlEngine>
#include <QQmlContext>
#include <QDir>
#include <QMutex>

#include "Background.h"
#include "ComboBoxModel.h"
#include "keyboard.h"


HHOOK hHook = NULL;  // keyboard hook
Keyboard kbd;  // paths, app
QMutex mut;


///  Key hook
//-------------------------------------------------------------------------------------------------------
LRESULT CALLBACK keyHandler(int nCode, WPARAM wp, LPARAM lp)
{
    if (nCode < 0)
        return CallNextHookEx(hHook, nCode, wp, lp);

    if (nCode == HC_ACTION)
    {
        KBDLLHOOKSTRUCT k = *((KBDLLHOOKSTRUCT*)lp);
        int vk = k.vkCode & 0xFF;
        //Key sk;
        //sk.sc = k.scanCode & 0xFF;
        //sk.ex = k.flags & LLKHF_EXTENDED ? 1 : 0;

        QObject *o = kbd.vk2obj[vk];

        if (o)
        if (wp == WM_SYSKEYDOWN || wp == WM_KEYDOWN)  // press
        {
            mut.lock();
            o->setProperty("on", true);
            //kbd.AddKey(sk);
            mut.unlock();
        }
        else
        if (wp == WM_SYSKEYUP || wp == WM_KEYUP)  // release
        {
            mut.lock();
            o->setProperty("on", false);
            //kbd.RemKey(sk);
            mut.unlock();
        }
    }
    return CallNextHookEx(hHook, nCode, wp, lp);
}


//  main
//-----------------------------------------------------------------------------------------------------------
int main(int argc, char **argv)
{
    //  init
    QGuiApplication app(argc, argv);

    if (!kbd.Init(QCoreApplication::applicationDirPath()))
    {
        //QMessageBox(QMessageBox::Critical, "CKeys", "Can't find data path!", QMessageBox::Ok);
        return -1;
    }

    //  hook kbd  * *
    hHook = SetWindowsHookEx(WH_KEYBOARD_LL, keyHandler, NULL, 0);


    //  main.qml  gui create, load
    //-----------------------------------
    qmlRegisterType<Background>("QBackground", 1, 0, "Background");

    QQuickView view;
    view.setSource(QUrl::fromLocalFile(kbd.data + "main.qml"));
    QQmlEngine& engine = *view.engine();
    view.create();


    //  list files in dir, layout .json
    //-----------------------------------
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
    kbd.root = view.rootObject();
    Background *bck = kbd.root->findChild<Background*>("base");

    kbd.LoadIndex(2);  // last .set

    //  fps  ----
    QObject* oFps = kbd.root->findChild<QObject*>("fps");
    if (bck)  bck->setFps(oFps);


    //  run
    //-----------------------------------
    QObject::connect(view.engine(), SIGNAL(quit()), qApp, SLOT(quit()));
    view.show();

    int ret = app.exec();

    //  unhook  * *
    UnhookWindowsHookEx(hHook);

    return ret;
}
