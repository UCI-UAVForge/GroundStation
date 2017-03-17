#include "qttabtest.h"

//TODO Somebody please fix all the memory leaks in this project. We want a clean program close.
//This doesn't seem to work lol

/**
 * Constructor for the main window
 */
QtTabTest::QtTabTest(QWidget *parent) : QMainWindow( parent ) , ui( new Ui::QtTabTest ) , isFirstTabEmpty( true ) {
    ui->setupUi( this );
}

/**
 * Destructor for the main window
 */
QtTabTest::~QtTabTest() {

    delete ui;

}

/* Roman Parise - Temporary function for adding a new tab to the window. Eventually,
 *
 * have a special QWidget with this function */

void QtTabTest::addNewTab( QWidget * myNewTabWidget , QString label ) {

    //The tab itself

    QGridLayout * newTab = new QGridLayout();

    QMdiArea * newMdiArea = new QMdiArea();

    newMdiArea->addSubWindow( myNewTabWidget );

    myNewTabWidget->showMaximized();

    newTab->addWidget( newMdiArea );

    this->ui->tabWidget->addTab( myNewTabWidget , label );

    if ( isFirstTabEmpty == true ) {
        /* If we're still stuck with the default empty first tab in tabWidget, remove it. */
        this->ui->tabWidget->removeTab(0);
        isFirstTabEmpty = false;
    }

    else {

        /* Do nothing */

    }

}

void QtTabTest::deleteTabIndex( int index ) {
    this->ui->tabWidget->removeTab( index );
}

void QtTabTest::deleteTabWidget( QWidget * qw ) {
    this->ui->tabWidget->removeTab( this->ui->tabWidget->indexOf(qw) );
}
