#ifndef CASHPAYMENT_H
#define CASHPAYMENT_H
#include "Payment.h"
#include <map>

class CashPayment : public Payment {
private:
    std::map<int, int> orderedProductQuantities;

public:
    CashPayment(double amountPaid, const std::map<int, int>& orderedProductQuantities);
    void displayReceipt() const override;
};
#endif // CASHPAYMENT_H