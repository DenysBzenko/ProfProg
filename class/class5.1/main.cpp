#include "MegaDataPool.hpp"
#include <iostream>
#include <cassert>

void runTests() {
    
    MegaDataPool pool(3);
    assert(pool.size() == 3);
    assert(pool.getUsedSize() == 0);

    
    MegaData* obj1 = pool.acquire();
    assert(pool.getUsedSize() == 1);

    
    obj1->smallArray[0] = 0.0f;
    obj1->bigArray[0] = 0.0;

    
    pool.release(obj1);
    assert(pool.getUsedSize() == 0);

    
    MegaData* obj2 = pool.acquire();
    assert(obj2->smallArray[0] == 42.0f);
    assert(obj2->bigArray[0] == 42.0);
    assert(pool.getUsedSize() == 1);

    
    pool.release(obj2);
    assert(pool.getUsedSize() == 0);

    std::cout << "All tests passed!" << std::endl;
}

int main() {
    runTests();
    return 0;
}
