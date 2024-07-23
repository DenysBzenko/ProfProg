#ifndef MEGADATAPOOL_HPP
#define MEGADATAPOOL_HPP

#include <queue>
#include <stdexcept>
#include <mutex>
#include "MegaData.hpp"

class MegaDataPool {
public:
    static MegaDataPool& getInstance(size_t poolSize);

    MegaDataPool(const MegaDataPool&) = delete;
    MegaDataPool& operator=(const MegaDataPool&) = delete;

    MegaData* acquire();
    void release(MegaData* obj);

    [[nodiscard]] size_t size() const;
    [[nodiscard]] size_t getUsedSize() const;

private:
    MegaDataPool(size_t poolSize);

    size_t poolSize;
    size_t usedSize;
    std::queue<MegaData*> pool;
    std::mutex mutex;
};

#endif 
