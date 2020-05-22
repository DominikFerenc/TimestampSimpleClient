#include "timestamp.h"


TimeStampData::TimeStampData()
{
	li_vn_mode =  (qint8) 227;
    stratum = (qint8) 3;
    poll = (qint8) 6;
    precision = (qint8) 0;
    rootDelay =(qint32) 0;
    rootDispersion = (qint32) 0;
    referencesID = (qint32) 0;
    referenceTimestamp = (qint64) 0;
    originateTimeStamp= (qint64) 0;
    receiveTimeStamp = (qint64) 0;
    transmitTimeStamp = (qint64) 0;
    //authenticator = (quint8) 0;
}


TimestampWriter::TimestampWriter()
{
    timeData = new TimeStampData();
    socket = new QUdpSocket();
    socket->connectToHost("193.110.137.171", 123);
    if (!QUdpSocket::UnconnectedState)
        qDebug() << "Error Connection";
    else
        getMyTime();
}

TimestampWriter::~TimestampWriter(){}

void TimestampWriter::getMyTime()
{
    //second
    quint32 myTime_t;
    myTime_t = QDateTime::currentSecsSinceEpoch();
    myTime_t =  myTime_t + 2208988800L;

    //mili second
    quint32 myTime_ms;
    myTime_ms = QDateTime::currentMSecsSinceEpoch();

    setTimestampData(myTime_t, myTime_ms);
}

void TimestampWriter::setTimestampData(quint32 myTime_t, quint32 myTime_ms)
{
    QDataStream dataStream(&dataTimestampArray, QIODevice::WriteOnly);
    dataStream.setByteOrder(QDataStream::BigEndian);
    dataStream << timeData->li_vn_mode;
    dataStream << timeData->stratum;
    dataStream << timeData->poll;
    dataStream << timeData->precision;
    dataStream << timeData->rootDelay;
    dataStream << timeData->rootDispersion;
    dataStream << timeData->referencesID;
    dataStream << timeData->referenceTimestamp;
    dataStream << timeData->originateTimeStamp;
    dataStream << timeData->receiveTimeStamp;
    dataStream << myTime_t;
    dataStream << myTime_ms; //(quint32) 0;

	qDebug() << "Value setTimestampData: " << dataTimestampArray.toHex();
    sendDatagrams(dataTimestampArray);
}

void TimestampWriter::sendDatagrams(QByteArray dateTimestampArray)
{
    QByteArray datagram;
    const quint16 port = 123;

    if (socket->writeDatagram(dataTimestampArray, QHostAddress("193.110.137.171"), port))
    {
        qDebug() << "Send";
        while (true)
		{
            while (socket->hasPendingDatagrams())
            {
                datagram.resize(socket->pendingDatagramSize());
                socket->readDatagram(datagram.data(), datagram.size(), addr, &port);
                printDatagram(datagram);
            }
        }
    }

}
void TimestampWriter::printDatagram(QByteArray datagram)
{
     qDebug()   << "/*******************************/"
                <<       "Message from server NTP"
                << "/*******************************/"
                << "\n";

    QDateTime *timestamp = new QDateTime();

    qDebug() << "Datagram.toHex: " << datagram.toHex() << "\n";
    qDebug() << "Datagram: " << datagram << "\n";
}



