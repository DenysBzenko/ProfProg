#include "MegaDataPool.hpp"

MegaDataPool::MegaDataPool(size_t poolSize) : poolSize(poolSize), usedSize(0) {
    for (size_t i = 0; i < poolSize; ++i) {
        pool.push(new MegaData());
    }
}

MegaDataPool::~MegaDataPool() {
    while (!pool.empty()) {
        delete pool.front();
        pool.pop();
    }
}

MegaData* MegaDataPool::acquire() {
    if (pool.empty()) {
        throw std::runtime_error("No available objects in the pool");
    }
    MegaData* obj = pool.front();
    pool.pop();
    ++usedSize;
    return obj;
}

void MegaDataPool::release(MegaData* obj) {
    if (obj == nullptr) {
        throw std::invalid_argument("Cannot release a null object");
    }
    obj->reset();
    pool.push(obj);
    --usedSize;
}

size_t MegaDataPool::size() const {
    return poolSize;
}

size_t MegaDataPool::getUsedSize() const {
    return usedSize;
}
