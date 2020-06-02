#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "lib/devicesearcher.h"

using namespace ONVIF;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    DeviceSearcher* mySearch;

private slots:
    void addONVIF(const QHash<QString, QString> &data);

    void on_GetDateTime_clicked();

    void on_GetDeviceInfo_clicked();

    void on_Search_clicked();

    void on_GetCapabilties_clicked();

    void on_GetStreamURI_clicked();

    void on_GetProfiles_clicked();

    void Trace(QString data);

    void on_actionAbout_triggered();

    void on_actionTrace_to_Clipboard_triggered();

    void on_pushButton_clicked();

    void on_GetUsers_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
