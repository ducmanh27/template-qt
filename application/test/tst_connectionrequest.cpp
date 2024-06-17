
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>
#include "interface/IEncode.h"
#include "communication/Encode.h"
#include "tcp_header/Status.h"

using namespace testing;

// class MockEncode : public IEncode {
// public:
//     MOCK_METHOD((std::pair<std::unique_ptr<uint8_t[]>, uint8_t>), connectionRequestData, (), (override));
//     MOCK_METHOD((std::pair<std::unique_ptr<uint8_t[]>, uint8_t>), setupCommunicationData, (), (override));
//     MOCK_METHOD((std::pair<std::unique_ptr<uint8_t[]>, uint8_t>), communicationPLCData, (command, syntax_id, length_t, area, address_t, data_t), (override));
// };
class EncodeTest : public ::testing::Test{
protected:
    std::unique_ptr<IEncode> encode;
    command Command;
    syntax_id SyntaxID;
    length_t Length;
    area MemoryArea;
    address_t Adress;
    data_t DataWrite;
    void SetUp() override {
        // Code here will be called immediately after the constructor (right
        // before each test).
        encode = std::make_unique<Encode>();

    }
    void TearDown() override {
    }

};


TEST_F(EncodeTest, ReadVariableData)
{
    Command = ReadBytes;
    SyntaxID = S7_ANY;
    Length = 1;
    MemoryArea = DB;
    Adress.append( 0x00);
    Adress.append( 0x00);
    Adress.append( 0x00);
    DataWrite.append(0x00);
    std::pair<std::unique_ptr<uint8_t[]>, uint8_t> DataEncode = encode->communicationPLCData(Command, SyntaxID, Length, MemoryArea, Adress, DataWrite);
    std::unique_ptr<uint8_t[]> bytesData = std::move(DataEncode.first);
    std::uint8_t length = DataEncode.second;
    EXPECT_EQ(length, 31);

    // TPKT
    EXPECT_EQ(bytesData[0], TPKTHeader::TPKT_Version);
    EXPECT_EQ(bytesData[1], 0x00);
    EXPECT_EQ(bytesData[2], 0x00);
    EXPECT_EQ(bytesData[3], 0x1F);
    // COTP
    EXPECT_EQ(bytesData[4], DataTransferHeader::LI);
}
TEST_F(EncodeTest, ReadBytes_Success)
{
    command Command = ReadBytes;
    syntax_id SyntaxID = AlarmMessage;
    length_t Length = 1;
    area MemoryArea = Timer;
    address_t Adress = {0x00, 0x00, 0x01}; // Invalid address
    data_t DataWrite = {}; // Dont need

    std::pair<std::unique_ptr<uint8_t[]>, uint8_t> DataEncode = encode->communicationPLCData(Command, SyntaxID, Length, MemoryArea, Adress, DataWrite);
    std::unique_ptr<uint8_t[]> bytesData = std::move(DataEncode.first);
    uint8_t length = DataEncode.second;
    EXPECT_EQ(length, sizeof(tpkt) + sizeof(cotp_s7comm) + sizeof(S7CommReadByte::header) + sizeof(S7CommReadByte::param));

    EXPECT_EQ(bytesData[0], TPKTHeader::TPKT_Version);
    EXPECT_EQ(bytesData[4], DataTransferHeader::LI);
    EXPECT_EQ(bytesData[17], FunctionsCode::ReadVariable);
    EXPECT_EQ(bytesData[21], Encode::syntaxID_Table.value(SyntaxID));
    EXPECT_EQ(bytesData[27], Encode::areaTable.value(MemoryArea));
}

TEST_F(EncodeTest, WriteBytes_Success)
{
    command Command = WriteBytes;
    syntax_id SyntaxID = AlarmMessage;
    length_t Length = 1;
    area MemoryArea = Timer;
    address_t Adress = {0x00, 0x00, 0x01}; // Invalid address
    data_t DataWrite = {0x00}; // Dont need

    std::pair<std::unique_ptr<uint8_t[]>, uint8_t> DataEncode = encode->communicationPLCData(Command, SyntaxID, Length, MemoryArea, Adress, DataWrite);
    std::unique_ptr<uint8_t[]> bytesData = std::move(DataEncode.first);
    uint8_t length = DataEncode.second;
    EXPECT_EQ(length, sizeof(tpkt) + sizeof(cotp_s7comm) + sizeof(S7CommReadByte::header) + sizeof(S7CommReadByte::param));


    EXPECT_EQ(bytesData[0], TPKTHeader::TPKT_Version);
    EXPECT_EQ(bytesData[4], DataTransferHeader::LI);
    EXPECT_EQ(bytesData[17], FunctionsCode::WriteVariable);
    EXPECT_EQ(bytesData[21], Encode::syntaxID_Table.value(SyntaxID));
    EXPECT_EQ(bytesData[27], Encode::areaTable.value(MemoryArea));
}
