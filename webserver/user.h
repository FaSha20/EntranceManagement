#ifndef USER_H
#define USER_H

#include <QObject>
#include <QDateTime>

class User : public QObject
{
    Q_OBJECT
public:
    explicit User(QObject *parent = nullptr);
    User(const QString &id, const QDate &date, const QTime &time, QObject *parent = nullptr);
    User(const User& other, QObject *parent = nullptr);
    QString getId() const;
    QDate getDate() const;
    QTime getTime() const;

signals:

private:
    QString m_id;
    QDate m_date;
    QTime m_time;
};

#endif // USER_H
