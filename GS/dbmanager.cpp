#include <dbmanager.h>
#include <actionpacket.h>

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#include <QVector>
#include <iostream>

DbManager::DbManager(const QString &path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open())
    {
        qDebug() << "Error: connection with database fail";
    }
    else
    {
        qDebug() << "Database: connection ok";
    }

    this->createTablesIfDoesntExist();
}

void DbManager::createTablesIfDoesntExist()
{
    QSqlQuery query;

    query.prepare("CREATE TABLE mission(id INTEGER UNIQUE PRIMARY KEY AUTOINCREMENT, name TEXT UNIQUE);");

    if (!query.exec())
    {
        qDebug() << "Couldn't create the table 'mission': one might already exist.";
    }

    query.prepare("CREATE TABLE flightinfo(id INTEGER, lat REAL, lon REAL, alt REAL, speed REAL, FOREIGN KEY (id) REFERENCES mission(id));");

    if (!query.exec())
    {
        qDebug() << "Couldn't create the table 'flightinfo': one might already exist.";
    }
}

DbManager::~DbManager()
{
    if (m_db.isOpen())
    {
        m_db.close();
    }
}


////=== Accessors ===////


//bool DbManager::isOpen() const
//{
//    return m_db.isOpen();
//}

//QVector<std::string> DbManager::getAllMissions() const
//{
//    QVector<std::string> list;
//    return list;
//}


////=== Mutators ===////


//bool DbManager::addMission(const QString& name)
//{
//    return false;
//}

//bool DbManager::addWaypointsToMission(const QString& missionName, QList<Waypoint>* wp){
//    bool succeeded = false;
//    QSqlQuery findID;
//    findID.prepare("SELECT id FROM mission WHERE name = :missionName");
//    findID.addBindValue(":missionName", missonName);
//    findID.exec();

//    Protocol::Waypoint temp;
//    for (int i = 0; i < wp->size(); i++){
//        temp = wp->at(i);
//        QSqlQuery query;
//        query.prepare("INSERT INTO flightinfo (id) VALUES (:id)");
//        query.addBindValue(":id", findID.value("id").toInt());
//        query.prepare("INSERT INTO flightinfo (lat) VALUES (:lat)");
//        query.addBindValue(":lat", temp.lat);
//        query.prepare("INSERT INTO flightinfo (lon) VALUES (:lon)");
//        query.addBindValue(":lon", temp.lon);
//        query.prepare("INSERT INTO flightinfo (alt) VALUES (:alt)");
//        query.addBindValue(":alt", temp.alt);
//        query.prepare("INSERT INTO flightinfo (speed) VALUES (:speed)");
//        query.addBindValue(":speed", temp.speed);

//        if(query.exec())
//        {
//            succeeded = true;
//        }
//        else
//        {
//            qDebug() << "addValues error:  " << query.lastError();
//        }
//    }

//    return succeeded;
//}


bool DbManager::clearMission(const QString& name)
{
    return false;
}

bool DbManager::clearAllMissions()
{
    return false;
}

