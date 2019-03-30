#pragma once
#include <sstream>
#include <string>
using namespace std;

class Checkout{
public:
	Checkout();
	string ScanItem(string item, double weight = 0.0);
	string RemoveItem(string item, double weight = 0.0);
	double GetPriceOfItem(string item, double weight = 0.0);
protected:
private:
	double totalPrice;
};
