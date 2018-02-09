#include "connectionwidget.h"
#include "ui_connectionwidget.h"

ConnectionWidget::ConnectionWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionWidget)
{
    ui->setupUi(this);
    connect(ui->connectButton, &QPushButton::clicked, this, &ConnectionWidget::connectUAV);
    connect(ui->refreshButton, &QPushButton::clicked, this, &ConnectionWidget::refresh);
    ui->serialButton->setChecked(true);
    buttons = new QButtonGroup();
    buttons->addButton(ui->tcpButton, 0);
    buttons->addButton(ui->udpButton, 1);
    buttons->addButton(ui->serialButton, 2);
}

void ConnectionWidget::connectUAV() {
    Link * newLink;
    switch (buttons->checkedId()) {
        case 0:
            newLink = new TcpLink();
            emit(connectTo(newLink, ui->tcp->text()));
        break;
        case 1:
            newLink = new UdpLink();
            emit(connectTo(newLink, ui->udp->text()));
        break;
        case 2:
            newLink = new SerialLink();
            emit(connectTo(newLink, ui->serialBox->currentText()));
        break;
        default: break;
    }
}

void ConnectionWidget::refresh() {
    ui->serialBox->clear();
    for (auto e: QSerialPortInfo::availablePorts()) {
        ui->serialBox->addItem(e.portName());
    }
}

void ConnectionWidget::setStatus(QString status) {
    ui->status->setText(status);
}

ConnectionWidget::~ConnectionWidget()
{
    delete ui;
}
