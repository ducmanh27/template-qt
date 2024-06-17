#include "ErrorTable.h"

QMap<uint16_t, QString> ErrorTable::errorCode = {
    {0x00'00, "No error"},
    {0x01'10, "Invalid block type number"},
    {0x01'12, "Invalid parameter"},
    {0x01'1A, "PG resource error"},
    {0x01'1B, "PLC resource error"},
    {0x01'1C, "Protocol error"},
    {0x01'1F, "User buffer too short"},
    {0x01'41, "Request error"},
    {0x01'C0, "Version mismatch"},
    {0x01'F0, "Not implemented"},
    {0x80'01, "L7 invalid CPU state"},
    {0x85'00, "L7 PDU size error"},
    {0xD4'01, "L7 invalid SZL ID"},
    {0xD4'02, "L7 invalid index"},
    {0xD4'03, "L7 DGS Connection already announced"},
    {0xD4'04, "L7 Max user NB"},
    {0xD4'05, "L7 DGS function parameter syntax error"},
    {0xD4'06, "L7 no info"},
    {0xD6'01, "L7 PRT function parameter syntax error"},
    {0xD8'01, "L7 invalid variable address"},
    {0xD8'02, "L7 unknown request"},
    {0xD8'03, "L7 invalid request status"}
};

QMap<uint16_t, QString> ErrorTable::errorClass = {
    {0x00, "No error"},
    {0x81, "Application relationship error"},
    {0x82, "Object definition error"},
    {0x83, "No resources available error"},
    {0x84, "Error on service processing"},
    {0x85, "Error on supplies"},
    {0x87, "Access error"}
};
ErrorTable::ErrorTable(QObject *parent)
    : QObject{parent}
{
}
