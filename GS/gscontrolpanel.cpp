#include "gscontrolpanel.h"
#include "ui_gscontrolpanel.h"

/**
 * @brief Default constructor for GSControlPanel
 * @param parent
 */
GSControlPanel::GSControlPanel(QWidget *parent):QDialog(parent),ui(new Ui::GSControlPanel) {
    // Set up the GUI
    this->ui->setupUi(this);
    connect( this , SIGNAL( updateGSCP() ) , this , SLOT( updateStateGSCP() ) ) ;
    // Initialize current state
    emit updateGSCP() ;
}

/**
 * @brief Default destructor for GSControlPanel
 */
GSControlPanel::~GSControlPanel() {
    delete ui;
}

/**
 * @brief Transitions from Main Menu to Planning
 */
void GSControlPanel::on_CreateMissionButton_clicked() {
    this->CurrentState = Planning ;
    emit updateGSCP() ;
    emit createMissionButton_clicked();
}

/**
 * @brief What happens when StartMissionButton is clicked. Hides GUI elements related to mission planning
 * and shows GUI elements related to mission execution.
 */
void GSControlPanel::on_StartMissionButton_clicked() {
    ///\todo Have StartMissionButton be disabled until you have at least one point in your flightpath
    this->CurrentState = Execution ;
    emit updateGSCP() ;
    emit startMissionButton_clicked();
}

/**
 * @brief What happens when FinishMissionButton is clicked. Hides GUI elements related to mission execution
 * and shows GUI elements related to mission planning.
 */
void GSControlPanel::on_FinishMissionButton_clicked() {
    this->CurrentState = Recap ;
    emit updateGSCP() ;
    emit finishMissionButton_clicked();
}

/**
 * @brief GSControlPanel::on_LoadMissionButton_clicked
 */
void GSControlPanel::on_LoadMissionButton_clicked() {
    this->CurrentState = LoadMission ;
    emit updateGSCP() ;
    emit loadMissionButton_clicked();
}

/**
 * @brief GSControlPanel::on_SaveMissionButton_clicked
 */
void GSControlPanel::on_SaveMissionButton_clicked() {
    emit updateGSCP() ;
    emit saveMissionButton_clicked();
}

/**
 * @brief GSControlPanel::on_ClearPointsButton_clicked
 */
void GSControlPanel::on_ClearPointsButton_clicked()
{
    ///\todo Rename. It is now the Clear Flightpath button.
    emit updateGSCP() ;
    emit clearPointsButton_clicked();
}

/**
 * @brief What to do when ExitButton is clicked. Exit the program.
 */
