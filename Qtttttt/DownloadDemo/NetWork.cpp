#include "NetWork.h"

#include <QString>
#include <QFile>
#include <QUrl>
#include <QNetworkReply>
#include <QDebug>

NetWork::NetWork(QObject *parent)
    : QObject{parent}
{

}

NetWork::~NetWork()
{

}

void NetWork::onStartDownload()
{

    emit setPushButtonEnabled(false);
    m_request.setUrl(QUrl("https://dldir1.qq.com/qqfile/qq/PCQQ9.7.1/QQ9.7.1.28940.exe"));
//    m_request.setUrl(QUrl("https://d1.music.126.net/dmusic/NeteaseCloudMusic_Music_official_2.10.12.201849_32.exe"));
    m_reply = m_manager.get(m_request);

    connect(m_reply, &QNetworkReply::finished, [=](){
       if(m_reply->error() == QNetworkReply::NoError){
            QByteArray response = m_reply->readAll();
            qDebug() << response.length();
            QFile file("C:/Users/qlz/Desktop/DDD.exe");
            if(file.open(QIODevice::WriteOnly)) {
                file.write(response, response.length());
                file.close();

                emit displayFinishedWidget("Download completed: Path is C:/Users/qlz/Desktop.");
            }
        } else {
            emit displayFinishedWidget("Error: " + m_reply->errorString());
        }

        m_reply->deleteLater();
        m_reply = nullptr;
        emit setPushButtonEnabled(true);
    });
    connect(m_reply, &QNetworkReply::downloadProgress, [&](qint64 bytesReceived, qint64 bytesTotal){
        int p = 0;
        if(bytesTotal > 0)
            p = (double)((double)bytesReceived / (double)bytesTotal) * 100.0; // c++类型转换
        qDebug() << p;
        emit setProgressBarVal(p);
    });


    return;
}

void NetWork::onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    int p = (int)(bytesReceived / bytesTotal) * 100; // c++类型转换
    emit setProgressBarVal(p);
}


