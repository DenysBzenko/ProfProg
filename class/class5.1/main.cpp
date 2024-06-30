#include <gtest/gtest.h>
#include "MegaData.hpp"
#include "MegaDataPool.hpp"

// Тест ініціалізації MegaData
TEST(MegaDataTest, Initialization) {
    MegaData data;
    for (const auto& val : data.smallArray) {
        EXPECT_EQ(val, 42.0f);
    }
    for (const auto& val : data.bigArray) {
        EXPECT_EQ(val, 42.0);
    }
}

// Тест скидання MegaData
TEST(MegaDataTest, Reset) {
    MegaData data;
    data.smallArray[0] = 0.0f;
    data.bigArray[0] = 0.0;
    data.reset();
    EXPECT_EQ(data.smallArray[0], 42.0f);
    EXPECT_EQ(data.bigArray[0], 42.0);
}

// Тест acquire та release в MegaDataPool
TEST(MegaDataPoolTest, AcquireAndRelease) {
    MegaDataPool pool(2);
    EXPECT_EQ(pool.size(), 2);
    EXPECT_EQ(pool.usedSize(), 0);

    MegaData* data1 = pool.acquire();
    EXPECT_EQ(pool.usedSize(), 1);

    MegaData* data2 = pool.acquire();
    EXPECT_EQ(pool.usedSize(), 2);

    pool.release(data1);
    EXPECT_EQ(pool.usedSize(), 1);

    pool.release(data2);
    EXPECT_EQ(pool.usedSize(), 0);
}

// Тест виключення при переповненні MegaDataPool
TEST(MegaDataPoolTest, OutOfRange) {
    MegaDataPool pool(1);
    MegaData* data = pool.acquire();
    EXPECT_THROW(pool.acquire(), std::out_of_range);
    pool.release(data);
    EXPECT_NO_THROW(pool.acquire());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
