#pragma once
#include <string>
#include <vector>
#include <QQmlComponent>

class QObject;

class Keyboard
{
public:
    void LoadFromJson(QQmlComponent& cBtn, QObject *root, std::string path);
    void Remove();

    std::vector<QObject*> objs;
};
