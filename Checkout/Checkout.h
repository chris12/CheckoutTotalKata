#pragma once
#include <sstream>
#include <string>
#include <map>
using namespace std;

typedef enum {
	NONE,
	BOGO,				// BuyOneGetOne
	BUYXGETYFREE,		// Can be used for buy 2 get 1 free specials
	DISCOUNT,			// Discount
	BUYXGETYOFF,		// Buy X items get Y at % off
	BUYXFORY,			// Buy X Items for $Y
} SaleType;	

typedef struct {
	string name;			// Name of the item
	double price;			// Regular price of the item
	double salePrice;		// Sale price of the item
	int saleLimit;			// Sales limits for eaches and weighted items (rounded to full pound).
	int numPurchased;		// Number of eaches item purchased
	double lbsPurchased;    // Pounds of a weight item purchased
	bool isOnSale;			// True if item is on sale
	SaleType saleType;	    // Type of sale see enumeration for options
	int buyXItems;			// Buy X quantity of item to qualify for discount
	double buyXLbs;			// Buy X pounds of item to qualify for discount
	int getYFree;			// Get Y quantity free when buyXItems requirement is met
	double forYprice;		// Used for Buy X Get Y off (percent 0-1, 0.5 == 50% discount) or Buy X for $Y
	string saleItemBundled;	// Used for Buy Item X Get Item Y on sale (Y = saleItemBundled)
} Item;

class Checkout {
public:
	Checkout();
	string ScanItem(string item, double weight = 0.0);
	string GetTotal();
	string RemoveItemFromOrder(string item, double weight = 0.0);
	double GetPriceOfItem(string item, double weight = 0.0);
	void AddItem(string name, double price, double salePrice, int saleLimit, bool onSale, SaleType saleType = NONE);
	void AddItem(Item newItem);
	void EditItem(Item item);
	void ResetTotal();
protected:
private:
	double BuyXGetYFree(Item item);
	double BuyXForYSale(Item item);
	double BuyXGetYOff(Item item);
	double BuyXLbsGetYOff(Item item, double weight);
	double totalPrice;
	map<string, Item> itemDirectory;
};
