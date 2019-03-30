#pragma once
#include <string>
using namespace std;

class Checkout{
public:
	Checkout();
	double ScanItem(string item, double weight = 0.0);
	double GetPriceOfItem(string item, double weight = 0.0);
protected:
private:
	double totalPrice;
};
