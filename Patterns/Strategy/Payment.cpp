#include <iostream> 

using namespace std;

enum class PaymentType
{
    UPI, CreditCard
};

class PaymentStrategy
{
    public:
        virtual void processPayment(double amount) = 0;
        virtual ~PaymentStrategy() = default;
};

class CreditCard: public PaymentStrategy
{
    public:
        void processPayment(double amount) override
        {
            cout << "Payment processed via CC. Amount: " << amount << endl;
        }
};

class UPI: public PaymentStrategy
{
    public:
        void processPayment(double amount) override
        {
            cout << "Payment processed via UPI. Amount: " << amount << endl;
        }
};

class OrderService
{
    public:
        void completePurchase(double amount, PaymentStrategy *strategy)
        {
            cout << "Your order is being processed.." << endl;
            strategy->processPayment(amount);
        }
};

class PaymentStrategyFactory
{
    public:

        PaymentStrategy* createPaymentStrategy(PaymentType paymentType)
        {
            switch(paymentType)
            {
                case PaymentType::UPI:
                {
                    return new UPI();
                }
                case PaymentType::CreditCard:
                {
                    return new CreditCard();
                }
            }
        }
};

int main()
{
    PaymentStrategyFactory factory = PaymentStrategyFactory();
    OrderService orderService;
    PaymentStrategy* selectedStrategy = factory.createPaymentStrategy(PaymentType::UPI);
    orderService.completePurchase(200.0, selectedStrategy);
    selectedStrategy = factory.createPaymentStrategy(PaymentType::CreditCard);
    orderService.completePurchase(300.0, selectedStrategy);
    return 0;
}