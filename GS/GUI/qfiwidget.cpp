#include "qfiwidget.h"

QFIWidget::QFIWidget( QWidget *parent ) :
        QWidget( parent )
{
    layout = new QVBoxLayout(this);
    layout->setSpacing(6);

    // Primary Flight Display
    m_pfd = new qfi_PFD(parent);
    m_pfd->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_pfd->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_pfd->setFixedSize(250,250);
    layout->addWidget(m_pfd);
    layout->setSizeConstraint(QLayout::SetFixedSize);


    // Turn Coordinator Instrument
//    m_tc = new qfi_TC(parent);
//    m_tc->setMinimumSize(400,400);
//    m_tc->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    m_tc->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    layout->addWidget(m_tc);

    setLayout(layout);
}
