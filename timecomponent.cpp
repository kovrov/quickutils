#include <QtCore/QTimerEvent>

#include "timecomponent.h"

enum {
    ONE_MINUTE = 1000 * 60
};

Time::Time(QObject *parent) :
    QObject (parent),
    m_dateTime (QDateTime::currentDateTime())
{
    int align = ONE_MINUTE - QTime::currentTime().msecsSinceStartOfDay() % ONE_MINUTE;
    m_timer = startTimer(align, Qt::PreciseTimer);
}

void Time::timerEvent(QTimerEvent *ev)
{
    const QTime &currentTime = QTime::currentTime();
    if (currentTime.second() != 0 || m_timer) {
        if (m_timer == 0) {
            qWarning("Correcting timer events drift (%d msec).",
                     currentTime.msecsSinceStartOfDay() % (1000 * 60 * 60));
        }
        killTimer(ev->timerId());
        int align = ONE_MINUTE - currentTime.msecsSinceStartOfDay() % ONE_MINUTE;
        int id = startTimer(align, Qt::PreciseTimer);
        m_timer = m_timer ? 0 : id;
    }

    if (currentTime.minute() != m_dateTime.time().minute()) {
        auto dateTime = m_dateTime;
        m_dateTime = QDateTime::currentDateTime();
        emit dateTimeChanged(m_dateTime);
        emit minuteChanged(m_dateTime.time().minute());
        if (dateTime.time().hour() != m_dateTime.time().hour())
            emit hourChanged(m_dateTime.time().hour());
        if (dateTime.date().day() != m_dateTime.date().day())
            emit dayChanged(m_dateTime.date().day());
        if (dateTime.date().month() != m_dateTime.date().month())
            emit monthChanged(m_dateTime.date().month());
        if (dateTime.date().year() != m_dateTime.date().year())
            emit yearChanged(m_dateTime.date().year());
    }
}
