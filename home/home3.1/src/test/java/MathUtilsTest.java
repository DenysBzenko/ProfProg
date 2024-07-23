package com.example;

import static org.junit.Assert.assertEquals;
import org.junit.Test;

public class MathUtilsTest {

    @Test
    public void testInverseProduct() {
        assertEquals(0.5, MathUtils.computeValue(2, 1, 1), 1e-6);
    }

    @Test
    public void testInverseSum() {
        assertEquals(0.2, MathUtils.computeValue(0, 2, 3), 1e-6);
    }

    @Test
    public void testSumIsZero() {
        assertEquals(3.0, MathUtils.computeValue(0, -1, 1), 1e-6);
    }

    @Test
    public void testAllZeros() {
        assertEquals(0.0, MathUtils.computeValue(0, 0, 0), 1e-6);
    }
}
