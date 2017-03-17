#include "dbmanager.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#include <QVector>
#include <iostream>


////=== Constructors/Destructors with initialization commands ===////

DbManager::DbManager(const QString& fileName, const QString& directory)
    : fileName(fileName), directory(directory)
{
    if (!(this->open(fileName, directory)))
        qDebug() << "Database: connection failed";
    else
    {
        qDebug() << "Database: connection ok";
    }
}

DbManager::~DbManager()
{
    if (this->m_db.isOpen())
        this->m_db.close();
}

void DbManager::initializeDatabaseSettings()
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
    queryStatement += "lon      REAL,";
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
        data.lon = query.value(2).toDouble();
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
    queryStatement += "actionNum    INTEGER PRIMARY KEY,";
    queryStatement += "delay        REAL";
    queryStatement += ");";
    query.prepare(queryStatement);
    query.exec();

    queryStatement = "CREATE TABLE FlightData (";
    queryStatement += "data_id     INTEGER PRIMARY KEY,";
    queryStatement += "actionNum   INTEGER NOT NULL,";
    queryStatement += "content     UNSIGNED TINYINT,";
    queryStatement += "FOREIGN KEY (actionNum) REFERENCES FlightPath (actionNum) "
                      "ON DELETE CASCADE";
    queryStatement += ");";
    query.prepare(queryStatement);
    query.exec();

    // Parse data into objects.
    query.prepare("SELECT * FROM FlightPath ORDER BY actionNum ASC");
    query.exec();
    while (query.next())
    {
        FlightPathData data;
        data.actionNum = query.value(0).toInt();
        data.delay = query.value(1).toDouble();
        this->flightPath.push_back(data);
    }

    for (int i = 0; i < this->flightPath.length(); ++i)
    {
        queryStatement = "SELECT * FROM FlightData ";
        queryStatement += "WHERE actionNum = :actionNum ";
        queryStatement += "ORDER BY data_id ASC;";
        query.prepare(queryStatement);
        query.bindValue(":actionNum", this->flightPath.at(i).actionNum);
        query.exec();

        while (query.next())
        {
            this->flightPath[i].data.push_back((unsigned char) query.value(2).toInt());
        }
    }
}

////=== General Commands ===////

void DbManager::saveAll()
{
    this->missionSaveToFile();
    this->flightPathSaveToFile();
}

void DbManager::clearAll()
{
    this->missionClear();
    this->flightPathClear();
}

void DbManager::clearAllFiles()
{
    this->missionClearFile();
    this->flightPathClearFile();
}

bool DbManager::isOpen() const
{
    return this->m_db.isOpen();
}

bool DbManager::open(const QString& fileName, const QString& directory)
{
    if (this->isOpen()) {
        this->close();
    }

    QString fileDirectory;
    if (directory == "")
        fileDirectory = fileName + this->kFileExtension;
    else
        fileDirectory = directory + this->kPathSeparator + fileName + this->kFileExtension;

    this->m_db = QSqlDatabase::addDatabase("QSQLITE");
    this->m_db.setDatabaseName(fileDirectory);
    this->m_db.open();

    if (this->m_db.isOpen()) {
        // Load data from tables. Create new tables if they don't already exist.
        this->initializeDatabaseSettings();
        this->createOrLoadMissionTable();
        this->createOrLoadFlightPathTable();
    }

    return this->m_db.isOpen();
}

void DbManager::close()
{
    this->m_db.close();
    qDebug() << "Database: connection closed";
}

unsigned char* DbManager::toArray(QVector<unsigned char> vector)
{
    unsigned char* charArray = new unsigned char[vector.size()];
    for (int index = 0; index < vector.size(); ++index)
        charArray[index] = vector.at(index);
    return charArray;
}

QVector<unsigned char> DbManager::toVector(unsigned char* array, size_t size)
{
    QVector<unsigned char> vector;
    for (size_t index = 0; index < size; ++index)
        vector.push_back(array[index]);
    return vector;
}

////=== Mission Commands ===////

void DbManager::missionAdd(MissionData newData)
{
    this->mission.push_back(newData);
}

const QVector<MissionData> DbManager::missionGet() const
{
    return this->mission;
}

void DbManager::missionClear()
{
    this->mission.clear();
}

void DbManager::missionSaveToFile()
{
    this->missionClearFile(); // First remove old data in the table.

    QSqlQuery query;
    foreach (MissionData data, mission) {
        query.prepare("INSERT INTO Mission (heading, lat, lon, alt, pitch, roll, yaw, xvel, yvel, zvel)"
                      "VALUES (:heading, :lat, :lon, :alt, :pitch, :roll, :yaw, :xvel, :yvel, :zvel)");
        query.bindValue(":heading", data.heading);
        query.bindValue(":lat",     data.lat);
        query.bindValue(":lon",     data.lon);
        query.bindValue(":alt",     data.alt);
        query.bindValue(":pitch",   data.pitch);
        query.bindValue(":roll",    data.roll);
        query.bindValue(":yaw",     data.yaw);
        query.bindValue(":xvel",    data.xvel);
        query.bindValue(":yvel",    data.yvel);
        query.bindValue(":zvel",    data.zvel);
        query.exec();
    }
}

void DbManager::missionClearFile()
{
    QSqlQuery query;
    query.prepare("DELETE FROM Mission");
    query.exec();
}

////=== FlightPath Commands ===////

void DbManager::flightPathAdd(FlightPathData newData)
{
    this->flightPath.push_back(newData);
}

const QVector<FlightPathData> DbManager::flightPathGet() const
{
    return this->flightPath;
}

void DbManager::flightPathClear()
{
    this->flightPath.clear();
}

void DbManager::flightPathSaveToFile()
{
    this->flightPathClearFile(); // First remove old data in the table.

    QSqlQuery query;
    foreach (FlightPathData data, this->flightPath) {
        // Save FlightPath
        query.prepare("INSERT INTO FlightPath (actionNum, delay) "
                      "VALUES (:actionNum, :delay)");
        query.bindValue(":actionNum", data.actionNum);
        query.bindValue(":delay",     data.delay);
        query.exec();

        // Save FlightData
        for (int index = 0; index < data.data.length(); ++index)
        {
            query.prepare("INSERT INTO FlightData (actionNum, content) "
                          "VALUES (:actionNum, :content)");
            query.bindValue(":actionNum", data.actionNum);
            query.bindValue(":content", data.data.at(index));
            query.exec();
        }
    }
}

void DbManager::flightPathClearFile()
{
    QSqlQuery query;
    query.prepare("DELETE FROM FlightPath");
    query.exec();

    // Not required since it will be deleted on cascade.
    // Enable this if required for older versions of SQLite.
    query.prepare("DELETE FROM FlightData");
    query.exec();
}
