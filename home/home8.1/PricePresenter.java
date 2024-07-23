public class PricePresenter<PRIORITY extends Number> {
    private PRIORITY priority;

    public PricePresenter(PRIORITY priority) {
        this.priority = priority;
    }

    public <T extends Pricable, U extends Pricable> void printTotalPrice(T obj1, U obj2) {
        double total = priority.doubleValue() * obj1.getCoefficient() * obj1.getBasePrice() 
                       + obj2.getCoefficient() * obj2.getBasePrice();
        System.out.println("Total Price: " + total);
    }
}