void GSControlPanel::on_ExitButton_clicked()
{

    /// \todo Change so that it can report errors via error codes
    /// \todo Transfer exiting over to MainMDIDisplay?
    /// \todo Should exit be an FSM state?
    ///         YES plz! - Jordan
    emit updateGSCP() ;
    emit exitButton_clicked();
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


/**
 * @brief Get the name of the flightpath the user put in SaveFlightPathTextBox.
 * @return QString of the flightpath name to save
 */
QString GSControlPanel::getFlightpathNameToSave() {
    return this->ui->SaveFlightPathTextBox->text() ;
}

/**
 * @brief Get the name of the flightpath the user selected in LoadFlightpathDropdown.
 * @return QString of the flightpath name to load
 */
QString GSControlPanel::getFlightpathNameToLoad() {
    return this->ui->LoadFlightpathDropdown->itemData( this->ui->LoadFlightpathDropdown->currentIndex() ).toString() ;
}

/**
 * @brief Add a flightpath to LoadFlightpathDropdown.
 * @param newFlightpathToLoad - name of flightpath being added to the dropdown menu
 */
void GSControlPanel::addFlightpathToLoad( QString newFlightpathToLoad ) {
    this->ui->LoadFlightpathDropdown->insertItem( this->ui->LoadFlightpathDropdown->count() , newFlightpathToLoad );
}

/**
 * @brief GSControlPanel::on_LoadFlightpathButton_clicked
 */
void GSControlPanel::on_LoadFlightpathButton_clicked() {
    if ( this->CurrentState == MainMenu ) {
        this->CurrentState = LoadFlightpath ;
    }
    else if ( this->CurrentState == LoadFlightpath ) {
        this->CurrentState = Planning ;
    }
    else {
        // Do nothing.
    }
    this->updateGSCP() ;
    emit loadFlightpathButton_clicked() ;
}

/**
 * @brief GSControlPanel::on_MainMenuButton_clicked
 */
void GSControlPanel::on_MainMenuButton_clicked() {
    this->CurrentState = MainMenu ;
    this->updateGSCP() ;
    emit mainMenuButton_clicked() ;
}

/**
 * @brief GSControlPanel::on_SaveFlightpathButton_clicked
 */
void GSControlPanel::on_SaveFlightpathButton_clicked() {
    this->updateGSCP() ;
    emit saveFlightpathButton_clicked() ;
}

/**
 * @brief GSControlPanel::on_MissionRecapButton_clicked
 */
void GSControlPanel::on_MissionRecapButton_clicked() {
    this->CurrentState = Recap ;
    this->updateGSCP() ;
    emit missionRecapButton_clicked() ;
}

/**
 * @brief GSControlPanel::updateStateGSCP
 */
void GSControlPanel::updateStateGSCP() {
    ///Update state hides and shows GUI elements based on the value of CurrentState.
    ///The following is a list of all the GUI elements in GSControlPanel:
    /// - CreateMissionButton
    /// - StartMissionButton
    /// - FinishMissionButton
    /// - LoadFlightpathButton
    /// - LoadMissionButton
    /// - SaveMissionButton
    /// - MissionRecapButton
    /// - ClearPointsButton ( ClearFlightpathButton)
    /// - SaveFlightpathButton
    /// - ExitButton
    /// - MainMenuButton
    /// - LoadMissionLabel
    /// - LoadMissionDropdown
    /// - SaveMissionLabel
    /// - SaveMissionTextBox
    /// - LoadFlightpathLabel
    /// - LoadFlightpathDropdown
    /// - SaveFlightpathLabel
    /// - SaveFlightpathTextBox

    switch ( this->CurrentState ) {
        case MainMenu:
            this->setWindowTitle( "Main Menu" );
            ui->CreateMissionButton->show() ;
            ui->StartMissionButton->hide() ;
            ui->FinishMissionButton->hide() ;
            ui->LoadFlightpathButton->show() ;
            ui->LoadMissionButton->show() ;
            ui->SaveMissionButton->hide() ;
            ui->MissionRecapButton->hide() ;
            ui->ClearPointsButton->hide() ;
            ui->SaveFlightpathButton->hide() ;
            ui->ExitButton->show() ;
            ui->MainMenuButton->hide() ;
            ui->LoadMissionLabel->hide() ;
            ui->LoadMissionDropdown->hide() ;
            ui->SaveMissionLabel->hide() ;
            ui->SaveMissionTextBox->hide() ;
            ui->LoadFlightpathLabel->hide() ;
            ui->LoadFlightpathDropdown->hide() ;
            ui->SaveFlightpathLabel->hide() ;
            ui->SaveFlightPathTextBox->hide() ;
            emit inMainMenuState() ;
            break ;
        case LoadFlightpath:
            this->setWindowTitle( "Load Flightpath" );
            ui->CreateMissionButton->hide() ;
            ui->StartMissionButton->hide() ;
            ui->FinishMissionButton->hide() ;
            ui->LoadFlightpathButton->show() ;
            ui->LoadMissionButton->hide() ;
            ui->SaveMissionButton->hide() ;
            ui->MissionRecapButton->hide() ;
            ui->ClearPointsButton->hide() ;
            ui->SaveFlightpathButton->hide() ;
            ui->ExitButton->hide() ;
            ui->MainMenuButton->show() ;
            ui->LoadMissionLabel->hide() ;
            ui->LoadMissionDropdown->hide() ;
            ui->SaveMissionLabel->hide() ;
            ui->SaveMissionTextBox->hide() ;
            ui->LoadFlightpathLabel->show() ;
            ui->LoadFlightpathDropdown->show() ;
            ui->SaveFlightpathLabel->hide() ;
            ui->SaveFlightPathTextBox->hide() ;
            emit inLoadFlightpathState() ;
            break ;
        case Planning:
            this->setWindowTitle( "Planning" );
            ui->CreateMissionButton->hide() ;
            ui->StartMissionButton->show() ;
            ui->FinishMissionButton->hide() ;
            ui->LoadFlightpathButton->hide() ;
            ui->LoadMissionButton->hide() ;
            ui->SaveMissionButton->hide() ;
            ui->MissionRecapButton->hide() ;
            ui->ClearPointsButton->show() ;
            ui->SaveFlightpathButton->show() ;
            ui->ExitButton->hide() ;
            ui->MainMenuButton->show() ;
            ui->LoadMissionLabel->hide() ;
            ui->LoadMissionDropdown->hide() ;
            ui->SaveMissionLabel->hide() ;
            ui->SaveMissionTextBox->hide() ;
            ui->LoadFlightpathLabel->hide() ;
            ui->LoadFlightpathDropdown->hide() ;
            ui->SaveFlightpathLabel->show() ;
            ui->SaveFlightPathTextBox->show() ;
            emit inPlanningState() ;
            break ;
        case LoadMission:
            this->setWindowTitle( "Load Mission" );
            ui->CreateMissionButton->hide() ;
            ui->StartMissionButton->hide() ;
            ui->FinishMissionButton->hide() ;
            ui->LoadFlightpathButton->hide() ;
            ui->LoadMissionButton->hide() ;
            ui->SaveMissionButton->hide() ;
            ui->MissionRecapButton->show() ;
            ui->ClearPointsButton->hide() ;
            ui->SaveFlightpathButton->hide() ;
            ui->ExitButton->hide() ;
            ui->MainMenuButton->show() ;
            ui->LoadMissionLabel->show() ;
            ui->LoadMissionDropdown->show() ;
            ui->SaveMissionLabel->hide() ;
            ui->SaveMissionTextBox->hide() ;
            ui->LoadFlightpathLabel->hide() ;
            ui->LoadFlightpathDropdown->hide() ;
            ui->SaveFlightpathLabel->hide() ;
            ui->SaveFlightPathTextBox->hide() ;
            emit inLoadMissionState() ;
            break ;
        case Execution:
            this->setWindowTitle( "Execution" );
            ui->CreateMissionButton->hide() ;
            ui->StartMissionButton->hide() ;
            ui->FinishMissionButton->show() ;
            ui->LoadFlightpathButton->hide() ;
            ui->LoadMissionButton->hide() ;
            ui->SaveMissionButton->hide() ;
            ui->MissionRecapButton->hide() ;
            ui->ClearPointsButton->hide() ;
            ui->SaveFlightpathButton->hide() ;
            ui->ExitButton->hide() ;
            ui->MainMenuButton->hide() ;
            ui->LoadMissionLabel->hide() ;
            ui->LoadMissionDropdown->hide() ;
            ui->SaveMissionLabel->hide() ;
            ui->SaveMissionTextBox->hide() ;
            ui->LoadFlightpathLabel->hide() ;
            ui->LoadFlightpathDropdown->hide() ;
            ui->SaveFlightpathLabel->hide() ;
            ui->SaveFlightPathTextBox->hide() ;
            emit inExecutionState() ;
            break ;
        case Recap:
            this->setWindowTitle( "Recap" );
            ui->CreateMissionButton->hide() ;
            ui->StartMissionButton->hide() ;
            ui->FinishMissionButton->hide() ;
            ui->LoadFlightpathButton->hide() ;
            ui->LoadMissionButton->hide() ;
            ui->SaveMissionButton->show() ;
            ui->MissionRecapButton->hide() ;
            ui->ClearPointsButton->hide() ;
            ui->SaveFlightpathButton->hide() ;
            ui->ExitButton->hide() ;
            ui->MainMenuButton->show() ;
            ui->LoadMissionLabel->hide() ;
            ui->LoadMissionDropdown->hide() ;
            ui->SaveMissionLabel->show() ;
            ui->SaveMissionTextBox->show() ;
            ui->LoadFlightpathLabel->hide() ;
            ui->LoadFlightpathDropdown->hide() ;
            ui->SaveFlightpathLabel->hide() ;
            ui->SaveFlightPathTextBox->hide() ;
            emit inRecapState() ;
            break ;
        default:
            this->setWindowTitle( "" );
            ui->CreateMissionButton->hide() ;
            ui->StartMissionButton->hide() ;
            ui->FinishMissionButton->hide() ;
            ui->LoadFlightpathButton->hide() ;
            ui->LoadMissionButton->hide() ;
            ui->SaveMissionButton->hide() ;
            ui->MissionRecapButton->hide() ;
            ui->ClearPointsButton->hide() ;
            ui->SaveFlightpathButton->hide() ;
            ui->ExitButton->hide() ;
            ui->MainMenuButton->hide() ;
            ui->LoadMissionLabel->hide() ;
            ui->LoadMissionDropdown->hide() ;
            ui->SaveMissionLabel->hide() ;
            ui->SaveMissionTextBox->hide() ;
            ui->LoadFlightpathLabel->hide() ;
            ui->LoadFlightpathDropdown->hide() ;
            ui->SaveFlightpathLabel->hide() ;
            ui->SaveFlightPathTextBox->hide() ;
            emit inUndefinedState() ;
            break ;
    }
}
