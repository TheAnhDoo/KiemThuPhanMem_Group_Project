#ifndef PAYMENT_H
#define PAYMENT_H
#include <iostream>

class Payment {
protected:
    double amountPaid;

public:
    Payment(double amountPaid);
    virtual ~Payment() = default;
    virtual void displayReceipt() const = 0;
};

#endif // PAYMENT_H