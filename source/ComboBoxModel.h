#pragma once
#include <QObject>
#include <QStringList>
#include <QDebug>

#include "keyboard.h"


class ComboBoxModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QStringList comboList READ comboList WRITE setComboList NOTIFY comboListChanged)
    Q_PROPERTY(int count READ count WRITE setCount NOTIFY countChanged)

public:
    ComboBoxModel(QObject *parent = 0);
    ComboBoxModel(const QStringList &list,int count, QObject *parent = 0);

    const QStringList comboList();
    void setComboList(const QStringList &comboList);

    int count();
    void setCount(int cnt);

    Q_INVOKABLE void addElement(const QString &element);
    Q_INVOKABLE void removeElement(int index);

signals:

    void comboListChanged();
    void countChanged();

public slots:


private:

    QStringList m_comboList;
    int         m_count;
};


class GuiEvent : public QObject
{
    Q_OBJECT

public:

    GuiEvent()
        : kbd(0)
    {   }


    Q_INVOKABLE void comboChange(int id) const {
        //qDebug() << "id: " << id;
        kbd->LoadIndex(id);
    }

    Q_INVOKABLE void btnClick() const {
        //qDebug() << "aaa";
    }

    class Keyboard* kbd;
};
