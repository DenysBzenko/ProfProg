#include "MegaDataPool.hpp"
#include <stdexcept>

MegaDataPool::MegaDataPool(size_t poolSize) : poolSize(poolSize), usedCount(0) {
    pool.reserve(poolSize);
    for (size_t i = 0; i < poolSize; ++i) {
        pool.push_back(new MegaData());
    }
}

MegaDataPool::~MegaDataPool() {
    for (auto obj : pool) {
        delete obj;
    }
}

MegaData* MegaDataPool::acquire() {
    if (usedCount == poolSize) {
        throw std::out_of_range("No available objects in the pool");
    }
    return pool[usedCount++];
}

void MegaDataPool::release(MegaData* obj) {
    if (usedCount == 0) {
        throw std::out_of_range("No objects to release");
    }
    obj->reset();
    std::swap(pool[--usedCount], obj);
}

size_t MegaDataPool::size() const {
    return poolSize;
}

size_t MegaDataPool::usedSize() const {
    return usedCount;
}
