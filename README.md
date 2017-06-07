UCI-SoftwareDev
===============
Spring Quarter updates:
UCI-UAVForge Software Development Team Repository 

Current state of MAVLink test:

The main.cpp file in this fork essentially just starts up GsServer. Run the simulator simultaneously
so that you can test communication between a UAV and the Ground Station (GS).

Currently, the GS is able to receive MAVLink telemetry packets (GLOBAL_POSITION_INT #33) and understands that they are telemetry packets.
More specifically, the UAV sends a telemetry packet whose message id is 33, and the GS reads the same message id (33)
when it receives the packet. The issue is that the GS interprets the telemetry packet as a MISSION_CLEAR_ALL packet (45) and parses it as such.