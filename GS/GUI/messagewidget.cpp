#include "messagewidget.h"
#include "ui_messagewidget.h"

MessageWidget::MessageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MessageWidget)
{
    ui->setupUi(this);
    QListWidgetItem * q = new QListWidgetItem("Message Widget Ready");
    ui->listWidget->addItem(q);
}

void MessageWidget::updateMessages(mavlink_statustext_t stattext) {
    QListWidgetItem * message = new QListWidgetItem(stattext.text);
    ui->listWidget->addItem(message);
    ui->listWidget->scrollToBottom();
}

void MessageWidget::updateMessages_str(QString text) {
    QListWidgetItem * message = new QListWidgetItem(text);
    ui->listWidget->addItem(message);
    ui->listWidget->scrollToBottom();
}

void MessageWidget::updateClearMission(bool success) {
    if (success)
        updateMessages_str(QString("Missions cleared."));
    else
        updateMessages_str(QString("Mission clear request unsuccessful."));
}

MessageWidget::~MessageWidget()
{
    delete ui;
}
