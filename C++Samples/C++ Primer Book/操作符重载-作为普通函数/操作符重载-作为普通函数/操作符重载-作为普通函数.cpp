#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;
class Money                                 //以美国货币计的Money类
{
public: 
	Money();
	Money(double amount);
	Money(int theDollars);
	Money(int theDollars, int theCents);
	double getAmount() const;
	int getDollars() const;
	int getCents() const;
	void input();                           //同时读入美元符号和数字
	void output() const;
private:
	int dollars;                           //负数表示"美元"、"美分"部分均为负，
	int cents;                             //负的$4.50表示-4和-50。
	int dollarsPart(double amount) const;
	int centsPart(double amount) const;
	int round(double number) const;
};
const Money operator +(const Money& amount1, const Money& amount2);
const Money operator -(const Money& amount1, const Money& amount2);
bool operator ==(const Money& amount1, const Money& amount2);
const Money operator -(const Money& amount);
int main()
{
	Money yourAmount, myAmount(10, 9);
	cout << "Enter an amount of money: ";
	yourAmount.input();
	cout << "Your amount is ";
	yourAmount.output();
	cout << endl;
	cout << "My amount is ";
	myAmount.output();
	cout << endl;
	if (yourAmount == myAmount)
		cout << "We have the same amounts.\n";
	else
		cout << "One of us is richer.\n";
	Money ourAmount = yourAmount + myAmount;
	yourAmount.output(); cout << " + "; myAmount.output();
	cout << " equals "; ourAmount.output(); cout << endl;
	Money diffAmount = yourAmount - myAmount;
	yourAmount.output(); cout << " - "; myAmount.output();
	cout << " equals "; diffAmount.output(); cout << endl;
	return 0;
}
const Money operator +(const Money& amount1, const Money& amount2)
{
	int allcents1 = amount1.getCents() + amount1.getDollars() * 100;
	int allcents2 = amount2.getCents() + amount2.getDollars() * 100;
	int sumAllCents = allcents1 + allcents2;
	int absAllcents = abs(sumAllCents);
	int finalDollars = absAllcents / 100;
	int finalCents = absAllcents % 100;
	if (sumAllCents < 0)
	{
		finalDollars = -finalDollars;
		finalCents = -finalCents;
	}
	return Money(finalDollars, finalCents);                         //构造函数可以返回对象
}
const Money operator -(const Money& amount1, const Money& amount2)
{
	int allcents1 = amount1.getCents() + amount1.getDollars() * 100;
	int allcents2 = amount2.getCents() + amount2.getDollars() * 100;
	int diffAllCents = allcents1 - allcents2;
	int absAllcents = abs(diffAllCents);
	int finalDollars = absAllcents / 100;
	int finalCents = absAllcents % 100;
	if (diffAllCents < 0)
	{
		finalDollars = -finalDollars;
		finalCents = -finalCents;
	}
	return Money(finalDollars, finalCents);
}
bool operator ==(const Money& amount1, const Money& amount2)
{
	return ((amount1.getDollars() == amount2.getDollars()) && (amount1.getCents() == amount2.getCents()));
}
const Money operator -(const Money& amount)
{
	return Money(-amount.getDollars(), -amount.getCents());
}
Money::Money() :dollars(0), cents(0)
{/*函数体有意为空*/
}
Money::Money(double amount) : dollars(dollarsPart(amount)), cents(centsPart(amount))
{/*函数体有意为空*/
}
Money::Money(int theDollars) : dollars(theDollars), cents(0)
{/*函数体有意为空*/
}
Money::Money(int theDollars, int theCents)
{
	if ((theDollars < 0 && theCents > 0) || (theDollars > 0 && theCents < 0))
	{
		cout << "Inconsistent money date.\n";
		exit(1);
	}
	dollars = theDollars;
	cents = theCents;
}
double Money::getAmount() const
{
	return (dollars + cents*0.01);
}
int Money::getDollars() const
{
	return dollars;
}
int Money::getCents() const
{
	return cents;
}
void Money::output() const
{
	int absDollars = abs(dollars);
	int absCents = abs(cents);
	if (dollars < 0 || cents < 0)
		cout << "$-";
	else
		cout << "$";
	cout << absDollars;
	if (absCents >= 10)
		cout << "." << absCents;
	else
		cout << "." << "0" << absCents;
}
void Money::input()
{
	char dollarSign;
	cin >> dollarSign;
	if (dollarSign != '$')
	{
		cout << "No dollar sign in money input.\n";
		exit(1);
	}
	double amountAsDouble;
	cin >> amountAsDouble;
	dollars = dollarsPart(amountAsDouble);
	cents = centsPart(amountAsDouble);
}
int Money::dollarsPart(double amount) const
{
	return static_cast<int>(amount);
}
int Money::centsPart(double amount) const
{
	double doubleCents = amount * 100;
	int intCents = (round(fabs(doubleCents))) % 100;
	if (amount < 0)
		intCents = -intCents;
	return intCents;
}
int Money::round(double number) const
{
	return static_cast<int>(floor(number + 0.5));
}