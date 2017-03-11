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

#ifndef COORDINATOR_INFOPACKET_H
#define COORDINATOR_INFOPACKET_H

#include <string>
#include "string.h"
#include "stdint.h"
#include "packet.h"

namespace Protocol
{
	class InfoPacket : public Packet
	{
	private:
		uint16_t pointsStorable;
		uint16_t batteryState;
		std::string other;

	public:
		InfoPacket() : Packet(PacketType::Info) {}

		InfoPacket(uint8_t* buffer, size_t len);

		void SetStorable(uint16_t s);

		void SetBattery(uint16_t b);

		void SetOther(std::string s);

		uint16_t GetStorable();

		uint16_t GetBattery();

		std::string GetOther();

		virtual size_t GetBytes(uint8_t* buffer, size_t len);
	};
}

#endif
