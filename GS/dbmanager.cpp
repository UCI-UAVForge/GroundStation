#include <dbmanager.h>

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#include <QVector>
#include <iostream>


////=== Constructors/Destructors ===////

DbManager::DbManager(const QString& fileName, const QString& directory)
    : fileName(fileName), directory(directory)
{
    if (!(this->open(fileName, directory)))
        qDebug() << "Database: connection failed";
    else
    {
        qDebug() << "Database: connection ok";

        // Load data from tables. Create new tables if they don't already exist.
        this->initializeDatabaseSettings();
        this->createOrLoadMissionTable();
        this->createOrLoadFlightPathTable();
    }
}

DbManager::~DbManager()
{
    if (this->m_db.isOpen())
        this->m_db.close();
}

void DbManager::initializeDatabase()
{
    QSqlQuery query;
    query.prepare("PRAGMA foreign_keys = ON;");
    query.exec();
}

void DbManager::createOrLoadMissionTable()
{
    QSqlQuery query;

    // Creates table if it doesn't exist.
    QString queryStatement;
    queryStatement += "CREATE TABLE Mission (";
    queryStatement += "heading  REAL,";
    queryStatement += "lat      REAL,";
    queryStatement += "lan      REAL,";
    queryStatement += "alt      REAL,";
    queryStatement += "pitch    REAL,";
    queryStatement += "roll     REAL,";
    queryStatement += "yaw      REAL,";
    queryStatement += "xvel     REAL,";
    queryStatement += "yvel     REAL,";
    queryStatement += "zvel     REAL";
    queryStatement += ");";
    query.prepare(queryStatement);
    query.exec();

    query.prepare("SELECT * FROM Mission ORDER BY ROWID ASC");
    query.exec();
    while (query.next())
    {
        MissionData data;
        data.heading = query.value(0).toFloat();
        data.lat = query.value(1).toDouble();
        data.lan = query.value(2).toDouble();
        data.alt = query.value(3).toFloat();
        data.pitch = query.value(4).toFloat();
        data.roll = query.value(5).toFloat();
        data.yaw = query.value(6).toFloat();
        data.xvel = query.value(7).toFloat();
        data.yvel = query.value(8).toFloat();
        data.zvel = query.value(9).toFloat();
        this->mission.push_back(data);
    }
}

void DbManager::createOrLoadFlightPathTable()
{
    QSqlQuery query;
    QString queryStatement;

    // Create tables if they doesn't exist.
    queryStatement += "CREATE TABLE FlightPath (";
    queryStatement += "flight_id    INTEGER PRIMARY KEY,";
    queryStatement += "delay        REAL";
    queryStatement += ");";
    query.prepare(queryStatement);
    query.exec();

    queryStatement = "CREATE TABLE Data (";
    queryStatement += "data_id     INTEGER PRIMARY KEY,";
    queryStatement += "flight_id   INTEGER NOT NULL,";
    queryStatement += "content     UNSIGNED TINYINT,";
    queryStatement += "FOREIGN KEY (flight_id) REFERENCES FlightPath (flight_id)";
    queryStatement += ");";
    query.prepare(queryStatement);
    query.exec();

    // Parse data into objects.
    query.prepare("SELECT * FROM FlightPath ORDER BY flight_id ASC");
    query.exec();
    while (query.next())
    {
        FlightPathData data;
        data.actionNum = query.value(0).toString();
        data.delay = query.value(1).toDouble();
        this->flightPath.push_back(data);
    }

    foreach (FlightPathData flightPath, this->flightPath)
    {
        queryStatement = "SELECT * FROM Data ";
        queryStatement += "WHERE Data.flight_id = :actionNum ";
        queryStatement += "ORDER BY Data.flight_id ASC;";
        query.prepare(queryStatement);
        query.addBindValue(":actionNum", flightPath.actionNum);
        query.exec();

        int index = 0;
        while (query.next())
        {
            flightPath.data[index] = query.value(2).toChar();
        }
    }
}

////=== General Commands ===////

void DbManager::saveAll()
{
    this->saveMissionToFile();
    this->saveFlightPathToFile();
}

bool DbManager::isOpen() const
{
    return this->m_db.isOpen();
}

bool DbManager::open(const QString& fileName)
{
    this->open(fileName, "");
}

