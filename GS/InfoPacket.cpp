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

#include "InfoPacket.h"

Protocol::InfoPacket::InfoPacket(uint8_t* buffer, size_t len) : InfoPacket()
{
	size_t offset = this->ReadHeader(buffer, len);

	this->pointsStorable = *((uint16_t*)(buffer + offset));
	this->batteryState = *((uint16_t*)(buffer + offset + 2));
	uint16_t otherLen = *((uint16_t*)(buffer + offset + 4));
	char* otherBytes = new char[otherLen + 1];
	strncpy(otherBytes, (char*)(buffer + 6), otherLen);
    this->other = std::string((char*)otherBytes);
}

void Protocol::InfoPacket::SetStorable(uint16_t s)
{
	this->pointsStorable = s;
}

void Protocol::InfoPacket::SetBattery(uint16_t b)
{
	this->batteryState = b;
}

void Protocol::InfoPacket::SetOther(std::string s)
{
	this->other = s;
}

uint16_t Protocol::InfoPacket::GetStorable()
{
	return this->pointsStorable;
}

uint16_t Protocol::InfoPacket::GetBattery()
{
	return this->batteryState;
}

std::string Protocol::InfoPacket::GetOther()
{
	return this->other;
}

size_t Protocol::InfoPacket::GetBytes(uint8_t* buffer, size_t len)
{
	size_t offset = this->WriteHeader(buffer, len);

	*((uint16_t*)(buffer + offset)) = this->pointsStorable;
	*((uint16_t*)(buffer + offset + 2)) = this->batteryState;
	*((uint16_t*)(buffer + offset + 4)) = (uint16_t)this->other.length();
    //@TODO: Figure out what to do with this
//	this->other.getBytes(buffer + 6, len, offset + 6);
	offset += 6;

	return this->SetChecksum(buffer, len, offset);
}
