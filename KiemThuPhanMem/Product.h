#pragma once
#include <iostream>
#include <string>
using namespace std;
class Product
{
private:
	string ID;
	string product_name;
	double price;
public:
	Product();
	Product(string ID, string product_name, double price);
	void set_ID(string ID);
	void set_product_name(string product_name);
	void set_price(double price);
	string get_ID();
	string get_product_name();
	double get_price();
	void display();
};

