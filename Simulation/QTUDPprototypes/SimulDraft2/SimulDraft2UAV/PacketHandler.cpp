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

#include "PacketHandler.h"

const static size_t BUF_SIZE = 1024;
static uint8_t buffer[BUF_SIZE];

static IPAddress remoteAddr;
static uint16_t remotePort;

Protocol::Packet* Protocol::ReadPacket()
{
	IPAddress sourceAddr;
	uint16_t sourcePort;
	size_t len = Network::Receive(buffer, BUF_SIZE, sourceAddr, sourcePort);
	if (len == 0)
	{
		// No data read
		return nullptr;
	}
	if (sourceAddr != remoteAddr || sourcePort != remotePort)
	{
		// To provide an absolute minimum level of security, reject any data
		// that doesn't come from the expected endpoint
		Serial.println("Warning: Data received from unexpected endpoint.");
		return nullptr;
	}

	return Packet::Parse(buffer, len);
}

void Protocol::SendPacket(Packet* p)
{
	if (p == nullptr)
	{
		Serial.println("Warnign: Attempting to send null packet.");
		return;
	}

	size_t len = p->GetBytes(buffer, BUF_SIZE);
	Network::Send(buffer, len, remoteAddr, remotePort);
}

void Protocol::HandlePacket(Packet* p)
{
	return;
}

void Protocol::Setup(IPAddress& addr, uint16_t port)
{
	remoteAddr = addr;
	remotePort = port;
}