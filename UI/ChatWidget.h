#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>

class QPushButton;
class QTextEdit;
class QLineEdit;
class OpenAIChatClient;
class ChatWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChatWidget(QWidget *parent = nullptr);

signals:

private:
    void init();
    void initConnection();

private slots:
    void onSendBtnClicked();
    void onTextGenerated(const QString& text);

private:
    OpenAIChatClient *m_apiClient;
    QPushButton *m_sendBtn;
    QLineEdit *m_sendEdit;
    QTextEdit *m_textEdit;
};

#endif // CHATWIDGET_H