bool DbManager::open(const QString& fileName, const QString& directory)
{          
    QString fileDirectory;
    if (directory == "")
        fileDirectory = fileName + this->kFileExtension;
    else
        fileDirectory = directory + this->kPathSeparator + fileName + this->kFileExtension;

    this->m_db = QSqlDatabase::addDatabase("QSQLITE");
    this->m_db.setDatabaseName(fileDirectory);
    return this->m_db.open();
}

void DbManager::close()
{
    this->m_db.close();
}

////=== Mission Commands ===////

void DbManager::addMissionData(MissionData newData)
{
    this->mission.push_back(newData);
}

const QVector<MissionData> DbManager::getMission() const
{
    return this->mission;
}

void DbManager::saveMissionToFile()
{
    QSqlQuery query;

    this->clearMissionTable(); // First remove old data in the table.

    // TODO: if performance is slow, try to optimise here to insert all at once.
    foreach (MissionData mission, mission) {
        query.prepare("INSERT INTO Mission (heading, lat, lan, alt, pitch, roll, yaw, xvel, yvel, zvel)"
                      "VALUES (:heading, :lat, :lan, :alt, :pitch, :roll, :yaw, :xvel, :yvel, :zvel)");
        query.bindValue(":heading", mission.heading);
        query.bindValue(":lat",     mission.lat);
        query.bindValue(":lan",     mission.lan);
        query.bindValue(":alt",     mission.alt);
        query.bindValue(":pitch",   mission.pitch);
        query.bindValue(":roll",    mission.roll);
        query.bindValue(":yaw",     mission.yaw);
        query.bindValue(":xvel",    mission.xvel);
        query.bindValue(":yvel",    mission.yvel);
        query.bindValue(":zvel",    mission.zvel);
        query.exec();
    }
}

void DbManager::clearMissionTable()
{
    QSqlQuery query;
    query.prepare("DELETE FROM Mission");
    query.exec();
}

////=== FlightPath Commands ===////

void DbManager::addFlightPathData(FlightPathData newData)
{
    this->flightPath.push_back(newData);
}

const QVector<FlightPathData> getFlightPath() const
{
    return this->flightPath;
}

void saveFlightPathToFile()
{
    QSqlQuery query;

    this->clearFlightPathTable(); // First remove old data in the table.

    // STILL TODO.
    foreach (FlightPathData flightPath, this->flightPath) {
        query.prepare("INSERT INTO FlightPath (heading, lat, lan, alt, pitch, roll, yaw, xvel, yvel, zvel)"
                      "VALUES (:heading, :lat, :lan, :alt, :pitch, :roll, :yaw, :xvel, :yvel, :zvel)");
        query.bindValue(":heading", mission.heading);
        query.bindValue(":lat",     mission.lat);
        query.bindValue(":lan",     mission.lan);
        query.bindValue(":alt",     mission.alt);
        query.bindValue(":pitch",   mission.pitch);
        query.bindValue(":roll",    mission.roll);
        query.bindValue(":yaw",     mission.yaw);
        query.bindValue(":xvel",    mission.xvel);
        query.bindValue(":yvel",    mission.yvel);
        query.bindValue(":zvel",    mission.zvel);
        query.exec();
    }
}

void DbManager::clearFlightPathTable()
{
    QSqlQuery query;
    query.prepare("DELETE FROM FlightPath; DELETE FROM Data");
    query.exec();
}

void DbManager::

//void DbManager::createFlightPathTable()
//{
//    QSqlQuery query;

//    query.prepare("CREATE TABLE mission(id INTEGER UNIQUE PRIMARY KEY AUTOINCREMENT, name TEXT UNIQUE);");

//    if (!query.exec())
//    {
//        qDebug() << "Couldn't create the table 'mission': one might already exist.";
//    }

//    query.prepare("CREATE TABLE flightinfo(id INTEGER, lat REAL, lon REAL, alt REAL, speed REAL, FOREIGN KEY (id) REFERENCES mission(id));");

//    if (!query.exec())
//    {
//        qDebug() << "Couldn't create the table 'flightinfo': one might already exist.";
//    }
//}

//void DbManager::createDataTable()
//{

//}

////=== Mutators ===////

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

