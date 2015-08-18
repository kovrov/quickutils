#ifndef TIME_COMPONENT_H
#define TIME_COMPONENT_H

#include <QtCore/QObject>
#include <QtCore/QDateTime>

class Time : public QObject
{
    Q_OBJECT
    Q_PROPERTY (QDateTime dateTime READ dateTime NOTIFY dateTimeChanged)
    Q_PROPERTY (int year READ year NOTIFY yearChanged)
    Q_PROPERTY (int month READ month NOTIFY monthChanged)
    Q_PROPERTY (int day READ day NOTIFY dayChanged)
    Q_PROPERTY (int hour READ hour NOTIFY hourChanged)
    Q_PROPERTY (int minute READ minute NOTIFY minuteChanged)

public:
    explicit Time(QObject *parent = nullptr);

    QDateTime dateTime() const { return m_dateTime; }
    int year() const { return m_dateTime.date().year(); }
    int month() const { return m_dateTime.date().month(); }
    int day() const { return m_dateTime.date().day(); }
    int hour() const { return m_dateTime.time().hour(); }
    int minute() const { return m_dateTime.time().minute(); }

protected:
    void timerEvent(QTimerEvent *) override;

signals:
    void dateTimeChanged(const QDateTime &dateTime);
    void yearChanged(int year);
    void monthChanged(int month);
    void dayChanged(int day);
    void hourChanged(int hour);
    void minuteChanged(int minute);

private:
    QDateTime m_dateTime;
    int m_timer = 0;
};

#endif // TIME_COMPONENT_H
