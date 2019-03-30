#pragma once
#include <string>
using namespace std;

class Checkout{
public:
	double GetPriceOfItem(string item);
protected:
private:
	double totalPrice = 0.0;
};
