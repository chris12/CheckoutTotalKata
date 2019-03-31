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