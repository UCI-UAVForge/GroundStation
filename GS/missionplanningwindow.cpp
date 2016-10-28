#include "missionplanningwindow.h"

//Code by David Moe

//Note: Some parts of the code were edited by Roman Parise. The original
//source can be found here: https://gist.github.com/logicxd .

MissionPlanningWindow::MissionPlanningWindow(QWidget *parent) : QDialog(parent)
{
    // Execute Button
    buttonLayout = new QHBoxLayout();
    executeButton = new QPushButton("Execute");

    buttonLayout->addWidget( executeButton );

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
    this->superLayout->addLayout( layout );

    // MissionPlanningWindow Settings
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("Mission Planning"));
    this->setWindowTitle(QStringLiteral("Mission Planning"));
    this->resize(250,100);
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

/* Roman Parise - used to integrate this window into MainMDIDisplay */

void MissionPlanningWindow::deleteExecuteButton() {

    delete this->executeButton;

    this->executeButton = NULL;

}

void MissionPlanningWindow::addButton( QPushButton * newButton) {

    this->buttonLayout->addWidget( newButton );

}

/**/

MissionPlanningWindow::~MissionPlanningWindow()
{
    delete executeButton;
    delete uavComboBox;
    delete missionPlanComboBox;
    delete layout;
} // ~MissionPlanningWindow()
