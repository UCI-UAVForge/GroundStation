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

#ifndef COORDINATOR_ACKPACKET_H
#define COORDINATOR_ACKPACKET_H

#include "stdio.h"
#include "Packet.h"

namespace Protocol
{
	class AckPacket : public Packet
	{
	public:
		AckPacket() : Packet(PacketType::Ack) {}

		AckPacket(uint8_t* buffer, size_t len) : Packet(PacketType::Ack)
		{
			this->ReadHeader(buffer, len);
		}

		size_t GetBytes(uint8_t* buffer, size_t len)
		{
			size_t offset = this->WriteHeader(buffer, len);
			return this->SetChecksum(buffer, len, offset);
		}
	};
}

#endif