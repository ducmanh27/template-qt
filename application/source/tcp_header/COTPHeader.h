#ifndef COTPHEADER_H
#define COTPHEADER_H
#include <iostream>
#include <optional>
#pragma pack(push, 1)

struct cotp_connection{
    uint8_t li;
    uint8_t type;
    uint16_t desref;
    uint16_t srcref;
    uint8_t Class;
    uint8_t parameter_code_tpdu;
    uint8_t parameter_length_tpdu;
    uint8_t tpdu_size;
    uint8_t parameter_code_src;
    uint8_t parameter_length_src;
    uint16_t src_tsap_bytes;
    uint8_t parameter_code_dst;
    uint8_t parameter_length_dst;
    uint16_t dst_tsap_bytes;
};

struct cotp_s7comm{
    uint8_t li;
    uint8_t type;
    uint8_t tpdu_number;
};
enum COTPFixedPart: uint16_t {
    COTP_LI = 0x11,
    COTP_CR = 0xe0,
    COTP_CC = 0xd0,
    COTP_CLASS = 0x00
};
enum COTPFixedPartBytes: uint16_t{
    COTP_DST = 0x0000,
    COTP_SRC = 0x0001,
};

enum  COTPVariablePart: uint8_t {
    TPDU_Size_Code = 0xc0,
    TPDU_Size_Length = 0x01,
    TPDU_Size_Value_512 = 0x09,
    TPDU_Size_Value_1024 = 0x0a,

    TSAP_Src_Code = 0xc1,
    TSAP_Src_Length = 0x02,
    TSAP_Src_Device_Group = 0x01, // PG/PC
    TSAP_Src_ID = 0x00,

    TSAP_Dst_Length = 0x02,
    TSAP_Param_Length_Dst = 0x02,
    TSAP_Dst_Device_Group_OP = 0x02,
    TSAP_Dst_Device_Group_Other = 0x03,
    TSAP_Dst_ID_S71200 = 0x01,

    TSAP_Dst = 0xc2};
enum COTPVariablePartBytes : uint16_t{
    TSAP_Bytes = 0x0100,
    TSAP_Dst_Byte = 0x0301,
};

enum DataTransferHeader: uint8_t{
    LI = 0x02,
    PDU_Type = 0xf0,
    TPDU_number = 0x80
};

enum class S7CommunicationHeader:uint8_t{
    ProtocolID = 0x32,
    Reserved = 0x0000

};
#pragma pack(pop)
#endif // COTPHEADER_H
