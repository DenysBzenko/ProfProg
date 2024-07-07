#ifndef MEGADATAPOOL_HPP
#define MEGADATAPOOL_HPP

#include <queue>
#include <stdexcept>
#include "MegaData.hpp"

class MegaDataPool {
public:
    explicit MegaDataPool(size_t poolSize);

    ~MegaDataPool();

    MegaData* acquire();

    void release(MegaData* obj);

    size_t size() const;

    size_t getUsedSize() const;

private:
    size_t poolSize;
    size_t usedSize;
    std::queue<MegaData*> pool;
};

#endif 
