package com.example;

public class MathUtils {

    public static double computeValue(double x, double y, double z) {
        double product = x * y * z;
        if (product != 0) {
            return 1 / product;
        }

        double sum = x + y + z;
        if (sum != 0) {
            return 1 / sum;
        }

        return x + (y + 1) * (z - 1);
    }
}
