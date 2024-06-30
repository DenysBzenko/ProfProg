#include "MegaData.hpp"

MegaData::MegaData() {
    smallArray.fill(42.0f);
    bigArray.fill(42.0);
}

void MegaData::reset() {
    smallArray.fill(42.0f);
    bigArray.fill(42.0);
}
