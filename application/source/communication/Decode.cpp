#include "Decode.h"

QList<uint8_t> Decode::ReadData;
Decode::Decode(QObject *parent) : QObject{parent} {}


status Decode::connectionConfirm(QByteArray responseData) {
    uint8_t lengthResponseData = responseData.size();
    // Check TPKT Version
    if (static_cast<uint8_t>(responseData[0]) != TPKTHeader::TPKT_Version) {
        return status::TPKT_INVALID_VERSION;
    }
    // Check TPKT length
    uint16_t TPKTLength = (static_cast<uint8_t>(responseData[2]) << 8) | static_cast<uint8_t>(responseData[3]);
    if (TPKTLength != lengthResponseData){
        return status::TPKT_INVALID_LENGTH;
    }
    // Check COPT Length
    uint8_t COTPLength = lengthResponseData - sizeof(tpkt) -1;
    if (static_cast<uint8_t>(responseData[4]) != COTPLength){
        return status::COTP_CR_INVALID_LENGTH;
    }
    // Check PDU Type
    if (static_cast<uint8_t>(responseData[5]) != COTPFixedPart::COTP_CC){
        return status::COTP_CC_INVALID_PDU_TYPE;
    }
    return status::CONNECTION_REQEUEST_SUCCESSFULL;
}

status Decode::communicationPLC(QByteArray responseData) {
    uint8_t lengthResponseData = responseData.size();
    // Check TPKT Version
    if (static_cast<uint8_t>(responseData[0]) != TPKTHeader::TPKT_Version) {
        return status::TPKT_INVALID_VERSION;
    }
    // Check TPKT Reversed
    if (static_cast<uint8_t>(responseData[1]) != TPKTHeader::TPKT_Reserved) {
        return status::TPKT_INVALID_RESERVED;
    }
    // Check TPKT Length
    uint16_t TPKTLength = (static_cast<uint8_t>(responseData[2]) << 8) | static_cast<uint8_t>(responseData[3]);
    if (lengthResponseData != TPKTLength) {
        return status::TPKT_INVALID_LENGTH;
    }
    // Check COTP length
    uint8_t COTPLength = sizeof(cotp_s7comm) -1 ;
    if (static_cast<uint8_t>(responseData[sizeof(tpkt)]) != COTPLength){
        return status::COTP_COMMUNICATION_INVALID_LENGTH;
    }
    // Check ROSCTR
    if (static_cast<uint8_t>(responseData[sizeof(tpkt) + sizeof(cotp_s7comm) + 1]) != MessageType::ACK_DATA) {
        return status::S7_HEADER_ERROR_ROSCTR;
    }
    // Check error information
    uint8_t errClassByte = sizeof(tpkt) + sizeof(cotp_s7comm) + sizeof(header_ack_t) -2;
    uint8_t errCodeByte = errClassByte + 1;
    uint8_t functionCodeByte = errCodeByte + 1;
    if (static_cast<uint8_t>(responseData[errClassByte]) == 0x00 && static_cast<uint8_t>(responseData[errCodeByte]) == 0x00){
        // Check function code
        switch (static_cast<uint8_t>(responseData[functionCodeByte])) {
        case FunctionsCode::SetupCommunication:
            return status::SETUP_COMMUNICATION_SUCCESSFUL;
            break;
        case FunctionsCode::WriteVariable:{
            if (static_cast<uint8_t>(responseData[lengthResponseData-1]) != ReturnCode::SUCCESS){
                return status::WRITE_FAILED;
            }
            return status::WRITE_SUCCESSFUL;
            break;
        }

        case FunctionsCode::ReadVariable:
        {
            uint8_t ITEM_COUNT = static_cast<uint8_t>(responseData[functionCodeByte + 1]);
            uint8_t dataByteStart = sizeof(tpkt) + sizeof(cotp_s7comm) + sizeof(header_ack_t) + sizeof(param_comm_ack); // 21
            uint8_t sizeDataPackge = sizeof(DataReadACK);
            for (uint8_t i = 1; i <= ITEM_COUNT; i++){
                // Need write generic
                if (static_cast<uint8_t>(responseData[dataByteStart + (i - 1) * sizeDataPackge]) == ReturnCode::SUCCESS)
                    ReadData.append(static_cast<uint8_t>(responseData[dataByteStart + 4 + (i - 1)*5]));
            }
            // Show data

            return status::READ_SUCCESSFUL;
            break;
        }

        default:
            return status::S7_UNKNOWN_FUNCTION_CODE;
            break;
        }
    }
    else{
        // search in error table
        return status::S7_RETURN_CODE_ERROR;
    }
    return status::S7_DATA_ERROR;
}
