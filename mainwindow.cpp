#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "lib/devicemanagement.h"
#include "lib/mediamanagement.h"
#include "lib/media_management/videoencoderconfiguration.h"
#include <QInputDialog>
#include "networkdialog.h"
//#include <opencv2/opencv.hpp>
#include "aboutdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mySearch = NULL;

    //cv::Mat med;
}

MainWindow::~MainWindow()
{
    delete ui;
    if( mySearch )
        delete mySearch;
}

void MainWindow::on_Search_clicked()
{
    if( mySearch )
        delete mySearch;

    mySearch = new DeviceSearcher(this);
    NetworkDialog selectInterface;
    selectInterface.exec();
    ui->Response->append("Searching interface at " + selectInterface.Bind2IP + " for ONVIF devices\n");
    connect(mySearch, SIGNAL(receiveData(const QHash<QString, QString>)), this, SLOT(addONVIF(const QHash<QString, QString>)));
    connect(mySearch, SIGNAL(Trace(QString)), this, SLOT(Trace(QString)));
    mySearch->sendSearchMsg(selectInterface.Bind2IP);
}

void MainWindow::on_GetDeviceInfo_clicked()
{
    DeviceManagement myDevice(ui->URL->text(), ui->Username->text(), ui->Password->text());
    connect(myDevice.mClient, SIGNAL(Trace(QString)), this, SLOT(Trace(QString)));

    QHash<QString, QString> dev = myDevice.getDeviceInformation();
    QString reply  = "mf [" + QString(dev["mf"]) + "\r\n";
    reply += "model [" + dev["model"] + "\r\n";
    reply += "firmware_version [" + dev["firmware_version"] + "\r\n";
    reply += "serial_number [" + dev["serial_number"] + "\r\n";
    reply += "hardware_id [" + dev["hardware_id"] + "\r\n";

    ui->Response->append(reply);
}

void MainWindow::addONVIF(const QHash<QString, QString> &data) {
    ui->Response->append("Device ["+data["device_service_address"]+"]");
}

void MainWindow::on_GetDateTime_clicked()
{
    DeviceManagement myDevice(ui->URL->text(), ui->Username->text(), ui->Password->text());
    connect(myDevice.mClient, SIGNAL(Trace(QString)), this, SLOT(Trace(QString)));

    SystemDateAndTime* dev = myDevice.getSystemDateAndTime();

    QString lt = dev->localTime().toString();
    QString utc=dev->utcTime().toString();

    ui->Response->append(lt);
    ui->Response->append(utc + "\n");

}

void MainWindow::on_GetCapabilties_clicked()
{
    DeviceManagement myDevice(ui->URL->text(), ui->Username->text(), ui->Password->text());
    connect(myDevice.mClient, SIGNAL(Trace(QString)), this, SLOT(Trace(QString)));

    Capabilities* myCap = myDevice.getCapabilitiesMedia();
    QString caps = "Caps:\n";
    if( myCap ) {
       if( myCap->rtpTcp() )
           caps += "Has rtpTcp\n";
       if( myCap->rtpRtspTcp() )
           caps += "Has rtpRtspTCP\n";
       if( myCap->dynDNS() )
           caps += "Has dynDNS\n";
    }
    ui->Response->append(caps);
}

void MainWindow::on_GetStreamURI_clicked()
{
    bool ok;
    int nProfile = QInputDialog::getInt(this, tr("Select Stream"), tr("Profile number"), 0, 0, 100, 1, &ok);

    if (ok) {
        MediaManagement myMedia(ui->URL->text(), ui->Username->text(), ui->Password->text());
        connect(myMedia.mClient, SIGNAL(Trace(QString)), this, SLOT(Trace(QString)));

        StreamUri *stream = myMedia.getStreamUri(nProfile);
        if( stream ) {
            ui->Response->append(stream->uri() + "\n");
        }
        else {
            ui->Response->append("Stream " + QString::number(nProfile) + " not found\n");
        }
    }

}

void MainWindow::on_GetProfiles_clicked()
{
    MediaManagement myMedia(ui->URL->text(), ui->Username->text(), ui->Password->text());
    connect(myMedia.mClient, SIGNAL(Trace(QString)), this, SLOT(Trace(QString)));

    Profiles *prof = myMedia.getProfiles();
    ui->Response->append("Profiles:");
    if( prof ) {
        ui->Response->append(QString::number(prof->m_namePro.size()));
        for(int i=0; i<prof->m_namePro.size(); i++) {
            ui->Response->append(prof->m_namePro[i] + "->" + QString::number(prof->m_widthVec[i]) + ":"+ QString::number(prof->m_heightVec[i]));
        }
    }
}

void MainWindow::Trace(QString data) {
    ui->Trace->append(data);
}

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog myAbout;
    myAbout.exec();
}

void MainWindow::on_actionTrace_to_Clipboard_triggered()
{
    ui->Trace->selectAll();
    ui->Trace->copy();
}

void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::on_GetUsers_clicked()
{
    DeviceManagement myDevice(ui->URL->text(), ui->Username->text(), ui->Password->text());
    connect(myDevice.mClient, SIGNAL(Trace(QString)), this, SLOT(Trace(QString)));

    Users* myCap = myDevice.getUsers();
    QString caps = "Users:\n";
}
