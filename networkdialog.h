#ifndef NETWORKDIALOG_H
#define NETWORKDIALOG_H

#include <QDialog>

namespace Ui {
class NetworkDialog;
}

class NetworkDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NetworkDialog(QWidget *parent = nullptr);
    ~NetworkDialog();

    void SetBindAddresses();
    QString Bind2IP;

private slots:
    void on_Networks_currentIndexChanged(const QString &arg1);

private:
    Ui::NetworkDialog *ui;
};

#endif // NETWORKDIALOG_H
