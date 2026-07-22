#include <iostream>

using namespace std;

class Beverage
{
    public:
        virtual string getName() = 0;
        virtual double getCost() = 0;
        virtual ~Beverage() = default;
};

class Coffee: public Beverage
{
    public:
        string getName() override
        {
            return "Basic Coffee"; 
        }

        double getCost() override
        {
            return 10.0;
        }
};

class BeverageDecorator: public Beverage
{
    protected:
        Beverage* beverage;
    
    public:
        BeverageDecorator(Beverage* beverage): beverage(beverage){}
};

class Sugar: public BeverageDecorator
{
    public:
        Sugar(Beverage* beverage): BeverageDecorator(beverage){}

        string getName() override
        {
            return beverage->getName() + " + sugar";
        }

        double getCost() override
        {
            return beverage->getCost() + 5.0;
        }
};

int main()
{
    Beverage* coffee = new Coffee();
    cout << coffee->getName() << endl;
    cout << coffee->getCost() << endl;
    Beverage* coffeeWithSugar = new Sugar(coffee);
    cout << coffeeWithSugar->getName() << endl;
    cout << coffeeWithSugar->getCost() << endl;
    return 0;
}