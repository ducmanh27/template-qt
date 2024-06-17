#include "encode.h"

uint16_t Encode::pduRef = 0;
QMap<syntax_id, uint8_t> Encode::syntaxID_Table = {
    {S7_ANY, 0x10},
    {R_ID, 0x13},
    {AlarmMessage, 0x16},
    {AlarmAcknowledgeMessage, 0x19},
    {SinumerikNCKHMIAccess, 0x82},
    {DriveES_Any, 0xa2},
    {SymbolicAddressingMode, 0xb2},
    {SpecialDB_Adressing, 0xb0}
};

QMap<area, uint8_t> Encode::areaTable{
                                      {DB, 0x84},
                                      {Counter, 0x1c},
                                      {Timer, 0x1d},
                                      {P, 0x80},
                                      {I, 0x81},
                                      {O, 0x82},
                                      {M, 0x83},
                                      };
Encode::Encode(QObject *parent) : QObject{parent} {}

std::pair<std::unique_ptr<uint8_t[]>, uint8_t> Encode::connectionRequestData() {
    // TPKT Header
    tpkt TPKTConnection;
    TPKTConnection.version = TPKTHeader::TPKT_Version;
    TPKTConnection.reserved = TPKTHeader::TPKT_Reserved;
    // Big edian need to reverse byte
    TPKTConnection.length = ((sizeof(cotp_connection) + sizeof(tpkt)) >> 8) | ((sizeof(cotp_connection) + sizeof(tpkt)) << 8);
    // Fixed part
    cotp_connection COTPConnection;
    COTPConnection.li = COTPFixedPart::COTP_LI;
    COTPConnection.type = COTPFixedPart::COTP_CR;
    COTPConnection.desref = (COTPFixedPartBytes::COTP_DST >> 8) | (COTPFixedPartBytes::COTP_DST << 8); // 2
    COTPConnection.srcref = (COTPFixedPartBytes::COTP_SRC >> 8) | (COTPFixedPartBytes::COTP_SRC << 8); // 2
    COTPConnection.Class = COTPFixedPart::COTP_CLASS;
    COTPConnection.parameter_code_tpdu = COTPVariablePart::TPDU_Size_Code;
    COTPConnection.parameter_length_tpdu = COTPVariablePart::TPDU_Size_Length;
    COTPConnection.tpdu_size = COTPVariablePart::TPDU_Size_Value_512;
    COTPConnection.parameter_code_src = COTPVariablePart::TSAP_Src_Code;
    COTPConnection.parameter_length_src = COTPVariablePart::TSAP_Src_Length;
    COTPConnection.src_tsap_bytes = static_cast<uint16_t>((COTPVariablePartBytes::TSAP_Bytes >> 8) | (COTPVariablePartBytes::TSAP_Bytes << 8));
    COTPConnection.parameter_code_dst = COTPVariablePart::TSAP_Dst;
    COTPConnection.parameter_length_dst = COTPVariablePart::TSAP_Param_Length_Dst;
    COTPConnection.dst_tsap_bytes = static_cast<uint16_t>((COTPVariablePartBytes::TSAP_Dst_Byte >> 8) | (COTPVariablePartBytes::TSAP_Dst_Byte << 8)) ;

    std::unique_ptr<uint8_t[]> packedData(new uint8_t[sizeof(TPKTConnection) + sizeof(COTPConnection)]);
    std::memcpy(packedData.get(), &TPKTConnection, sizeof(TPKTConnection));
    std::memcpy(packedData.get() + sizeof(TPKTConnection), &COTPConnection, sizeof(COTPConnection));

    uint8_t length = sizeof(TPKTConnection) + sizeof(COTPConnection);
    return std::make_pair(std::move(packedData), length);
}

