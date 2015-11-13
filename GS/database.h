#ifndef DATABASE
#define DATABASE

#include <QApplication>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlQuery>
#include <QDebug>

/*
 * Database Documentation:
 *  The database will not run without first installing some outside software and the .pro file for the project
 *  may need to be formatted as well.
 *
 *  MySql Server needs to be downloaded, I am using MySql Server 5.6 and it has to be installed and running
 *  everytime you try to run the ground station with database connectivity. I recommend first downloading and installing
 *  MySqlInstaller, at least for Windows, so that MySql Server can be installed through it and then set as a Windows
 *  Service so that it always starts on computer start up. Hopefully there is a corresponding way to do it with Macs,
 *  etc. but you need MySql Server running in any event.
 *
 *  Then you need to create a database connection on your local version of MySql Server, specifying user name, database
 *  name, and password. The way I did this was to download and install MySql Workbench and set up a connection through
 *  there. For host name use localhost or 127.0.0.1, they mean the same thing though sometimes one or the other gives
 *  people trouble. You don't have to create any database tables on your database, the formatDatabase() function has that
 *  covered. Refer to the createConnection() function in database.cpp to see what the current settings are for
 *  database name, user name, and password and change them to match your connection.
 *
 *  Now if you've gotten this far you can try out the database simply by changing the Database class instantiations in
 *  mainwindow.cpp and mapplanning.cpp from having false as an argument to having no arguments (e.g. Database(false) to
 *  Database()). However, there's no guarantee the database will work as you may need to format the .pro file for the
 *  project. To do this you should find the relevant section on the webpage:
 *
 *  http://doc.qt.io/qt-5/sql-driver.html
 *
 *  and hopefully the directions make enough sense for you to build the QMYSQL driver for your groundstation QT project.
*/

class Database : public QSqlDatabase{
    Q_OBJECT
public:
    Database();
    Database(bool active);//Set active to false if your database isn't set up
    ~Database();

public slots:
    bool activated();
    bool connected();
    bool formatDatabase();
    void newMission(QList<QList<QString>> mission);
    void editMission(int number, QList<QList<QString>> mission);
    void deleteMission(int number);
    QList<QList<QString>> loadMission(int missionNumber);
private:
    bool active;
    QSqlDatabase connection;

private slots:
    bool newEntry(QString missionName, int waypoint, QString behavior, float lat, float lon, QString action);
    bool editEntry(QString missionName, int waypoint, QString behavior, float lat, float lon, QString action);
    bool deleteEntry(QString missionName, int waypoint);
    QSqlDatabase createConnection();
};

#endif // DATABASE
