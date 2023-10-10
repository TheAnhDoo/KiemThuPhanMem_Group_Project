// CashPayment.cpp
#include "CashPayment.h"
#include "ProductDatabase.h"
#include <iostream>

CashPayment::CashPayment(double amountPaid, const std::vector<std::pair<int, std::string>>& orderedProducts)
    : Payment(amountPaid, orderedProducts) {}

void CashPayment::displayReceipt() const {
    // Display the receipt for cash payment
    std::cout << "\nCash Receipt:\n";

    double totalAmount = 0.0;

    // Calculate total amount and display ordered products
    for (const auto& orderedProduct : orderedProducts) {
        int productID = orderedProduct.first;
        std::string productName = orderedProduct.second;
        // Fetch product details from the database (ProductDatabase::ProductInfo) and calculate total
        // ...

        std::cout << "Product ID: " << productID << ", Product Name: " << productName
                  << ", Quantity: " << quantity << ", Unit Price: $" << unitPrice
                  << ", Total Amount: $" << productTotal << std::endl;
    }

    std::cout << "Total Amount: $" << totalAmount << std::endl;
    std::cout << "Amount Paid: $" << amountPaid << std::endl;

    // Calculate and display change
    if (amountPaid >= totalAmount) {
        double change = amountPaid - totalAmount;
        std::cout << "Change: $" << change << std::endl;
    } else {
        std::cout << "Insufficient payment. Please provide additional funds." << std::endl;
    }
}
