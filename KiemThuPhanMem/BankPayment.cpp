// BankPayment.cpp
#include "BankPayment.h"
#include "ProductDatabase.h"
#include <iostream>

BankPayment::BankPayment(double amountPaid, const std::vector<std::pair<int, std::string>>& orderedProducts,
                         const std::string& bankName, const std::string& accountNumber)
    : Payment(amountPaid, orderedProducts), bankName(bankName), accountNumber(accountNumber) {}

void BankPayment::displayReceipt() const {
    // Display the receipt for bank payment
    std::cout << "\nBank Receipt:\n";

    // Display bank account details
    std::cout << "Bank Name: " << bankName << std::endl;
    std::cout << "Account Number: " << accountNumber << std::endl;

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

    // Handle bank payment confirmation manually (outside the system)
    std::cout << "Bank transfer confirmed manually. Payment received." << std::endl;
}
