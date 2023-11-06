#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include "CashPayment.cpp"
#include "BankPayment.cpp"
#include "Product_management_program.h"

ProductManagementProgram::ProductManagementProgram() : filename("Products.csv") {
    // Check if the file exists
    if (!fileExists(filename)) {
        // If the file doesn't exist, create it and add some initial data
        std::ofstream file(filename);
        if (file.is_open()) {
            // Write some initial data to the file
            file << "ID,Product Name,Price\n";
            file.close();
            std::cout << "Data file created: " << filename << "\n";
        } else {
            std::cerr << "Error: Could not create data file.\n";
        }
    } else {
        // File exists, read the existing data
        read_product_data();
    }
}

bool ProductManagementProgram::fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

void ProductManagementProgram::read_product_data() {
    // Read product data from the file
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open data file for reading.\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string id, product_name, price_str;

        if (std::getline(ss, id, ',') &&
            std::getline(ss, product_name, ',') &&
            std::getline(ss, price_str, ',')) {
            try {
                // Convert string to appropriate types
                int product_id = std::stoi(id);
                double price = std::stod(price_str);

                // Create a product and add it to the vector
                Product product(product_id, product_name, price);
                products.push_back(product);
            } catch (const std::invalid_argument& e) {
                std::cerr << "Error: Invalid data format in the file.\n";
                // Handle the invalid data (skip or take appropriate action)
            }
        }
    }

    file.close();
}


void ProductManagementProgram::save_product_data() {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open data file for writing.\n";
        return;
    }

    // Write product data to the file
    file << "ID,Product Name,Price\n";
    for (const Product& product : products) {
        file << product.get_ID() << "," << product.get_product_name() << "," << product.get_price() << "\n";
    }

    // Check for errors during write
    if (file.fail()) {
        std::cerr << "Error: Failed to write to data file.\n";
    }

    file.close();
}


void ProductManagementProgram::display_main_menu() {
    int choice = -1;
    while (choice != 0) {
        std::cout << "\nChuong trinh quan ly cua hang Cafe:\n";
        std::cout << "1. Quan ly san pham\n";
        std::cout << "2. Thanh toan\n";
        std::cout << "0. Thoat\n";
        std::cout << "Nhap lua chon cua ban: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Quan ly san pham:\n";
                std::cout << "1. Xem tat ca san pham\n";
                std::cout << "2. Them san pham\n";
                std::cout << "3. Cap nhat san pham\n";
                std::cout << "4. Xoa san pham\n";
                std::cout << "0. Quay lai menu chinh\n";
                int productMenuChoice;
                std::cout << "Nhap lua chon cua ban: ";
                std::cin >> productMenuChoice;
                switch (productMenuChoice) {
                    case 1:
                        show_all_products();
                        break;
                    case 2:
                        add_product();
                        break;
                    case 3:
                        update_product();
                        break;
                    case 4:
                        delete_product();
                        break;
                    case 0:
                        break;
                    default:
                        std::cout << "Lua chon khong hop le. Vui long thu lai.\n";
                }
                break;
            case 2:
                system("cls");
                std::cout << "1. Thanh toan tien mat\n";
                std::cout << "2. Thanh toan qua ngan hang\n";
                std::cout << "0. Quay lai Menu chinh\n";
                int paymentChoice;
                std::cout << "Nhap lua chon cua ban: ";
                std::cin >> paymentChoice;
                switch (paymentChoice) {
                    case 1:
                        processCashPayment();
                        break;
                    case 2:
                        processBankPayment();
                        break;
                    case 0:
                        break;
                    default:
                        std::cout << "Lua chon khong hop le. Vui long thu lai.\n";
                }
                break;
            case 0:
                save_product_data();  // Lưu dữ liệu trước khi thoát
                std::cout << "Dang thoat ra khoi chuong trinh.\n";
                break;
            default:
                std::cout << "Lua chon khong hop le. Vui long thu lai.\n";
        }
    }
}


void ProductManagementProgram::show_all_products() const {
    if (products.empty()) {
        std::cout << "Khong co san pham nao ton tai.\n";
        return;
    }

    std::cout << "Danh sach san pham:\n";
    for (const Product& product : products) {
        product.display();
    }
}

