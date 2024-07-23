#ifndef MEGADATA_HPP
#define MEGADATA_HPP

#include <vector>
#include <algorithm>

class MegaData {
public:
    std::vector<float> smallArray;
    std::vector<double> bigArray;

    MegaData();

    void reset();
};

#endif 