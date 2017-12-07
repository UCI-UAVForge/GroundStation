//#include "missiondetailswindow.h"

//missionDetailsWindow::missionDetailsWindow(QWidget *parent, Interop *interop,QQuickWidget * mapWidget) : QWidget(parent), interop(interop), mapWidget(mapWidget)
//{
//    layout = new QGridLayout(this);
//    layout->setSpacing(6);

//    title = new clickableQLabel();
//    title->setText("Mission _");
//    title->setAlignment(Qt::AlignCenter);
//    title->setStyleSheet("QLabel {border: 1px solid black; font-size: 16pt; font-weight: bold;}");
//    layout->addWidget(title                                                 ,0,0,1,2);
//    connect(title, SIGNAL(clicked()),SLOT(updateMission()));


//    titleb = createTitleBox("Search Grid Points");
//    layout->addWidget(titleb                                                ,1,0,1,2);
//    connect(titleb, SIGNAL(clicked()),SLOT(showsgpLayout()));

//    titlec = createTitleBox("Mission Way Points");
//    layout->addWidget(titlec                                                ,2,0,1,2);
//    connect(titlec, SIGNAL(clicked()),SLOT(showmwLayout()));

//    titled = createTitleBox("Fly Zones");
//    layout->addWidget(titled                                                ,3,0,1,2);
//    connect(titled, SIGNAL(clicked()),SLOT(showfzLayout()));

//    createposLayout();
//    createsgpLayout();
//    createmwLayout();
//    createfzLayout();

//    currLayout=posLayout;
//    layout->addLayout(currLayout,0,2,4,8);



//    setLayout(layout);
//}




//clickableQLabel * missionDetailsWindow::createTitleBox(QString t){

//    clickableQLabel * temp = new clickableQLabel();
//    temp->setText(t);
//    temp->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
//    temp->setStyleSheet("QLabel {border: 1px solid black; font-size: 12pt;}");
//    return temp;
//}

//QLabel * missionDetailsWindow::createTextBox(QString t){

//    QLabel * temp = new QLabel(t);
//    temp->setAlignment(Qt::AlignCenter);
//    return temp;
//}

//void missionDetailsWindow::createposLayout(){
//    posLayout = new QGridLayout(nullptr);

//    off_axis_odlc_pos= new posLayoutBox("Off Axis ODLC Pos","N/A","N/A");
//    posLayout->addLayout(off_axis_odlc_pos                                     ,0,0,2,2);

//    emergent_last_known_pos= new posLayoutBox("Emergent Last Known Pos","N/A","N/A");
//    posLayout->addLayout(emergent_last_known_pos                               ,0,2,2,2);

//    home_pos= new posLayoutBox("Home Pos","N/A","N/A");
//    posLayout->addLayout(home_pos                                              ,2,0,2,2);

//    air_drop_pos= new posLayoutBox("Air Drop Pos","N/A","N/A");
//    posLayout->addLayout(air_drop_pos                                          ,2,2,2,2);
//}

//void missionDetailsWindow::createsgpLayout(){
//    sgpLayout = new QGridLayout(nullptr);
////    QScrollArea::setWidget(sgpLayout->widget());


//}

//void missionDetailsWindow::createmwLayout(){
//    mwLayout = new QGridLayout(nullptr);
////    QScrollArea::setWidget(mwLayout->widget());
//}

//void missionDetailsWindow::createfzLayout(){
//    fzLayout = new QGridLayout(nullptr);
//    fz = new fzLayoutBox();
//    fzLayout->addLayout(fz,0,0,4,4);
////     QScrollArea::setWidget(fzLayout->widget());
//}


//void missionDetailsWindow::updateMission(){
//    loadNewMission(1);
//}

//void missionDetailsWindow::loadNewMission(int i){
//    mission.setMission(interop->getMission(i));

//    QJsonValue test = mission.get_air_drop_pos()["latitude"];
////    qDebug()<<mission.get_air_drop_pos()["latitude"];
////    qDebug()<<mission.get_air_drop_pos()["latitude"].toString();
//    off_axis_odlc_pos->setLatLon(QString::number(mission.get_off_axis_odlc_pos()["latitude"].toDouble()),QString::number(mission.get_off_axis_odlc_pos()["longitude"].toDouble()));
//    emergent_last_known_pos->setLatLon(QString::number(mission.get_emergent_last_known_pos()["latitude"].toDouble()),QString::number(mission.get_emergent_last_known_pos()["longitude"].toDouble()));
//    home_pos->setLatLon(QString::number(mission.get_home_pos()["latitude"].toDouble()),QString::number(mission.get_home_pos()["longitude"].toDouble()));
//    air_drop_pos->setLatLon(QString::number(mission.get_air_drop_pos()["latitude"].toDouble()),QString::number(mission.get_air_drop_pos()["longitude"].toDouble()));
//    currLayout=posLayout;
//    mission.loadMissionObjects(mapWidget);
//}

//void missionDetailsWindow::showsgpLayout(){
//    currLayout=sgpLayout;
//}

//void missionDetailsWindow::showmwLayout(){
//    currLayout=mwLayout;
//}

//void missionDetailsWindow::showfzLayout(){
//    currLayout=fzLayout;
//}

//void missionDetailsWindow::clearOldMission(){

//}
