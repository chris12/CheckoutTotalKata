#include "Checkout.h"
#include "gtest\gtest.h"

TEST(CheckoutTest, WhenGetPriceOfItemIsCalledForACanOfSoupItReturnsTheRegularPrice) {
	Checkout checkout;
	EXPECT_DOUBLE_EQ(1.89, checkout.GetPriceOfItem("soup"));
}

TEST(CheckoutTest, WhenGetPriceOfItemIsCalledForAPoundOfGroundBeefItReturnsTheRegularPrice) {
	Checkout checkout;
	EXPECT_DOUBLE_EQ(5.99, checkout.GetPriceOfItem("Ground Beef"));
}

