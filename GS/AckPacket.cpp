#include "AckPacket.h"

Protocol::AckPacket::AckPacket(uint8_t* buffer, size_t len) : AckPacket()
{
    Protocol::Packet::set_type(Protocol::PacketType::Ack);
    this->ReadHeader(buffer, len);
}

void Protocol::AckPacket::set_timestamp(unsigned long time) {
    this->timestamp = time;
}

size_t Protocol::AckPacket::GetBytes(uint8_t* buffer, size_t len) {
    size_t offset = this->WriteHeader(buffer, len);
    return this->SetChecksum(buffer, len, offset);
}
