#ifndef CHATLOGGER_H
#define CHATLOGGER_H

#include <QObject>
#include <QFile>
#include <QTextStream>

class ChatLogger : public QObject
{
    Q_OBJECT
public:
    ChatLogger();
    ~ChatLogger();
    void log(const QString& message);
private:
    QFile mLogFile;
    QTextStream mLogStream;
};

#endif // CHATLOGGER_H
