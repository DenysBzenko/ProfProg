#ifndef MEGADATAPOOL_HPP
#define MEGADATAPOOL_HPP

#include <vector>
#include "MegaData.hpp"

class MegaDataPool {
public:
    MegaDataPool(size_t poolSize);
    ~MegaDataPool();

    MegaData* acquire();
    void release(MegaData* obj);
    size_t size() const;
    size_t usedSize() const;

private:
    size_t poolSize;
    size_t usedCount;
    std::vector<MegaData*> pool;
};

#endif // MEGADATAPOOL_HPP
