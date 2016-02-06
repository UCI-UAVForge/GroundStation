#include <QCoreApplication>
#include <QTextStream>
#include <QString>


#include <groundstation.h>

#include "Messagebox.h"

#include <vector>
#include <queue>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTextStream(stdout) << "run this";



    GroundStation station;

    messagebox mb; 
    mb.load_action_packet(1,2,3,4);
    mb.load_action_packet(5,6,7,8);
    mb.load_action_packet(9,10,11,12);

    std::vector<Protocol::ActionPacket> actionPacket = mb.get_action_packets();
    std::queue<Protocol::Packet*> packets_to_send;

    for (auto& action : actionPacket)
        packets_to_send.push(&action);

    station.sendAllPackets(packets_to_send);
//    station.sendAllActionPackets(actionPacket);


//    return 0;
   return a.exec();
}


