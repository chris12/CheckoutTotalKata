#include "Checkout.h"

double Checkout::GetPriceOfItem(string item) {
	if (item == "soup") {
		return 1.89;
	} 
	else if (item == "Ground Beef") {
		return 5.99;
	} 
	else if (item == "Bananas") {
		return 2.38;
	}
}