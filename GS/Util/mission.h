#ifndef MISSION_H
#define MISSION_H

//#include <QString>
//#include <QVector>
//#include <QPair>
//#include <QMap>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QQuickWidget>
#include <QQuickItem>
class Mission {
public:
    Mission();

    Mission(QString filename);
    Mission(QJsonDocument document);

    /** @brief Extracts data from an input Packet and stores the values in
     * the values field.
     *  @param telemPacket A pointer to the packet that will be read.
     *  @date April 8, 2016
     */


    QVector<double> *getValuesForID(int id);
    QVector<double> *getValuesForIndex(int index);
    double getValueForIndexAndID(int index,int id);

    bool save(QString filename);
    int numOfEntries();

    QJsonObject get_off_axis_odlc_pos();
    QJsonArray get_search_grid_points();
    QJsonArray get_mission_waypoints();
    QJsonArray get_fly_zones();
    QJsonObject get_emergent_last_known_pos();
    bool isActive();
    int get_id();
    QJsonObject get_home_pos();
    QJsonObject get_air_drop_pos();
    void loadMissionObjects(QQuickWidget * mapWidget);

private:
    void initValues();
    void Clear(QJsonArray &arr);
    QJsonDocument jsonDoc;
    QJsonObject off_axis_odlc_pos;
    QJsonArray search_grid_points;
    QJsonArray mission_waypoints;
    QJsonArray fly_zones;
    QJsonObject emergent_last_known_pos;
    bool active;
    int id;
    QJsonObject home_pos;
    QJsonObject air_drop_pos;

    QVector<QVector<double>* > values;
};

#endif // MISSION_H
