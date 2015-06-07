#include "mapexecution.h"

MapExecution::MapExecution(QWidget *parent) : QDialog(parent), ui(new Ui::MapExecution) {
    buttonGroup = new QButtonGroup();
    model = new TableModel();

    ui->setupUi(this);
    ui->tableView->setModel(model);
    ui->tableView->setItemDelegate(new QComboBoxDelegate());

    connect(ui->webView->page()->mainFrame(),SIGNAL(javaScriptWindowObjectCleared()),this,SLOT(addClickListener()), Qt::UniqueConnection);
    ui->webView->load(QUrl("qrc:/res/html/mapsExecution.html"));

    connect(ui->backButton, SIGNAL(clicked()), this, SLOT(on_backButton_clicked()), Qt::UniqueConnection);
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(on_cancelButton_clicked()), Qt::UniqueConnection);
    connect(ui->finishButton, SIGNAL(clicked()), this, SLOT(on_finishButton_clicked()), Qt::UniqueConnection);
    connect(ui->returnHomeButton, SIGNAL(clicked()), this, SLOT(on_returnHomeButton_clicked()), Qt::UniqueConnection);
    connect(ui->stopButton, SIGNAL(clicked()), this, SLOT(on_stopButton_clicked()), Qt::UniqueConnection);
}

MapExecution::MapExecution(QList<QString> strings, QWidget *parent) : QDialog(parent), ui(new Ui::MapExecution) {
    ui->setupUi(this);
    buttonGroup = new QButtonGroup();

    model = new TableModel();
    ui->tableView->setModel(model);
    ui->tableView->setItemDelegate(new QComboBoxDelegate());

    mapStrings = strings;
    connect(ui->webView->page()->mainFrame(),SIGNAL(javaScriptWindowObjectCleared()),this,SLOT(addClickListener()), Qt::UniqueConnection);
    ui->webView->load(QUrl("qrc:/res/html/mapsExecution.html"));

    connect(ui->backButton, SIGNAL(clicked()), this, SLOT(on_backButton_clicked()), Qt::UniqueConnection);
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(on_cancelButton_clicked()), Qt::UniqueConnection);
    connect(ui->finishButton, SIGNAL(clicked()), this, SLOT(on_finishButton_clicked()), Qt::UniqueConnection);
    connect(ui->returnHomeButton, SIGNAL(clicked()), this, SLOT(on_returnHomeButton_clicked()), Qt::UniqueConnection);
    connect(ui->stopButton, SIGNAL(clicked()), this, SLOT(on_stopButton_clicked()), Qt::UniqueConnection);

    std::cout<<"PREPARE" << std::endl;
    QList <QPair<double, double > > h;
    h << QPair<double, double >(32, 32);
    myClient.set_list(getDoublePairs(mapStrings));
    std::cout<<"FOR" << std::endl;
    myClient.gsc_connect_start();
    std::cout<<"THE DEVOURING," << std::endl;
    myClient.gsc_send_message();
    std::cout<<"PUNY HUMANS" << std::endl;
}

MapExecution::~MapExecution() {
    delete ui;
}

// finish button
// redirect to mission recap window
void MapExecution::on_finishButton_clicked() {
    this->done(3);
}

// stop button
void MapExecution::on_stopButton_clicked() {
    QList <QPair<double, double > > h;
    h << QPair<double, double >(999.99,999.99);
    myClient.set_list(h);
    myClient.gsc_send_message();
}

// return home button
// redirect to main window
void MapExecution::on_returnHomeButton_clicked() {
    this->done(0);
}

// cancel button
// redirect to mission planning
void MapExecution::on_cancelButton_clicked() {
    this->done(1);
}

// back button
// redirect to mission planning
void MapExecution::on_backButton_clicked() {
    this->done(1);
}

/* Sends a request for the map to clear itself, causing the JavaScript page
to reload itself. This function then cycles through each entry in the string
list and sends it to the addPoint(QString) function to be added to the map.
Function added by Jordan Dickson Feb 21st 2015. */
void MapExecution::setMap(QList<QString> list) {
    //Sends clearMap request.
    ui->webView->page()->mainFrame()->evaluateJavaScript("clearMap()");

    //Loops through list entries
    for(int i = 0; i < list.length(); i++){
        addPoint(list[i]);
    }
}

QList<QPair<double,double> > MapExecution::getDoublePairs(QList<QString> strings) {
    QList<QPair<double,double> > returnList;
    for(QString string: strings){
        QList<QString> comps = string.split(",");

        //Converts West and South coordinates to negative numbers.
        double lat = comps[3].toDouble();
        double lng = comps[1].toDouble();
        if(comps[2] == "W") {
            lng *= -1.0;
        }
        if(comps[4] == "S") {
            lat *= -1.0;
        }
        returnList.append(QPair<double,double>(lat,lng));
    }

    return returnList;

}

/*  Takes a QString formated (Action,Longitude,LongDirection,Latitude,
LatDirection,Behavior) and extracts the (lat,lng) pair needed to add
a new point to the map. Function added by Jordan Dickson Feb 21st 2015. */
void MapExecution::addPoint(QString string) {
    //Split the string into a list of components separated by ','
    QList<QString> comps = string.split(",");

    //Converts West and South coordinates to negative numbers.
    double lat = comps[3].toDouble();
    double lng = comps[1].toDouble();
    if(comps[2] == "W"){
        lng *= -1.0;
    }
    if(comps[4] == "S"){
        lat *= -1.0;
    }

    //Sends the add point request with its parameters.
    ui->webView->page()->mainFrame()->evaluateJavaScript("addLatLngCoords("+QString::number(lat)+","+QString::number(lng)+")");
}

void MapExecution::push_new_point(QString string) {
   QList<QString> points = string.split(",");
}

/* Since c++/JS bridges are broken when the JS page refreshes this slot
 is used to rebruild the bridge each time when triggered by a
 javaScriptWindowObjectCleared signal from the page frame. Function
 added by Jordan Dickson Feb 21st 2015. */
void MapExecution::addClickListener() {
    //Creates the bridge called cbridge between the java script object and this class.
    ui->webView->page()->mainFrame()->addToJavaScriptWindowObject("cbridge",this);
}

/*  Function called by the JavaScript to add the map data from mission planning.
This is necessary because data cannot be added until the html file is completely
loaded. Jordan 2/21/2015 */
void MapExecution::addNewMap() {
    setMap(mapStrings);
    ui->webView->page()->mainFrame()->evaluateJavaScript("simulateInput()");
}

/*  Sends a (latitude,longitude) pair to the map to be plotted.
Used for telemetry. */
void MapExecution::plotPosition(double lat, double lng) {
    ui->webView->page()->mainFrame()->evaluateJavaScript("addActualPath("+QString::number(lat)+","+QString::number(lng)+")");
}

void MapExecution::updateTable(int lat, int lng) {
    model->insertRow(lng, lat);
//    ui->tableView->update;
    ui->tableView->scrollToBottom();
}
