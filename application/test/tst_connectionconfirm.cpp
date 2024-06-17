
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>
#include "communication/Decode.h"
#include "tcp_header/Status.h"
using namespace testing;

class DecodeTest : public ::testing::Test{
protected:
    std::unique_ptr<IDecode> t_decode;
    QByteArray t_ResponseData;
    void SetUp() override {
        // Code here will be called immediately after the constructor (right
        // before each test).
        t_decode = std::make_unique<Decode>();

    }
    void TearDown() override {

    }
};
TEST_F(DecodeTest, ConnectionConfirm){
    // 03 00 00 16 11 d0 00 01 00 21 00 c0 01 09 c1 02 01 00 c2 02 03 01
    t_ResponseData.append(static_cast<uint8_t>(0x04));
    t_ResponseData.append(static_cast<uint8_t>(0x00));
    t_ResponseData.append(static_cast<uint8_t>(0x00));
    t_ResponseData.append(static_cast<uint8_t>(0x16));
    t_ResponseData.append(static_cast<uint8_t>(0x11));
    t_ResponseData.append(static_cast<uint8_t>(0xd0));
    t_ResponseData.append(static_cast<uint8_t>(0x00));
    t_ResponseData.append(static_cast<uint8_t>(0x01));
    t_ResponseData.append(static_cast<uint8_t>(0x00));
    t_ResponseData.append(static_cast<uint8_t>(0x21));
    t_ResponseData.append(static_cast<uint8_t>(0x00));
    t_ResponseData.append(static_cast<uint8_t>(0xc0));
    t_ResponseData.append(static_cast<uint8_t>(0x01));
    t_ResponseData.append(static_cast<uint8_t>(0x09));
    t_ResponseData.append(static_cast<uint8_t>(0xc1));
    t_ResponseData.append(static_cast<uint8_t>(0x02));
    t_ResponseData.append(static_cast<uint8_t>(0x01));
    t_ResponseData.append(static_cast<uint8_t>(0x00));
    t_ResponseData.append(static_cast<uint8_t>(0xc2));
    t_ResponseData.append(static_cast<uint8_t>(0x02));
    t_ResponseData.append(static_cast<uint8_t>(0x03));
    t_ResponseData.append(static_cast<uint8_t>(0x01));

    EXPECT_EQ(t_decode->connectionConfirm(t_ResponseData), status::CONNECTION_REQEUEST_SUCCESSFULL);
}
