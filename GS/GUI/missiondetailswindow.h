//#ifndef MISSIONDETAILSWINDOW_H
//#define MISSIONDETAILSWINDOW_H

//#include <QGridLayout>
//#include <QLabel>
//#include <QJsonObject>
//#include <QJsonValue>
//#include <QScrollArea>
//#include <QVBoxLayout>
//#include <QWidget>

//#include "clickableqlabel.h"
//#include "fzlayoutbox.h"
//#include "interop.h"
//#include "mission.h"
//#include "poslayoutbox.h"


//class missionDetailsWindow : public QWidget
//{
//    Q_OBJECT
//public:
//    explicit missionDetailsWindow(QWidget *parent = nullptr, Interop *interop=nullptr, QQuickWidget * mapWidget=nullptr);

//private:
//    Interop *interop;
//    QGridLayout *layout, *posLayout, *sgpLayout, *mwLayout, *fzLayout, *currLayout;
//    QQuickWidget * mapWidget;
//    QLabel * title, *titleb,*titlec,*titled;
//    posLayoutBox *off_axis_odlc_pos, *emergent_last_known_pos, *home_pos, *air_drop_pos;
//    fzLayoutBox *fz;
//    Mission mission;
//    clickableQLabel * createTitleBox(QString t);
//    QLabel * createTextBox(QString t);
//    void createposLayout();
//    void createsgpLayout();
//    void createmwLayout();
//    void createfzLayout();

//signals:

//public slots:
//    void updateMission();

//private slots:
//    void loadNewMission(int i);
//    void showsgpLayout();
//    void showmwLayout();
//    void showfzLayout();
//    void clearOldMission();
//};

//#endif // MISSIONDETAILSWINDOW_H
