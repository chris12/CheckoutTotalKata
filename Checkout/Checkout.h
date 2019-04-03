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
	string name;
	double price;
	double salePrice;
	int saleLimit;
	int numPurchased;
	double lbsPurchased;
	bool isOnSale;
	SaleType saleType;
	int buyXItems;
	double buyXLbs;
	int getYFree;
	double forYprice;
	string saleItemBundled;
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
