// Product.h
#ifndef PRODUCT_H
#define PRODUCT_H
#include <iostream>
#include <string>

class Product {
private:
    int ID;
    std::string product_name;
    double price;

public:
    Product();
    Product(int ID, const std::string& product_name, double price);
    void set_ID(int ID);
    void set_product_name(const std::string& product_name);
    void set_price(double price);
    void set_product_details(int ID, const std::string& product_name, double price);
    int get_ID() const;
    std::string get_product_name() const;
    double get_price() const;
    void display() const;
};

#endif // PRODUCT_H