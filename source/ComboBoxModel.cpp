#include "comboboxmodel.h"
#include "qdebug.h"

ComboBoxModel::ComboBoxModel(QObject *parent) :
    QObject(parent)
{
}

ComboBoxModel::ComboBoxModel(const QStringList &list, int count, QObject *parent) :
    QObject(parent), m_comboList(list), m_count(count)
{

}

const QStringList ComboBoxModel::comboList()
{
    return m_comboList;
}

void ComboBoxModel::setComboList(const QStringList &comboList)
{

    if (m_comboList != comboList)
    {
        m_comboList = comboList;
        emit comboListChanged();
    }

}

int ComboBoxModel::count()
{
    return m_count;
}

void ComboBoxModel::setCount(int cnt)
{
    if (cnt != m_count)
    {
        m_count = cnt;
        emit countChanged();
    }
}

void ComboBoxModel::addElement(const QString &element)
{
    m_comboList.append(element);
    emit comboListChanged();
    setCount(m_comboList.count());
    emit countChanged();

    for (int i = 0; i<m_count; i++)
    {
        qDebug() << m_comboList.at(i);
    }
}

void ComboBoxModel::removeElement(int index)
{
    if (index < m_comboList.count())
    {
        m_comboList.removeAt(index);
        emit comboListChanged();
        setCount(m_comboList.count());
        emit countChanged();
    }

    for (int i = 0; i<m_count; i++)
    {
        qDebug() << m_comboList.at(i);
    }
}
