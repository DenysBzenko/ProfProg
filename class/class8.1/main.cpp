#include <iostream>
#include <concepts>


template<typename T>
concept Pricable = requires(T a) {
    { a.getCoefficient() } -> std::convertible_to<double>;
    { a.getBasePrice() } -> std::convertible_to<double>;
};


template<std::size_t PRIORITY>
class PricePresenter {
public:
    template<Pricable T1, Pricable T2>
    void printTotalPrice(const T1& obj1, const T2& obj2) const {
        double totalPrice = PRIORITY * obj1.getCoefficient() * obj1.getBasePrice()
                            + obj2.getCoefficient() * obj2.getBasePrice();
        std::cout << "Total Price: " << totalPrice << std::endl;
    }
};


class Milk {
public:
    double getCoefficient() const {
        return 1.5;
    }

    double getBasePrice() const {
        return 10.0;
    }
};


class Cookies {
public:
    double getCoefficient() const {
        return 2.0;
    }

    double getBasePrice() const {
        return 5.0;
    }
};


class Pineapple {
public:
    double getCoefficient() const {
        return 1.2;
    }

    double getBasePrice() const {
        return 15.0;
    }
};


int main() {
    Milk milk;
    Cookies cookies;
    Pineapple pineapple;

    PricePresenter<2> presenter;

    presenter.printTotalPrice(milk, cookies);       
    presenter.printTotalPrice(cookies, pineapple);   

    return 0;
}
