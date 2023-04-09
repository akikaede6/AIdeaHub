#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "OpenAIApiClient.h"

#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QLineEdit>
#include <QWebEngineView>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onSendBtnClicked();
    void onTextGenerated(const QString& text);

private:
    OpenAIApiClient m_apiClient;
    QPushButton *m_sendBtn;
    QLineEdit *m_sendEdit;
    QTextEdit *m_textEdit;
    QWebEngineView *view;
};
#endif // MAINWINDOW_H
