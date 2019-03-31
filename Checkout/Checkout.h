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
	int numPurchased;
	bool isOnSale;
	SaleType saleType;
	int buyXItems;
	double forYprice;
	string saleItemBundled;
} Item;

class Checkout {
public:
	Checkout();
	string ScanItem(string item, double weight = 0.0);
	string RemoveItem(string item, double weight = 0.0);
	double GetPriceOfItem(string item, double weight = 0.0);
	void AddItem(string name, double price, double salePrice, int saleLimit, bool onSale, SaleType saleType = NONE);
	void AddItem(Item newItem);
protected:
private:
	double BOGOSale(Item item);
	double BuyXForYSale(Item item);
	double BuyXGetYOff(Item item);
	double totalPrice;
	map<string, Item> itemDirectory;
};
