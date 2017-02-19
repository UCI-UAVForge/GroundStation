#include "gscontrolpanel.h"
#include "ui_gscontrolpanel.h"

/**
 * @brief Default constructor for GSControlPanel
 * @param parent
 */
GSControlPanel::GSControlPanel(QWidget *parent) : QDialog(parent),ui(new Ui::GSControlPanel)
{

    // Set up the GUI
    this->ui->setupUi(this);

    //Hide any GUI elements not used at start
    this->ui->FinishMissionButton->hide() ;

}

/**
 * @brief Default destructor for GSControlPanel
 */
GSControlPanel::~GSControlPanel()
{
    delete this->ui;
}

/**
 * @brief What happens when StartMissionButton is clicked. Hides GUI elements related to mission planning
 * and shows GUI elements related to mission execution.
 */
void GSControlPanel::on_StartMissionButton_clicked()
{

    //TODO Have StartMissionButton be disabled until you have at least one point in your flightpath

    //Hide GUI elements related to mission planning
    this->ui->StartMissionButton->hide() ;
    this->ui->LoadMissionButton->hide() ;
    this->ui->SaveMissionButton->hide() ;
    this->ui->ClearPointsButton->hide() ;
    this->ui->LoadMissionLabel->hide() ;
    this->ui->LoadMissionDropdown->hide() ;
    this->ui->SaveMissionLabel->hide() ;
    this->ui->SaveMissionTextBox->hide() ;

    //Show hidden GUI elements related to mission execution
    this->ui->FinishMissionButton->show() ;

}

/**
 * @brief What happens when FinishMissionButton is clicked. Hides GUI elements related to mission execution
 * and shows GUI elements related to mission planning.
 */
void GSControlPanel::on_FinishMissionButton_clicked()
{

    //Show hidden GUI elements related to mission planning
    this->ui->StartMissionButton->show() ;
    this->ui->LoadMissionButton->show() ;
    this->ui->SaveMissionButton->show() ;
    this->ui->ClearPointsButton->show() ;
    this->ui->LoadMissionLabel->show() ;
    this->ui->LoadMissionDropdown->show() ;
    this->ui->SaveMissionLabel->show() ;
    this->ui->SaveMissionTextBox->show() ;

    //Hide GUI elements related to mission execution
    this->ui->FinishMissionButton->hide() ;

}

/**
 * @brief GSControlPanel::on_LoadMissionButton_clicked
 */
void GSControlPanel::on_LoadMissionButton_clicked()
{

}

/**
 * @brief GSControlPanel::on_SaveMissionButton_clicked
 */
void GSControlPanel::on_SaveMissionButton_clicked()
{

}

/**
 * @brief GSControlPanel::on_ClearPointsButton_clicked
 */
void GSControlPanel::on_ClearPointsButton_clicked()
{

}

/**
 * @brief What to do when ExitButton is clicked. Exit the program.
 */
void GSControlPanel::on_ExitButton_clicked()
{

    //TODO Change so that it can report errors via error codes
    //TODO Transfer exiting over to MainMDIDisplay?
    QApplication::quit() ;

}

/**
 * @brief Get the name of the mission the user put in SaveMissionTextBox.
 * @return QString of the mission name to save
 */
QString GSControlPanel::getMissionNameToSave() {

    return this->ui->SaveMissionTextBox->text() ;

}

/**
 * @brief Get the name of the mission the user selected in LoadMissionDropdown.
 * @return QString of the mission name to load
 */
QString GSControlPanel::getMissionNameToLoad() {

    return this->ui->LoadMissionDropdown->itemData( this->ui->LoadMissionDropdown->currentIndex() ).toString() ;

}

/**
 * @brief Add a mission to LoadMissionDropdown.
 * @param newMissionToLoad - name of mission being added to the dropdown menu
 */
void GSControlPanel::addMissionToLoad( QString newMissionToLoad ) {

    this->ui->LoadMissionDropdown->insertItem( this->ui->LoadMissionDropdown->count() , newMissionToLoad );

}