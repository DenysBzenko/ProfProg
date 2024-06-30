package com;

public class MegaData {
    private float[] smallArray;
    private double[] bigArray;

    public MegaData() {
        this.smallArray = new float[10];
        this.bigArray = new double[10];
        for (int i = 0; i < 10; i++) {
            smallArray[i] = 42.0f;
            bigArray[i] = 42.0;
        }
    }

    public float[] getSmallArray() {
        return smallArray;
    }

    public double[] getBigArray() {
        return bigArray;
    }

    public void reset() {
        for (int i = 0; i < 10; i++) {
            smallArray[i] = 42.0f;
            bigArray[i] = 42.0;
        }
    }
}
