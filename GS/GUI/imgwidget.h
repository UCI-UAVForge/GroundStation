#ifndef IMGWIDGET_H
#define IMGWIDGET_H

#include <QWidget>
#include <QtCore>
#include <QImage>
#include <QMouseEvent>
namespace Ui {
class ImgWidget;
}

class ImgWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ImgWidget(QWidget *parent = 0);
    QImage img,newimg;
    void setEditMode();
    void LoadImg();
    void UndoEdit();
    void ImgSave();
    ~ImgWidget();

private:
    Ui::ImgWidget *ui;
    QPoint lastpoint = QPoint(0,0);
    QPoint endpoint = QPoint(0, 0);
    bool EditEnable = false;
    bool MouseHolding = false;
    void CropToFill();
    QSize ContainerSize;
    void ResetFocusPoint();
protected:
    void paintEvent(QPaintEvent* e) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // IMGWIDGET_H

