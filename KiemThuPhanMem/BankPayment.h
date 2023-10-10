// BankPayment.h
#pragma once
#include "Payment.h"

class BankPayment : public Payment {
private:
    std::string bankName;
    std::string accountNumber;

public:
    BankPayment(double amountPaid, const std::vector<std::pair<int, std::string>>& orderedProducts,
                const std::string& bankName, const std::string& accountNumber);
    void displayReceipt() const override;
};
