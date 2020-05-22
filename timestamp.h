#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include <QUdpSocket>
#include <QDateTime>
#include <QTime>
#include <QThread>
#include <qdatastream.h>
#include <iostream>
#include <QtEndian>


class TimeStampData
{
    public:

        qint8 li_vn_mode;
        qint8 stratum;
        qint8 poll;
        qint8 precision;
        qint32 rootDelay;
        qint32 rootDispersion;
        qint32 referencesID;
        qint64 referenceTimestamp;
        qint64 originateTimeStamp;
        qint64 receiveTimeStamp;
        qint64 transmitTimeStamp;
        //quint16 authenticator;

        TimeStampData();

};

class TimestampWriter : public QObject
{
    Q_OBJECT

    public:
        TimestampWriter();
        ~TimestampWriter();
        void getMyTime();
        void setTimestampData(quint32 myTime_t, quint32 myTime_ms);
        void sendDatagrams(QByteArray dataTimestampArray);
        void printDatagram(QByteArray datagram);

    private:
        QUdpSocket * socket = nullptr;
        QTime * myTime;
        QDateTime * myDateTime;
        TimeStampData *timeData = nullptr;
        QByteArray dataTimestampArray;



};




#endif // TIMESTAMP_H
