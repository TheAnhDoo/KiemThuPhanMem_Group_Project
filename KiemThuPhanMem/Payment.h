// Payment.h
#pragma once
#include <string>
#include <vector>

class Payment {
protected:
    double amountPaid;
    std::vector<std::pair<int, std::string>> orderedProducts;  // ID and name of ordered products

public:
    Payment(double amountPaid, const std::vector<std::pair<int, std::string>>& orderedProducts);
    virtual void displayReceipt() const = 0;  // Make it a pure virtual function
    double getAmountPaid() const;
};
