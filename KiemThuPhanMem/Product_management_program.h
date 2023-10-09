#ifndef PRODUCT_MANAGEMENT_PROGRAM_H
#define PRODUCT_MANAGEMENT_PROGRAM_H

#include "Product.h"
#include <vector>

class ProductManagementProgram {
private:
    std::string filename;
    std::vector<Product> products;

public:
    ProductManagementProgram();
    void read_product_data();
    void save_product_data();
    void display_main_menu();
    void show_all_products() const;
    void add_product();
    void update_product();
    void delete_product();
    bool fileExists(const std::string& filename);
};

#endif // PRODUCT_MANAGEMENT_PROGRAM_H
