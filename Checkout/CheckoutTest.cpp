#include "Checkout.h"
#include "gtest\gtest.h"

void SetUpTestCase() {
	Checkout checkout;
}

TEST(CheckoutTest, WhenGetPriceOfItemIsCalledForACanOfSoupItReturnsTheRegularPrice) {
	Checkout checkout;
	EXPECT_DOUBLE_EQ(1.89, checkout.GetPriceOfItem("soup"));
}

TEST(CheckoutTest, WhenGetPriceOfItemIsCalledForAPoundOfGroundBeefItReturnsTheRegularPrice) {
	Checkout checkout;
	EXPECT_DOUBLE_EQ(5.99, checkout.GetPriceOfItem("Ground Beef", 1.0));
}

TEST(CheckoutTest, WhenGetPriceOfItemIsCalledForAPoundOfBananasItReturnsTheRegularPrice) {
	Checkout checkout;
	EXPECT_DOUBLE_EQ(2.38, checkout.GetPriceOfItem("Bananas", 1.0));
}

TEST(CheckoutTest, WhenSoupIsScannedThePriceIsAddedToCheckoutTotalAndReturned) {
	Checkout checkout;
	EXPECT_EQ("1.89", checkout.ScanItem("soup", 0.0));
}

TEST(CheckoutTest, WhenTwoPoundsOfGroundBeefIsScannedThePriceIsAddedToCheckoutTotalAndReturned) {
	Checkout checkout;
	EXPECT_EQ("11.98", checkout.ScanItem("Ground Beef", 2.0));
}

TEST(CheckoutTest, WhenThreePoundsOfBananasIsScannedThePriceIsAddedToCheckoutTotalAndReturned) {
	Checkout checkout;
	EXPECT_EQ("7.14", checkout.ScanItem("Bananas", 3.0));
}

TEST(CheckoutTest, WhenSoupTwoptTwoPoundsGroundBeefAndOnePtSevenPoundsOfBannanasArePurchasedCorrectTotalIsReturned) {
	Checkout checkout;
	EXPECT_EQ("1.89", checkout.ScanItem("soup"));
	EXPECT_EQ("15.07", checkout.ScanItem("Ground Beef", 2.2));
	EXPECT_EQ("19.11", checkout.ScanItem("Bananas", 1.7));
}

TEST(CheckoutTest, WhenItemIsRemovedAfterScanningTheTotalPriceIsReturnedWithTheRemovedItemTotalSubtracted) {
	Checkout checkout;
	EXPECT_EQ("11.98", checkout.ScanItem("Ground Beef", 2.0));
	EXPECT_EQ("13.87", checkout.ScanItem("soup"));
	EXPECT_EQ("11.98", checkout.RemoveItem("soup"));
}

TEST(CheckoutTest, WhenUserCreatesAnItemThePriceIsReturnedCorrectly) {
	Checkout checkout;
	checkout.AddItem("soup", 1.77, 1.59, 4, false);
	EXPECT_DOUBLE_EQ(1.77, checkout.GetPriceOfItem("soup"));
}

TEST(CheckoutTest, WhenNewItemIsAddedToCheckoutsItemDirectoryAndThenScannedTheCorrectTotalIsReturned) {
	Checkout checkout;
	checkout.AddItem("Chicken Breast", 1.99, 1.49, 4, true);
	EXPECT_EQ("2.98", checkout.ScanItem("Chicken Breast", 2.0));
}

TEST(CheckoutTest, WhenItemIsOnSaleTheSaleLimitIsCorrectlyFollowed) {
	Checkout checkout;
	checkout.AddItem("soup", 1.89, 0.99, 3, true);
	checkout.AddItem("Ground Beef", 5.99, 4.50, 2, true);
	EXPECT_EQ("0.99", checkout.ScanItem("soup"));
	EXPECT_EQ("1.98", checkout.ScanItem("soup"));
	EXPECT_EQ("2.97", checkout.ScanItem("soup"));
	EXPECT_EQ("4.86", checkout.ScanItem("soup"));
	EXPECT_EQ("9.36", checkout.ScanItem("Ground Beef", 1.0));
	EXPECT_EQ("16.11", checkout.ScanItem("Ground Beef", 1.5));
	EXPECT_EQ("28.09", checkout.ScanItem("Ground Beef", 2.0));
}

TEST(CheckoutTest, WhenItemIsBuyOneGetOneFreeTheTotalPriceWillBeThePriceOfOneItem) {
	Checkout checkout;
	Item juice;
	juice.name = "Juice";
	juice.isOnSale = true;
	juice.price = 1.99;
	juice.saleLimit = 6;
	juice.saleType = BOGO;
	checkout.AddItem(juice);
	EXPECT_EQ("1.99", checkout.ScanItem("Juice"));
	EXPECT_EQ("1.99", checkout.ScanItem("Juice"));
}

