#include "gscontrolpanel.h"
#include "ui_gscontrolpanel.h"
#include "QDebug.h"
#include <QDir>
#include <QStandardPaths>

GSCPState GSControlPanel::persistantState = MainMenuState;

/**
 * @brief Default constructor for GSControlPanel
 * @param parent
 */
GSControlPanel::GSControlPanel(QWidget *parent):QDialog(parent),ui(new Ui::GSControlPanel) {
    // Set up the GUI
    this->ui->setupUi(this);

    //temporarily disable these for design review
    //this->ui->LoadMissionButton->setEnabled(false);
    //this->ui->SaveMissionButton->setEnabled(false);

    // Embed MissionStatusWindow into the GSControlPanel window.
    this->ui->MissionStatusWindowWidget->setWindowFlags(Qt::Widget);
    //this->setCurrentTelemetryPacket(EMPTY_TELEMETRY_PACKET);
    // Whenever GSControlPanel's state is updated, update the GUI accordingly
    connect( this , SIGNAL( updateGSCP() ) , this , SLOT( updateStateGSCP() ) ) ;
    // Initialize current state
    //static GSCPState persistantState = MainMenuState;

    CurrentState = GSControlPanel::persistantState;
    emit updateGSCP();
}

/**
 * @brief Default destructor for GSControlPanel
 */
GSControlPanel::~GSControlPanel() {
    delete ui;
}

/*
void GSControlPanel::setCurrentTelemetryPacket(Protocol::TelemetryPacket * tp) {
    this->ui->MissionStatusWindowWidget->setCurrentTelemetryPacket(tp);
}*/

void GSControlPanel::setCurrentTelemetryData(TelemetryData* data) {
    this->ui->MissionStatusWindowWidget->setCurrentTelemetryData(data);
}

/**
 * @brief Transitions from Main Menu to Planning
 */
void GSControlPanel::on_CreateMissionButton_clicked() {
    this->CurrentState = PlanningState ;
    emit updateGSCP() ;
    emit createMissionButton_clicked();
}

/**
 * @brief What happens when StartMissionButton is clicked. Hides GUI elements related to mission planning
 * and shows GUI elements related to mission execution.
 */
void GSControlPanel::on_StartMissionButton_clicked() {
    ///\todo Have StartMissionButton be disabled until you have at least one point in your flightpath
    this->CurrentState = ExecutionState ;
    emit updateGSCP() ;
    emit startMissionButton_clicked();
}

/**
 * @brief What happens when FinishMissionButton is clicked. Hides GUI elements related to mission execution
 * and shows GUI elements related to mission planning.
 */
void GSControlPanel::on_FinishMissionButton_clicked() {
    this->CurrentState = RecapState ;
    emit updateGSCP() ;
    emit finishMissionButton_clicked();
}

/**
 * @brief GSControlPanel::on_LoadMissionButton_clicked
 */
void GSControlPanel::on_LoadMissionButton_clicked() {
    this->CurrentState = LoadMissionState ;


    //coppied code
    //Clear the current dropdown menu
    this->ui->LoadMissionDropdown->clear();

    // Open folder from the 'Documents' directory.
    const QString documentDir = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).first();
    this->folder = documentDir + "/UAVForge";
    if (!QDir(this->folder).exists())
        QDir().mkdir(this->folder);

    // Load all the database files.
    QDir dbFolder(this->folder);
    dbFolder.setSorting(QDir::SortFlag::Name);
    QStringList dbFiles = dbFolder.entryList({"*_mis.db"});
    foreach (QString file, dbFiles) {
        addMissionToLoad(file.remove(file.length()-7, 7));
    }
    //end coppied code

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
    QString name = this->ui->SaveMissionTextBox->text() ;
    if(name == ""){
        return "";
    }
    return this->folder + this->kPathSeparator + name + "_mis";
}

/**
 * @brief Get the name of the mission the user selected in LoadMissionDropdown.
 * @return QString of the mission name to load
 */
QString GSControlPanel::getMissionNameToLoad() {
    QString name = ui->LoadMissionDropdown->currentText();
    if(name == ""){
        return "";
    }
    return this->folder + this->kPathSeparator + name + "_mis";
}

