/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QGuiApplication>
#include <QtQuick/QQuickView>

#include <string>
#include <fstream>
#include <sstream>
using namespace std;

#include "squircle.h"
#include "jsmn.h"


static bool replK(string& str, const string& what, const string& to)
{
    size_t p = str.find(what);
    bool rep = p != string::npos;
    if (rep)
        str.replace(p, what.length(), to);
    return rep;
}


int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);

    //  find data path
	QString data = app.applicationDirPath();
    if (data.contains("build"))
        data += "/../../data/";
    else
    if (data.contains("bin"))
        data += "/../data/";
    else
        data += "/data/";

    //  qml gui create, load
    qmlRegisterType<Squircle>("OpenGLUnderQML", 1, 0, "Squircle");

    QQuickView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    //view.setFlags();
    view.setSource(QUrl("qrc:///main.qml"));
    view.create();

//    Squircle* sq = view.findChild<Squircle*>("base");  //-
    const QVariant &parent = QVariant::fromValue<QObject*>(view.rootObject());
    QQmlComponent co(view.engine(), QUrl("qrc:///Button.qml"));


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
                bool k2 = replK(k, "\\n", "\n");  // key has 2 descr: up,dn
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
