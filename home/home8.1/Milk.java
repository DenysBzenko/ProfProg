public class Milk implements Pricable {
    private double coefficient;
    private double basePrice;

    public Milk(double coefficient, double basePrice) {
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
