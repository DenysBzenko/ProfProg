public class Main {
    public static void main(String[] args) {
        Milk milk = new Milk(2.0, 1.5);
        Cookies cookies = new Cookies(1.5, 2.0);
        Pineapple pineapple = new Pineapple(1.8, 3.0);

        PricePresenter<Integer> presenter = new PricePresenter<>(2);
        presenter.printTotalPrice(milk, cookies);
        presenter.printTotalPrice(cookies, pineapple);
        presenter.printTotalPrice(milk, pineapple);
    }
}
