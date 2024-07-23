public class Pineapple implements Pricable {
    private double coefficient;
    private double basePrice;

    public Pineapple(double coefficient, double basePrice) {
        this.coefficient = coefficient;
        this.basePrice = basePrice;
    }

    @Override
    public double getCoefficient() {
        return coefficient;
    }

    @Override
    public double getBasePrice() {
        return basePrice;
    }
}
