#include "mainwindow.h"

/**
 * Constructor for the main window
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    //Resize the image for the Mission Execution button
    QPixmap pixmap(":/res/longButtons/Mission_Execution_Button_Type_2.png");
    QIcon ButtonIcon(pixmap);
    ui->pushButton_8->setIcon(ButtonIcon);
    ui->pushButton_8->setIconSize(pixmap.rect().size()/13);

    //Resize the image for the Mission Planning button
    QPixmap pixmap2(":/res/longButtons/Mission_Planning_Button_Type_2.png");
    QIcon ButtonIcon2(pixmap2);
    ui->pushButton_9->setIcon(ButtonIcon2);
    ui->pushButton_9->setIconSize(pixmap2.rect().size()/13);

    //Resize the image for the Mission Recap button
    QPixmap pixmap3(":/res/longButtons/Mission_Recap_Button_Type_2.png");
    QIcon ButtonIcon3(pixmap3);
    ui->pushButton_7->setIcon(ButtonIcon3);
    ui->pushButton_7->setIconSize(pixmap3.rect().size()/13);

    //Resize the image for the Tutorial button
    QPixmap pixmap4(":/res/longButtons/Tutorial_Button_Type_2.png");
    QIcon ButtonIcon4(pixmap4);
    ui->pushButton_6->setIcon(ButtonIcon4);
    ui->pushButton_6->setIconSize(pixmap4.rect().size()/13);
}

/**
 * Deconstrutor for the main window
 */
MainWindow::~MainWindow() {
    delete ui;
}

/**
 * When the tutorial button is clicked, create a new tutorial window,
 * close the main window, and open the tutorial window in full screen
 */
void MainWindow::openTutorial() {

    Tutorial *tutorial = new Tutorial();
    this -> close();
    tutorial -> showFullScreen();
}

/**
 * When the mission planning button is clicked, create a new mission planning
 * window, close the main window, and open the mission planning window in full screen
 */
void MainWindow::missionPlanningClicked() {
    MapPlanning *mapPlanning = new MapPlanning();
//    this->close();
    mapPlanning->showFullScreen();
}

/**
 * When the mission execution button is clicked, create a new mission execution
 * window, close the main window, and open the mission execution window in full screen
 */
void MainWindow::missionExecutionClicked() {
    MapExecution *mapExecution = new MapExecution();
//    this->close();
    mapExecution->showFullScreen();
}

/**
 * When the mission recap buttion is clicked, create a new mission recap window,
 * close the main window, and open the mission recap window in full screen
 */
void MainWindow::missionRecapClicked() {
    MissionRecap *missionRecap = new MissionRecap();
//    this->close();
    missionRecap->showFullScreen();
}

/**
 * Close the main window when ALT + Q is clicked
 */
void MainWindow::on_actionQuit_triggered() {
    this->close();
}
