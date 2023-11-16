#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

#define DOWNLOAD_URL "https://dldir1.qq.com/music/clntupate/QQMusic_Setup_Home.exe"

class NetWork : public QObject
{
    Q_OBJECT
public:
    explicit NetWork(QObject *parent = nullptr);
    virtual ~NetWork();
private slots:
    void onStartDownload();
    void onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);
signals:
    void setPushButtonEnabled(bool flag);
    void setProgressBarVal(int p);
    void displayFinishedWidget(const QString& desc);
private:
    QNetworkAccessManager m_manager;
    QNetworkRequest m_request;
    QNetworkReply *m_reply = nullptr;
};

#endif // NETWORK_H
