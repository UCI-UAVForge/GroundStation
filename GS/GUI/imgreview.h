#ifndef IMGREVIEW_H
#define IMGREVIEW_H

#include <QWidget>
#include "imgwidget.h"
#include "propertywidget.h"
#include "style.h"
namespace Ui {
class ImgReview;
}

class ImgReview : public QWidget
{
    Q_OBJECT

public:
    explicit ImgReview(QWidget *parent = 0);
    ~ImgReview();
    ImgWidget* ImgContainer;
    PropertyWidget* PropertyContainer;
    Ui::ImgReview * ui;
    Style style;
public slots:
    void ImgEditingEnable();
    void ImgSave();
    void ImgReset();
    // void ImgSend();
    // void ImgNext();
    void PropertyReset();
    void PropertySave();
    //void PropertySend();
    //void PropertyNext();
    QPushButton* ImgSendButton();
    QPushButton* ImgNextButton();
    QPushButton* PropertySendButton();
    QPushButton* PropertyNextButton();
};

#endif // IMGREVIEW_H
