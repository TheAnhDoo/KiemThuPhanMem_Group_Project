#include "Product.h"
Product::Product() : ID(""), product_name(""), price(0.0){}
Product::Product(string ID, string product_name, double price) : ID(ID), product_name(product_name), price(price) {}
void Product::set_ID(string ID) {
	this->ID = ID;
}
void Product::set_product_name(string product_name) {
	this->product_name = product_name;
}
void Product::set_price(double price) {
	this->price = price;
}
string Product::get_ID() {
	return this->ID;
}
string Product::get_product_name() {
	return this->product_name;
}
double Product::get_price() {
	return this->price;
}
void Product::display() {
	cout << "ID: " << this->ID << endl;
	cout << "Name: " << this->product_name << endl;
	cout << "Price: " << this->price << endl;
}