#include <QGuiApplication>
#include <QtQuick/QQuickView>
#include <QQmlContext>
#include <QDir>

#include <string>
#include <fstream>
#include <sstream>
using namespace std;

#include "squircle.h"
#include "jsmn.h"
#include "ComboBoxModel.h"


static bool replK(string& str, const string& what, const string& to)
{
    size_t p = str.find(what);
    bool rep = p != string::npos;
    if (rep)
        str.replace(p, what.length(), to);
    return rep;
}

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

    //  qml gui create, load
    qmlRegisterType<Squircle>("QSquircle", 1, 0, "Squircle");
    QQuickView view;

    view.setResizeMode(QQuickView::SizeRootObjectToView);
    //view.setFlags();
    view.setSource(QUrl::fromLocalFile(data + "main.qml"));
    view.create();


    //  list files in dir, layout json
    //====================================
    QDir path(data);
    QStringList files = path.entryList(QStringList("*.json"), QDir::Files);


    //  fill combobox  ----
    ComboBoxModel combo;
    //QStringList tmp;  tmp << "1" << "2" << "3";
    combo.setComboList(files);
    view.rootContext()->setContextProperty("comboModel", &combo);

//    Squircle* sq = view.findChild<Squircle*>("base");  //-
    const QVariant &parent = QVariant::fromValue<QObject*>(view.rootObject());
    QQmlComponent co(view.engine(), QUrl::fromLocalFile(data + "Button.qml"));



    //  read json layout from file
    //-----------------------------------------------------------------------------------------------------------
    ifstream f(data.toStdString()+"default.json");
    stringstream ss;  ss << f.rdbuf();
    string str = ss.str();
    const char* s = str.c_str();

    //  jsmn json
    int i,r;
    jsmn_parser p;
    jsmntok_t t[512];  // const max
    jsmn_init(&p);

    QString re;  string q;
    r = jsmn_parse(&p, s, strlen(s), t, sizeof(t)/sizeof(t[0]));
    if (r < 0) {
        re += QString("Failed to parse JSON: %1\n").arg(r);
    }
    int x=0, y=0;
    float w=1.f, h=1.f;  string prim;
    const float sc = 1.3f;
    const int  sx = 40 * sc, sy = sx, se = 5,  // size x,y, empty margin
             yfnt = 14 * sc, x0 = 30, y0 = 120;  // font, start pos

    //  iterate all
    //-----------------------------------------------------------
    for (i = 1; i < r; i++)
    {
        if (t[i].type == JSMN_ARRAY)
        {   x = 0;  y += sy;  w = 1.f;  h = 1.f;  // next row
        }
        else
        if (t[i].type == JSMN_STRING)
        {
            //  key text
            string k = str.substr(t[i].start, t[i].end - t[i].start);
            if (k[0]>='a' && k[0]<='z')
                prim = k;
            else
            {
                //  replace
                /*bool k2 =*/ replK(k, "\\n", "\n");  // key has 2 descr: up,dn
                replK(k, "Lock", "");  // rem Lock
                replK(k, "\\\\", "\\");
                replK(k, "\\\"", "\"");

                //  font scale
                float sf = w < 0.7f ? 0.6f/*ck4 mini*/ : 0.8f;
                //float sf = k2 ? 0.8f :
                //    k.length() > 1 ? 0.7f : 1.f;

                //  add key in qml
                QObject *o = co.create();
                o->setProperty("xx", x0 + x);  x += w * sx;
                o->setProperty("yy", y0 + y);
                o->setProperty("w", sx * w - se);
                o->setProperty("h", sy * h - se);
                o->setProperty("txt", QString(k.c_str()));
                o->setProperty("sc", sf * yfnt);
                o->setProperty("parent", parent);
                //o->setProperty("on", rand()%40<=2);  //test
                w = 1.f;  h = 1.f;  // reset
        }   }
        else
        if (t[i].type == JSMN_PRIMITIVE)
        {
            string p = str.substr(t[i].start, t[i].end - t[i].start);
            if (p[0]>='a' && p[0]<='z')
                prim = p;
            else
            {   float f = 0.f;
                sscanf(p.c_str(), "%f", &f);

                if (prim == "x")  x += f * sx;
                else
                if (prim == "y")  y += f * sy;
                else
                if (prim == "w")  w = f;
                else
                if (prim == "h")  h = f;
            }
        }
    }


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
    //-----------------------------------------------------------
    view.show();

    return app.exec();
}
