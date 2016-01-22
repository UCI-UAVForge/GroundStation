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

#ifndef COORDINATOR_TELEMETRYPACKET_H
#define COORDINATOR_TELEMETRYPACKET_H

#include <string>
#include "Packet.h"

namespace Protocol
{
	class TelemetryPacket : public Packet
	{
	private:
		uint32_t sequenceNumber;
		float vX;
		float vY;
		float vZ;
		float pitch;
		float roll;
		float yaw;
		double lat;
		double lon;
		float alt;
		float heading;

	public:
		TelemetryPacket();

		TelemetryPacket(uint8_t* buffer, size_t len);

		TelemetryPacket(uint32_t seqNo);

		void SetVelocity(float x, float y, float z);

		void SetOrientation(float p, float r, float y);

		void SetLocation(double lat, double lon, float alt);

		void SetLocation(double lat, double lon);

		void SetHeading(float h);

		void GetVelocity(float* x, float* y, float* z);

		void GetOrientation(float* p, float* r, float* y);

		void GetLocation(double* lat, double* lon, float* alt);

		void GetHeading(float* h);

		virtual size_t GetBytes(uint8_t* buffer, size_t len);
	};
}

#endif