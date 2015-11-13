#include "database.h"

//Refer to the documentation at the top of database.h for instructions on how to set up a working database connection

Database::Database()
{
    active = true;
    connection = createConnection();
}

Database::Database(bool active)
{
    this->active = active;
    if(active)
    {
       connection = createConnection();
    }
}

Database::~Database()
{
    connection.close();
}

bool Database::activated()
{
    return active;
}

bool Database::connected()
{
    if (!connection.open()) {
        return false;
    }
    return true;
}

bool Database::formatDatabase()
{
    QSqlQuery query = QSqlQuery::QSqlQuery(connection);
    return query.exec("CREATE TABLE Missions(ID int, Completed bool, Primary Key(ID))");
}

void Database::newMission(QList<QList<QString>> mission)
{
    int missionNumber = 1;
    QSqlQuery query = QSqlQuery::QSqlQuery(connection);
    query.exec("SELECT ID FROM Missions");

    if(connection.driver()->hasFeature(QSqlDriver::QuerySize))
    {
        missionNumber = query.size() + 1;
    }

    else
    {
        while(query.next())
        {
            missionNumber++;
        }
    }

    query.prepare("INSERT INTO Missions (ID, Completed)" "VALUES(:id, :completed)");
    query.bindValue(":id", missionNumber);
    query.bindValue(":completed", false);
    query.exec();

    QList<int> errorList;
    QString missionName;
    missionName.setNum(missionNumber);
    missionName = "Mission" + missionName;
    QString query_string = "CREATE TABLE " + missionName + " (Waypoint int, Behavior varchar(20), Latitude float, Longitude float, Action varchar(20), Primary Key(Waypoint))";
    if(query.exec(query_string))
    {
        for(int i = 0; i < mission.size(); i++)
        {
            float lon = mission[i][1].toFloat();
            float lat = mission[i][3].toFloat();
            if(mission[i][2] == "W")
            {
                lon *= -1;
            }
            if(mission[i][4] == "S")
            {
                lat *= -1;
            }

            if(!Database::newEntry(missionName, i+1, mission[i][0], lat, lon, mission[i][5]))
            {
                errorList.append(i);
            }
        }
    }
    else
    {

    }

    if (errorList.size() != 0)
    {

    }
    else
    {

    }
}

void Database::editMission(int missionNumber, QList<QList<QString>> mission)
{
    QSqlQuery query = QSqlQuery::QSqlQuery(connection);
    QString missionName;
    missionName.setNum(missionNumber);
    missionName = "Mission" + missionName;
    query.exec("SELECT * FROM " + missionName);

    for(int i = 0; i < mission.size(); i++)
    {
        if(query.next())
        {
            float lon = mission[i][1].toFloat();
            float lat = mission[i][3].toFloat();
            if(mission[i][2] == "W")
            {
                lon *= -1;
            }
            if(mission[i][4] == "S")
            {
                lat *= -1;
            }

            Database::editEntry(missionName, i+1, mission[i][0], lat, lon, mission[i][5]);
        }
        else
        {
            Database::newEntry(missionName, i+1, mission[i][0], lat, lon, mission[i][5]);
        }
    }

    int i = mission.size();
    while(query.next()){
        Database::deleteEntry(missionName, i++);
    }
}

void Database::deleteMission(int missionNumber)
{
    QSqlQuery query = QSqlQuery::QSqlQuery(connection);
    QString missionName;
    QString s_missionNum;
    s_missionNum.setNum(missionNumber);
    missionName = "Mission" + s_missionNum;

    query.exec("DROP TABLE " + missionName);
    query.exec("DELETE FROM Missions where ID = " + s_missionNum);
}

QList<QList<QString>> Database::loadMission(int missionNumber)
{
    int NUM_PARAMS = 5;
    QList<QList<QString>> fullMission;
    QSqlQuery query = QSqlQuery::QSqlQuery(connection);
    QString missionName;
    missionName.setNum(missionNumber);
    missionName = "Mission" + missionName;

    query.exec("SELECT * FROM " + missionName);

    QString direction;
    while(query.next())
    {
        QList<QString> missionLeg;
        for(int i = 0; i < NUM_PARAMS; i++)
        {
            if(i == 0)
            {

            }
            else
            {
                missionLeg.append(query.value(i).toString());
                if(i == 2)
                {
                    if(query.value(i) < 0)
                    {
                        direction = "W";
                        missionLeg.append(direction);
                    }
                    else
                    {
                        direction = "E";
                        missionLeg.append(direction);
                    }
                }
                else if(i == 3)
                {
                    if(query.value(i) < 0)
                    {
                        direction = "S";
                        missionLeg.append(direction);
                    }
                    else
                    {
                        direction = "N";
                        missionLeg.append(direction);
                    }
                }
             }
        }
        fullMission.append(missionLeg);
    }

    return fullMission;
}

bool Database::newEntry(QString missionName, int waypoint, QString behavior, float lat, float lon, QString action)
{
    QSqlQuery query = QSqlQuery::QSqlQuery(connection);
    query.prepare("INSERT INTO " + missionName + " (Waypoint, Behavior, Latitude, Longitude, Action)" "VALUES (:Waypoint, :Behavior, :Lat, :Lon, :Action)");
    query.bindValue(":Waypoint", waypoint);
    query.bindValue(":Behavior", behavior);
    query.bindValue(":Lat", lat);
    query.bindValue(":Lon", lon);
    query.bindValue(":Action", action);

    return query.exec();
}

bool Database::editEntry(QString missionName, int waypoint, QString behavior, float lat, float lon, QString action)
{
    QString s_waypoint;
    s_waypoint.setNum(waypoint);
    QSqlQuery query = QSqlQuery::QSqlQuery(connection);
    return query.exec("UPDATE " + missionName + " SET Behavior = " + behavior + ", Latitude = " + lat + ", Longitude = " + lon + ", Action = " + action + " WHERE Waypoint = " + s_waypoint);
}

bool Database::deleteEntry(QString missionName, int waypoint)
{
    QString s_waypoint;
    s_waypoint.setNum(waypoint);
    QSqlQuery query = QSqlQuery::QSqlQuery(connection);
    return query.exec("DELETE FROM " + missionName + " WHERE Waypoint = " + s_waypoint);
}

QSqlDatabase Database::createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("uavdatabase");
    db.setUserName("root");
    db.setPassword("uavforge");
    return db;
}

