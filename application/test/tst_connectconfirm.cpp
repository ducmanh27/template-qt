
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

using namespace testing;

TEST(EncodeTest, ConnectConfirm)
{
    EXPECT_EQ(1, 1);
    ASSERT_THAT(0, Eq(0));
}
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
