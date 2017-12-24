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

MessageWidget::~MessageWidget()
{
    delete ui;
}
