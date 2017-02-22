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

#include "actionpacket.h"

Protocol::ActionPacket::ActionPacket(uint8_t* buffer, size_t len) : ActionPacket()
{
	size_t offset = this->ReadHeader(buffer, len);
    Protocol::Packet::set_type(Protocol::PacketType::Action);

	this->action = *((ActionType*)(buffer + offset));
	this->waypoint.lat = *((double*)(buffer + offset + 1));
	this->waypoint.lon = *((double*)(buffer + offset + 9));
	this->waypoint.alt = *((float*)(buffer + offset + 17));
	this->waypoint.speed = *((float*)(buffer + offset + 21));
}

void Protocol::ActionPacket::SetAction(Protocol::ActionType a)
{
	this->action = a;
}

void Protocol::ActionPacket::SetWaypoint(Waypoint wp)
{
	this->waypoint = wp;
}

Protocol::ActionType Protocol::ActionPacket::GetAction()
{
	return this->action;
}

Protocol::Waypoint Protocol::ActionPacket::GetWaypoint()
{
	return this->waypoint;
}

size_t Protocol::ActionPacket::GetBytes(uint8_t* buffer, size_t len)
{
	size_t offset = this->WriteHeader(buffer, len);

	*(buffer + offset) = (uint8_t)this->action;
	*((double*)(buffer + offset + 1)) = this->waypoint.lat;
	*((double*)(buffer + offset + 9)) = this->waypoint.lon;
	*((float*)(buffer + offset + 17)) = this->waypoint.alt;
	*((float*)(buffer + offset + 21)) = this->waypoint.speed;
	offset += 25;

	return this->SetChecksum(buffer, len, offset);
}
