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
    std::cout << "Khach hang da chuyen khoan chua? (y/n): ";
    std::cin >> paymentStatus;

    if (paymentStatus == "y" || paymentStatus == "Y") {
        double change = amountPaid - totalAmount;

    } else {
        std::cout << "Thanh toán chưa được xác nhận (nhấn một nút bất kì để xác nhận lại một lần nữa)...\n";
        std::cin.ignore();
        std::cin.get();  // Wait for any key press
    }
    // Display invoice details
    std::cout << "\nHoa don:\n";
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

                    std::cout << "ID san pham: " << product_id << ", Ten san pham: " << productName
                            << ", So luong san pham: " << quantity << ", Don gia: $" << productPrice
                            << ", Tong tien: $" << productTotal << std::endl;
                } 
            } catch (const std::invalid_argument& e) {
                std::cerr << "Error: Invalid data format in the product data file.\n";
            }
        }
    }

    std::cout << "Tong tien: $" << totalAmount << std::endl;
    std::cout << "So tien khach hang tra: $" << amountPaid << std::endl;


  
}
