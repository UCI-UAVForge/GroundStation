/**
 * Class: DBManager
 * Date: Feb 24, 2017
 * Author: Aung(David) Moe
 * Description: Database system for logging system information to/from the drones for the UAVF project.
 * Required: Add 'QT += sql' to 'UAV-Forge-New.pro' file.
 */

/*

Example using the class:

int main()
{
    DbManager db("DbFile");   // Creates or opens a file ./DbFile.db.
    if (db.isOpen())
    {
        // Clear any previously loaded values.
        db.clearAll();

        // Mission data.
        MissionData missionData; // Each mission data represents one point.
        missionData.lon = 1.5;
        missionData.lat = 2.5;

        // Save 1
        db.missionAdd(missionData);
        db.missionSaveToFile();

        // Save 2
        db.missionAdd({});
        db.missionAdd({4,1,1,1,1,1,1,1,1,1});
        db.missionSaveToFile();

        // FlightPath data.
        FlightPathData flightPathData;
        flightPathData.actionNum = 2;
        flightPathData.delay = 4;
        flightPathData.data = {10,11,12};

        // Save 1
        db.flightPathAdd(flightPathData);
        db.flightPathSaveToFile();

        // Save 2
        db.flightPathAdd({});
        db.flightPathAdd({5,10, {13,14,15}});
        db.flightPathSaveToFile();
    }
    return 0;
}
*/

#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QString>
#include <QSqlDatabase>
#include <QVector>

const unsigned int kDataSize = 40;

// One 'Mission' data represents an actual location point on the map.
struct MissionData {
    float heading;
    double lat;
    double lon;
    float alt;
    float pitch;
    float roll;
    float yaw;
    float xvel;
    float yvel;
    float zvel;

    MissionData(float heading = 0, double lat = 0, double lon = 0, float alt = 0, float pitch = 0, float roll = 0, float yaw = 0, float xvel = 0, float yvel = 0, float zvel = 0)
    {
        this->heading = heading;
        this->lat = lat;
        this->lon = lon;
        this->alt = alt;
        this->pitch = pitch;
        this->roll = roll;
        this->yaw = yaw;
        this->xvel = xvel;
        this->yvel = yvel;
        this->zvel = zvel;
    }
};

// One 'FlightPath' data represents a theorectical location point on the map.
struct FlightPathData {
    unsigned int actionNum;
    double delay;
    QVector<unsigned char> data;

    FlightPathData(unsigned int actionNum = 0, double delay = 0, QVector<unsigned char> data = {})
    {
        this->actionNum = actionNum;
        this->delay = delay;
        this->data = data;
    }
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

    // Clear all data stored in variables.
    void clearAll();

    // Clear all data stored in database.
    void clearAllFiles();

    // Returns true if a database is connected.
    bool isOpen() const;

    // Opens and loads from database file 'directory/filename'. Automatically called by the constructor.
    bool open(const QString& fileName, const QString& directory = "");

    // Close current database connection.
    void close();

    // Convert vector into array.
    static unsigned char* toArray(QVector<unsigned char> vector);

    // Convert array of 'size' into vector.
    static QVector<unsigned char> toVector(unsigned char* array, size_t size);

////=== Mission Commands ===////

    // Inserts into the variable 'mission'. Does not modify the database.
    void missionAdd(MissionData newData);

    // Returns the variable 'mission'. May not be the same information from database if it was changed.
    const QVector<MissionData> missionGet() const;

    // Clears the variable 'mission'.
    void missionClear();

    // Save mission to database. Modifies the database.
    void missionSaveToFile();

    // Clears the Mission database.
    void missionClearFile();

////=== FlightPath Commands ===////

    void flightPathAdd(FlightPathData newData);

    const QVector<FlightPathData> flightPathGet() const;

    void flightPathClear();

    void flightPathSaveToFile();

    void flightPathClearFile();

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
    void initializeDatabaseSettings();
    void createOrLoadMissionTable();
    void createOrLoadFlightPathTable();
};

#endif // DBMANAGER_H
