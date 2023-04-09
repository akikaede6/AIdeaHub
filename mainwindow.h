#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "OpenAIApiClient.h"

#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QLineEdit>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(const std::string& api_key, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_sendRequestButton_clicked();
    void onTextGenerated(const std::string& text);

private:
    OpenAIApiClient m_apiClient;
    QPushButton *m_sendBtn;
    QLineEdit *m_sendEdit;
    QTextEdit *m_textEdit;
};
#endif // MAINWINDOW_H
