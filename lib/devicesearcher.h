#ifndef ONVIF_DEVICESEARCHER_H
#define ONVIF_DEVICESEARCHER_H

#include <QObject>
#include <QUdpSocket>
#include <QFile>
#include <QTextStream>

namespace ONVIF {
    class DeviceSearcher : public QObject {
        Q_OBJECT
    public:
        static DeviceSearcher* searcher;
        static DeviceSearcher* instance();
        explicit DeviceSearcher(QObject *parent = 0);
        ~DeviceSearcher();
        
        void sendSearchMsg(QString localSocket);

        void SendSignal();

    signals:
        void receiveData(const QHash<QString, QString> &data);

        void Trace(QString data);

    public slots:
    private slots:
        void readPendingDatagrams();
    private:
        QUdpSocket *mUdpSocket;
    };
}
#endif // ONVIF_DEVICESEARCHER_H

