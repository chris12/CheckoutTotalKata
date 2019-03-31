#pragma once
#include <sstream>
#include <string>
#include <map>
using namespace std;

class Checkout {
public:
	Checkout();
	string ScanItem(string item, double weight = 0.0);
	string RemoveItem(string item, double weight = 0.0);
	double GetPriceOfItem(string item, double weight = 0.0);
	void AddItem(string name, double price, double salePrice, int saleLimit, bool onSale);
protected:
private:
	typedef struct {
		string name;
		double price;
		double salePrice;
		int saleLimit;
		int numPurchasedOnSale;
		bool isOnSale;
	} Item;
	double totalPrice;
	map<string, Item> itemDirectory;
};
