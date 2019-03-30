#include "Checkout.h"

//Constructor
Checkout::Checkout() {
	totalPrice = 0.0;
}

double Checkout::ScanItem(string item, double weight) {
	return totalPrice += GetPriceOfItem(item, weight);
}

double Checkout::GetPriceOfItem(string item, double weight) {
	double price = 0.0;
	if (item == "soup") {
		return 1.89;
	} 
	else if (item == "Ground Beef") {
		price = weight * 5.99;
		return price;
	} 
	else if (item == "Bananas") {
		price = weight * 2.38;
		return price;
	}
	return 0.0;
}