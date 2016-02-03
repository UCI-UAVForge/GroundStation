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

#include <QDateTime>

#include "Packet.h"
#include "AckPacket.h"
#include "ActionPacket.h"
#include "InfoPacket.h"
#include "TelemetryPacket.h"
#include "stdint.h"

// Statically allocate space for one of each type of packet for use with
// Packet::Parse.
static Protocol::AckPacket ack;
static Protocol::ActionPacket action;
static Protocol::InfoPacket info;
static Protocol::TelemetryPacket telem;

Protocol::Packet::Packet(Protocol::PacketType t)
{
    //@TODO: Need to create timestamp from creation of program or messaage box
    //this->timestamp = millis();
	this->type = t;
}

size_t Protocol::Packet::WriteHeader(uint8_t* buffer, size_t len)
{

	*(buffer) = (uint8_t)this->type;
	*((uint32_t*)(buffer + 1)) = this->timestamp;

	return 5;
}

size_t Protocol::Packet::ReadHeader(uint8_t* buffer, size_t len)
{
	// Note: Type will be set by the subtype constructor before calling this method
	this->timestamp = *((uint32_t*)(buffer + 1));

	return 5;
}

uint32_t Protocol::Packet::get_timestamp(){
    return this->timestamp;
}
void Protocol::Packet::set_type(Protocol::PacketType a){
    this->type = a;
}

Protocol::PacketType Protocol::Packet::get_type(){
    return this->type;
}

size_t Protocol::Packet::SetChecksum(uint8_t* buffer, size_t len, size_t offset)
{
	// Appends a Fletcher-16 checksum to the specified packet. See
	// http://en.wikipedia.org/wiki/Fletcher%27s_checksum for more information.
	// The checksum is appended in check-byte format. i.e. recalculating the
	// checksum over the entire packet will yield 0 for both sums.
	if (len - offset < 2)
	{
        fprintf(stderr, "ERROR: Unable to append checksum.");
	}

	uint16_t sum1 = 0;
	uint16_t sum2 = 0;
	uint8_t* ptr = buffer;
	for (size_t i = offset; i > 0; --i)
	{
		sum1 = (sum1 + *ptr++) % 255;
		sum2 = (sum2 + sum1) % 255;
	}
	uint8_t check1 = 255 - ((sum1 + sum2) % 255);
	uint8_t check2 = 255 - ((sum1 + check1) % 255);
	buffer[offset] = check1;
	buffer[offset + 1] = check2;
	return offset + 2;
}

// Checks that the Fletcher-16 checksum of a packet is 0.
bool ValidateChecksum(const uint8_t* data, size_t len)
{
	uint16_t sum1 = 0;
	uint16_t sum2 = 0;
	while (len--)
	{
		sum1 = (sum1 + *data++) % 255;
		sum2 = (sum2 + sum1) % 255;
	}
	return sum1 == 0 && sum2 == 0;
}

Protocol::Packet* Protocol::Packet::Parse(uint8_t* buffer, size_t len)
{
	if (len < 1)
	{
        fprintf(stderr, "ERROR: Packet length must be greater than 0.");
		return nullptr;
	}
    if (!ValidateChecksum(buffer, len))
    {
        fprintf(stderr, "Warning: Packet Checksum failed.");
        return nullptr;
    }

	PacketType type = (PacketType)buffer[0];
	switch (type)
	{
	case PacketType::Ack:
		ack = AckPacket(buffer, len);
		return &ack;
	case PacketType::Action:
		action = ActionPacket(buffer, len);
		return &action;
	case PacketType::Telem:
		telem = TelemetryPacket(buffer, len);
		return &telem;
	case PacketType::Info:
		info = InfoPacket(buffer, len);
		return &info;
	default:
        fprintf(stderr, "Warning: Unknown packet type.");
		return nullptr;
	}
}
