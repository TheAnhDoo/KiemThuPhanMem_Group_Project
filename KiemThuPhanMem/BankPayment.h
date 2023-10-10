// BankPayment.h
#ifndef BANKPAYMENT_H
#define BANKPAYMENT_H
#include "Payment.h"
#include <map>
class BankPayment : public Payment {
private:
    std::map<int, int> orderedProductQuantities;
public:
    BankPayment(double amountPaid, const std::map<int, int>& orderedProductQuantities);
    void displayReceipt() const override;
};

#endif // BANKPAYMENT_H