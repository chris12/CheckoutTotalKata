#include "Checkout.h"
#include "gtest\gtest.h"

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
	EXPECT_DOUBLE_EQ(1.89, checkout.ScanItem("soup", 0.0));
}

TEST(CheckoutTest, WhenTwoPoundsOfGroundBeefIsScannedThePriceIsAddedToCheckoutTotalAndReturned) {
	Checkout checkout;
	EXPECT_DOUBLE_EQ(11.98, checkout.ScanItem("Ground Beef", 2.0));
}

TEST(CheckoutTest, WhenThreePoundsOfBananasIsScannedThePriceIsAddedToCheckoutTotalAndReturned) {
	Checkout checkout;
	EXPECT_DOUBLE_EQ(7.14, checkout.ScanItem("Bananas", 3.0));
}


