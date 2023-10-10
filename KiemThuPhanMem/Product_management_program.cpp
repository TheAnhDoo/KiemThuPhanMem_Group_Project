#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
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

//  void ProductManagementProgram::read_product_data() {
//      // Read product data from the file
//      std::ifstream file(filename);
//      if (!file.is_open()) {
//          std::cerr << "Error: Could not open data file.\n";
//          return;
//      }

//      std::string line;
//      while (std::getline(file, line)) {
//          std::istringstream ss(line);
//          std::string id, product_name, price_str;
//          std::getline(ss, id, ',');
//          std::getline(ss, product_name, ',');
//          std::getline(ss, price_str, ',');

//          // Convert string to appropriate types
//          int product_id = std::stoi(id);
//          double price = std::stod(price_str);

//          // Create a product and add it to the vector
//          Product product(product_id, product_name, price);
//          products.push_back(product);
//      }

//      file.close();
//  }
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



// void ProductManagementProgram::save_product_data() {
//     std::ofstream file(filename);
//     if (!file.is_open()) {
//         std::cerr << "Error: Could not open data file for writing.\n";
//         return;
//     }

//     // Write product data to the file
//     file << "ID,Product Name,Price\n";
//     for (const Product& product : products) {
//         file << product.get_ID() << "," << product.get_product_name() << "," << product.get_price() << "\n";
//     }

//     file.close();
// }
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
        std::cout << "\nMain Menu:\n";
        std::cout << "1. Show all products\n";
        std::cout << "2. Add a product\n";
        std::cout << "3. Update a product\n";
        std::cout << "4. Delete a product\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                system("cls");
                show_all_products();
                break;
            case 2:
                system("cls");
                add_product();
                break;
            case 3:
                system("cls");
                update_product();
                break;
            case 4:
                system("cls");
                delete_product();
                break;
            case 0:
                save_product_data();  // Save data before exiting
                std::cout << "Exiting the program.\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

void ProductManagementProgram::show_all_products() const {
    if (products.empty()) {
        std::cout << "No products available.\n";
        return;
    }

    std::cout << "All Products:\n";
    for (const Product& product : products) {
        product.display();
    }
}

// void ProductManagementProgram::add_product() {
//     Product product;

//     std::cout << "Enter product details:\n";
//     int id;
//     std::string product_name;
//     double price;

//     std::cout << "ID: ";
//     std::cin >> id;
//     product.set_ID(id);

//     std::cout << "Product Name: ";
//     std::cin.ignore();  // Clear the newline from the buffer
//     std::getline(std::cin, product_name);
//     product.set_product_name(product_name);

//     std::cout << "Price: ";
//     std::cin >> price;
//     if(price >= 15000 && price <= 100000){
//     product.set_price(price);

//     products.push_back(product);
//     save_product_data();  // Save the product data after adding a new product
//     std::cout << "Product added successfully.\n";
//     }
//     else {
//         std::cout << "Invaid price!";
//     }
// }

// void ProductManagementProgram::update_product() {
//     int id;
//     std::cout << "Enter the ID of the product you want to update: ";
//     std::cin >> id;

//     auto it = std::find_if(products.begin(), products.end(), [id](const Product& product) {
//         return product.get_ID() == id;
//     });

//     if (it != products.end()) {
//         std::cout << "Enter the updated details:\n";

//         std::cout << "Product Name: ";
//         std::cin.ignore();  // Clear the newline from the buffer
//         std::string product_name;
//         std::getline(std::cin, product_name);
//         it->set_product_name(product_name);

//         std::cout << "Price: ";
//         double price;
//         std::cin >> price;
//         if(price >= 15000 && price <= 100000){
//             it->set_price(price);
//             save_product_data();  // Save the product data after updating
//             std::cout << "Product updated successfully.\n";
//         }
//        else{
//         std::cout << "Invaid price!";
//        }
//     } else {
//         std::cout << "Product with ID " << id << " not found.\n";
//     }
// }
void ProductManagementProgram::add_product() {
    int id;
    std::cout << "Enter product details:\n";
    std::cout << "ID: ";
    std::cin >> id;

    // Check if a product with the given ID already exists
    auto it = std::find_if(products.begin(), products.end(), [id](const Product& product) {
        return product.get_ID() == id;
    });

    if (it != products.end()) {
        std::cout << "A product with ID " << id << " already exists. Failed to add a new product.\n";
        return;
    }

    std::string product_name;
    double price;

    std::cout << "Product Name: ";
    std::cin.ignore();  // Clear the newline from the buffer
    std::getline(std::cin, product_name);

    std::cout << "Price: ";
    std::cin >> price;

    if (price >= 15000 && price <= 100000) {
        Product product(id, product_name, price);
        products.push_back(product);
        save_product_data();  // Save the product data after adding a new product
        std::cout << "Product added successfully.\n";
    } else {
        std::cout << "Invalid price!\n";
    }
}

void ProductManagementProgram::update_product() {
    int id;
    std::cout << "Enter the ID of the product you want to update: ";
    std::cin >> id;

    // Check if a product with the given ID exists for updating
    auto it = std::find_if(products.begin(), products.end(), [id](const Product& product) {
        return product.get_ID() == id;
    });

    if (it == products.end()) {
        std::cout << "Product with ID " << id << " not found. Failed to update.\n";
        return;
    }

    std::cout << "Enter the updated details:\n";

    std::cout << "Product Name: ";
    std::cin.ignore();  // Clear the newline from the buffer
    std::string product_name;
    std::getline(std::cin, product_name);

    std::cout << "Price: ";
    double price;
    std::cin >> price;

    if (price >= 15000 && price <= 100000) {
        it->set_product_details(id, product_name, price);
        save_product_data();  // Save the product data after updating
        std::cout << "Product updated successfully.\n";
    } else {
        std::cout << "Invalid price!\n";
    }
}

void ProductManagementProgram::delete_product() {
    int id;
    std::cout << "Enter the ID of the product you want to delete: ";
    std::cin >> id;

    auto it = std::find_if(products.begin(), products.end(), [id](const Product& product) {
        return product.get_ID() == id;
    });

    if (it != products.end()) {
        std::cout << "Product found:\n";
        it->display();

        std::cout << "Are you sure you want to delete this product? (y/n): ";
        char choice;
        std::cin >> choice;

        if (tolower(choice) == 'y') {
            products.erase(it);
            save_product_data();  // Save the product data after deletion
            std::cout << "Product deleted successfully.\n";
        } else {
            std::cout << "Deletion canceled.\n";
        }
    } else {
        std::cout << "Product with ID " << id << " not found.\n";
    }
}
