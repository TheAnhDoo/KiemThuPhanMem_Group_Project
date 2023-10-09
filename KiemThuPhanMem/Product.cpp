// Product.cpp
#include "Product.h"
#include <iostream>

Product::Product() : ID(0), product_name(""), price(0.0) {}

Product::Product(int ID, const std::string& product_name, double price) : ID(ID), product_name(product_name), price(price) {}

void Product::set_ID(int ID) {
    this->ID = ID;
}

void Product::set_product_name(const std::string& product_name) {
    this->product_name = product_name;
}

void Product::set_price(double price) {
    this->price = price;
}

int Product::get_ID() const {
    return this->ID;
}

std::string Product::get_product_name() const {
    return this->product_name;
}

double Product::get_price() const {
    return this->price;
}

void Product::display() const {
    std::cout << "ID: " << this->ID << std::endl;
    std::cout << "Name: " << this->product_name << std::endl;
    std::cout << "Price: " << this->price << std::endl;
}