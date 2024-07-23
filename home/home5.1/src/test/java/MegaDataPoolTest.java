package com;

import org.junit.Test;
import static org.junit.Assert.*;
import java.util.NoSuchElementException;

public class MegaDataPoolTest {

    @Test
    public void testAcquireAndRelease() {
        MegaDataPool pool = new MegaDataPool(2);
        MegaData obj1 = pool.acquire();
        MegaData obj2 = pool.acquire();

        assertEquals(2, pool.size());
        assertEquals(2, pool.usedSize());

        pool.release(obj1);
        assertEquals(1, pool.usedSize());

        pool.release(obj2);
        assertEquals(0, pool.usedSize());
    }

    @Test
    public void testAcquireBeyondPoolSize() {
        MegaDataPool pool = new MegaDataPool(1);
        MegaData obj1 = pool.acquire();

        assertThrows(NoSuchElementException.class, pool::acquire);

        pool.release(obj1);
    }

    @Test
    public void testReleaseInvalidObject() {
        MegaDataPool pool = new MegaDataPool(1);
        MegaData obj1 = pool.acquire();
        MegaData obj2 = new MegaData();

        assertThrows(IllegalArgumentException.class, () -> pool.release(obj2));

        pool.release(obj1);
    }

    @Test
    public void testResetOnRelease() {
        MegaDataPool pool = new MegaDataPool(1);
        MegaData obj = pool.acquire();

        obj.getSmallArray()[0] = 100.0f;
        obj.getBigArray()[0] = 100.0;

        pool.release(obj);

        assertEquals(42.0f, obj.getSmallArray()[0], 0.0);
        assertEquals(42.0, obj.getBigArray()[0], 0.0);
    }
}
