/**
 * Class: DBManager
 * Date: Fall 2016
 * Author: Aung(David) Moe
 * Description: Database system for logging system information to/from the drones for the UAVF project.
 * Required: Add 'QT += sql' to the .pro file.
 */

/*
Example use:
int main(){
    DbManager db("Test1","Database");   // Creates a file Database/Test1.db. The folder must exist
    if (db.isOpen())
    {
        // To save
        db.addMissionData({});      // Each mission data represents one point.
        db.addMissionData({2.1,1.1,1.1,1.1,1.1,1.1,1.1,1.1,1.1,1.1});
        db.addMissionData({3.2,1.2,1.2,1.2,1.2,1.2,1.2,1.2,1.2,1.2});
        db.addMissionData({4,1,1,1,1,1,1,1,1,1});
        db.saveMissionToFile();

        // To read
        foreach (MissionData data, db.getMission())
        {
            // read all the data missions.
        }
    }
}
*/

#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QString>
#include <QSqlDatabase>
#include <QVector>

// One 'Mission' data represents a theorectical location point on the map.
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

// One 'FlightPath' data represents an actual location point on the map.
struct FlightPathData {
    int actionNum;
    double delay;
    unsigned char data[40];
};

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
    DbManager(const QString& fileName = "unnamed_database", const QString& directory = "");

    // Closes any connection.
    ~DbManager();


////=== General Commands ===////

    // Saves all the files to the database.
    void saveAll();

    // Returns true if a database is connected.
    bool isOpen() const;

    // Opens a database connection to './filename'. It's automatically called by the constructor.
    bool open(const QString& fileName);

    // Opens a database connection to 'directory/filename'.
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
    void addMissionData(MissionData newData);

    // Get current mission with all the added information. Returns instance variable 'mission'
    const QVector<MissionData> getMission() const;

    // Save mission to database. Modifies the database.
    void saveMissionToFile();

    // Clear all the records in the Mission database.
    void clearMissionTable();

////=== FlightPath Commands ===////

    void addFlightPathData(FlightPathData newData);

    const void getFlightPath() const;

    void saveFlightPathToFile();

private:
    QSqlDatabase m_db;                  // database connection
    QVector<MissionData> mission;       // the path the drone SHOULD go.
    QVector<FlightPathData> flightPath; // the path the drone ACTUALLY went.

    // File related variables.
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


    // Functions to be run on initializing.
    void initializeDatabase();
    void createOrLoadMissionTable();
    void createOrLoadFlightPathTable();
};

#endif // DBMANAGER_H