void ProductManagementProgram::add_product() {
    int id;
    std::cout << "Nhap thong tin san pham:\n";
    std::cout << "ID: ";
    std::cin >> id;

    // Check if a product with the given ID already exists
    auto it = std::find_if(products.begin(), products.end(), [id](const Product& product) {
        return product.get_ID() == id;
    });

    if (it != products.end()) {
        std::cout << "San pham voi ID " << id << " da ton tai. Them moi san pham khong thanh cong.\n";
        return;
    }
    if (id <= 0) {
        std::cout << "ID khong hop le, them moi san pham khong thanh cong.\n";
        return;
    }
    std::string product_name;
    double price;

    std::cout << "Ten san pham: ";
    std::cin.ignore();  // Clear the newline from the buffer
    std::getline(std::cin, product_name);

    std::cout << "Don gia san pham: ";
    std::cin >> price;

    if (price >= 15000 && price <= 100000) {
        Product product(id, product_name, price);
        products.push_back(product);
        save_product_data();  // Save the product data after adding a new product
        std::cout << "Da them san pham moi thanh cong.\n";
    } else {
        std::cout << "Vui long nhap lai, muc gia cho phep cua san pham la [15000,100000]!\n";
    }
}

void ProductManagementProgram::update_product() {
    int id;
    std::cout << "Nhap ID cua san pham ban muon chinh sua: ";
    std::cin >> id;

    // Check if a product with the given ID exists for updating
    auto it = std::find_if(products.begin(), products.end(), [id](const Product& product) {
        return product.get_ID() == id;
    });
    
    it->display();

    if (it == products.end()) {
        std::cout << "San pham voi ID: " << id << " khong ton tai. Cap nhat san pham khong thanh cong.\n";
        return;
    }
    if (id <= 0) {
        std::cout << "ID khong hop le, cap nhat san pham khong thanh cong.\n";
        return;
    }

    std::cout << "San pham voi ID: " << id << "tim thay thanh cong.\n";
    std::cout << "Nhap thong tin moi cua san pham:\n";

    std::cout << "Ten san pham: ";
    std::cin.ignore();  // Clear the newline from the buffer
    std::string product_name;
    std::getline(std::cin, product_name);

    std::cout << "Don gia cua san pham: ";
    double price;
    std::cin >> price;

    if (price >= 15000 && price <= 100000) {
        it->set_product_details(id, product_name, price);
        save_product_data();  // Save the product data after updating
        std::cout << "San pham da duoc cap nhat thanh cong.\n";
    } else {
        std::cout << "Vui long nhap lai, muc gia cho phep cua san pham la [15000,100000]!\n";
    }
}

void ProductManagementProgram::delete_product() {
    int id;
    std::cout << "Nhap ID cua san pham ban muon xoa: ";
    std::cin >> id;

    auto it = std::find_if(products.begin(), products.end(), [id](const Product& product) {
        return product.get_ID() == id;
    });

    if (it != products.end()) {
        std::cout << "San pham khong ton tai:\n";
        it->display();
    if (id <= 0) {
        std::cout << "ID khong hop le, xoa san pham khong thanh cong.\n";
        return;
    }
        std::cout << "Ban co chac chan muon xoa san pham nay khong? (y/n): ";
        char choice;
        std::cin >> choice;

        if (tolower(choice) == 'y') {
            products.erase(it);
            save_product_data();  // Save the product data after deletion
            std::cout << "Da xoa san pham thanh cong.\n";
        } else {
            std::cout << "Da huy viec xoa san pham.\n";
        }
    } else {
        std::cout << "San pham voi ID " << id << " khong ton tai.\n";
    }
}

