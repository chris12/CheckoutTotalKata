# CheckoutTotalKata
Checkout Order Total Kata for Pillar Technology

Code is written in C++ using Visual Studio 2017 Community Edition. The googletest framework has been choosen to write my tests.

Checkout.exe can be run from the command line or double clicked and the results of the tests will be displayed.

Checkout - This directory contains source code for Checkout Order Total and all of the tests.

Checkout contains Items which are placed into an ItemDirectory to track all items available for purchase.

The interface for Items is as follows:

typedef struct {
*	string name;            // Name of the item
*	double price;           // Regular price of the item
*	double salePrice;       // Sale price of the item
*	int saleLimit;          // Sales limits for eaches and weighted items (rounded to full pound).
*	int numPurchased;       // Number of eaches item purchased
*	double lbsPurchased;    // Pounds of a weight item purchased
*	bool isOnSale;          // True if item is on sale
*	SaleType saleType;      // Type of sale see enumeration for options
*	int buyXItems;          // Buy X quantity of item to qualify for discount
*	double buyXLbs;         // Buy X pounds of item to qualify for discount
*	int getYFree;           // Get Y quantity free when buyXItems requirement is met
*	double forYprice;       // Used for Buy X Get Y off (percent 0-1, 0.5 == 50% discount) or Buy X for $Y
*	string saleItemBundled;	// Used for Buy Item X Get Item Y on sale (Y = saleItemBundled)

} Item;

typedef enum {
*   NONE,
*   BOGO,              // Buy one Get One Free
*   BUYXGETYFREE,      // Used for Buy X Get Y Free specials
*   DISCOUNT,          // Save $X per item purchased
*   BUYXGETYOFF,       // Buy X for item N Get $Y or Y% off Item M
*   BUYXFORY,          // Buy X of item N for $Y

} SaleType;

Adding an item to the directory is as simple as creating a new item and calling AddItem and passing the newly created item in.

Items can be scanned by calling ScanItem and providing the name of the item and if applicable the weight being scanned. ScanItem returns the running total of all items purchased. 
 
googletest-master - This directory contains source code for googletest framework.
