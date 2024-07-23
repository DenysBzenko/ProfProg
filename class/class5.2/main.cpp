#include "PoolHelpers.hpp"
#include <iostream>
#include <cassert>
#include <thread>
#include <vector>


void doWork(MegaData* obj) {
   
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}


void runTests() {
    constexpr int numObjects = 10;
    std::vector<MegaData*> objects;

    
    for (int i = 0; i < numObjects; ++i) {
        MegaData* obj = acquireFromPool();
        objects.push_back(obj);
    }

   
    std::vector<std::thread> threads;
    for (int i = 0; i < numObjects; ++i) {
        threads.emplace_back([i, &objects]() {
            MegaData* obj = objects[i];
            doWork(obj);
            releaseToPool(obj);
        });
    }

    
    for (auto& thread : threads) {
        thread.join();
    }

    
    assert(poolSize() == numObjects);
    std::cout << "All tests passed!" << std::endl;

    
    for (auto obj : objects) {
        delete obj;
    }
}

int main() {
    runTests();
    return 0;
}
