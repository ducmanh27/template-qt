#ifndef TPKTHEADER_H
#define TPKTHEADER_H
#include <stdint.h>
#pragma pack(push, 1)
//
struct tpkt {
    uint8_t version;   // 1 byte
    uint8_t reserved;  // 1 byte
    uint16_t length;   // 2 bytes
};
enum  TPKTHeader {
    TPKT_Version = 0x03,
    TPKT_Reserved = 0x00,
    TPKT_Length_LSB_CR = 0x16,
    TPKT_Length_LSB_SC = 0x16
};
#pragma pack(pop)
#endif // TPKTHEADER_H