std::pair<std::unique_ptr<uint8_t[]>, uint8_t> Encode::setupCommunicationData() {
    // TPKT Header
    tpkt TPKTSetup;
    TPKTSetup.version = TPKTHeader::TPKT_Version;
    TPKTSetup.reserved = TPKTHeader::TPKT_Reserved;
    uint16_t t_length = sizeof(s7comm_setup) + sizeof(cotp_s7comm) + sizeof(tpkt);
    TPKTSetup.length = (t_length >> 8) | (t_length << 8);
    // Data transfer
    cotp_s7comm DataTransfer;
    DataTransfer.li = DataTransferHeader::LI;
    DataTransfer.type = DataTransferHeader::PDU_Type;
    DataTransfer.tpdu_number = DataTransferHeader::TPDU_number;
    // S7 commnunication parameter in setup communication
    s7comm_setup S7Communication;
    S7Communication.param.func = FunctionsCode::SetupCommunication;
    S7Communication.param.reserved = S7ParamsValueReserverd::Reserved_Param;
    S7Communication.param.maxamq_calling = S7ParamsValue::MaxAmQ_Calling >> 8 | S7ParamsValue::MaxAmQ_Calling << 8;
    S7Communication.param.maxamq_called = S7ParamsValue::MaxAmQ_Called >> 8 | S7ParamsValue::MaxAmQ_Called << 8;
    S7Communication.param.pdu_length = static_cast<uint16_t>((S7ParamsValue::PDU_Length >> 8) | (S7ParamsValue::PDU_Length << 8));
    // S7 communication header
    S7Communication.header.protocolId = 0x32;
    S7Communication.header.ROSCTR = MessageType::JOB;
    S7Communication.header.redId = S7HeaderValue::Reserved >> 8 | S7HeaderValue::Reserved << 8 ;
    S7Communication.header.pduRef = Encode::pduRef >> 8 | Encode::pduRef << 8;
    Encode::pduRef++;
    S7Communication.header.parLg = sizeof(S7Communication.param) >> 8 | sizeof(S7Communication.param) << 8;
    S7Communication.header.datLg = 0x0000;

    std::unique_ptr<uint8_t[]> packedData(new uint8_t[sizeof(tpkt) + sizeof(cotp_s7comm) + sizeof(s7comm_setup)]);
    std::memcpy(packedData.get(), &TPKTSetup, sizeof(TPKTSetup));
    std::memcpy(packedData.get() + sizeof(TPKTSetup), &DataTransfer, sizeof(DataTransfer));
    std::memcpy(packedData.get() + sizeof(TPKTSetup) + sizeof(DataTransfer), &S7Communication.header, sizeof(S7Communication.header));
    std::memcpy(packedData.get() + sizeof(TPKTSetup) + sizeof(DataTransfer) + sizeof(S7Communication.header), &S7Communication.param, sizeof(S7Communication.param));
    uint8_t length = sizeof(TPKTSetup) + sizeof(DataTransfer) + sizeof(S7Communication.header) + + sizeof(S7Communication.param);
    return std::make_pair(std::move(packedData), length);
}