/**
 * @brief Add a mission to LoadMissionDropdown.
 * @param newMissionToLoad - name of mission being added to the dropdown menu
 */
void GSControlPanel::addMissionToLoad( QString newMissionToLoad ) {

    //if (this->ui->LoadMissionDropdown->findText(newMissionToLoad) == -1) {
        this->ui->LoadMissionDropdown->insertItem( this->ui->LoadMissionDropdown->count() , newMissionToLoad );
    //}
}


/**
 * @brief Get the name of the flightpath the user put in SaveFlightPathTextBox.
 * @return QString of the flightpath name to save
 */
QString GSControlPanel::getFlightpathNameToSave() {
    QString name = this->ui->SaveFlightPathTextBox->text() ;
    if(name == ""){
        return "";
    }
    return this->folder + this->kPathSeparator + name + "_fp";
}

/**
 * @brief Get the name of the flightpath the user selected in LoadFlightpathDropdown.
 * @return QString of the flightpath name to load
 */
QString GSControlPanel::getFlightpathNameToLoad() {
    QString name = ui->LoadFlightpathDropdown->currentText();
    if(name == ""){
        return "";
    }
    return this->folder + this->kPathSeparator + name + "_fp";
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
    if ( this->CurrentState == MainMenuState ) {
        this->CurrentState = LoadFlightpathState ;

        //Clear the current dropdown menu
        this->ui->LoadFlightpathDropdown->clear();

        // Open folder from the 'Documents' directory.
        const QString documentDir = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).first();
        this->folder = documentDir + "/UAVForge";
        if (!QDir(this->folder).exists())
            QDir().mkdir(this->folder);

        // Load all the database files.
        QDir dbFolder(this->folder);
        dbFolder.setSorting(QDir::SortFlag::Name);
        QStringList dbFiles = dbFolder.entryList({"*_fp.db"});
        foreach (QString file, dbFiles) {
            addFlightpathToLoad(file.remove(file.length()-6, 6));
        }
    }
    else if ( this->CurrentState == LoadFlightpathState ) {
        emit loadFlightpathButton_clicked() ;
        this->CurrentState = PlanningState ;
    }
    else {
        // Do nothing.
    }
    this->updateGSCP() ;
}

/**
 * @brief GSControlPanel::on_MainMenuButton_clicked
 */
void GSControlPanel::on_MainMenuButton_clicked() {
    this->CurrentState = MainMenuState ;
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
    this->CurrentState = RecapState ;
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

    GSControlPanel::persistantState = CurrentState;

    switch ( this->CurrentState ) {
        case MainMenuState:
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
            ui->MissionStatusWindowWidget->hide();
            ui->MissionStatusWindowWidget->stopWidgets();
            emit inMainMenuState() ;
            break ;
        case LoadFlightpathState:
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
            ui->MissionStatusWindowWidget->hide();
            ui->MissionStatusWindowWidget->stopWidgets();
            emit inLoadFlightpathState() ;
            break ;
        case PlanningState:
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
            ui->MissionStatusWindowWidget->hide();
            ui->MissionStatusWindowWidget->stopWidgets();
            emit inPlanningState() ;
            break ;
        case LoadMissionState:
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
            ui->MissionStatusWindowWidget->hide();
            ui->MissionStatusWindowWidget->stopWidgets();
            emit inLoadMissionState() ;
            break ;
        case ExecutionState:
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
            ui->MissionStatusWindowWidget->initiateWidgets();
            ui->MissionStatusWindowWidget->show();
            emit inExecutionState() ;
            break ;
        case RecapState:
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
            ui->MissionStatusWindowWidget->hide();
            ui->MissionStatusWindowWidget->stopWidgets();
            emit inRecapState() ;
            break ;
        default: //Undefined state
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
            ui->MissionStatusWindowWidget->hide();
            ui->MissionStatusWindowWidget->stopWidgets();
            emit inUndefinedState() ;
            break ;
    }
}

/**
 * @brief Sets the LoadMissionDropdown and SaveMission to 'text'.
 * @param text - the currently selected mission.
 */
void GSControlPanel::setSelectedMission(QString text) {
    this->ui->SaveMissionTextBox->setText(text);
    this->ui->LoadMissionDropdown->setCurrentText(text);
}

