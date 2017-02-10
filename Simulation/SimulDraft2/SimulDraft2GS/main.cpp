#include <QCoreApplication>
#include <QTextStream>
#include <QString>


#include <groundstation.h>

//#include "Messagebox.h"

#include <vector>
#include <queue>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //QTextStream(stdout) << "run this";

    GroundStation station;

//    messagebox mb;
//    mb.load_action_packet(1,2,3,4);
//    mb.load_action_packet(5,6,7,8);
//    mb.load_action_packet(9,10,11,12);

//    std::vector<Protocol::ActionPacket> actionPacket = mb.get_action_packets();
    std::queue<Protocol::Packet*> packets_to_send;

//    for (auto& action : actionPacket)
//        packets_to_send.push(&action);

//    Protocol::InfoPacket info;
//    info.SetBattery(150);
//    info.SetOther("Im");
//    info.SetStorable(300);
//    packets_to_send.push(&info);

    Protocol::ActionPacket initialInfoReq;
    initialInfoReq.SetAction(Protocol::ActionType::RequestInfo);
    packets_to_send.push(&initialInfoReq);
//    Protocol::AckPacket ack;
//    packets_to_send.push(&ack);
//    station.sendAllActionPackets(actionPacket);
//    Protocol::TelemetryPacket tel;
//    tel.SetVelocity(1,2,3);
//    tel.SetOrientation(4,5,6);
//    tel.SetLocation(7,8,9);
//    tel.SetHeading(10);
//    packets_to_send.push(&tel);
    Protocol::ActionPacket waypoint1, waypoint2;
    waypoint1.SetAction(Protocol::ActionType::AddWaypoint);
    Protocol::Waypoint wp;
    wp.lon = -117;
    wp.lat = 33.6;
    waypoint1.SetWaypoint(wp);
    packets_to_send.push(&waypoint1);

    wp.lon = -115;
    wp.lat = 37;
    waypoint2.SetAction(Protocol::ActionType::AddWaypoint);
    waypoint2.SetWaypoint(wp);
    packets_to_send.push(&waypoint2);

    Protocol::ActionPacket start;
    start.SetAction(Protocol::ActionType::Start);

    packets_to_send.push(&start);
    station.sendAllPackets(packets_to_send);

//    return 0;
   return a.exec();
}


