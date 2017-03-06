#include "missionplanningwindow.h"

//Code by David Moe

//Note: Some parts of the code were edited by Roman Parise. The original
//source can be found here: https://gist.github.com/logicxd .

MissionPlanningWindow::MissionPlanningWindow(QWidget *parent) : QDialog(parent)
{
    // Execute Button
    buttonLayout = new QHBoxLayout();
    textBoxLayout = new QHBoxLayout();
    executeButton = new QPushButton("Execute");

    this->addButton( executeButton );

    // UAV ComboBox
    uavComboBox = new QComboBox();
    uavComboBox->addItem("Select UAV");
    uavComboBox->addItem("UAV 1");
    uavComboBox->addItem("UAV 2");
    uavComboBox->addItem("UAV 3");
    //QObject::connect(uavComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setExecutionButtonEnabled()));

    // Mission Plan ComboBox
    missionPlanComboBox = new QComboBox();
    missionPlanComboBox->addItem("Select Mission");
    missionPlanComboBox->addItem("Mission 1");
    missionPlanComboBox->addItem("Mission 2");
    missionPlanComboBox->addItem("Mission 3");
    //QObject::connect(missionPlanComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setExecutionButtonEnabled()));

    // Layout
    layout = new QGridLayout;
    //layout->addWidget(buttonLayout,1,3,1,3);
    layout->addWidget(uavComboBox,3,1,1,3);
    layout->addWidget(missionPlanComboBox,3,5,1,3);

    //Incorporate all GUI elements into superLayout
    this->superLayout = new QVBoxLayout();
    this->superLayout->addLayout( buttonLayout );
    this->superLayout->addLayout( textBoxLayout );
    this->superLayout->addLayout( layout );

    // MissionPlanningWindow Settings
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("Mission Planning"));
    this->setWindowTitle(QStringLiteral("Mission Planning"));
    this->resize(300,150);
    this->setSizeGripEnabled(true);
    this->setModal(false);
    this->setLayout( this->superLayout );
} // MissionPlanningWindow(QWidget *parent)

/*
void MissionPlanningWindow::setExecutionButtonEnabled()
{
    if (uavComboBox->currentIndex() != 0 && missionPlanComboBox->currentIndex() != 0)
        executeButton->setEnabled(true);
    else
        executeButton->setEnabled(false);
} // setExecutionButtonEnabled()
*/

/* Roman Parise - used to integrate this window into MainMDIDisplay
Rendered obsolete by dumpButtons.

TODO Add dumpButton(QPushButton *) function
*/

void MissionPlanningWindow::deleteExecuteButton() {

    delete this->executeButton;

    this->executeButton = NULL;

}

void MissionPlanningWindow::addButton( QPushButton * newButton) {

    this->buttonLayout->addWidget( newButton );

    this->buttonList.append( newButton );

}

void MissionPlanningWindow::addComboBox( QComboBox * newComboBox ) {

    //TODO Give "layout" the name "comboBoxLayout"

    this->layout->addWidget( newComboBox );

    this->comboBoxList.append( newComboBox );

}

void MissionPlanningWindow::addTextBox( QLineEdit * newLineEdit ) {

    this->textBoxLayout->addWidget( newLineEdit );

    this->textBoxList.append( newLineEdit );

}

//Add textbox with caption written to the left of it.
//Ex. caption -> "Enter your name: ". In the window: "Enter your name: (newLineEdit goes here)"
void MissionPlanningWindow::addTextBox( QLineEdit * newLineEdit , QLabel * caption ) {

    this->textBoxLabelList.append( caption ) ;

    this->textBoxLayout->addWidget( caption );

    this->addTextBox( newLineEdit );

}

/* Delete all the buttons */
void MissionPlanningWindow::dumpButtons() {

    int i , currentLength ;

    QPushButton * tempButton ;

    //Save before loop since it may change as we go through and delete items

    currentLength = buttonList.length();

    for ( i = 0 ; i < currentLength ; i++ ) {

        tempButton = this->buttonList.first() ;

        this->buttonLayout->removeWidget( tempButton ) ;

        this->buttonList.removeFirst() ;

        if ( tempButton == this->executeButton ) {

            delete this->executeButton;

            this->executeButton = NULL;

        }

        //TODO Make sure this is called at some point: delete tempButton ; for the specific button

    }

}

void MissionPlanningWindow::dumpComboBoxes() {

    int i , currentLength ;

    QComboBox * tempComboBox ;

    //Save before loop since it may change as we go through and delete items

    currentLength = comboBoxList.length();

    qDebug() << "Current Length is " << currentLength ;

    for ( i = 0 ; i < currentLength ; i++ ) {

        tempComboBox = this->comboBoxList.first() ;

        this->layout->removeWidget( tempComboBox ) ;

        this->comboBoxList.removeFirst() ;

        //TODO Potentially get rid of this once we make use of uav and mission plan combo box

        if ( tempComboBox == this->uavComboBox ) {

            delete this->uavComboBox;

            this->uavComboBox = NULL;

        }

        else if ( tempComboBox == this->missionPlanComboBox ) {

            delete this->missionPlanComboBox;

            this->missionPlanComboBox = NULL;

        }

        //TODO Make sure this is called at some point: delete tempComboBox ; for the specific ComboBox

    }

}

void MissionPlanningWindow::changeTitle( QString newWindowTitle ) {

    this->setWindowTitle( newWindowTitle );

}

//Return value of uavComboBox
QString MissionPlanningWindow::getUAV() {

    return this->uavComboBox->currentText() ;

}

//Return value of missionPlanComboBox
QString MissionPlanningWindow::getMission() {

    return this->missionPlanComboBox->currentText() ;

}

/**/

MissionPlanningWindow::~MissionPlanningWindow()
{
    delete executeButton;
    delete uavComboBox;
    delete missionPlanComboBox;
    delete layout;
} // ~MissionPlanningWindow()
