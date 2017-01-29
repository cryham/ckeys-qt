#ifndef COMBOBOXMODEL_H
#define COMBOBOXMODEL_H

#include <QObject>
#include <QStringList>

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

#endif // COMBOBOXMODEL_H
