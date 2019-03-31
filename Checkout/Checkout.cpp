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
	// Check if item exists in the ItemDirectory
	if (iter != itemDirectory.end()) {
		if (iter->second.isOnSale && iter->second.numPurchasedOnSale < iter->second.saleLimit) {
			price = iter->second.salePrice;
			iter->second.numPurchasedOnSale++;
			if (iter->second.saleType == BOGO) {
				price = BOGOSale(iter->second);
			}
			// Calculate price if it is by weight
			if (weight > 0) {
				return price * weight;
			}
			else {
				return price;
			}
		}
		else {
			if (weight > 0) {
				return iter->second.price * weight;
			}
			else {
				return iter->second.price;
			}
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

double Checkout::BOGOSale(Item item) {
	if (item.numPurchasedOnSale % 2) {
		return item.price;
	}
	else {
		return 0.0;
	}
}

void Checkout::AddItem(string item, double price, double salePrice, int saleLimit, bool onSale, SaleType saleType) {
	Item newItem;
	newItem.name = item;
	newItem.price = price;
	newItem.salePrice = salePrice;
	newItem.saleLimit = saleLimit;
	newItem.isOnSale = onSale;
	newItem.saleType = saleType;
	itemDirectory.insert(pair<string, Item>(item, newItem));
}

void Checkout::AddItem(Item newItem) {
	// Ensure numPurchased is set to zero when added
	newItem.numPurchasedOnSale = 0;
	itemDirectory.insert(pair<string, Item>(newItem.name, newItem));
}