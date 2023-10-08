#include <iostream>
#include <vector>
#include "Product.h"
int main() {
	vector<Product> products;
	string Pro_name;
	double price;
	string id;
	int input_sp;
	for (int i = 0; i <= input_sp; i++) {
		cout << "Product 1: " << endl;
		cout << "Enter product name: ";
		cin >> Pro_name;
		cout << "Enter product price: ";
		cin >> price;
		id = "000" + i;
		Product product(id, Pro_name, price);
		products.push_back(product);
	}
	for (int i = 0; i <= input_sp; i++)
	{
		products.at(i).display();
	}
	return 0;
}
