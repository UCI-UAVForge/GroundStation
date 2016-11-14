#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>

/**
 * Class: DBManager
 * Date: Fall 2016
 * Credits: Aung(David) Moe, Rayan Ahmed
 *
 * Database system for logging system information from the drones for the UAVF project.
 *
 * Required: SQLite
 *
 * Can follow instructions from: https://github.com/katecpp/sql_with_qt
 *
 */
class QString;

class DbManager
{
public:
    ////=== Constructors ===////
    // Sets up a connection with db from 'file' and opens it. Creates db if it doesn't already exist.
    DbManager(const QString& path = "./UAVFDatabase.db");
    ~DbManager(); // Closes the db connection

    ////=== Accessors ===////
    bool isOpen() const;
   // QVector<std::string> getAllMissions() const;

    ////=== Mutators ===////
  //  bool addMission(const QString& name);
  //  bool addWaypointsToMission(const QString& missionName, QList<Waypoint>* wp);
    bool clearMission(const QString& name);
    bool clearAllMissions();

private:
    QSqlDatabase m_db;

    // Create required tables for UAVF if it doesn't already exist
    // Caller: constructor.
    void createTablesIfDoesntExist();
};

#endif // DBMANAGER_H
