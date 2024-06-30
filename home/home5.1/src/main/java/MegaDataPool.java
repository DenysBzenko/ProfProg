package com;

import java.util.ArrayList;
import java.util.List;
import java.util.NoSuchElementException;

public class MegaDataPool {
    private final List<MegaData> pool;
    private final boolean[] used;

    public MegaDataPool(int poolSize) {
        pool = new ArrayList<>(poolSize);
        used = new boolean[poolSize];
        for (int i = 0; i < poolSize; i++) {
            pool.add(new MegaData());
            used[i] = false;
        }
    }

    public synchronized MegaData acquire() {
        for (int i = 0; i < pool.size(); i++) {
            if (!used[i]) {
                used[i] = true;
                return pool.get(i);
            }
        }
        throw new NoSuchElementException("No available MegaData objects in the pool");
    }

    public synchronized void release(MegaData obj) {
        int index = pool.indexOf(obj);
        if (index >= 0 && used[index]) {
            used[index] = false;
            obj.reset();
        } else {
            throw new IllegalArgumentException("The object was not acquired from this pool");
        }
    }

    public synchronized int size() {
        return pool.size();
    }

    public synchronized int usedSize() {
        int count = 0;
        for (boolean u : used) {
            if (u) {
                count++;
            }
        }
        return count;
    }
}
