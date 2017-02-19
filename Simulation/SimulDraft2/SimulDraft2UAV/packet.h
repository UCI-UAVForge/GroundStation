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

#ifndef COORDINATOR_PACKET_H
#define COORDINATOR_PACKET_H

#include "time.h"
#include "stdio.h"
#include "stdint.h"

namespace Protocol
{
	enum class PacketType : uint8_t
	{
		Ack = 0,
		Telem = 1,
		Action = 2,
		Info = 3
	};

	class Packet
	{
    public:
        uint32_t get_timestamp();
        void set_type(PacketType a);
        PacketType get_type();
        void setTimestamp();
    private:
		PacketType type;


	protected:
        uint32_t timestamp;

		Packet(PacketType t);

		/// Writes information shared by all packets to the given buffer.
		///
		/// \author Jason Watkins
		/// \date 2015-11-16
		///
		/// \param buffer[in] An array to write the header to.
		/// \param len[in]    The length of \p buffer.
		/// \returns          The number of bytes written to buffer.
		size_t WriteHeader(uint8_t* buffer, size_t len);

		/// Reads information shared by all packets from the given buffer.
		///
		/// \author Jason Watkins
		/// \date 2015-11-16
		///
		/// \param buffer[in] An array containing a valid packet
		/// \param len[in]    The length of \p buffer.
		/// \returns          The number of bytes contained in the header.
		size_t ReadHeader(uint8_t* buffer, size_t len);

		/// Sets the checksum bytes at the end of a packet.
		///
		/// \author Jason Watkins
		/// \date 2015-11-16
		///
		/// \param buffer[in] An array to write the header to.
		/// \param len[in]    The length of \p buffer.
		/// \param offset[in] The index of the last byte that should be part of
		///                   the calculated checksum. \p offset should be at
		///                   least two less than \p len to leave room for the
		///                   checksum bytes.
		/// \returns          The end of the packet with the checksum appended.
		size_t SetChecksum(uint8_t* buffer, size_t len, size_t offset);
	public:
		/// Stores the byte representation of a packet in the given buffer.
		///
		/// \author Jason Watkins
		/// \date 2015-11-16
		///
		/// \param buffer[in] An array to write the packet to.
		/// \param len[in]    The length of \p buffer.
		virtual size_t GetBytes(uint8_t* buffer, size_t len) = 0;

		static Packet* Parse(uint8_t* buffer, size_t len);
	};
}

#endif

