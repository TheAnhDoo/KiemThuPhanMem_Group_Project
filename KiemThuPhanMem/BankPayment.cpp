#include "BankPayment.h"
#include <iomanip>
#include <iostream>
#include <fstream>
BankPayment::BankPayment(double amountPaid, const std::map<int, int>& orderedProductQuantities)
    : Payment(amountPaid), orderedProductQuantities(orderedProductQuantities) {}
void BankPayment::displayReceipt() const {
    double totalAmount = 0.0;
  // Ask if customer has paid
    std::string paymentStatus;
    std::cout << "Has the customer paid? (y/n): ";
    std::cin >> paymentStatus;

    if (paymentStatus == "y" || paymentStatus == "Y") {
        double change = amountPaid - totalAmount;

    } else {
        std::cout << "Payment not confirmed. Program on hold. Press any key to continue...\n";
        std::cin.ignore();
        std::cin.get();  // Wait for any key press
    }
    // Display invoice details
    std::cout << "\nInvoice:\n";
    std::ifstream file("Products.csv");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open product data file.\n";
        return;
    }

    std::string line;
    std::getline(file, line);  // Skip the header line

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string id, product_name, price_str;

        if (std::getline(ss, id, ',') &&
            std::getline(ss, product_name, ',') &&
            std::getline(ss, price_str, ',')) {
            try {
                int product_id = std::stoi(id);
                std::string productName = product_name;
                double productPrice = std::stod(price_str);

                // Check if this product is in the ordered products
                auto it = orderedProductQuantities.find(product_id);

                if (it != orderedProductQuantities.end()) {
                    // Product is in the order, display details
                    int quantity = it->second;
                    double productTotal = productPrice * quantity;
                    totalAmount += productTotal;

                    std::cout << "Product ID: " << product_id << ", Product Name: " << productName
                            << ", Quantity: " << quantity << ", Unit Price: $" << productPrice
                            << ", Total Amount: $" << productTotal << std::endl;
                } 
            } catch (const std::invalid_argument& e) {
                std::cerr << "Error: Invalid data format in the product data file.\n";
            }
        }
    }

    std::cout << "Total Amount: $" << totalAmount << std::endl;
    std::cout << "Amount Paid: $" << amountPaid << std::endl;


  
}