TEST(CheckoutTest, WhenItemIsBuyOneGetOneFreeWithALimitOfFourTheSixthItemWillNotBeFree) {
	Checkout checkout;
	Item juice;
	juice.name = "Juice";
	juice.isOnSale = true;
	juice.price = 1.99;
	juice.saleLimit = 4;
	juice.saleType = BOGO;
	checkout.AddItem(juice);
	EXPECT_EQ("1.99", checkout.ScanItem("Juice"));
	EXPECT_EQ("1.99", checkout.ScanItem("Juice"));
	EXPECT_EQ("3.98", checkout.ScanItem("Juice"));
	EXPECT_EQ("3.98", checkout.ScanItem("Juice"));
	EXPECT_EQ("5.97", checkout.ScanItem("Juice"));
	EXPECT_EQ("7.96", checkout.ScanItem("Juice"));
}

TEST(CheckoutTest, WhenSoupIsBuyThreeForFiveWithALimitOfThreeTheCorrectTotalIsReturnedForThreeAndSixCansOfSoup) {
	Checkout checkout;
	Item soup;
	soup.name = "soup";
	soup.isOnSale = true;
	soup.price = 1.89;
	soup.saleLimit = 3;
	soup.saleType = BUYXFORY;
	soup.buyXItems = 3;
	soup.forYprice = 5.00;
	checkout.AddItem(soup);
	EXPECT_EQ("1.67", checkout.ScanItem("soup"));
	EXPECT_EQ("3.33", checkout.ScanItem("soup"));
	EXPECT_EQ("5.00", checkout.ScanItem("soup"));
	EXPECT_EQ("6.89", checkout.ScanItem("soup"));
	EXPECT_EQ("8.78", checkout.ScanItem("soup"));
	EXPECT_EQ("10.67", checkout.ScanItem("soup"));
}

TEST(CheckoutTest, WhenThreeCansOfSoupAreBoughtGetJuiceAtFiftyPercentOff) {
	Checkout checkout;
	Item soup, juice;
	soup.name = "soup";
	soup.isOnSale = false;
	soup.price = 1.89;
	soup.saleLimit = 3;
	soup.buyXItems = 3;
	juice.name = "juice";
	juice.isOnSale = true;
	juice.saleType = BUYXGETYOFF;
	juice.saleItemBundled = "soup";
	juice.buyXItems = 3;
	juice.forYprice = .5;
	juice.price = 1.99;
	juice.saleLimit = 2;

	checkout.AddItem(soup);
	checkout.AddItem(juice);
	EXPECT_EQ("1.89", checkout.ScanItem("soup"));
	EXPECT_EQ("3.78", checkout.ScanItem("soup"));
	EXPECT_EQ("5.67", checkout.ScanItem("soup"));
	EXPECT_EQ("6.67", checkout.ScanItem("juice"));
	EXPECT_EQ("7.66", checkout.ScanItem("juice"));
	EXPECT_EQ("9.65", checkout.ScanItem("juice"));
}

TEST(CheckoutTest, WhenResetTotalIsCalledThePriceIsCorrectlyResetToZero) {
	Checkout checkout;
	Item soup, juice;
	soup.name = "soup";
	soup.price = 1.00;
	soup.isOnSale = false;
	juice.name = "juice";
	juice.price = 0.0;
	juice.isOnSale = false;
	checkout.AddItem(soup);
	checkout.AddItem(juice);
	EXPECT_EQ("0.00", checkout.ScanItem("juice"));
	EXPECT_EQ("1.00", checkout.ScanItem("soup"));
	EXPECT_EQ("1.00", checkout.ScanItem("juice"));
	checkout.ResetTotal();
	EXPECT_EQ("0.00", checkout.ScanItem("juice"));
}

TEST(CheckoutTest, WhenSaleEndsPriceRevertsBackToRegularPrice) {
	Checkout checkout;
	Item salsa;
	salsa.name = "salsa";
	salsa.price = 2.00;
	salsa.isOnSale = true;
	salsa.salePrice = 1.00;
	salsa.saleType = DISCOUNT;
	salsa.saleLimit = 5;
	checkout.AddItem(salsa);
	EXPECT_EQ("1.00", checkout.ScanItem(salsa.name));
	salsa.isOnSale = false;
	salsa.saleType = NONE;
	checkout.EditItem(salsa);
	EXPECT_EQ("3.00", checkout.ScanItem(salsa.name));
}
