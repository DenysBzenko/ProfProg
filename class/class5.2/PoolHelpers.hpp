#ifndef POOLHELPERS_HPP
#define POOLHELPERS_HPP

#include "MegaDataPool.hpp"

MegaData* acquireFromPool() {
    return MegaDataPool::getInstance(10).acquire(); 
}

void releaseToPool(MegaData* obj) {
    MegaDataPool::getInstance(10).release(obj);
}

size_t poolSize() {
    return MegaDataPool::getInstance(10).size(); 
}

#endif 