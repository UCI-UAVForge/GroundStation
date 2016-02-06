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

#ifndef COORDINATOR_PACKETHANDLER_H
#define COORDINATOR_PACKETHANDLER_H

#include "Arduino.h"
#include "Network.h"
#include "Packet.h"

namespace Protocol
{
	/// Trys to read a packet from the network link.
	///
	/// Reads a UDP packet and parses it into a meaningful Packet understood by
	/// the rest of the Coordinator subsystems.
	///
	/// \author Jason Watkins
	/// \date 2015-11-21
	///
	/// \returns           A pointer to the parsed packet.
	Packet* ReadPacket();

	/// Sends a packet over the network link.
	///
	/// \author Jason Watkins
	/// \date 2015-11-21
	///
	/// \param p[in] A pointer to the packet to send.
	void SendPacket(Packet* p);
	
	/// Dispatches an incomming packet to an appropriate handler.
	///
	/// \author Jason Watkins
	/// \date 2015-11-21
	///
	/// \param p[in] A pointer to the packet to handle.
	void HandlePacket(Packet* packet);

	/// Performs initial actions required to initialize packet handler.
	///
	/// \author Jason Watkins
	/// \date 2015-11-21
	///
	/// \param addr[in] The remote IP address of the ground station.
	/// \param port[in] The local port of the ground station.
	void Setup(IPAddress& addr, uint16_t port);
}

#endif