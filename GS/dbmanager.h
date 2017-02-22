/**
 * Class: DBManager
 * Date: Fall 2016
 * Author: Aung(David) Moe, Rayan Ahmed
 * Description: Database system for logging system information to/from the drones for the UAVF project.
 *
 *
 * !!!!!! IMPORTANT: Add 'QT += sql' to the .pro file. !!!!!!
 *
 * Example for Mission:
 *  DbManager db("Test1","Database");   // Creates a file Database/Test1.db. The folder must exist
    if (db.isOpen())
    {
        db.addMissionData({});
        db.addMissionData({2.1,1.1,1.1,1.1,1.1,1.1,1.1,1.1,1.1,1.1});
        db.addMissionData({3.2,1.2,1.2,1.2,1.2,1.2,1.2,1.2,1.2,1.2});
        db.addMissionData({4,1,1,1,1,1,1,1,1,1});
        db.saveMissionToFile();

        foreach (MissionData data, db.getMission())
        {
            // do something
        }
 *
 *
 */

#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QString>
#include <QSqlDatabase>
#include <QVector>

// Represents a 'Mission' data.
struct MissionData {
    float heading;
    double lat;
    double lan;
    float alt;
    float pitch;
    float roll;
    float yaw;
    float xvel;
    float yvel;
    float zvel;
};

/**
 * @brief The DbManager class - Interaction to save/load UAVF information will be handled in this class.
 */
class DbManager
{
public:
////=== Constructors/Destructors ===////

    /**
     * @brief DbManager - Opens a connection with the database from 'directory/fileName'.
     * Creates a new database with 'fileName' in 'directory' if the file doesn't exist.
     * @param fileName - The name of the mission file without the extension.
     * @param directory - The folder where the database file is located.
     * @note - Do not include the fileName's extension (e.g. mission1.db -> just mission1)
     */
    DbManager(const QString& fileName = "aDatabase", const QString& directory = "");

    // Closes any connection.
    ~DbManager();


////=== General Commands ===////

    // Returns true if a database is connected.
    bool isOpen() const;

    // Opens a database connection to 'directory/filename'
    bool open(const QString& fileName, const QString& directory);

    // Close current database connection.
    void close();

////=== Mission Commands ===////

    /*
       Note: all the mission commands here interact with an instance variable; they
       do not alter or modify the database.

       Use DbManager::saveMissionToFile() to save the instance variable 'mission' to database.
    */

    // Add a data to the mission. Changes the instance variable 'mission'.
    void addMissionData(MissionData data);

    // Get current mission with all the added information. Returns instance variable 'mission'
    const QVector<MissionData> getMission() const;

    // Save mission to database. Modifies the database.
    void saveMissionToFile();





    /**
     * @brief getAllWaypoints - Gets all the waypoints for the current mission.
     * @return - All the waypoints in the database.
     */
//    QList<Protocol::Waypoint> getWaypoints() const;
//    bool addWaypointsToMission(const QString& missionName, QList<Protocol::Waypoint> wp);

private:
    QSqlDatabase m_db;
    QVector<MissionData> mission;


    // File Related
    QString fileName;
    QString directory;
    const QString kDatabaseType = "QSQLITE";
    const QString kFileExtension = ".db";
    const char kPathSeparator =
        #ifdef _WIN32
                                '\\';
        #else
                                '/';
        #endif


////=== Constructor/Destructor ===////

    // These are called by DbManager::createTablesIfDoesntExist()
    void createOrLoadMissionTable();

////=== Mission Commands ===////

    // Clear all the records in [Mission] database.
    void clearMissionTable();

};

#endif // DBMANAGER_H
