#include "ChatLogger.h"
#include <QDateTime>

ChatLogger::ChatLogger()
{
    mLogFile.setFileName("log.txt");
    mLogFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
    mLogStream.setDevice(&mLogFile);
}

ChatLogger::~ChatLogger()
{
    mLogFile.close();
}

void ChatLogger::log(const QString &message)
{
    QDateTime dateTime = QDateTime::currentDateTime();
    QString formattedMessage = QString("%1: %2").arg(dateTime.toString(Qt::TextDate)).arg(message);
    mLogStream << formattedMessage << Qt::endl;
}
