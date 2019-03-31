# CheckoutTotalKata
Checkout Order Total Kata for Pillar Technology

Code is written in C++ using Visual Studio 2017 Community Edition. The googletest framework has been choosen to write my tests.

Checkout - This directory contains source code for Checkout Order Total and all of the tests.

Checkout contains Items which are placed into an ItemDirectory to track all items available for purchase.

The interface for Items is as follows:

typedef struct {
   string name;             // Name of item 
   double price;            // Regular price of item
   int saleLimit;           // Limit on number of items that can be purchased on sale
   bool isOnSale;           // If true, designates item is on sale
   SaleType saleType;       // Used for more complex sales (bogo, buyXforY etc) See SaleType enum for more information
   int buyXItems;           // 
   double forYPrice;        // 
   string saleItemBundled;  // For Buy X Get Y Off, For item getting Y off set SaleItemBundled to Buy X item
} Item;

typedef enum {
   NONE,
   BOGO,              // Buy one Get One Free
   DISCOUNT,          // Save $X per item purchased
   BUYXGETYOFF,       // Buy X for item N Get Y off Item M
   BUYXFORY,          // Buy X of item N for $Y
} SaleType;

Adding an item to the directory is as simple as creating new item and calling AddItem and passing the newly created item in.

Items can be scanned by calling ScanItem and providing the name of the item and if applicable the weight being scanned. ScanItem returns the running total of all items purchased. 
 
googletest-master - This directory contains source code for googletest framework.
