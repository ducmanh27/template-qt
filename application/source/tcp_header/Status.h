#ifndef STATUS_H
#define STATUS_H
#include <cstdint>
enum class status: uint8_t  {
    // Status activity
    CONNECTION_REQEUEST_SUCCESSFULL,
    CONNECTION_REQUEST_ERROR,
    SETUP_COMMUNICATION_SUCCESSFUL,
    SETUP_COMMUNICATION_ACK_ERROR,
    WRITE_SUCCESSFUL,
    WRITE_FAILED,
    READ_SUCCESSFUL,
    READ_FAILED,
    // Status TPKT data
    TPKT_INVALID_VERSION,
    TPKT_INVALID_RESERVED,
    TPKT_INVALID_LENGTH,
    // Status COTP data
    COTP_CR_INVALID_LENGTH,
    COTP_CC_INVALID_PDU_TYPE,
    COTP_INVALID_VALUE,
    COTP_COMMUNICATION_INVALID_LENGTH,
    // Status S7 Communication data
    S7_HEADER_ERROR_ROSCTR,
    S7_DATA_ERROR,
    S7_PARAM_INVALID_LENGTH,
    S7_UNKNOWN_FUNCTION_CODE,
    S7_PARAM_SETUP_INVALID,
    S7_WRITE_BYTE_FAILED,
    S7_RETURN_CODE_ERROR,

};
#endif // STATUS_H
