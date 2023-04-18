#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include "qwebengineview.h"
#include <QWidget>

class QPushButton;
class QLineEdit;
class OpenAIImageClient;
class QNetworkAccessManager;
class ImageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ImageWidget(QWidget *parent = nullptr);

signals:

private:
    void init();
    void initConnection();

private slots:
    void onSendBtnClicked();
    void onTextGenerated(const QString& text);
    void onDownloadTriggered(bool triggered);

private:
    QWebEngineView *m_view;
    QPushButton *m_sendBtn;
    QLineEdit *m_sendEdit;
    OpenAIImageClient *m_apiClient;
    QAction *m_downloadAction;
};

#endif // IMAGEWIDGET_H
