#include "imgreview.h"
#include "ui_imgreview.h"

ImgReview::ImgReview(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImgReview)
{
    ui->setupUi(this);
    this->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    ImgContainer = new ImgWidget(this);
    ui->ImgContainer->setGeometry(0,10,800,600);

    ImgContainer->setMaximumSize(800,600);
    ui->ImgContainer = ImgContainer;
    PropertyContainer = new PropertyWidget(this);
       //PropertyContainer = nullptr;
    ui->PropertyContainer = PropertyContainer;
    ui->PropertyContainer->setGeometry(820,10,PropertyContainer->width(),600);
    connect(ui->IEditButton,SIGNAL(clicked()),this,SLOT(ImgEditingEnable()));
    connect(ui->IResetButton,SIGNAL(clicked()),this,SLOT(ImgReset()));
    connect(ui->ISaveButton,SIGNAL(clicked()),this,SLOT(ImgSave()));
    connect(ui->NextButton,SIGNAL(clicked()),this,SLOT(ImgNext()));
    connect(ui->IEditButton,SIGNAL(clicked()),this,SLOT(ImgEditingEnable()));
    connect(ui->PresetButton,SIGNAL(clicked()),this,SLOT(PropertyReset()));
    connect(ui->PSaveButton,SIGNAL(clicked()),this,SLOT(PropertySave()));
    connect(ui->NextButton,SIGNAL(clicked()),this,SLOT(PropertyNext()));

   /* Style style = Style();
    foreach(QPushButton * p, this->findChildren<QPushButton*>()) {
          style.setButtonDefault(p);
       }*/
}
void ImgReview::ImgEditingEnable()
{
    ImgContainer->setEditMode();
}

void ImgReview::ImgSave()
{
    ImgContainer->ImgSave();
}

void ImgReview::ImgReset()
{
    ImgContainer->UndoEdit();
}

void ImgReview::ImgNext()
{
    ImgContainer->LoadNextImg();
}

void ImgReview::PropertyReset()
{
    PropertyContainer->resetProperty();
}

void ImgReview::PropertySave()
{
    PropertyContainer->saveProperty();
}

void ImgReview::PropertyNext()
{
    PropertyContainer->loadNextProperty();
}

QPushButton *ImgReview::ImgSendButton()
{
    return ui->ISendButton;
}
/*
QPushButton *ImgReview::ImgNextButton()
{
    return ui->NextButton;
}
*/
QPushButton *ImgReview::PropertySendButton()
{
    return ui->PSendButton;
}
/*
QPushButton *ImgReview::PropertyNextButton()
{
    return ui->PNextButton;
}
*/
ImgReview::~ImgReview()
{
    delete ui;
}
