#include "client.h"
#include <QEventLoop>
#include <QUrl>
#include <QDebug>
//#include <QMessageBox>

using namespace ONVIF;

Client::Client(const QString &url) {
    mUrl = url;
    //reply->ignoreSslErrors();
}

QString Client::sendData(const QString &data) {
    //    qDebug() << "send to url => " << mUrl << " | data => " << data;

    emit Trace("Send request");
    emit Trace(mUrl);

    emit Trace(data+"\n");

    QUrl url(mUrl);
    QNetworkRequest request(url);
    request.setHeader( QNetworkRequest::ContentTypeHeader, QVariant( QString("application/soap+xml;charset=utf-8")));
    request.setHeader(QNetworkRequest::ContentLengthHeader, QVariant( qulonglong(data.size()) ));
    request.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QVariant( int(QNetworkRequest::AlwaysNetwork) ));
    //requete.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/x-www-form-urlencoded"));

    QNetworkAccessManager *manager = new QNetworkAccessManager;
    reply = manager->post(request, data.toUtf8());
    reply->ignoreSslErrors();
    waitForFinished(reply);
    if(reply->error() != QNetworkReply::NoError) {
        emit Trace(reply->readAll());
        return "";
    }

    QString reponse = reply->readAll();
    emit Trace("Response");
    emit Trace(reponse+"\n");

    return reponse;
}

void Client::waitForFinished(const QNetworkReply* reply) {
    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
}

