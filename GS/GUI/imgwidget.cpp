#include "imgwidget.h"
#include "ui_imgwidget.h"
#include <QPainter>
#include <QMessageBox>
#include <QThread>
#include <QDebug>
#include <QDir>
ImgWidget::ImgWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImgWidget)
{
    ui->setupUi(this);
    ContainerSize = this->size();
    LoadImg();
}
void ImgWidget::paintEvent(QPaintEvent* e)
{

    QPainter p(this);
    p.drawImage(0,0,newimg);

    QPen pen(Qt::black,4);
    p.setPen(pen);

    p.drawRect(QRect(lastpoint,endpoint));
}

void ImgWidget::mousePressEvent(QMouseEvent* event)
{
    //QMessageBox box(this);
    if (EditEnable)
    {
    QPainter p(this);
    p.drawRect(50, 50, 100, 100);
        if (event->button() == Qt::LeftButton)
        {
            lastpoint = event->pos();
            MouseHolding = true;
        }
    }
}

void ImgWidget::mouseMoveEvent(QMouseEvent* event)
{
    if (EditEnable)
    {
        if ((event->buttons() & Qt::LeftButton) && MouseHolding)
        {
            endpoint = event->pos();
            update();
        }
    }
}

void ImgWidget::mouseReleaseEvent(QMouseEvent* event)
{

    if ( MouseHolding)
    {
        endpoint = event->pos();
        MouseHolding = false;
        update();
        CropToFill();
    }
}

void ImgWidget::setEditMode()
{
    EditEnable = true;
}

void ImgWidget::CropToFill()
{
    newimg = newimg.copy(QRect(lastpoint, endpoint));
    newimg = newimg.scaled(ContainerSize);
    ResetFocusPoint();
    update();
    //ImgSave();
}
void ImgWidget::ResetFocusPoint()
{
    lastpoint = QPoint(0, 0);
    endpoint = QPoint(0, 0);
}

void ImgWidget::LoadImg()
{

    //img.load(QDir::currentPath()+"/field_image.png");
    img.load(QDir::currentPath() + "/../../GroundStation/GS/res/img" +QString::number(imgNum)+".png");
    img = img.scaled(ContainerSize);
    newimg = img;
}

void ImgWidget::LoadNextImg()
{
    //not bound check, could load null image if exceed existing max number
    qDebug()<<"load next image";
    imgNum++;
    LoadImg();
    update();
}

void ImgWidget::UndoEdit()
{
    newimg = img;
    update();
    ResetFocusPoint();
}

void ImgWidget::ImgSave()
{
   // if (!newimg.save("new_img.jpeg"))
   if (!newimg.save(QDir::currentPath() + "/../../GroundStation/GS/res/new_image.png"))
        QMessageBox(QMessageBox::Warning, "image not saved", "image not saved, try again");
}

ImgWidget::~ImgWidget()
{
    delete ui;
}
