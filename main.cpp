#include <QCoreApplication>
#include <iostream>
#include <QDebug>
#include "timestamp.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    TimestampWriter *timeStampWriter = new TimestampWriter();
    return a.exec();
}