std::pair<std::unique_ptr<uint8_t[]>, uint8_t> Encode::communicationPLCData(command Command, syntax_id SyntaxID,
                                                                            length_t Length, area MemoryArea,
                                                                            address_t Adress, data_t DataWrite) {
    switch (Command) {
    case ReadBytes: {
        // TPKT Header
        tpkt TPKTSetup;
        TPKTSetup.version = TPKTHeader::TPKT_Version;
        TPKTSetup.reserved = TPKTHeader::TPKT_Reserved;
        uint16_t TPKTLength =  sizeof(S7CommReadByte) + sizeof(cotp_s7comm) + sizeof(tpkt);
        TPKTSetup.length = TPKTLength >> 8 | TPKTLength << 8;
        cotp_s7comm DataTransfer;
        DataTransfer.li = DataTransferHeader::LI;
        DataTransfer.type = DataTransferHeader::PDU_Type;
        DataTransfer.tpdu_number = DataTransferHeader::TPDU_number;

        S7CommReadByte S7Communication;
        S7Communication.header.protocolId = 0x32;
        S7Communication.header.ROSCTR = MessageType::JOB;
        S7Communication.header.redId = S7HeaderValue::Reserved >> 8 | S7HeaderValue::Reserved << 8;
        S7Communication.header.pduRef = Encode::pduRef >> 8 | Encode::pduRef << 8;
        Encode::pduRef++;
        S7Communication.header.parLg = sizeof(S7Communication.param) >> 8 | sizeof(S7Communication.param) << 8;
        S7Communication.header.datLg = 0x0000;

        S7Communication.param.func = FunctionsCode::ReadVariable;
        S7Communication.param.itemCount = 0x01;
        S7Communication.param.item.varSpec = 0x12;
        S7Communication.param.item.varSpec_Length = 0x0a;
        S7Communication.param.item.syntaxId = Encode::syntaxID_Table.value(SyntaxID);
        S7Communication.param.item.transp_size = 0x02;
        S7Communication.param.item.length = static_cast<uint16_t>(Length) >> 8 | static_cast<uint16_t>(Length) << 8;
        S7Communication.param.item.db = 0xe803;
        S7Communication.param.item.area = areaTable.value(MemoryArea);
        S7Communication.param.item.address[0] = Adress[0];
        S7Communication.param.item.address[1] = Adress[1];
        S7Communication.param.item.address[2] = Adress[2];

        std::unique_ptr<uint8_t[]> packedData(new uint8_t[sizeof(tpkt) + sizeof(cotp_s7comm) + sizeof(S7CommReadByte)]);
        std::memcpy(packedData.get(), &TPKTSetup, sizeof(TPKTSetup));
        std::memcpy(packedData.get() + sizeof(TPKTSetup), &DataTransfer, sizeof(DataTransfer));
        std::memcpy(packedData.get() + sizeof(TPKTSetup) + sizeof(DataTransfer), &S7Communication.header, sizeof(S7Communication.header));
        std::memcpy(packedData.get() + sizeof(TPKTSetup) + sizeof(DataTransfer) + sizeof(S7Communication.header), &S7Communication.param, sizeof(S7Communication.param));

        uint8_t length = sizeof(TPKTSetup) + sizeof(DataTransfer) + sizeof(S7Communication.header) + sizeof(S7Communication.param);
        return std::make_pair(std::move(packedData), length);
        break;
    }
    case WriteBytes:
    {
        tpkt TPKTSetup;
        TPKTSetup.version = TPKTHeader::TPKT_Version;
        TPKTSetup.reserved = TPKTHeader::TPKT_Reserved;
        uint16_t TPKTLength =  sizeof(S7CommWriteByte) - 1 + sizeof(cotp_s7comm) + sizeof(tpkt);
        TPKTSetup.length = TPKTLength >> 8 | TPKTLength << 8;

        cotp_s7comm DataTransfer;
        DataTransfer.li = DataTransferHeader::LI;
        DataTransfer.type = DataTransferHeader::PDU_Type;
        DataTransfer.tpdu_number = DataTransferHeader::TPDU_number;


        S7CommWriteByte S7Communication;

        S7Communication.header.protocolId = 0x32;
        S7Communication.header.ROSCTR = MessageType::JOB;
        S7Communication.header.redId = S7HeaderValue::Reserved >> 8 | S7HeaderValue::Reserved << 8;
        S7Communication.header.pduRef = Encode::pduRef >> 8 | Encode::pduRef << 8;
        Encode::pduRef++;
        S7Communication.header.parLg = sizeof(S7Communication.param) >> 8 | sizeof(S7Communication.param) << 8;
        S7Communication.header.datLg = sizeof(data_write_t) >> 8 | sizeof(data_write_t) << 8;

        S7Communication.param.func = FunctionsCode::WriteVariable;
        S7Communication.param.itemCount = 0x01;
        S7Communication.param.item.varSpec = 0x12; // hard code
        S7Communication.param.item.varSpec_Length = 0x0a; // hard code
        S7Communication.param.item.syntaxId = Encode::syntaxID_Table.value(SyntaxID);
        S7Communication.param.item.transp_size = 0x02; // hard code
        S7Communication.param.item.length = static_cast<uint16_t>(Length) >> 8 | static_cast<uint16_t>(Length) << 8;
        S7Communication.param.item.db = 0xe803; // hard code
        S7Communication.param.item.area = areaTable.value(MemoryArea);
        S7Communication.param.item.address[0] = static_cast<uint8_t>(Adress[0]);
        S7Communication.param.item.address[1] = static_cast<uint8_t>(Adress[1]);
        S7Communication.param.item.address[2] = static_cast<uint8_t>(Adress[2]);

        S7Communication.data.returnCode = ReturnCode::ReservedData;
        S7Communication.data.transportSize = RequestDataType::WORD; // need fix
        S7Communication.data.length[0] = 0x00;
        S7Communication.data.length[1] = 0x01; // need scale to more bytes
        S7Communication.data.data[0] = DataWrite[0];


        std::unique_ptr<uint8_t[]> packedData(new uint8_t[sizeof(tpkt) + sizeof(cotp_s7comm) + sizeof(S7CommReadByte)]);
        std::memcpy(packedData.get(), &TPKTSetup, sizeof(TPKTSetup));
        std::memcpy(packedData.get() + sizeof(TPKTSetup), &DataTransfer, sizeof(DataTransfer));

        std::memcpy(packedData.get() + sizeof(TPKTSetup) + sizeof(DataTransfer), &S7Communication.header, sizeof(S7Communication.header));
        std::memcpy(packedData.get() + sizeof(TPKTSetup) + sizeof(DataTransfer) + sizeof(S7Communication.header), &S7Communication.param, sizeof(S7Communication.param));
        std::memcpy(packedData.get() + sizeof(TPKTSetup) + sizeof(DataTransfer) + sizeof(S7Communication.header) + sizeof(S7Communication.param), &S7Communication.data, sizeof(S7Communication.data));
        uint8_t length = sizeof(TPKTSetup) + sizeof(DataTransfer) + sizeof(S7Communication.header) + sizeof(S7Communication.param);
        return std::make_pair(std::move(packedData), length);
        break;
    }
    default:
        std::cerr << "Error: Invalid command" << std::endl;
        std::exit(EXIT_FAILURE);
        break;
    }
}
