#pragma once
#include <sstream>
#include <string>
#include <map>
using namespace std;

typedef enum {
	NONE,
	BOGO,				// BuyOneGetOne
	DISCOUNT,			// Discount
	BUYXGETYOFF,		// Buy X items get Y at % off
	BUYXFORY,			// Buy X Items for $Y
} SaleType;	

typedef struct {
	string name;
	double price;
	double salePrice;
	int saleLimit;
	int numPurchasedOnSale;
	bool isOnSale;
	SaleType saleType;
} Item;

class Checkout {
public:
	Checkout();
	string ScanItem(string item, double weight = 0.0);
	string RemoveItem(string item, double weight = 0.0);
	double GetPriceOfItem(string item, double weight = 0.0);
	double BOGOSale(Item item);
	void AddItem(string name, double price, double salePrice, int saleLimit, bool onSale, SaleType saleType = NONE);
	void AddItem(Item newItem);
protected:
private:
	double totalPrice;
	map<string, Item> itemDirectory;
};
