#include "MegaData.hpp"

MegaData::MegaData() : smallArray(1024, 42.0f), bigArray(1024 * 1024, 42.0) {}

void MegaData::reset() {
    std::fill(smallArray.begin(), smallArray.end(), 42.0f);
    std::fill(bigArray.begin(), bigArray.end(), 42.0);
}
