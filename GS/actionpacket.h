// Copyright (c) 2015:
// Jason Watkins <watkins1@uci.edu>
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
// WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
// ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
// WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
// ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
// OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

#ifndef COORDINATOR_ACTIONPACKET_H
#define COORDINATOR_ACTIONPACKET_H

#include  <string>
#include "packet.h"

namespace Protocol
{
	enum class ActionType : uint8_t
	{
		Start = 0,
		RequestInfo = 1,
		AddWaypoint = 2,
		SetHome = 3,
		RemoveWaypoint = 4,
		Stop = 14,
		Shutdown = 15
	};

    /*Roman Parise (10/10/2016) - had to change
    from "typedef struct { ... } Waypoint;" to
    "struct Waypoint {...}; typedef struct Waypoint Waypoint."

    For some reason, it won't compile on Windows in Qt 5.4.0 otherwise.
    Maybe it's because the MSVC compiler won't recognize it. Who knows.*/

    struct Waypoint {
        double lat = 0;
        double lon = 0;
        float alt = 0;
        float speed = 0;
    };

    typedef struct Waypoint Waypoint;

    class ActionPacket : public Packet
    {
    private:
        ActionType action;
        Waypoint waypoint;

	public:
        ActionPacket() : Packet(PacketType::Action){}

		ActionPacket(uint8_t* buffer, size_t len);

		void SetAction(ActionType a);

		void SetWaypoint(Waypoint wp);

		ActionType GetAction();

		Waypoint GetWaypoint();

		virtual size_t GetBytes(uint8_t* buffer, size_t len);
	};
}

#endif
