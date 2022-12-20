//不能将插入操作符"<<"和提取操作符">>"作为成员函数重载。
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
	friend const Money operator +(const Money& amount1, const Money& amount2); //友元函数、、、、
	friend const Money operator -(const Money& amount1, const Money& amount2);
	friend bool operator ==(const Money& amount1, const Money& amount2);
	friend const Money operator -(const Money& amount);                       //调用对象就是第一个操作数
	friend ostream& operator << (ostream& outputStream, const Money& amount);  //重载"<<"
	friend istream& operator >> (istream& inputStream, Money& amount);        //重载">>" 
private:
	int dollars;                           //负数表示"美元"、"美分"部分均为负，
	int cents;                             //负的$4.50表示-4和-50。
	int dollarsPart(double amount) const;
	int centsPart(double amount) const;
	int round(double number) const;
};
int main()
{
	Money yourAmount, myAmount(10, 9);
	cout << "Enter an amount of money: ";
	cin >> yourAmount;
	cout << "Your amount is " << yourAmount << endl;
	cout << "My amount is " << myAmount << endl;
	if (yourAmount == myAmount)
		cout << "We have the same amounts.\n";
	else
		cout << "One of us is richer.\n";
	Money ourAmount = yourAmount + myAmount;
	cout << yourAmount << " + " << myAmount
	     << " equals " << ourAmount << endl;
	Money diffAmount = yourAmount - myAmount;
	cout << yourAmount << " - " << myAmount
	     << " equals " << diffAmount << endl;
	return 0;
}
const Money operator +(const Money& amount1, const Money& amount2)
{
	int allcents1 = amount1.cents + amount1.dollars * 100;
	int allcents2 = amount2.cents + amount2.dollars * 100;
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
	int allcents1 = amount1.cents + amount1.dollars * 100;
	int allcents2 = amount2.cents + amount2.dollars * 100;
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
	return ((amount1.dollars == amount2.dollars) && (amount1.cents == amount2.cents));
}
const Money operator -(const Money& amount)
{
	return Money(-amount.dollars, -amount.cents);
}
ostream& operator << (ostream& outputStream, const Money& amount)
{															//在main函数中，cout的值被传递给outputStream
	int absDollars = abs(amount.dollars);
	int absCents = abs(amount.cents);
	if (amount.dollars < 0 || amount.cents < 0)
		outputStream << "$-";
	else
		outputStream << "$";
	outputStream << absDollars;
	if (absCents >= 10)
		outputStream << '.' << absCents;
	else
		outputStream << '.' << '0' << absCents;
	return outputStream;									//返回一个引用
}
istream& operator >> (istream& inputStream, Money& amount)
{                                                          //在main函数中，cin的值被传递给inputStream
	char dollarSign;
	inputStream >> dollarSign;
	if (dollarSign != '$')
	{
		cout << "No dollar sign in money input.\n";
		exit(1);
	}
	double amountAsDouble;
	inputStream >> amountAsDouble;                          //非成员操作符，
	amount.dollars = amount.dollarsPart(amountAsDouble);    //使用Money类的成员函数时必须指定调用对象。
	amount.cents = amount.centsPart(amountAsDouble);
	return inputStream;                                     //返回一个引用
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