void ProductManagementProgram::processCashPayment() {
    std::map<int, int> orderedProductQuantities;

    char addMoreProducts = 'y';
    while (addMoreProducts == 'y' || addMoreProducts == 'Y') {
        int productId, quantity;

        // Prompt for product ID and quantity
        std::cout << "Nhap ID cua san pham: ";
        std::cin >> productId;
     
        
        // Check if the product ID exists
        auto it = std::find_if(products.begin(), products.end(), [productId](const Product& product) {
            return product.get_ID() == productId;
        });
        if (it == products.end()) {
            // Product ID doesn't exist, prompt to retry or exit
            std::cout << "San pham voi ID " << productId << " khong ton tai. Thu lai (y/n) hoac Thoat (e/E): ";
            std::cin >> addMoreProducts;

            // Check if the staff wants to exit
            if (addMoreProducts == 'e' || addMoreProducts == 'E') {
                std::cout << "Dang tro lai man hinh chinh.\n";
                return;
            }

            continue;
        }

        std::cout << "Nhap so luong san pham khach mua: ";
        std::cin >> quantity;
        orderedProductQuantities[productId] = quantity;

        std::cout << "Ban co muon them san pham nao nua khong? (y/n) hoac Thoat (e/E): ";
        std::cin >> addMoreProducts;

        // Check if the staff wants to exit
        if (addMoreProducts == 'e' || addMoreProducts == 'E') {
            std::cout << "Dang tro lai man hinh chinh.\n";
            return;
        }
    }
    std::cout << "Tong tien: $" << calculateTotalPrice(orderedProductQuantities, products) << std::endl;
    double amountPaid;//
    std::cout << "Nhap so tien khach hang tra: $";
    std::cin >> amountPaid;

    // Display the receipt
    CashPayment cashPayment(amountPaid, orderedProductQuantities);
    cashPayment.displayReceipt();
}
double ProductManagementProgram::calculateTotalPrice(const std::map<int, int>& orderedProductQuantities, const std::vector<Product>& products) {
    double totalAmount = 0.0;

    for (const auto& entry : orderedProductQuantities) {
        int productId = entry.first;
        int quantity = entry.second;

        auto it = std::find_if(products.begin(), products.end(), [productId](const Product& product) {
            return product.get_ID() == productId;
        });

        if (it != products.end()) {
            double productTotal = it->get_price() * quantity;
            totalAmount += productTotal;
        }
    }//

    return totalAmount;
}

void ProductManagementProgram::processBankPayment() {
    std::map<int, int> orderedProductQuantities;

    char addMoreProducts = 'y';
    while (addMoreProducts == 'y' || addMoreProducts == 'Y') {
        int productId, quantity;

        // Prompt for product ID and quantity
        std::cout << "Nhap ID san pham: ";
        std::cin >> productId;

        // Check if the product ID exists
        auto it = std::find_if(products.begin(), products.end(), [productId](const Product& product) {
            return product.get_ID() == productId;
        });

        if (it == products.end()) {
            // Product ID doesn't exist, prompt to retry or exit
            std::cout << "San pham voi ID " << productId << " khong ton tai. Thu lai (y/n) hoac Thoat (e/E): ";
            std::cin >> addMoreProducts;

            // Check if the staff wants to exit
            if (addMoreProducts == 'e' || addMoreProducts == 'E') {
                std::cout << "Dang tro lai man hinh chinh.\n";
                return;
            }

            continue;
        }

        std::cout << "Nhap so luong san pham khach mua: ";
        std::cin >> quantity;
        orderedProductQuantities[productId] = quantity;

        std::cout << "Ban co muon them san pham nao nua khong? (y/n) hoac Thoat (e/E): ";
        std::cin >> addMoreProducts;

        // Check if the staff wants to exit
        if (addMoreProducts == 'e' || addMoreProducts == 'E') {
            std::cout << "Dang tro lai man hinh chinh.\n";
            return;
        }
    }
    double amountPaid = calculateTotalPrice(orderedProductQuantities, products);
    std::cout << "\nThong tin ngan hang cua cua hang:\n";
    std::cout << "Ten ngan hang: Vietcombank\n";
    std::cout << "So tai khoan: 101699996\n";
    std::cout << "Ten chu ngan hang: Do The Anh\n";
    std::cout << "Tong so tien can thanh toan: $" << calculateTotalPrice(orderedProductQuantities, products) << std::endl;
    
    // Display the receipt
    BankPayment bankPayment(amountPaid, orderedProductQuantities);
    bankPayment.displayReceipt();
}