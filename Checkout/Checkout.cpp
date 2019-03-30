#include "Checkout.h"

//Constructor
Checkout::Checkout() {
	totalPrice = 0.0;
}

string Checkout::ScanItem(string item, double weight) {
	ostringstream currentTotal;
	currentTotal.precision(2);
	totalPrice += GetPriceOfItem(item, weight);
	currentTotal << fixed << totalPrice;
	return currentTotal.str();
}

string Checkout::RemoveItem(string item, double weight) {
	ostringstream currentTotal;
	currentTotal.precision(2);
	totalPrice -= GetPriceOfItem(item, weight);
	currentTotal << fixed << totalPrice;
	return currentTotal.str();
}

double Checkout::GetPriceOfItem(string item, double weight) {
	double price = 0.0;
	auto iter = itemDirectory.find(item);
	if (iter != itemDirectory.end()) {
		if (!iter->second.isOnSale) {
			return iter->second.price;
		}
		else {
			return iter->second.salePrice;
		}
	}
	else if (item == "soup") {
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

void Checkout::AddItem(string item, double price, double salePrice, int saleLimit, bool onSale) {
	Item newItem;
	newItem.name = item;
	newItem.price = price;
	newItem.salePrice = salePrice;
	newItem.saleLimit = saleLimit;
	newItem.isOnSale = onSale;
	itemDirectory.insert(pair<string, Item>(item, newItem));
}