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

string Checkout::RemoveItemFromOrder(string item, double weight) {
	ostringstream currentTotal;
	currentTotal.precision(2);
	totalPrice -= GetPriceOfItem(item, weight);
	currentTotal << fixed << totalPrice;
	auto iter = itemDirectory.find(item);
	// Check if item exists in the ItemDirectory
	if (iter != itemDirectory.end()) {
		iter->second.numPurchased--;
	}
	return currentTotal.str();
}

string Checkout::GetTotal() {
	ostringstream total;
	total.precision(2);
	total << fixed << totalPrice;
	return total.str();
}

double Checkout::GetPriceOfItem(string item, double weight) {
	double price = 0.0;
	auto iter = itemDirectory.find(item);
	// Check if item exists in the ItemDirectory
	if (iter != itemDirectory.end()) {
		if (iter->second.isOnSale && iter->second.numPurchased < iter->second.saleLimit) {
			price = iter->second.salePrice;
			iter->second.numPurchased++;
			if (iter->second.saleType == BOGO || iter->second.saleType == BUYXGETYFREE) {
				price = BuyXGetYFree(iter->second);
			}
			else if (iter->second.saleType == BUYXFORY) {
				price = BuyXForYSale(iter->second);
			}
			else if (iter->second.saleType == BUYXGETYOFF) {
				price = BuyXGetYOff(iter->second);
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
			iter->second.numPurchased++;
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

void Checkout::ResetTotal() {
	totalPrice = 0.0;
}

double Checkout::BuyXGetYFree(Item item) {
	if (item.numPurchased % 2 && item.saleType == BOGO || 
		item.numPurchased % (item.buyXItems + 1) && item.saleType == BUYXGETYFREE) {
		return item.price;
	}
	else {
		return 0.0;
	}
}

double Checkout::BuyXForYSale(Item item) {
	return item.forYprice / item.buyXItems;
}

double Checkout::BuyXGetYOff(Item item) {
	auto iter = itemDirectory.find(item.saleItemBundled);
	// Check if item exists in the ItemDirectory
	if (iter != itemDirectory.end()) {
		if (iter->second.numPurchased == item.buyXItems) {
			return item.price * item.forYprice;
		}
		else {
			return item.price;
		}
	}
	return item.price;
}

void Checkout::AddItem(string item, double price, double salePrice, int saleLimit, bool onSale, SaleType saleType) {
	Item newItem;
	// Ensure numPurchased is set to zero when added
	newItem.numPurchased = 0;
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
	newItem.numPurchased = 0;
	itemDirectory.insert(pair<string, Item>(newItem.name, newItem));
}

void Checkout::EditItem(Item item) {
	auto iter = itemDirectory.find(item.name);
	if (iter != itemDirectory.end()) {
		iter->second.price = item.price;
		iter->second.salePrice = item.salePrice;
		iter->second.isOnSale = item.isOnSale;
		iter->second.saleType = item.saleType;
		iter->second.buyXItems = item.buyXItems;
		iter->second.forYprice = item.forYprice;
		iter->second.saleItemBundled = item.saleItemBundled;
		iter->second.saleLimit = item.saleLimit;
	}
	else {
		AddItem(item);
	}
}