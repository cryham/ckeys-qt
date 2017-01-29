#include "keyboard.h"
#include <string>
#include <fstream>
#include <sstream>

#include "jsmn.h"
#include <QQmlProperty>
#include <QQmlEngine>
using namespace std;


static bool replK(string& str, const string& what, const string& to)
{
    size_t p = str.find(what);
    bool rep = p != string::npos;
    if (rep)
        str.replace(p, what.length(), to);
    return rep;
}

void Keyboard::LoadFromJson(QQmlComponent& cBtn, QObject *root, std::string path)
{
    //  read json layout from file
    //-----------------------------------------------------------------------------------------------------------
    ifstream f(path);
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
                /*bool k2 = */replK(k, "\\n", "\n");  // key has 2 descr: up,dn
                replK(k, "Lock", "");  // rem Lock
                replK(k, "\\\\", "\\");
                replK(k, "\\\"", "\"");

                //  font scale
                float sf = w < 0.7f ? 0.6f/*ck4 mini*/ : 0.8f;
                //float sf = k2 ? 0.8f :
                //    k.length() > 1 ? 0.7f : 1.f;

                //  add key in qml
                QObject *o = cBtn.create();
                o->setProperty("xx", x0 + x);  x += w * sx;
                o->setProperty("yy", y0 + y);
                o->setProperty("w", sx * w - se);
                o->setProperty("h", sy * h - se);
                o->setProperty("txt", QString(k.c_str()));
                o->setProperty("sc", sf * yfnt);

                //o->setProperty("parent", parent);
                QQmlProperty::write(o, "parent", QVariant::fromValue<QObject*>(root));
                QQmlEngine::setObjectOwnership(o, QQmlEngine::CppOwnership);
                //o->deleteLater();  //remove all..
                objs.push_back(o);

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

}

void Keyboard::Remove()
{
    //  remove layout, all keys
    foreach (auto o, objs) {
        o->deleteLater();
    }
    objs.clear();
}
