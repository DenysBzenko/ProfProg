#ifndef MEGADATA_HPP
#define MEGADATA_HPP

#include <array>

class MegaData {
public:
    std::array<float, 1024> smallArray;
    std::array<double, 1024 * 1024> bigArray;

    MegaData();
    void reset();
};

#endif // MEGADATA_HPP
