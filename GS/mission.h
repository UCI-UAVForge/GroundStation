#ifndef MISSION_H
#define MISSION_H

#include <QString>
#include <QVector>
#include <QPair>
#include <QMap>
#include "actionpacket.h"
#include "telemetrypacket.h"
#include "flightpath.h"
#include "messagebox.h"

class Mission {
public:
    Mission();

    Mission(QString filename);

    Mission(FlightPath flightPath);

    ~Mission();

    /** @brief Extracts data from an input Packet and stores the values in
     * the values field.
     *  @param telemPacket A pointer to the packet that will be read.
     *  @date April 8, 2016
     */
    void addPacket(Protocol::TelemetryPacket telemPacket);


    FlightPath *getFlightPath();

    QVector<double> *getValuesForID(int id);
    QVector<double> *getValuesForIndex(int index);
    double getValueForIndexAndID(int index,int id);

    bool save(QString filename);
    int numOfEntries();

private:
    void initValues();
    FlightPath myFlightPath;

    QVector<QVector<double>* > values;
};

#endif // MISSION_H
