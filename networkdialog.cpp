#include "networkdialog.h"
#include "ui_networkdialog.h"
#include <QNetworkInterface>

NetworkDialog::NetworkDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NetworkDialog)
{
    ui->setupUi(this);
    SetBindAddresses();
}

NetworkDialog::~NetworkDialog()
{
    delete ui;
}

void NetworkDialog::SetBindAddresses()
{
    // From https://stackoverflow.com/questions/5572263/get-current-qnetworkinterface-active-and-connected-to-the-internet

    QList<QString> possibleMatches;
    QList<QNetworkInterface> ifaces = QNetworkInterface::allInterfaces();
    if ( !ifaces.isEmpty() )
    {
      for(int i=0; i < ifaces.size(); i++)
      {
        unsigned int flags = ifaces[i].flags();
        bool isLoopback = (bool)(flags & QNetworkInterface::IsLoopBack);
        bool isP2P = (bool)(flags & QNetworkInterface::IsPointToPoint);
        bool isRunning = (bool)(flags & QNetworkInterface::IsRunning);

        // If this interface isn't running, we don't care about it
        if ( !isRunning ) continue;
        // We only want valid interfaces that aren't loopback/virtual and not point to point
        if ( !ifaces[i].isValid() || isLoopback || isP2P ) continue;
        QList<QHostAddress> addresses = ifaces[i].allAddresses();
        for(int a=0; a < addresses.size(); a++)
        {
          // Ignore local host --- allow local host
          //if ( addresses[a] == QHostAddress::LocalHost ) continue;

          // Ignore non-ipv4 addresses
          if ( !addresses[a].toIPv4Address() ) continue;

          QString ip = addresses[a].toString();
          if ( ip.isEmpty() ) continue;
          bool foundMatch = false;
          for (int j=0; j < possibleMatches.size(); j++) if ( ip == possibleMatches[j] ) { foundMatch = true; break; }
          if ( !foundMatch ) {
              possibleMatches.push_back( ip ); qDebug() << "possible address: " << ifaces[i].humanReadableName() << "->" << ip;
              ui->Networks->addItem(ip);
          }
        }
      }
    }
}

void NetworkDialog::on_Networks_currentIndexChanged(const QString &arg1)
{
    Bind2IP = arg1;
}
