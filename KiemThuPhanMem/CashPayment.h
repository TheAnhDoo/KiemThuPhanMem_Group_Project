// CashPayment.h
#pragma once
#include "Payment.h"

class CashPayment : public Payment {
public:
    CashPayment(double amountPaid, const std::vector<std::pair<int, std::string>>& orderedProducts);
    void displayReceipt() const override;
};
