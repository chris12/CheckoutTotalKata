#include "Checkout.h"
#include "gtest\gtest.h"

TEST(CheckoutTest, WhenSoupIsScannedPriceOfSoupIsAddedToTotal) {
	Checkout checkout;
	EXPECT_DOUBLE_EQ(1.89, checkout.GetPriceOfItem("soup"));
}