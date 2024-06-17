#ifndef S7COMM_H
#define S7COMM_H
#include <stdint.h>
#pragma pack(push, 1)
#include <QList>
// 10 bytes
struct header_t {
    uint8_t protocolId;
    uint8_t ROSCTR;
    uint16_t redId;
    uint16_t pduRef;
    uint16_t parLg;
    uint16_t datLg;
};
// 12 bytes
struct header_ack_t {
    uint8_t protocolId;
    uint8_t ROSCTR;
    uint16_t redId;
    uint16_t pduRef;
    uint16_t parLg;
    uint16_t datLg;
    uint8_t errCls;
    uint8_t errCod;
};
// 8 bytes
typedef struct param_setup_t {
    uint8_t func;
    uint8_t reserved;
    uint16_t maxamq_calling;
    uint16_t maxamq_called;
    uint16_t pdu_length;
} S7CommParamSetup;

// 12 bytes
struct item_t {
    uint8_t varSpec;
    uint8_t varSpec_Length;
    uint8_t syntaxId;
    uint8_t transp_size;
    uint16_t length;
    uint16_t db;
    uint8_t area;
    uint8_t address[3];
};
// 14 bytes
struct param_comm_t {
    uint8_t func;
    uint8_t itemCount;
    item_t item;
};
// Read data ACK - 5 bytes
// 5 bytes
typedef struct data_read_ack_t {
    uint8_t returnCode;
    uint8_t transportSize;
    uint16_t length;
    uint8_t data;
} DataReadACK;

struct data_write_t {
    uint8_t returnCode;
    uint8_t transportSize;
    uint8_t length[2];
    uint8_t data[1];
};

// 1 bytes
typedef struct data_write_ack_t {
    uint8_t returnCode;
}DataWriteAck;

// 2 bytes
typedef struct param_comm_ack {
    uint8_t func;
    uint8_t itemCount;
}ParamCommACK;

//
typedef struct s7comm_read_ack_t {
    header_ack_t header;
    ParamCommACK param;
    DataReadACK data;
} S7CommReadAck;

//
typedef struct s7comm_write_ack_t {
    header_ack_t header;
    ParamCommACK param;
    DataWriteAck data;
} S7CommWriteAck;

// 18 bytes
typedef struct s7comm_setup {
    header_t header;
    S7CommParamSetup param;
}  S7CommSetupCommunication;

//
typedef struct s7comm_read_t {
    header_t header;
    param_comm_t param;
} S7CommReadByte;

//
typedef struct s7comm_write_t {
    header_t header;
    param_comm_t param;
    data_write_t data;
} S7CommWriteByte;

enum S7HeaderValue : uint16_t { Reserved = 0x0000, PDU_Reference = 0x0000 };
enum S7ParamsValueReserverd : uint8_t
{
    Reserved_Param = 0x00,

};

enum S7ParamsValue : uint16_t {

    MaxAmQ_Calling = 0x0001,
    MaxAmQ_Called = 0x0001,
    PDU_Length = 0x01e0
};
enum MessageType : uint8_t {
    JOB = 0x01,      // request
    ACK = 0x02,      // acknowledge
    ACK_DATA = 0x03, // response
    USERDATA = 0x07, // request user data
    SRVCTRL = 0x08   // request server control
};

enum FunctionsCode : uint8_t {
    CPUServices = 0x00,
    SetupCommunication = 0xf0,
    ReadVariable = 0x04,
    WriteVariable = 0x05,
    RequestDownload = 0x1a,
    DownloadBlock = 0x1b,
    DownloadEnded = 0x1c,
    StartUpload = 0x1d,
    Upload = 0x1e,
    EndUpload = 0x1f,
    PLCControl = 0x28,
    PLCStop = 0x29
};
enum class PDUSizes : uint16_t {
    Default = 0x01e0, // 480 bytes
    S7_1200 = 0x00f0, // 240 bytes
    S7_1500 = 0x03c0  // 960 bytes
};
enum ReturnCode : uint8_t{
    SUCCESS = 0xff,
    ReservedData = 0x00,
};
enum RequestDataType : uint8_t{
    BIT = 0x01,
    BYTE,
    CHAR,
    WORD,
    INT,
    DWORD,
    DINT,
    REAL,
    DATE,
    TOD,
    TIME,
    S5TIME,
    DATE_AND_TIME,
    COUNTER,
    TIMER,
    IEC_TIMER,
    IEC_COUNTER,
    HS_COUNTER
};
enum command : uint8_t { ReadBytes = 0, WriteBytes };
enum syntax_id : uint8_t {

    S7_ANY = 0,
    R_ID,
    AlarmMessage,
    AlarmAcknowledgeMessage,
    SinumerikNCKHMIAccess,
    DriveES_Any,
    SymbolicAddressingMode,
    SpecialDB_Adressing,
    // Add features
    SyntaxID_Count // Tricks
};
enum area : uint8_t {
    DB = 0,
    Counter,
    Timer,
    P,
    I,
    O,
    M,
    // Add features
    Area_Count

};
using length_t = uint8_t;
using address_t = QList<uint8_t>;
using data_t = QList<uint8_t>;
#pragma pack(pop)
#endif // S7COMM_H
