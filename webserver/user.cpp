#include "user.h"

User::User(QObject *parent) : QObject(parent)
{
}

User::User(const QString &id, const QDate &date, const QTime &time, QObject *parent)
    : QObject(parent), m_id(id), m_date(date), m_time(time)
{
}

QString User::getId() const
{
    return m_id;
}

QDate User::getDate() const
{
    return m_date;
}

QTime User::getTime() const
{
    return m_time;
}
