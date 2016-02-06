// Copyright (c) 2015:
// Jason Watkins <watkins1@uci.edu>
// Harit Desai <hmdesai@uci.edu>
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

#include <iostream>
#include "TelemetryPacket.h"

Protocol::TelemetryPacket::TelemetryPacket() : Packet(PacketType::Telem)
{
    Protocol::Packet::set_type(Protocol::PacketType::Telem);
	static uint32_t sequence = 0;
	this->sequenceNumber = ++sequence;
}

Protocol::TelemetryPacket::TelemetryPacket(uint32_t seqNo) : Packet(PacketType::Telem)
{
	this->sequenceNumber = seqNo;
}

Protocol::TelemetryPacket::TelemetryPacket(uint8_t* buffer, size_t len)
	: Packet(PacketType::Telem)
{

}

void Protocol::TelemetryPacket::SetVelocity(float x, float y, float z)
{
	this->vX = x;
	this->vY = y;
	this->vZ = z;
}

void Protocol::TelemetryPacket::SetOrientation(float p, float r, float y)
{
	this->pitch = p;
	this->roll = r;
	this->yaw = y;
}

void Protocol::TelemetryPacket::SetLocation(double lat, double lon, float alt)
{
	this->lat = lat;
	this->lon = lon;
	this->alt = alt;
}

void Protocol::TelemetryPacket::SetLocation(double lat, double lon)
{
	this->lat = lat;
	this->lon = lon;
}

void Protocol::TelemetryPacket::SetHeading(float h)
{
	this->heading = h;
}

void Protocol::TelemetryPacket::GetVelocity(float* x, float* y, float* z)
{
	*x = this->vX;
	*y = this->vY;
	*z = this->vZ;
}

void Protocol::TelemetryPacket::GetOrientation(float* p, float* r, float* y)
{
	*p = this->pitch;
	*r = this->roll;
	*y = this->yaw;
}

void Protocol::TelemetryPacket::GetLocation(double* lat, double* lon, float* alt)
{
	*lat = this->lat;
	*lon = this->lon;
	*alt = this->alt;
}

void Protocol::TelemetryPacket::GetHeading(float* h)
{
	*h = this->heading;
}

size_t Protocol::TelemetryPacket::GetBytes(uint8_t* buffer, size_t len)
{
	if (len < sizeof(*this))
	{
		//randomly replaced with cout because i dont know what to do with this on the GS
		std::cout << "ERROR: Unable to serialize telemetry packet.";
		return 0;
	}

	size_t offset = this->WriteHeader(buffer, len);

	*((float*)(buffer + offset)) = this->vX;
	*((float*)(buffer + offset + 4)) = this->vY;
	*((float*)(buffer + offset + 8)) = this->vZ;
	*((float*)(buffer + offset + 12)) = this->pitch;
	*((float*)(buffer + offset + 16)) = this->roll;
	*((float*)(buffer + offset + 20)) = this->yaw;
	*((double*)(buffer + offset + 24)) = this->lat;
	*((double*)(buffer + offset + 32)) = this->lon;
	*((float*)(buffer + offset + 40)) = this->alt;
	*((float*)(buffer + offset + 44)) = this->heading;
	offset += 48;

	return this->SetChecksum(buffer, len, offset);
}
