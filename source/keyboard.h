#pragma once
#include <string>
#include <vector>
#include <QQmlComponent>
#include <QStringList>
#include <QDir>

class QObject;


class Keyboard
{
public:
    Keyboard();

    //  init, path  ----
    bool Init(QString appPath);

    QString data;  // path to data dir

    //  load layouts  ----
    void LoadIndex(int id);
    void LoadFromJson(std::string path);
    QObject* AddButton(
        int x, int y, int w, int h, float sc, QString txt);
    void Remove();

    QStringList files;  // .json layouts

//private:  //  ----
    QQmlComponent* cBtn;
    QObject *root;
    std::vector<QObject*> objs;  // key buttons
};


//  utility
static bool exists(QString path)
{
    QDir d(path);
    return d.exists();
}

//  replace in string
static bool replK(std::string& str, const std::string& what, const std::string& to)
{
    size_t p = str.find(what);
    bool rep = p != std::string::npos;
    if (rep)
        str.replace(p, what.length(), to);
    return rep;
}
