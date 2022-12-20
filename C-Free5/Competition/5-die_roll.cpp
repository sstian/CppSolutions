/*
	2018.05.12 20:23
	Die Roll  
*/
#include <iostream>

using namespace std;

const int POINT = 6;
int main()
{
	int y, w;
	int max;
	cout << "Input two integer numbers:" << endl;
	cin >> y >> w;
	
	max = y >= w ? y : w;
	switch(max)
	{
	case 1: cout << "1/1" << endl; break;
	case 2: cout << "5/6" << endl; break;
	case 3: cout << "2/3" << endl; break;
	case 4: cout << "1/2" << endl; break;
	case 5: cout << "1/3" << endl; break;
	case 6: cout << "1/6" << endl; break;
	default: break;
	} 
	return 0;
}
